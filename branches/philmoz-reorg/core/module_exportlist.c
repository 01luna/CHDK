/*
 *   THIS FILE IS FOR DECLARATION/LISTING OF EXPORTED TO MODULES SYMBOLS
 *
 *    CHDK-FLAT Module System.  Sergey Taranenko aka tsvstar
 */

#include "platform.h"
#include "module_exportlist.h"
#include "lang.h"
#include "stdlib.h"
#include "keyboard.h"
#include "raw_buffer.h"

#include "gui.h"
#include "gui_draw.h"
#include "gui_batt.h"
#include "gui_space.h"
#include "gui_menu.h"
#include "gui_osd.h"
#include "gui_mbox.h"
#include "gui_mpopup.h"
#include "gui_usb.h"
#include "conf.h"
#include "raw.h"
#include "font.h"
#include "histogram.h"
#include "shot_histogram.h"
#include "levent.h"
#include "kbd.h"
#include "ptp.h"

#include "modules.h"
#include "module_load.h"
#include "action_stack.h"
#include "console.h"
#include "gps.h"

extern short shooting_get_ev_correction1();

extern long* FlashParamsTable[]; 
extern unsigned _ExecuteEventProcedure(const char *name,...);

extern long shutter_open_time; // defined in platform/generic/capt_seq.c
extern long shutter_open_tick_count; // defined in platform/generic/capt_seq.c

// ATTENTION: DO NOT USE BRACES OR OWN /**/-STYLE COMMENTS ANYWHERE IN THIS FILE TO AVOID AUTO PARSING MISTAKES


// ** SECTION 1: DEFINE UNDECLARED EXPORTED ITEMS


// ** SECTION 2: IMPLEMENTATION OF EXPORTED #define VALUES
// 	  1. PLEASE DO NOT CHANGE START AND FINAL COMMENTS TO CORRECT AUTOPARSING

/* EXPORTED_DEFINES_BEGIN */

char SCREEN__EXPORTEDSYM_COLOR        = SCREEN_COLOR		;
char COLOR__EXPORTEDSYM_WHITE         = COLOR_WHITE         ;
char COLOR__EXPORTEDSYM_RED           = COLOR_RED           ;
char COLOR__EXPORTEDSYM_GREY          = COLOR_GREY          ;
char COLOR__EXPORTEDSYM_GREEN         = COLOR_GREEN         ;
char COLOR__EXPORTEDSYM_BLUE_LT       = COLOR_BLUE_LT       ;
char COLOR__EXPORTEDSYM_BLUE          = COLOR_BLUE          ;
char COLOR__EXPORTEDSYM_YELLOW        = COLOR_YELLOW        ;
char COLOR__EXPORTEDSYM_BG            = COLOR_BG            ;
char COLOR__EXPORTEDSYM_FG            = COLOR_FG            ;
char COLOR__EXPORTEDSYM_SELECTED_BG   = COLOR_SELECTED_BG   ;
char COLOR__EXPORTEDSYM_SELECTED_FG   = COLOR_SELECTED_FG   ;
char COLOR__EXPORTEDSYM_ALT_BG        = COLOR_ALT_BG        ;
char COLOR__EXPORTEDSYM_SPLASH_RED    = COLOR_SPLASH_RED    ;
char COLOR__EXPORTEDSYM_SPLASH_PINK   = COLOR_SPLASH_PINK   ;
char COLOR__EXPORTEDSYM_SPLASH_GREY   = COLOR_SPLASH_GREY   ;
char COLOR__EXPORTEDSYM_HISTO_R       = COLOR_HISTO_R       ;
char COLOR__EXPORTEDSYM_HISTO_R_PLAY  = COLOR_HISTO_R_PLAY  ;
char COLOR__EXPORTEDSYM_HISTO_B       = COLOR_HISTO_B       ;
char COLOR__EXPORTEDSYM_HISTO_G       = COLOR_HISTO_G       ;
char COLOR__EXPORTEDSYM_HISTO_G_PLAY  = COLOR_HISTO_G_PLAY  ;
char COLOR__EXPORTEDSYM_HISTO_BG      = COLOR_HISTO_BG      ;
char COLOR__EXPORTEDSYM_HISTO_RG      = COLOR_HISTO_RG      ;
char COLOR__EXPORTEDSYM_HISTO_RB      = COLOR_HISTO_RB      ;
char COLOR__EXPORTEDSYM_HISTO_RB_PLAY = COLOR_HISTO_RB_PLAY ;
char COLOR__EXPORTEDSYM_HISTO_B_PLAY  = COLOR_HISTO_B_PLAY  ;
char COLOR__EXPORTEDSYM_HISTO_BG_PLAY = COLOR_HISTO_BG_PLAY ;
char COLOR__EXPORTEDSYM_HISTO_RG_PLAY = COLOR_HISTO_RG_PLAY ;

/* EXPORTED_DEFINES_END */


// ** SECTION 3: LIST OF EXPORTED SYMBOLS (pointer to function/variable)
//	STOPLIST: open, opendir, closedir, rewinddir, readdir, stat

// This section is parsed by the makeexport.c program to generate the
// symbol hash table loaded later (from module_hashlist.h)
// Symbols to be exported should be on seperate lines, blank lines and '//' style comments are allowed

#if 0
{
			module_async_unload,
			module_set_flags,
			module_run,
			module_get_adr,
			module_async_unload_allrunned,
			module_rawop_load,
			module_curves_load,
            module_rawop_unload,
            module_mpopup_init,
			module_convert_dng_to_chdk_raw,
            module_grids_load,
            module_find_symbol_address,
            module_restore_edge,
            module_save_edge,

            &altGuiHandler,
            &camera_info,
            &camera_screen,
            &camera_sensor,
            &gui_version,
            &conf,

            malloc,
            free,
            umalloc,
            ufree,

            write,
            lseek,
            open,
            close,
            read,
            remove,
            rename,
            stat,
            opendir,
            readdir,
            closedir,
			mkdir,

            fopen,
            fclose,
            fseek,
            fread,
            fwrite,

            get_tick_count,
			time,
            utime,
            localtime,
			get_localtime,
            rand,
			srand,
            qsort,
			msleep,

            lang_str,
            sprintf,
			strlen,
			strcpy,
            strncmp,
            strpbrk,
            strchr,
			strcmp,
            strtol,
            strrchr,
            strncpy,
            toupper,
            memcpy,
            memset,

            draw_txt_string,
			draw_string,
			draw_rect,
            draw_filled_rect,
 			draw_filled_ellipse,
			draw_filled_round_rect,
			draw_line,
			draw_char,
            draw_get_pixel,
            draw_pixel,
            draw_txt_char,
			draw_rect_thick,
			draw_filled_rect_thick,
            draw_rect_shadow,
            draw_ellipse,
            draw_set_draw_proc,
            draw_restore,

            gui_get_mode,
            gui_set_mode,
			gui_default_kbd_process_menu_btn,
			get_batt_perc,
			gui_osd_draw_clock,
			gui_mbox_init,
            gui_browser_progress_show,
            gui_enum_value_change,
			gui_set_need_restore,

            gui_osd_calc_dof,
            gui_osd_draw_dof,
            gui_batt_draw_osd,
            gui_space_draw_osd,
            gui_osd_draw_state,
            gui_osd_draw_raw_info,
            gui_osd_draw_values,
            gui_osd_draw_temp,
            gui_osd_draw_histo,
            gui_usb_draw_osd,
            gui_osd_draw_ev_video,

            vid_get_bitmap_fb,
            vid_get_viewport_fb,
            vid_get_viewport_fb_d,
            vid_get_viewport_live_fb,
            vid_get_viewport_height,
			vid_get_viewport_width,
            vid_get_viewport_byte_width,
            vid_get_viewport_display_xoffset,
            vid_get_viewport_display_yoffset,
            vid_get_viewport_image_offset,
            vid_get_viewport_row_offset,
            vid_get_viewport_yscale,
            vid_get_viewport_active_buffer,

			get_raw_image_addr,
            hook_raw_image_addr,
			raw_prepare_develop,

            kbd_get_autoclicked_key,
            kbd_is_key_pressed,
            kbd_key_press,
			kbd_get_clicked_key,
			kbd_reset_autoclicked_key,
            get_jogdial_direction,

			// for rawop.flt
            GetFreeCardSpaceKb,
            debug_led,

			mode_get,
            shooting_get_zoom,
            shooting_set_zoom,
            shooting_get_prop,

			// for txtread.flt
            rbf_char_width,
            rbf_font_height,
            rbf_draw_char,
            rbf_load_from_file,

			// for modinsp.flt
			GetMemInfo,
			GetExMemInfo,

			// for fselect.flt
            img_prefixes,
            img_exts,
            GetTotalCardSpaceKb,

			// tetris.flt
			TurnOnBackLight,
			TurnOffBackLight,

			action_stack_create,
			action_pop,
			action_push,
			action_push_delay,
            action_push_release,
			action_stack_standard,
			console_clear,
			console_add_line,

            shooting_set_tv96_direct,
			shooting_get_iso_market,
			shooting_get_ev_correction1,

            get_focal_length,
			get_effective_focal_length,
			get_parameter_data,
			get_property_case,

            &shutter_open_time,
            &shutter_open_tick_count,
			&state_shooting_progress,
			get_raw_pixel,
			patch_bad_pixel,
			
			pow_calc,
			pow_calc_2,

			// export palette
			&SCREEN__EXPORTEDSYM_COLOR		 ,
			&COLOR__EXPORTEDSYM_WHITE        ,
			&COLOR__EXPORTEDSYM_RED          ,
			&COLOR__EXPORTEDSYM_GREY         ,
			&COLOR__EXPORTEDSYM_GREEN        ,
			&COLOR__EXPORTEDSYM_BLUE_LT      ,
			&COLOR__EXPORTEDSYM_BLUE         ,
			&COLOR__EXPORTEDSYM_YELLOW       ,
			&COLOR__EXPORTEDSYM_BG           ,
			&COLOR__EXPORTEDSYM_FG           ,
			&COLOR__EXPORTEDSYM_SELECTED_BG  ,
			&COLOR__EXPORTEDSYM_SELECTED_FG  ,
			&COLOR__EXPORTEDSYM_ALT_BG       ,
			&COLOR__EXPORTEDSYM_SPLASH_RED   ,
			&COLOR__EXPORTEDSYM_SPLASH_PINK  ,
			&COLOR__EXPORTEDSYM_SPLASH_GREY  ,
			&COLOR__EXPORTEDSYM_HISTO_R      ,
			&COLOR__EXPORTEDSYM_HISTO_R_PLAY ,
			&COLOR__EXPORTEDSYM_HISTO_B      ,
			&COLOR__EXPORTEDSYM_HISTO_G      ,
			&COLOR__EXPORTEDSYM_HISTO_G_PLAY ,
			&COLOR__EXPORTEDSYM_HISTO_BG     ,
			&COLOR__EXPORTEDSYM_HISTO_RG     ,
			&COLOR__EXPORTEDSYM_HISTO_RB     ,
			&COLOR__EXPORTEDSYM_HISTO_RB_PLAY,
			&COLOR__EXPORTEDSYM_HISTO_B_PLAY ,
			&COLOR__EXPORTEDSYM_HISTO_BG_PLAY,
			&COLOR__EXPORTEDSYM_HISTO_RG_PLAY,

            module_tbox_load,

            config_save,
            config_restore,

            dbg_printf,

            gps_getData,

    DoAFLock,
    GetJpgCount,
    GetRawCount,
    JogDial_CCW,
    JogDial_CW,
    UnlockAF,
    action_push_click,
    action_push_press,
    action_wait_for_click,
    camera_get_nr,
    camera_get_script_autostart,
    camera_set_led,
    camera_set_nr,
    camera_set_raw,
    camera_shutdown_in_a_second,
    &circle_of_confusion,
    conf_getValue,
    conf_save,
    conf_setValue,
    console_redraw,
    console_set_autoredraw,
    console_set_layout,
    exit_alt,
    get_battery_temp,
    get_ccd_temp,
    get_exposure_counter,
    get_optical_temp,
    get_usb_power,
    lens_get_zoom_point,
    levent_set_play,
    levent_set_record,
    mode_is_video,
    module_mdetect_load,
    &movie_status,
    play_sound,
    reboot,
    script_console_add_line,
    script_key_is_clicked,
    script_key_is_pressed,
    script_keyid_by_name,
    script_print_screen_statement,
    shooting_get_av96,
    shooting_get_bv96,
    shooting_get_day_seconds,
    shooting_get_depth_of_field,
    shooting_get_display_mode,
    shooting_get_drive_mode,
    shooting_get_far_limit_of_acceptable_sharpness,
    shooting_get_flash_mode,
    shooting_get_focus_mode,
    shooting_get_focus_ok,
    shooting_get_focus_state,
    shooting_get_hyperfocal_distance,
    shooting_get_is_mode,
    shooting_get_iso_mode,
    shooting_get_iso_real,
    shooting_get_min_stack_distance,
    shooting_get_near_limit_of_acceptable_sharpness,
    shooting_get_real_focus_mode,
    shooting_get_resolution,
    shooting_get_subject_distance,
    shooting_get_sv96,
    shooting_get_tick_count,
    shooting_get_tv96,
    shooting_get_user_av96,
    shooting_get_user_av_id,
    shooting_get_user_tv96,
    shooting_get_user_tv_id,
    shooting_in_progress,
    shooting_is_flash,
    shooting_mode_chdk2canon,
    shooting_set_av96,
    shooting_set_av96_direct,
    shooting_set_focus,
    shooting_set_iso_mode,
    shooting_set_iso_real,
    shooting_set_mode_canon,
    shooting_set_mode_chdk,
    shooting_set_nd_filter_state,
    shooting_set_prop,
    shooting_set_shutter_speed_ubasic,
    shooting_set_sv96,
    shooting_set_tv96,
    shooting_set_user_av96,
    shooting_set_user_av_by_id,
    shooting_set_user_av_by_id_rel,
    shooting_set_user_tv96,
    shooting_set_user_tv_by_id,
    shooting_set_user_tv_by_id_rel,
    shooting_set_zoom_rel,
    shooting_set_zoom_speed,
    shot_histogram_get_range,
    shot_histogram_isenabled,
    shot_histogram_set,
    stat_get_vbatt,
    &state_kbd_script_run,
    strcat,
    swap_partitions,
    get_part_count,
    get_part_type,
    get_active_partition,
    &zoom_points,

    &FlashParamsTable,
    PostLogicalEventForNotPowerType,
    PostLogicalEventToUI,
    SetFileAttributes,
    SetLogicalEventActive,
    SetScriptMode,
    enter_alt,
    errnoOfTaskGet,
    feof,
    fflush,
    fgets,
    ftell,
    get_flash_params_count,
    get_target_dir_name,
    isalnum,
    isalpha,
    iscntrl,
    islower,
    ispunct,
    isspace,
    isupper,
    isxdigit,
    levent_count,
    levent_id_for_name,
    levent_index_for_id,
    levent_index_for_name,
    levent_table,
    live_histogram_read_y,
    memchr,
    memcmp,
    mktime,
    module_fselect_init,
    script_colors,
    script_end,
    script_print_screen_end,
    script_start_gui,
    script_wait_and_end,
    set_property_case,
    shooting_get_common_focus_mode,
    shooting_update_dof_values,
    shutdown,
    strerror,
    strftime,
    strtoul,
    switch_mode_usb,
    tolower,

    call_func_ptr,
    _ExecuteEventProcedure,

    ptp_script_create_msg,
    ptp_script_write_msg,
    ptp_script_read_msg,
    ptp_script_write_error_msg,
}
#endif

// Symbol hash table for resolving exported symbol references
sym_hash symbol_hash_table[] =
{
    { EXPORTLIST_MAGIC_NUMBER, (void*)EXPORTLIST_LAST_IDX },
#include "module_hashlist.h"
};
