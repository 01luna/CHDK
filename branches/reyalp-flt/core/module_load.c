/*
 *   CHDK-FLAT Module System.  
 *
 *   (c)2011 Sergey Taranenko aka @tsv 
 *
 *   This is main file of module processing system. Module load/unload/service functions
 */

#include "stdlib.h"
#include "console.h"
#include "gui.h"

#include "flt.h"
#include "module_load.h"
#include "module_exportlist.h"


//********************************************************/
//**    TEMPORARY FROM .H FILES   **
//********************************************************/

#include "module_exportlist.c"


#define MAX_NUM_LOADED_MODULES 10
#define BUFFER_FOR_READ_SIZE   4096

//********************************************************/
//**    Small library for safe io to cacheable memory   **
//**  use smaller buffer then fopen so bigger could     **
//**  be loaded										    **
//********************************************************/

static char* buf_load=0;

int b_read(int fd, char* buf, int len)
{
  if (buf_load==0) {
    buf_load = umalloc( BUFFER_FOR_READ_SIZE );
    if (buf_load==0)
       return 0;
  }
  int loaded=0, now=1;

  while (now && loaded<len)
  {
     now = len-loaded;
     if ( now > BUFFER_FOR_READ_SIZE )
       now = BUFFER_FOR_READ_SIZE;

     now = read(fd,buf_load,now);
     
     memcpy(buf+loaded, buf_load, now);
     loaded+=now;
  }
  return loaded;
}

void b_close(int fd)
{
  if (fd >=0 )
  close(fd);

  if (buf_load)
   ufree(buf_load);
  buf_load=0;
}



//********************************************************/
//**       Auxilary module system functions             **
//********************************************************/

// array of pointer to loaded modules (NULL - slot is empty)
static struct flat_hdr* modules[MAX_NUM_LOADED_MODULES];

// >0- if correspondend module require to unload it
static unsigned char module_unload_request[MAX_NUM_LOADED_MODULES]; 

// =1- if correspondend module ask to unload it on exit from main menu
static unsigned char module_flags[MAX_NUM_LOADED_MODULES]; 


//-----------------------------------------------
// Cut module name to 11 sym + make it uppercase
//-----------------------------------------------
static void flat_module_name_make( char* tgt, char* name )
{
	char *p=tgt;

	for (; *name; name++ ){
		if ( *name=='/') {
			p=tgt;
		} else if ( (p-tgt) < 11 ) {
			*p=*name; p++;
		}
    }
    *p=0;
}

//-----------------------------------------------
// Do path to module
//-----------------------------------------------
static void flat_module_path_make( char* tgt, char* name )
{
	// check is name absolute path
	if ( name[0]=='A' && name[1]=='/')
   		strcpy(tgt,name);
	else
   sprintf(tgt,"A/CHDK/MODULES/%s",name);
}

//-----------------------------------------------
// PURPOSE: Find idx_loaded by module name or by module idx
// RETURN: -1 if module not loaded yet, otherwise idx in modules[]
//-----------------------------------------------
int module_find(char * name )
{
   char namebuf[12];
   int i = (uint32_t)name;

   // Check if given parameter is idx
   if (i < MAX_NUM_LOADED_MODULES)
    return (modules[i] ? i : -1);

   flat_module_name_make(namebuf,name);

   for ( i=0; i<MAX_NUM_LOADED_MODULES; i++ ) 
   {
    if ( modules[i] &&  !strcmp(namebuf, modules[i]->modulename) ) {
        return i;
    }
   }
   return -1;
}


//-----------------------------------------------

typedef int (*module_action_t)( struct flat_hdr* flat, uint32_t* relocbuf );

static int module_do_relocations( struct flat_hdr* flat, uint32_t* relocbuf )
{
   int i;
   unsigned int offs;
   unsigned char* buf = (unsigned char*)flat;

   for ( i=0; i < flat->reloc_count; i++ )
   {
      offs = *relocbuf;
      relocbuf++;
	  //@tsv todo: if (offs>=flat->reloc_start) error_out_of_bound
      *(uint32_t*)(buf+offs) += (uint32_t)buf;
   }  
   return 1;
}

static int module_do_imports( struct flat_hdr* flat, uint32_t* relocbuf )
{
	int i;
	unsigned int offs;
	uint32_t* ptr;
	unsigned char* buf = (unsigned char*)flat;
   

	for ( i=0; i < flat->import_count; i++ )
	{
		ptr = (uint32_t*)(buf+*relocbuf);
	  //@tsv todo: if (*relocbuf>=flat->reloc_start) error_out_of_bound
		if ( *ptr<2 || *ptr>EXPORTLIST_LAST_IDX )
			return 0;

		*ptr = /*0xFFFFFFFE &*/ (uint32_t) CHDK_EXPORT_LIST[*ptr];
		relocbuf++;
	}  
    return 1;
}

// variables to quick error
static char* module_filename;
static int module_fd;
static char* flat_buf;
static char* reloc_buf;

//-----------------------------------------------
static int moduleload_error(char* text, int value)
{
  if ( module_fd >=0 )
    b_close( module_fd);

  if ( flat_buf )
      free(flat_buf);
  if ( reloc_buf )
      ufree(reloc_buf);   

  char fmt[50];
  strcpy(fmt,"Fail to load %s: ");
  strcpy(fmt+17,text);

  char buf[100];
  sprintf(buf, fmt, module_filename, value);

  console_clear();
  console_add_line(buf);

  return -1;
}


//-----------------------------------------------
// return: 0 if error, otherwise ok
static int module_do_action( char* actionname, uint32_t offset, uint32_t count, module_action_t func )
{
   if ( !count ) 
		return 1;

   int size_reloc = count * sizeof(uint32_t);
   reloc_buf = umalloc( size_reloc );
   if ( !reloc_buf )
       	return (int)moduleload_error("malloc",0);   

   if ( offset != lseek(module_fd, offset, SEEK_SET) )
       	return (int)moduleload_error("action %s",(int)actionname);
   if ( size_reloc != read(module_fd, reloc_buf, size_reloc) )
       	return (int)moduleload_error("action %s", (int)actionname);

   // make relocations
   if ( !func( (struct flat_hdr*) flat_buf, (uint32_t*)reloc_buf ) )  
       	return (int)moduleload_error("bad import symbol",0);

   ufree(reloc_buf); reloc_buf=0;
   return 1;
}

//********************************************************/
//**           Main module system functions             **
//********************************************************/

//-----------------------------------------------
// PARAMETER:  name - filename of module
//             callback - function which bind/unbind chdk 
//         local pointers with module symbols.
//         Optional ( NULL - do not bind )
// RETURN:    -1 - failed, >=0 =idx of module
//-----------------------------------------------
int module_load( char* name, _module_loader_t callback)
{
   int idx;

   module_fd = -1;
   module_filename = name;
   flat_buf = 0;
   reloc_buf = 0;

/* possible to have idx=0. so no checks
   if (!name)		
      return -1;
*/

   //moduleload_error("Loading module %s", (uint32_t)name);

   // Check if module loaded
   idx = module_find(name);
   if ( idx>=0 ) {
	  // reset possible unload request
	  module_unload_request[idx]=0;
      return idx;
   }

   // Find empty slot   
   for ( idx=0; idx<MAX_NUM_LOADED_MODULES && modules[idx]; idx++ );

   if  ( idx == MAX_NUM_LOADED_MODULES )
      return moduleload_error("%d already loaded",MAX_NUM_LOADED_MODULES);

   module_unload_request[idx]=0;
   module_flags[idx]=0;

   char path[60];
   struct flat_hdr flat;
   int size_flat;

   flat_module_path_make(path,name);

   module_fd = open( path, O_RDONLY, 0777 );
   if ( module_fd <=0 )
      return moduleload_error("file not found",0);

   // @tsv TODO - compare loaded with requested
   b_read( module_fd, (char*)&flat, sizeof(flat) );

   if  ( flat.rev!=FLAT_VERSION || memcmp( flat.magic, FLAT_MAGIC_NUMBER, 4) )
      return moduleload_error("bad magicnum", 0);

   if  ( flat.chdk_min_version > CHDK_BUILD_NUM )
      return moduleload_error("require CHDK%d", flat.chdk_min_version);

   if  ( flat.chdk_req_platfid && flat.chdk_req_platfid != PLATFORMID )
      return moduleload_error("require platfid %d", flat.chdk_req_platfid);

   size_flat = flat.bss_end+1;

   flat_buf = malloc( size_flat );
   if ( !flat_buf ) 
      return moduleload_error("malloc",0);
    
   if ( 0!= lseek(module_fd, 0, SEEK_SET) )
        return moduleload_error("read",0);
   if ( size_flat != b_read(module_fd, flat_buf, size_flat) )
        return moduleload_error("read",0);

   b_close(-1);	// filebuf not needed below

   if ( !module_do_action( "reloc", flat.reloc_start, flat.reloc_count, module_do_relocations ) )
	  return -1;
   if ( !module_do_action( "export", flat.import_start, flat.import_count, module_do_imports ) )
	  return -1;

   b_close( module_fd );
   module_fd = -1;

   modules[idx] = (struct flat_hdr* )flat_buf;

   if ( flat._module_loader )    { modules[idx]->_module_loader += (unsigned int)flat_buf; }
   if ( flat._module_unloader )  { modules[idx]->_module_unloader += (unsigned int)flat_buf; }
   if ( flat._module_run )       { modules[idx]->_module_run += (unsigned int)flat_buf; }


   // store runtime params
   flat_module_name_make(modules[idx]->modulename, name);
   modules[idx]->runtime_bind_callback = callback;     //@tsv reuse unneeded entry to store valuable

   int bind_err=0;
   if ( flat._module_exportlist ) { 
        modules[idx]->_module_exportlist += (unsigned int)flat_buf; 
        if ( * ((uint32_t*)modules[idx]->_module_exportlist) != EXPORTLIST_MAGIC_NUMBER )
            return moduleload_error("wrong import magic",0);

        if ( callback )
            bind_err = callback( (void**) modules[idx]->_module_exportlist );
   }

   if ( modules[idx]->_module_loader ) {
		uint32_t x = ((_module_loader_t) modules[idx]->_module_loader )(CHDK_EXPORT_LIST);
        bind_err = bind_err || x; //( (_module_loader_t) modules[idx]->_module_loader )(CHDK_EXPORT_LIST));
   }

   if ( bind_err )
   {
        module_unload(name); flat_buf=0;
        return moduleload_error("chdk mismatch",0);
   }

   return idx;
}

//-----------------------------------------------
// PURPOSE: 	run module "name" with argn/argv arguments. 
//				callback = chdk-bind/unbind exported by module symbols.
//				unload_after = 0 - do not unload
//							   1 - unload if load and no run handler
//							   2 - unload always
// RETURN VALUE: passed from module. -1 if something was failed
//-----------------------------------------------
int module_run(char* name, _module_loader_t callback, int argn, void* args, enum ModuleUnloadMode unload_after)
{
   int rv = -1;
   int loadflag=0;

   int moduleidx = module_find(name);
	if ( moduleidx<0 )
	{
		loadflag=1;
	
		moduleidx = module_load( name, callback );
   		if ( moduleidx<0 )
      		return -1;
	}

   if ( modules[moduleidx]->_module_run ) {
      kbd_key_release_all();
	  module_unload_request[moduleidx]=0;	// sanity stability clean
      rv = ( (_module_run_t) modules[moduleidx]->_module_run )(moduleidx, argn, args);
	}
	else if ( unload_after==UNLOAD_IF_ERR && loadflag)
		unload_after=UNLOAD_ALWAYS;

   if ( unload_after==UNLOAD_ALWAYS )
      module_unload(name);
   return rv;
}


//-----------------------------------------------
void module_unload(char* name)
{
   int idx;
   _module_loader_t callback;

   idx = module_find(name);

   if ( idx>=0 ) {
        // Make finalization module
        if ( modules[idx]->_module_unloader )
           ((_module_unloader_t) modules[idx]->_module_unloader )();
        // Unbind pointers to module (chdk core callback)
        if ( modules[idx]->runtime_bind_callback ) {
           callback = (_module_loader_t)modules[idx]->runtime_bind_callback;
           callback(0);
        }
       
        // Free slot
        free ( modules[idx] );
        modules[idx]=0;
        module_unload_request[idx]=0;
        module_flags[idx]=0;
   }
}


//-----------------------------------------------
// Return: 0 no such module exist, !=0 found
//-----------------------------------------------
int module_check_is_exist(char* name)
{
  char path[60];
  flat_module_path_make(path, name);

   module_fd = open( path, O_RDONLY, 0777 );
   if ( module_fd >0 )
     close (module_fd);

   return (module_fd>=0);
}

//-----------------------------------------------
void module_async_unload(unsigned int idx)
{
  if (idx <MAX_NUM_LOADED_MODULES)
     module_unload_request[idx]=2;
}

void module_set_flags(unsigned int idx, char value)
{
  if (idx <MAX_NUM_LOADED_MODULES)
     module_flags[idx]=value;
}

//-----------------------------------------------
// Close all runned modules
//   1. Called when goto GUI_MODE_NONE
//   2. Close in 0.1sec to finalize possible in-module flow
//	 3. Close only modules which are raised flag autounload
//-----------------------------------------------
void module_async_unload_allrunned(int enforce)
{
	int idx;

    for( idx=0; idx<MAX_NUM_LOADED_MODULES; idx++) {
		if ( modules[idx] &&
				( enforce ||
				 (module_flags[idx]&MODULE_FLAG_DISABLE_AUTOUNLOAD)==0 ) )
			module_unload_request[idx]=10;
	}     	  
     
}



//-----------------------------------------------
// Called on each tick to safe asynchronous unload module by its requests 
//-----------------------------------------------
void module_tick_unloader()
{
  int idx;

  for( idx=0; idx<MAX_NUM_LOADED_MODULES; idx++) {
    if ( module_unload_request[idx] >0 ) {
        module_unload_request[idx]--;
        //do unload on second tick to give module time to finish
            // (even if we set it right before return from function tick could happen at same moment)
        if ( module_unload_request[idx] == 0 )
            module_unload((char*)idx);
    }
  }
}

void* module_get_adr(unsigned int idx)
{
	if (idx < MAX_NUM_LOADED_MODULES)
		return modules[idx];
	return 0;
}
