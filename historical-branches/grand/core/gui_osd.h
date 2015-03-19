#ifndef GUI_OSD_H
#define GUI_OSD_H

//-------------------------------------------------------------------
// A - RGB
#define OSD_HISTO_LAYOUT_A              0
#define OSD_HISTO_LAYOUT_Y              1
#define OSD_HISTO_LAYOUT_A_Y            2
#define OSD_HISTO_LAYOUT_R_G_B          3
#define OSD_HISTO_LAYOUT_A_yrgb         4
#define OSD_HISTO_LAYOUT_Y_argb         5
#define OSD_HISTO_LAYOUT_BLEND          6
#define OSD_HISTO_LAYOUT_BLEND_Y        7

#define ZEBRA_DRAW_NONE                 0
#define ZEBRA_DRAW_HISTO                1
#define ZEBRA_DRAW_OSD                  2

#define ZOOM_SHOW_X                     0
#define ZOOM_SHOW_FL                    1
#define ZOOM_SHOW_EFL                   2

//-------------------------------------------------------------------
extern void gui_osd_init();
extern void gui_osd_kbd_process();
extern void gui_osd_draw();

extern void gui_osd_zebra_init();

extern void gui_osd_draw_histo();
extern void gui_osd_draw_dof();
extern void gui_osd_draw_state();
extern void gui_osd_draw_values();
extern void gui_osd_draw_clock();
extern int  gui_osd_draw_zebra();

//-------------------------------------------------------------------
#endif