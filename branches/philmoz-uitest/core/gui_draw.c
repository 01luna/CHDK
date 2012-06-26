#include "stdlib.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"
#include "font.h"
#include "gui_draw.h"

//-------------------------------------------------------------------
static char*    frame_buffer[2];
void            (*draw_pixel_proc)(unsigned int offset, color cl);

//-------------------------------------------------------------------
static void draw_pixel_std(unsigned int offset, color cl) {
#ifdef DRAW_ON_ACTIVE_BITMAP_BUFFER_ONLY	
	extern int active_bitmap_buffer;
	frame_buffer[active_bitmap_buffer][offset] = cl & 0xff;
#else
	frame_buffer[0][offset] = frame_buffer[1][offset] = cl & 0xff;
#endif
}

//-------------------------------------------------------------------
void draw_set_draw_proc(void (*pixel_proc)(unsigned int offset, color cl)) {
    draw_pixel_proc = (pixel_proc)?pixel_proc:draw_pixel_std;
}

//-------------------------------------------------------------------
#ifdef CAM_DETECT_SCREEN_ERASE

#define GUARD_VAL   SCREEN_COLOR

void draw_set_guard()
{
    *((unsigned char*)(frame_buffer[0])) = GUARD_VAL;
    *((unsigned char*)(frame_buffer[1])) = GUARD_VAL;
}

int draw_test_guard()
{
    if (*((unsigned char*)(frame_buffer[0])) != GUARD_VAL) return 0;
    if (*((unsigned char*)(frame_buffer[1])) != GUARD_VAL) return 0;
    return 1;
}

// Test a pixel value in both frame buffers, returns 0 if either doesn't match or co-ords out of range
int draw_test_pixel(coord x, coord y, color c)
{
    if (x >= camera_screen.width || y >= camera_screen.height) return 0;
    return (frame_buffer[0][y * camera_screen.buffer_width + ASPECT_XCORRECTION(x)] == c) &&
           (frame_buffer[1][y * camera_screen.buffer_width + ASPECT_XCORRECTION(x)] == c);
}

#endif

//-------------------------------------------------------------------
void draw_init() {
    register int i;

    frame_buffer[0] = vid_get_bitmap_fb();
    frame_buffer[1] = frame_buffer[0] + camera_screen.buffer_size;
    draw_set_draw_proc(NULL);

#ifdef CAM_DETECT_SCREEN_ERASE
    draw_set_guard();
#endif
}

//-------------------------------------------------------------------
void draw_pixel(coord x, coord y, color cl) {
    if (x >= camera_screen.width || y >= camera_screen.height) return;
    else {
        register unsigned int offset = y * camera_screen.buffer_width + ASPECT_XCORRECTION(x);
        draw_pixel_proc(offset,   cl);
#if CAM_USES_ASPECT_CORRECTION
        draw_pixel_proc(offset+1, cl);  // Draw second pixel if screen scaling is needed
#endif
   }
}

//-------------------------------------------------------------------
color draw_get_pixel(coord x, coord y) {
    if (x >= camera_screen.width || y >= camera_screen.height) return 0;
    return frame_buffer[0][y * camera_screen.buffer_width + ASPECT_XCORRECTION(x) ];
}

//-------------------------------------------------------------------
#define swap(v1, v2)   {v1^=v2; v2^=v1; v1^=v2;}
//-------------------------------------------------------------------
void draw_line(coord x1, coord y1, coord x2, coord y2, color cl) {
     unsigned char steep = abs(y2 - y1) > abs(x2 - x1);
     if (steep) {
         swap(x1, y1);
         swap(x2, y2);
     }
     if (x1 > x2) {
         swap(x1, x2);
         swap(y1, y2);
     }
     int deltax = x2 - x1;
     int deltay = abs(y2 - y1);
     int error = 0;
     int y = y1;
     int ystep = (y1 < y2)?1:-1;
     int x;
     for (x=x1; x<=x2; ++x) {
         if (steep) draw_pixel(y, x, cl);
         else draw_pixel(x, y, cl);
         error += deltay;
         if ((error<<1) >= deltax) {
             y += ystep;
             error -= deltax;
         }
     }
}
//-------------------------------------------------------------------
void draw_hline(coord x, coord y, int len, color cl)
{
    if (x >= camera_screen.width || y >= camera_screen.height) return;
    if (x < 0) { len += x; x = 0; }
    if ((x + len) > camera_screen.width) len = camera_screen.width - x;
    register unsigned int offset = y * camera_screen.buffer_width + ASPECT_XCORRECTION(x);
    len = ASPECT_XCORRECTION(len);      // Scale the line length if needed
    for (; len>0; len--, offset++)
        draw_pixel_proc(offset, cl);
}

void draw_vline(coord x, coord y, int len, color cl)
{
    if ((x < 0) || (x >= camera_screen.width) || (y >= camera_screen.height)) return;
    if (y < 0) { len += y; y = 0; }
    if ((y + len) > camera_screen.height) len = camera_screen.height - y;
    for (; len>0; len--, y++)
      draw_pixel(x, y, cl);
}
//-------------------------------------------------------------------

// Local variables set up by draw_rectangle, and used in fill_rect
static unsigned int xMin, yMin, xMax, yMax;

static void draw_rectangle(coord x1, coord y1, coord x2, coord y2, color cl, int round) 
{
    register unsigned int x, y;

    if (x1>x2) {
    	xMax=x1; xMin=x2;
    } else {
    	xMin=x1; xMax=x2;
    }
    if (y1>y2) {
    	yMax=y1; yMin=y2;
    } else {
    	yMin=y1; yMax=y2;
    }
    if (xMax>=camera_screen.width) xMax=camera_screen.width-1;
    if (xMin>=camera_screen.width) xMin=camera_screen.width-1;
    if (yMax>=camera_screen.height) yMax=camera_screen.height-1;
    if (yMin>=camera_screen.height) yMin=camera_screen.height-1;

    for (y=yMin+(round<<1); y<=yMax-(round<<1); ++y)
    {
      draw_pixel(xMin, y, cl);
      draw_pixel(xMax, y, cl);
    }

    draw_hline(xMin+1+round, yMin, (xMax-1-round) - (xMin+1+round) + 1, cl);
    draw_hline(xMin+1+round, yMax, (xMax-1-round) - (xMin+1+round) + 1, cl);
}

//-------------------------------------------------------------------
void draw_rect(coord x1, coord y1, coord x2, coord y2, color cl) {
    draw_rectangle(x1,y1,x2,y2,cl&0xff,0);
}

void draw_rect_thick(coord x1, coord y1, coord x2, coord y2, color cl, int thickness) {
    int i;
    cl = cl & 0xff;
    for (i=0; i<thickness; i++)
    {
        draw_rectangle(x1+i,y1+i,x2-i,y2-i,cl,0);
    }
}

void draw_rect_shadow(coord x1, coord y1, coord x2, coord y2, color cl, int thickness) {
    int i;
    cl = cl & 0xff;
    for (i=0; i<thickness; i++)
    {
        draw_rectangle(x1+i,y1+i,x2+i,y2+i,cl,0);
    }
}
//-------------------------------------------------------------------
void draw_round_rect(coord x1, coord y1, coord x2, coord y2, color cl) { 
    draw_rectangle(x1,y1,x2,y2,cl&0xff,1);
} 

void draw_round_rect_thick(coord x1, coord y1, coord x2, coord y2, color cl, int thickness) { 
    int i;
    cl = cl & 0xff;
    draw_rectangle(x1,y1,x2,y2,cl,1);
    for (i=1; i<thickness; i++)
    {
        draw_rectangle(x1+i,y1+i,x2-i,y2-i,cl,0);
    }
} 
//-------------------------------------------------------------------
static void fill_rect(color cl) {
    register unsigned int x, y;

    cl = BG_COLOR(cl);
    for (y=yMin+1; y<=yMax-1; ++y)
    {
        draw_hline(xMin+1, y, (xMax-1) - (xMin+1) + 1, cl);
    }
}
//-------------------------------------------------------------------
void draw_filled_rect(coord x1, coord y1, coord x2, coord y2, color cl) {
    draw_rect(x1, y1, x2, y2, cl);
    fill_rect(cl);
}

void draw_filled_rect_thick(coord x1, coord y1, coord x2, coord y2, color cl, int thickness) {
    draw_rect_thick(x1, y1, x2, y2, cl, thickness);
    fill_rect(cl);
}
//-------------------------------------------------------------------
void draw_filled_round_rect(coord x1, coord y1, coord x2, coord y2, color cl) { 
    draw_round_rect(x1, y1, x2, y2, cl); 
    fill_rect(cl);
} 

void draw_filled_round_rect_thick(coord x1, coord y1, coord x2, coord y2, color cl, int thickness) { 
    draw_round_rect_thick(x1, y1, x2, y2, cl, thickness); 
    fill_rect(cl);
} 
//-------------------------------------------------------------------
void draw_char(coord x, coord y, const char ch, color cl)
{
    FontData *f = (FontData*)get_current_font_data(ch);
    const unsigned char *sym = (unsigned char*)f + sizeof(FontData) - f->offset;
    int i, ii;

    // First draw blank lines at top
    for (i=0; i<f->offset; i++)
        draw_hline(x, y+i, FONT_WIDTH, BG_COLOR(cl));
    // Now draw character data
    for (; i<f->offset+f->size; i++)
    {
	    for (ii=0; ii<FONT_WIDTH; ii++)
        {
            draw_pixel(x+ii ,y+i, (sym[i] & (0x80>>ii))? FG_COLOR(cl) : BG_COLOR(cl));
	    }
    }
    // Last draw blank lines at bottom
    for (; i<FONT_HEIGHT; i++)
        draw_hline(x, y+i, FONT_WIDTH, BG_COLOR(cl));
}

//-------------------------------------------------------------------
void draw_string(coord x, coord y, const char *s, color cl) {
    while(*s)
    {
	    draw_char(x, y, *s, cl);
	    s++;
	    x+=FONT_WIDTH;
	    if ((x>=camera_screen.width) && (*s))
        {
	        draw_char(x-FONT_WIDTH,y, '>', cl);
	        break;
	    }
    }
}

//-------------------------------------------------------------------
void draw_txt_rect(coord col, coord row, unsigned int length, unsigned int height, color cl) {
    draw_rect(col*FONT_WIDTH, row*FONT_HEIGHT, (col+length)*FONT_WIDTH-1, (row+height)*FONT_HEIGHT-1, cl);
}

//-------------------------------------------------------------------
void draw_txt_rect_exp(coord col, coord row, unsigned int length, unsigned int height, unsigned int exp, color cl) {
    draw_rect(col*FONT_WIDTH-exp, row*FONT_HEIGHT-exp, (col+length)*FONT_WIDTH-1+exp, (row+height)*FONT_HEIGHT-1+exp, cl);
}

//-------------------------------------------------------------------
void draw_txt_filled_rect(coord col, coord row, unsigned int length, unsigned int height, color cl) {
    draw_filled_rect(col*FONT_WIDTH, row*FONT_HEIGHT, (col+length)*FONT_WIDTH-1, (row+height)*FONT_HEIGHT-1, cl);
}

//-------------------------------------------------------------------
void draw_txt_filled_rect_exp(coord col, coord row, unsigned int length, unsigned int height, unsigned int exp, color cl) {
    draw_filled_rect(col*FONT_WIDTH-exp, row*FONT_HEIGHT-exp, (col+length)*FONT_WIDTH-1+exp, (row+height)*FONT_HEIGHT-1+exp, cl);
}

//-------------------------------------------------------------------
void draw_txt_string(coord col, coord row, const char *str, color cl) {
    draw_string(col*FONT_WIDTH, row*FONT_HEIGHT, str, cl);
}

//-------------------------------------------------------------------
void draw_txt_char(coord col, coord row, const char ch, color cl) {
    draw_char(col*FONT_WIDTH, row*FONT_HEIGHT, ch, cl);
}

// Restore CANON_OSD
//-------------------------------------------------------------------
void draw_restore() {
    vid_bitmap_refresh();

#ifdef CAM_DETECT_SCREEN_ERASE
    draw_set_guard();
#ifdef CAM_TOUCHSCREEN_UI
    redraw_buttons = 1;
#endif
#endif
}

//-------------------------------------------------------------------
void draw_circle(coord x, coord y, const unsigned int r, color cl) {
    int dx = 0;
    int dy = r;
    int p=(3-(r<<1));

    do {
        draw_pixel((x+dx),(y+dy),cl);
        draw_pixel((x+dy),(y+dx),cl);
        draw_pixel((x+dy),(y-dx),cl);
        draw_pixel((x+dx),(y-dy),cl);
        draw_pixel((x-dx),(y-dy),cl);
        draw_pixel((x-dy),(y-dx),cl);
        draw_pixel((x-dy),(y+dx),cl);
        draw_pixel((x-dx),(y+dy),cl);

        ++dx;

        if (p<0) 
            p += ((dx<<2)+6);
        else {
            --dy;
            p += (((dx-dy)<<2)+10);
        }
    } while (dx<=dy);
}

//-------------------------------------------------------------------
void draw_ellipse(coord xc, coord yc, unsigned int a, unsigned int b, color cl) {
    int x = 0, y = b;
    long a2 = (long)a*a, b2 = (long)b*b;
    long crit1 = -((a2>>2) + (a&1) + b2);
    long crit2 = -((b2>>2) + (b&1) + a2);
    long crit3 = -((b2>>2) + (b&1));
    long t = -a2*y;
    long dxt = b2*x*2, dyt = -2*a2*y;
    long d2xt = b2*2, d2yt = a2*2;

    while (y>=0 && x<=a) {
        draw_pixel(xc+x, yc+y, cl);
        if (x!=0 || y!=0)
            draw_pixel(xc-x, yc-y, cl);
        if (x!=0 && y!=0) {
            draw_pixel(xc+x, yc-y, cl);
            draw_pixel(xc-x, yc+y, cl);
        }
        if (t + b2*x <= crit1 || t + a2*y <= crit3)
            ++x, dxt += d2xt, t += dxt;
        else if (t - a2*y > crit2)
            --y, dyt += d2yt, t += dyt;
        else {
            ++x, dxt += d2xt, t += dxt;
            --y, dyt += d2yt, t += dyt;
        }
   }
}

//-------------------------------------------------------------------
void draw_filled_ellipse(coord xc, coord yc, unsigned int a, unsigned int b, color cl) {
    int x = 0, y = b;
    int rx = x, ry = y;
    unsigned int width = 1;
    unsigned int height = 1;
    long a2 = (long)a*a, b2 = (long)b*b;
    long crit1 = -((a2>>2) + (a&1) + b2);
    long crit2 = -((b2>>2) + (b&1) + a2);
    long crit3 = -((b2>>2) + (b&1));
    long t = -a2*y;
    long dxt = 2*b2*x, dyt = -2*a2*y;
    long d2xt = 2*b2, d2yt = 2*a2;
    
    color cl_fill = MAKE_COLOR(BG_COLOR(cl), BG_COLOR(cl));

    if (b == 0) {
        draw_filled_rect(xc-a, yc, (a<<1)+1, 1, cl_fill);
    } else {
        while (y>=0 && x<=a) {
            if (t + b2*x <= crit1 || t + a2*y <= crit3) {
                if (height == 1)
                    ; /* draw nothing */
                else if (ry*2+1 > (height-1)*2) {
                    draw_filled_rect(xc-rx, yc-ry, xc-rx+width-1, yc-ry+(height-1)-1, cl_fill);
                    draw_filled_rect(xc-rx, yc+ry+1, xc-rx+width-1, yc+ry+1+(1-height)-1, cl_fill);
                    ry -= height-1;
                    height = 1;
                }
                else {
                    draw_filled_rect(xc-rx, yc-ry, xc-rx+width-1, yc-ry+(ry*2+1)-1, cl_fill);
                    ry -= ry;
                    height = 1;
                }
                ++x, dxt += d2xt, t += dxt;
                rx++;
                width += 2;
            }
            else if (t - a2*y > crit2) {
                --y, dyt += d2yt, t += dyt;
                height++;
            }
            else {
                if (ry*2+1 > height*2) {
                    draw_filled_rect(xc-rx, yc-ry, xc-rx+width-1, yc-ry+height-1, cl_fill);
                    draw_filled_rect(xc-rx, yc+ry+1, xc-rx+width-1, yc+ry+1-height-1, cl_fill);
                }
                else {
                    draw_filled_rect(xc-rx, yc-ry, xc-rx+width-1, yc-ry+(ry*2+1)-1, cl_fill);
                }
                ++x, dxt += d2xt, t += dxt;
                --y, dyt += d2yt, t += dyt;
                rx++;
                width += 2;
                ry -= height;
                height = 1;
            }
        }

        if (ry > height) {
            draw_filled_rect(xc-rx, yc-ry, xc-rx+width-1, yc-ry+height-1, cl_fill);
            draw_filled_rect(xc-rx, yc+ry+1, xc-rx+width-1, yc+ry+1-height-1, cl_fill);
        }
        else {
            draw_filled_rect(xc-rx, yc-ry, xc-rx+width-1, yc-ry+(ry*2+1)-1, cl_fill);
        }
    }
}
//-------------------------------------------------------------------

// Colors for icons
// 3 shades for each color
//  icon_xxx[0] = dark, icon_xxx[1] = medium, icon_xxx[2] = light
color icon_green[3], icon_red[3], icon_yellow[3], icon_grey[3];

void draw_get_icon_colors()
{
    if((mode_get()&MODE_MASK) == MODE_REC)
    {
        icon_green[0]  = COLOR_ICON_REC_GREEN_DK;  icon_green[1]  = COLOR_ICON_REC_GREEN;  icon_green[2]  = COLOR_ICON_REC_GREEN_LT;
        icon_yellow[0] = COLOR_ICON_REC_YELLOW_DK; icon_yellow[1] = COLOR_ICON_REC_YELLOW; icon_yellow[2] = COLOR_ICON_REC_YELLOW_LT;
        icon_red[0]    = COLOR_ICON_REC_RED_DK;    icon_red[1]    = COLOR_ICON_REC_RED;    icon_red[2]    = COLOR_ICON_REC_RED_LT;
        icon_grey[0]   = COLOR_ICON_REC_GREY_DK;   icon_grey[1]   = COLOR_ICON_REC_GREY;   icon_grey[2]   = COLOR_ICON_REC_GREY_LT;
    }
    else
    {
        icon_green[0]  = COLOR_ICON_PLY_GREEN_DK;  icon_green[1]  = COLOR_ICON_PLY_GREEN;  icon_green[2]  = COLOR_ICON_PLY_GREEN_LT;
        icon_yellow[0] = COLOR_ICON_PLY_YELLOW_DK; icon_yellow[1] = COLOR_ICON_PLY_YELLOW; icon_yellow[2] = COLOR_ICON_PLY_YELLOW_LT;
        icon_red[0]    = COLOR_ICON_PLY_RED_DK;    icon_red[1]    = COLOR_ICON_PLY_RED;    icon_red[2]    = COLOR_ICON_PLY_RED_LT;
        icon_grey[0]   = COLOR_ICON_PLY_GREY_DK;   icon_grey[1]   = COLOR_ICON_PLY_GREY;   icon_grey[2]   = COLOR_ICON_PLY_GREY_LT;
    }
}
