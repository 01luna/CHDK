#include "platform.h"
#include "../module_load.h"
#include "../gui_draw.h"
#include "../gui_lang.h"
#include "../gui_mbox.h"

extern int basic_module_init();


// =========  MODULE INIT =================

int module_idx=-1;

/***************** BEGIN OF AUXILARY PART *********************
  ATTENTION: DO NOT REMOVE OR CHANGE SIGNATURES IN THIS SECTION
 **************************************************************/

void* MODULE_EXPORT_LIST[] = {
	/* 0 */	(void*)EXPORTLIST_MAGIC_NUMBER,
	/* 1 */	(void*)0
		};


//---------------------------------------------------------
// PURPOSE:   Bind module symbols with chdk. 
//		Required function
// PARAMETERS: pointer to chdk list of export
// RETURN VALUE: 1 error, 0 ok
//---------------------------------------------------------
int _module_loader( void** chdk_export_list )
{
  if ( (unsigned int)chdk_export_list[0] != EXPORTLIST_MAGIC_NUMBER )
     return 1;

  return 0;
}



//---------------------------------------------------------
// PURPOSE: Finalize module operations (close allocs, etc)
// RETURN VALUE: 0-ok, 1-fail
//---------------------------------------------------------
int _module_unloader()
{
  return 0;
}


//---------------------------------------------------------
// PURPOSE: Default action for simple modules (direct run)
// NOTE: Please comment this function if no default action and this library module
//---------------------------------------------------------
int _module_run(int moduleidx, int argn, int* arguments)
{
  module_idx=moduleidx;


  int rv = 0;
  if ((mode_get()&MODE_MASK) != MODE_PLAY) {
      gui_mbox_init(LANG_MSG_INFO_TITLE, LANG_MSG_SWITCH_TO_PLAY_MODE,
                    MBOX_FUNC_RESTORE|MBOX_TEXT_CENTER, 0);
  } else {
	rv = basic_module_init();
  }
  if ( ! rv )
	module_async_unload(moduleidx);		// fail to init - "unload me"

  return 0;
}


/*************** END OF AUXILARY PART *******************/
