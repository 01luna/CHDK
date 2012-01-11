/*
 *   CHDK-FLAT Module System.  
 *
 *   (c)2011 Sergey Taranenko aka tsvstar
 *
 *   Specific "shortcuts", dynamic libraries binding
 */

#include "modules.h"
#include "module_load.h"
#include "camera.h"
#include "stdlib.h"
#include "conf.h"
#include "gui_draw.h"
#include "dng.h"
#include "lang.h"

/************* GENERIC ******/

static int bind_module_generic( void** export_list, void** lib, int count, int major, int minor )
{
    *lib = 0;

	// Unbind
	if ( !export_list ) {
    	return 0;
  	}

	// Bind
	if ( (unsigned int)export_list[0] != EXPORTLIST_MAGIC_NUMBER )
	     return 1;
  	if ( (unsigned int)export_list[1] < count )
    	 return 1;

	*lib = (void*)export_list[2];

	if ( !*lib )
    	 return 1;
	if ( (major > 0) && !API_VERSION_MATCH_REQUIREMENT( *((int*)(*lib)), major, minor ) ) {
		*lib=0;
		return 1;
	}

	return 0;
}

// Return: 0-fail, addr-ok
static void* module_load_generic(void **lib, char *name, int (*callback)(void**), int flags)
{
    if (*lib == 0)
    {
        int module_idx = module_load(name, callback);
        if ( module_idx < 0 )
            module_unload(name);  
        else
        {
            if (flags)
    	 	    module_set_flags(module_idx, flags);
        }
    }

    return *lib;
}

/************* DYNAMIC LIBRARY RAWOPERATION ******/

#if CAM_SENSOR_BITS_PER_PIXEL==10
#define MODULE_NAME_RAWOP "_rawop10.flt"
#elif CAM_SENSOR_BITS_PER_PIXEL==12
#define MODULE_NAME_RAWOP "_rawop12.flt"
#else 
 #error define set_raw_pixel for sensor bit depth
#endif

// This is to minimize sharing sym to use this lib in other modules
struct librawop_sym* librawop;

void module_rawop_unload()
{
	if (librawop)
    {
    	module_unload(MODULE_NAME_RAWOP);  
        librawop = 0;
    }
}

static int bind_module_rawop( void** export_list )
{
    return bind_module_generic(export_list, (void**)&librawop, 1, 0, 0);
}

// Return: 0-fail, otherwise - bind list
struct librawop_sym* module_rawop_load()
{
    return module_load_generic((void**)&librawop, MODULE_NAME_RAWOP, bind_module_rawop, 0);
}


/************* DYNAMIC LIBRARY EDGE OVERLAY ******/

#ifdef OPT_EDGEOVERLAY

#define MODULE_NAME_EDGEOVR "edgeovr.flt"

struct libedgeovr_sym* libedgeovr;

static int bind_module_edgeovr( void** export_list )
{
    return bind_module_generic(export_list, (void**)&libedgeovr, 1, 1, 0);
}

// Return: 0-fail, 1-ok
struct libedgeovr_sym* module_edgeovr_load()
{
    // This flag is because edgeovr called each tick
    //   If module loading failed, then do not try to load it until reboot
    //    (otherwise we will try to load module each tick)
    static int flag_load_fail = 0;

    if ( flag_load_fail==0 )
    {
        module_load_generic((void**)&libedgeovr, MODULE_NAME_EDGEOVR, bind_module_edgeovr, MODULE_FLAG_DISABLE_AUTOUNLOAD);

        if (libedgeovr == 0)
    		flag_load_fail = 1;
    }

    return libedgeovr;
}


// edgeovr module will never unload to keep its picture
// void module_edgeovr_unload() {}

#endif


/************* DYNAMIC LIBRARY MOTION DETECT ******/

#define MODULE_NAME_MDETECT "mdetect.flt"

struct libmotiondetect_sym* libmotiondetect;

static int bind_module_motiondetect( void** export_list )
{
    return bind_module_generic(export_list, (void**)&libmotiondetect, 1, 1, 0);
}

// Return: 0-fail, 1-ok
struct libmotiondetect_sym* module_mdetect_load()
{
    return module_load_generic((void**)&libmotiondetect, MODULE_NAME_MDETECT, bind_module_motiondetect, MODULE_FLAG_DISABLE_AUTOUNLOAD);
}


/************* DYNAMIC LIBRARY ZEBRA ******/

#define MODULE_NAME_ZEBRA "zebra.flt"

struct libzebra_sym* libzebra;

static int bind_module_zebra( void** export_list )
{
    return bind_module_generic(export_list, (void**)&libzebra, 1, 1, 0);
}

// Return: 0-fail, 1-ok
struct libzebra_sym* module_zebra_load()
{
    return module_load_generic((void**)&libzebra, MODULE_NAME_ZEBRA, bind_module_zebra, MODULE_FLAG_DISABLE_AUTOUNLOAD);
}


/************* DYNAMIC LIBRARY CURVES ******/

#if defined(OPT_CURVES)

#define MODULE_NAME_CURVES "curves.flt"

struct libcurves_sym* libcurves;

static int bind_module_curves( void** export_list )
{
    return bind_module_generic(export_list, (void**)&libcurves, 1, 1, 0);
}

// Return: 0-fail, addr-ok
struct libcurves_sym* module_curves_load()
{
    return module_load_generic((void**)&libcurves, MODULE_NAME_CURVES, bind_module_curves, 0);
}

#endif


/************* DYNAMIC LIBRARY GRIDS ******/

#define MODULE_NAME_GRIDS "grids.flt"

struct libgrids_sym* libgrids;

static int bind_module_grids( void** export_list )
{
    return bind_module_generic(export_list, (void**)&libgrids, 1, 1, 0);
}

// Return: 0-fail, addr-ok
struct libgrids_sym* module_grids_load()
{
    return module_load_generic((void**)&libgrids, MODULE_NAME_GRIDS, bind_module_grids, 0);
}


/************* MODULE PALETTE ******/

void module_palette_run(int mode, color st_color, void (*on_select)(color clr))
{
	unsigned int argv[] = {	mode,
							(unsigned int)st_color,
							(unsigned int)on_select };
    module_run("palette.flt", 0, sizeof(argv)/sizeof(argv[0]), argv,  UNLOAD_IF_ERR);
}


/************* MODULE MPOPUP ******/

void module_mpopup_init(struct mpopup_item* popup_actions, const unsigned int flags, void (*on_select)(unsigned int actn), int mode)
{
	unsigned int argv[] = {	(unsigned int)popup_actions,
							(unsigned int)flags,
							(unsigned int)on_select,
							(unsigned int)mode,
							 };
    module_run("mpopup.flt", 0, sizeof(argv)/sizeof(argv[0]), argv,  UNLOAD_IF_ERR);
}


/************* MODULE FSELECT ******/

void module_fselect_init_w_mode(int title, const char* prev_dir, const char* default_dir, void (*on_select)(const char *fn), unsigned int key_redraw_mode)
{
	unsigned int argv[] = {	title,
							(unsigned int)prev_dir,
							(unsigned int)default_dir,
							(unsigned int)on_select,
							(unsigned int)key_redraw_mode,
							 };
    module_run("fselect.flt", 0,  sizeof(argv)/sizeof(argv[0]), argv, UNLOAD_IF_ERR);
}

void module_fselect_init(int title, const char* prev_dir, const char* default_dir, void (*on_select)(const char *fn))
{
	module_fselect_init_w_mode(title, prev_dir, default_dir, on_select, 0/*key_redraw_mode*/);
}

/************* MODULE DNG ******/

#define MODULE_NAME_DNG "_dng.flt"

// This is to keep module in memory while it required by anyone
static int module_dng_semaphore;

struct libdng_sym* libdng;

void module_dng_unload(int owner)
{
#if DNG_SUPPORT
	if (libdng==0)
    	return;

  	module_dng_semaphore &= ~owner;
	if (module_dng_semaphore)
		return;

	module_unload(MODULE_NAME_DNG);  
#endif
}

static int bind_module_dng( void** export_list )
{
    return bind_module_generic(export_list, (void**)&libdng, 1, 1, 0);
}

// Return: 0-fail, otherwise - bind list
struct libdng_sym* module_dng_load(int owner)
{
#if DNG_SUPPORT
    module_dng_semaphore |= owner;

    module_load_generic((void**)&libdng, MODULE_NAME_DNG, bind_module_dng, 0);

    if (libdng == 0)
        module_dng_semaphore=0;

    return libdng;
#else
    return 0;
#endif
}

// Make convertion or check operation exsitsing
// Parameter: fn = filename or 0 to just check is operation possible
// Return: 0-fail, 1-ok
//--------------------------------------------------------
int module_convert_dng_to_chdk_raw(char* fn)
{
#if DNG_SUPPORT
	if ( fn==0 )
		return module_check_is_exist(MODULE_NAME_DNG);
	if ( !module_dng_load(LIBDNG_OWNED_BY_CONVERT) )
		return 0;
	libdng->convert_dng_to_chdk_raw(fn);
	module_dng_unload(LIBDNG_OWNED_BY_CONVERT);
	return 1;
#else
	return 0;
#endif
}


/************* MODULE TBOX ******/

static char* tbox_file_buffer = 0;
static char* tbox_file_buffer_default = "_tbox.flt";
static int   tbox_file_buffer_size = 0;
static char* charmap_buffer = 0;
static int   charmap_buffer_size = 0;

// Auxilary function - Parse loaded keymap, ask module for its API version
// Input values: tbox_file_buffer, tbox_file_buffer_size
// Return value: 0-error, otherwise API version
//-----------------------------------------------------
static int module_tbox_charmap_preprocess() 
{
	charmap_buffer = 0;
	charmap_buffer_size = 0;

	//-- input checks
	if ( tbox_file_buffer==0 || tbox_file_buffer_size<=0 )
		return 0;

	int i, ver;

	//-- Parse: split to lines
	for( i=0; i<tbox_file_buffer_size; i++ )
	   if ( tbox_file_buffer[i] == 0x0d || tbox_file_buffer[i] == 0x0a)
		  tbox_file_buffer[i]=0;

	//-- First line is name of tbox module
	i = strlen(tbox_file_buffer);		// size
	if ( i==0 )
		return 0;

	// tbox "run scenario #1" - argc=1, argv=0 - mean "say your API version"
   	ver = module_run(tbox_file_buffer, 0,  1,0, UNLOAD_ALWAYS );

	// if mistake on load
	if ( ver<=0 ) 
		return 0;

	charmap_buffer=tbox_file_buffer+i+1;
	charmap_buffer_size= tbox_file_buffer_size - (i+1);

	return ver;
}

// Check version and existance and tbox api version
// return: 0 if no module exists at all, otherwise version of API of current tbox module
//-----------------------------------------------------
int module_tbox_get_version()
{
  static int last_loaded_tbox_hash = 0;
  static int cur_tbox_api_version = 0;

  // -- If keymap is loaded and not changed - return stored value

  if ( lang_strhash31((int)conf.charmap_file) == last_loaded_tbox_hash )
    return cur_tbox_api_version;

  // -- Free resources

  last_loaded_tbox_hash = 0;
  if ( tbox_file_buffer && tbox_file_buffer!=tbox_file_buffer_default )
    ufree( tbox_file_buffer );

  // -- Try to load keymap file

  tbox_file_buffer = load_file( conf.charmap_file, &tbox_file_buffer_size );

  // Check is module available, otherwise try default one

  cur_tbox_api_version = module_tbox_charmap_preprocess();


  // if keymap wrong/module can't be loaded - try default
  if ( cur_tbox_api_version==0 ) {
	 if ( tbox_file_buffer )
        ufree(tbox_file_buffer);

	 tbox_file_buffer = tbox_file_buffer_default;
	 tbox_file_buffer_size = strlen(tbox_file_buffer);
  	 cur_tbox_api_version = module_tbox_charmap_preprocess();
  }

  if ( cur_tbox_api_version )
	last_loaded_tbox_hash = lang_strhash31((int)conf.charmap_file);

  return cur_tbox_api_version;
}


//-----------------------------------------------------
void module_tbox_run( int title, int msg, char* defaultvalue, unsigned int maxsize, void (*on_select)(char* newstr))
{
	int ver = module_tbox_get_version();

	if ( API_VERSION_MATCH_REQUIREMENT( ver, 1, 0 ) ) {

		// Main "run scenario" - 7 argument, raise textbox
		unsigned int argv[] = {	(int)charmap_buffer,
								charmap_buffer_size,
								title,
								msg,
								(unsigned int)defaultvalue,
								maxsize,
								(unsigned int)on_select,
							 };
	    module_run(tbox_file_buffer, 0,  sizeof(argv)/sizeof(argv[0]), argv, UNLOAD_IF_ERR);
		
	}
}
