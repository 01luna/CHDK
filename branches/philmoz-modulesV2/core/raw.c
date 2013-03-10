#include "platform.h"
#include "raw_buffer.h"
#include "conf.h"
#include "stdlib.h"
#include "raw.h"
#include "console.h"
#include "math.h"
#include "modules.h"
#include "shot_histogram.h"

//-------------------------------------------------------------------
#define RAW_TARGET_DIRECTORY    "A/DCIM/%03dCANON"
//#define RAW_TMP_FILENAME        "HDK_RAW.TMP"
#define RAW_TARGET_FILENAME     "%s%04d%s"
#define RAW_BRACKETING_FILENAME "%s%04d_%02d%s" 

//-------------------------------------------------------------------
static char fn[64];
static char dir[32];
static int develop_raw=0;

//-------------------------------------------------------------------
void raw_prepare_develop(const char* filename) {
    if (filename) {
        develop_raw=1;
        strcpy(fn,filename);
    } else {
        develop_raw=0;
    }
}

//-------------------------------------------------------------------
void patch_bad_pixels(void);
//-------------------------------------------------------------------

char* get_raw_image_addr(void) {
    if (!conf.raw_cache) return hook_raw_image_addr();
    else return (char*) ((int)hook_raw_image_addr()&~CAM_UNCACHED_BIT);
}

char* get_alt_raw_image_addr(void) {    // return inactive buffer for cameras with multiple RAW buffers (otherwise return active buffer)
    if (!conf.raw_cache) return hook_alt_raw_image_addr();
    else return (char*) ((int)hook_alt_raw_image_addr()&~CAM_UNCACHED_BIT);
}
//-------------------------------------------------------------------

// Set in raw_savefile and used in get_raw_pixel & set_raw_pixel (for performance)
// Don't call set/get_raw_pixel until this value is initialised
static char *rawadr;    // Pointer to current raw image buffer

int raw_savefile()
{
    int ret = 0;
    int fd;
    static struct utimbuf t;
    static int br_counter; 

    // Get pointers to RAW buffers (will be the same on cameras that don't have two or more buffers)
    rawadr = get_raw_image_addr();
    char *altrawadr = get_alt_raw_image_addr();

#if DNG_SUPPORT
    if (conf.save_raw && conf.dng_raw && is_raw_enabled())
    {                             
        libdng->capture_data_for_exif();
	}
#endif    
    if (camera_info.state.state_kbd_script_run && shot_histogram_isenabled()) build_shot_histogram();

#if DNG_SUPPORT
    // count/save badpixels if requested
    if (libdng->raw_init_badpixel_bin())
    {
        return 0;
    }
#endif    

    if (develop_raw)
    {
        started();
        fd = open(fn, O_RDONLY, 0777);
        if (fd>=0) {
            read(fd, rawadr, camera_sensor.raw_size);
            close(fd);
        }
#ifdef OPT_CURVES
        if (conf.curve_enable)
            libcurves->curve_apply();
#endif
        finished();
        develop_raw=0;
        return 0;
    }

    if (conf.bad_pixel_removal) patch_bad_pixels();

    shooting_bracketing();

    if (conf.tv_bracket_value || conf.av_bracket_value || conf.iso_bracket_value || conf.subj_dist_bracket_value)
    {
        if (camera_info.state.state_shooting_progress != SHOOTING_PROGRESS_PROCESSING)
            br_counter = 1;
        else
            br_counter++;
    }
    else
        br_counter=0;

    // got here second time in a row. Skip second RAW saving.
    if (conf.raw_save_first_only && camera_info.state.state_shooting_progress == SHOOTING_PROGRESS_PROCESSING)
    {
        return 0;
    }

    camera_info.state.state_shooting_progress = SHOOTING_PROGRESS_PROCESSING;

    if (conf.save_raw && is_raw_enabled())
    {
        int timer; char txt[30];

        started();

        t.actime = t.modtime = time(NULL);

        mkdir_if_not_exist("A/DCIM");
        if (conf.raw_in_dir)
            get_target_dir_name(dir);
        else
            sprintf(dir, RAW_TARGET_DIRECTORY, 100);

        mkdir_if_not_exist(dir);

        sprintf(fn, "%s/", dir);
        if(br_counter && conf.bracketing_add_raw_suffix && (shooting_get_drive_mode()!=1)) {
            sprintf(fn+strlen(fn), 
                    RAW_BRACKETING_FILENAME,
                    img_prefixes[conf.raw_prefix],
                    get_target_file_num(),
                    br_counter,
                    conf.dng_raw&&conf.raw_dng_ext ? ".DNG" : img_exts[conf.raw_ext]);
        } else {
            sprintf(fn+strlen(fn),
                    RAW_TARGET_FILENAME,
                    img_prefixes[conf.raw_prefix],
                    get_target_file_num(),
                    conf.dng_raw&&conf.raw_dng_ext ? ".DNG" : img_exts[conf.raw_ext]);
        }
        fd = open(fn, O_WRONLY|O_CREAT, 0777);
        if (fd>=0) {
            timer=get_tick_count();
#if DNG_SUPPORT
            if (conf.dng_raw)
            {
                libdng->write_dng(fd, rawadr, altrawadr, CAM_UNCACHED_BIT );
            }
            else 
            {
                // Write active RAW buffer
                write(fd, (char*)(((unsigned long)rawadr)|CAM_UNCACHED_BIT), camera_sensor.raw_size);
            }
            close(fd);
            utime(fn, &t);
#else
            // Write active RAW buffer
            write(fd, (char*)(((unsigned long)rawadr)|CAM_UNCACHED_BIT), camera_sensor.raw_size);
            close(fd);
            utime(fn, &t);
#endif
            if (conf.raw_timer) {
                timer=get_tick_count()-timer;
                sprintf(txt, "saving time=%d", timer);
                console_add_line(txt);
            }
        }

        finished();

        ret = (fd >= 0);
    }

#ifdef OPT_CURVES
    if (conf.curve_enable)
        libcurves->curve_apply();
#endif
    return ret;
}

//-------------------------------------------------------------------
void raw_postprocess() {
}

//-------------------------------------------------------------------

void set_raw_pixel(unsigned int x, unsigned int y, unsigned short value) {
#if CAM_SENSOR_BITS_PER_PIXEL==10
    unsigned char* addr=(unsigned char*)rawadr+y*camera_sensor.raw_rowlen+(x/8)*10;
    switch (x%8) {
        case 0: addr[0]=(addr[0]&0x3F)|(value<<6); addr[1]=value>>2;                  break;
        case 1: addr[0]=(addr[0]&0xC0)|(value>>4); addr[3]=(addr[3]&0x0F)|(value<<4); break;
        case 2: addr[2]=(addr[2]&0x03)|(value<<2); addr[3]=(addr[3]&0xF0)|(value>>6); break;
        case 3: addr[2]=(addr[2]&0xFC)|(value>>8); addr[5]=value;                     break;
        case 4: addr[4]=value>>2;                  addr[7]=(addr[7]&0x3F)|(value<<6); break;
        case 5: addr[6]=(addr[6]&0x0F)|(value<<4); addr[7]=(addr[7]&0xC0)|(value>>4); break;
        case 6: addr[6]=(addr[6]&0xF0)|(value>>6); addr[9]=(addr[9]&0x03)|(value<<2); break;
        case 7: addr[8]=value;                     addr[9]=(addr[9]&0xFC)|(value>>8); break;
    }
#elif CAM_SENSOR_BITS_PER_PIXEL==12
    unsigned char* addr=(unsigned char*)rawadr+y*camera_sensor.raw_rowlen+(x/4)*6;
    switch (x%4) {
        case 0: addr[0] = (addr[0]&0x0F) | (unsigned char)(value << 4);  addr[1] = (unsigned char)(value >> 4);  break;
        case 1: addr[0] = (addr[0]&0xF0) | (unsigned char)(value >> 8);  addr[3] = (unsigned char)value;         break;
        case 2: addr[2] = (unsigned char)(value >> 4);  addr[5] = (addr[5]&0x0F) | (unsigned char)(value << 4);  break;
        case 3: addr[4] = (unsigned char)value; addr[5] = (addr[5]&0xF0) | (unsigned char)(value >> 8);  break;
    }
#elif CAM_SENSOR_BITS_PER_PIXEL==14
    unsigned char* addr=(unsigned char*)rawadr+y*camera_sensor.raw_rowlen+(x/8)*14;
    switch (x%8) {
        case 0: addr[ 0]=(addr[0]&0x03)|(value<< 2); addr[ 1]=value>>6;                                                         break;
        case 1: addr[ 0]=(addr[0]&0xFC)|(value>>12); addr[ 2]=(addr[ 2]&0x0F)|(value<< 4); addr[ 3]=value>>4;                   break;
        case 2: addr[ 2]=(addr[2]&0xF0)|(value>>10); addr[ 4]=(addr[ 4]&0x3F)|(value<< 6); addr[ 5]=value>>2;                   break;
        case 3: addr[ 4]=(addr[4]&0xC0)|(value>> 8); addr[ 7]=value;                                                            break;
        case 4: addr[ 6]=value>>6;                   addr[ 9]=(addr[ 9]&0x03)|(value<< 2);                                      break;
        case 5: addr[ 8]=value>>4;                   addr[ 9]=(addr[ 9]&0x3F)|(value>>12); addr[11]=(addr[11]&0x0F)|(value<<4); break;
        case 6: addr[10]=value>>2;                   addr[11]=(addr[11]&0xF0)|(value>>10); addr[13]=(addr[13]&0x3F)|(value<<6); break;
        case 7: addr[12]=value;                      addr[13]=(addr[13]&0xC0)|(value>> 8);                                      break;
    }
#else 
    #error define set_raw_pixel for sensor bit depth
#endif
}

//-------------------------------------------------------------------
unsigned short get_raw_pixel(unsigned int x,unsigned  int y) {
#if CAM_SENSOR_BITS_PER_PIXEL==10
    unsigned char* addr=(unsigned char*)rawadr+y*camera_sensor.raw_rowlen+(x/8)*10;
    switch (x%8) {
        case 0: return ((0x3fc&(((unsigned short)addr[1])<<2)) | (addr[0] >> 6));
        case 1: return ((0x3f0&(((unsigned short)addr[0])<<4)) | (addr[3] >> 4));
        case 2: return ((0x3c0&(((unsigned short)addr[3])<<6)) | (addr[2] >> 2));
        case 3: return ((0x300&(((unsigned short)addr[2])<<8)) | (addr[5]));
        case 4: return ((0x3fc&(((unsigned short)addr[4])<<2)) | (addr[7] >> 6));
        case 5: return ((0x3f0&(((unsigned short)addr[7])<<4)) | (addr[6] >> 4));
        case 6: return ((0x3c0&(((unsigned short)addr[6])<<6)) | (addr[9] >> 2));
        case 7: return ((0x300&(((unsigned short)addr[9])<<8)) | (addr[8]));
    }
#elif CAM_SENSOR_BITS_PER_PIXEL==12
    unsigned char* addr=(unsigned char*)rawadr+y*camera_sensor.raw_rowlen+(x/4)*6;
    switch (x%4) {
        case 0: return ((unsigned short)(addr[1])        << 4) | (addr[0] >> 4);
        case 1: return ((unsigned short)(addr[0] & 0x0F) << 8) | (addr[3]);
        case 2: return ((unsigned short)(addr[2])        << 4) | (addr[5] >> 4);
        case 3: return ((unsigned short)(addr[5] & 0x0F) << 8) | (addr[4]);
    }
#elif CAM_SENSOR_BITS_PER_PIXEL==14
    unsigned char* addr=(unsigned char*)rawadr+y*camera_sensor.raw_rowlen+(x/8)*14;
    switch (x%8) {
        case 0: return ((unsigned short)(addr[ 1])        <<  6) | (addr[ 0] >> 2);
        case 1: return ((unsigned short)(addr[ 0] & 0x03) << 12) | (addr[ 3] << 4) | (addr[ 2] >> 4);
        case 2: return ((unsigned short)(addr[ 2] & 0x0F) << 10) | (addr[ 5] << 2) | (addr[ 4] >> 6);
        case 3: return ((unsigned short)(addr[ 4] & 0x3F) <<  8) | (addr[ 7]);
        case 4: return ((unsigned short)(addr[ 6])        <<  6) | (addr[ 9] >> 2);
        case 5: return ((unsigned short)(addr[ 9] & 0x03) << 12) | (addr[ 8] << 4) | (addr[11] >> 4);
        case 6: return ((unsigned short)(addr[11] & 0x0F) << 10) | (addr[10] << 2) | (addr[13] >> 6);
        case 7: return ((unsigned short)(addr[13] & 0x3F) <<  8) | (addr[12]);
    }
#else 
    #error define get_raw_pixel for sensor bit depth
#endif
    return 0;
}

//-------------------------------------------------------------------
void patch_bad_pixel(unsigned int x,unsigned  int y) {
    int sum=0;
    int nzero=0;
    int i,j;
    int val;
    if ((x>=2) && (x<camera_sensor.raw_rowpix-2) && (y>=2) && (y<camera_sensor.raw_rows-2)) {
        if ((conf.bad_pixel_removal==1) || (conf.save_raw && conf.dng_raw)) {  // interpolation or DNG saving
            for (i=-2; i<=2; i+=2)
                for (j=-2; j<=2; j+=2)
                    if ((i!=0) && (j!=0)) {
                        val=get_raw_pixel(x+i, y+j);
                        if (val) {sum+=val; nzero++;}
                    }
                if (nzero) set_raw_pixel(x,y,sum/nzero);
        } else if (conf.bad_pixel_removal==2)  // or this makes RAW converter (internal/external)
            set_raw_pixel(x,y,0);
    }
}

struct point{
    int x;
    int y;
    struct point *next;
} *pixel_list=NULL;

void patch_bad_pixels(void) {
    struct point *pixel=pixel_list;
    while (pixel) {
        patch_bad_pixel((*pixel).x,(*pixel).y);
        pixel=(*pixel).next;
    }
}

#define PIXELS_BUF_SIZE 8192
int make_pixel_list(char * ptr, int size) {
    int x,y;
    struct point *pixel;
    char *endptr;
	
	if ( size <=0 ) return 0;
	if ( size >PIXELS_BUF_SIZE ) ptr[PIXELS_BUF_SIZE]=0;

    while(*ptr) {
        while (*ptr==' ' || *ptr=='\t') ++ptr;    // whitespaces
        x=strtol(ptr, &endptr, 0);
        if (endptr != ptr) {
            ptr = endptr;
            if (*ptr++==',') {
                while (*ptr==' ' || *ptr=='\t') ++ptr;    // whitespaces
                    if (*ptr!='\n' && *ptr!='\r') {
                        y=strtol(ptr, &endptr, 0);
                        if (endptr != ptr) {
                            ptr = endptr;
                            pixel=malloc(sizeof(struct point));
                            if (pixel) {
                                (*pixel).x=x;
                                (*pixel).y=y;
                                (*pixel).next=pixel_list;
                                pixel_list=pixel;
                            }
                        }
                    }
                }
        }
        while (*ptr && *ptr!='\n') ++ptr;    // unless end of line
        if (*ptr) ++ptr;
    }
	return 0;
}
