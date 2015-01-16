#include "keyboard.h"
#include "conf.h"
#include "platform.h"
#include "../generic/wrappers.c"

long lens_get_focus_pos()
{
    static long v=MAX_DIST;
    return (kbd_is_key_pressed(KEY_SHOOT_HALF) || camera_info.state.state_kbd_script_run || shooting_get_focus_mode())?v=_GetFocusLensSubjectDistance():v;
}

long lens_get_focus_pos_from_lens()
{
   static long v=MAX_DIST;
   return (kbd_is_key_pressed(KEY_SHOOT_HALF) || camera_info.state.state_kbd_script_run  || shooting_get_focus_mode())?v=_GetFocusLensSubjectDistanceFromLens():v;
}

long lens_get_target_distance()
{
    static long v=MAX_DIST;
    return (kbd_is_key_pressed(KEY_SHOOT_HALF) || camera_info.state.state_kbd_script_run  || shooting_get_focus_mode())?v=_GetCurrentTargetDistance():v;
}
 
 //--------------------------------------------------
 // DoMFLock : use _MFOn/_MFOff  or  _PT_MFOn/_PT_MFOff  or _SS_MFOn/_SS_MFOff if defined in stubs_entry.S
 //            otherwise use PostLogicalEventForNotPowerType(levent_id_for_name(PressSW1andMF),0); (see sx500hs for an example)
 
int DoMFLock(void)
{
  return(0);
 
}
 
int UnlockMF(void)
{
  return(0);
 
}
