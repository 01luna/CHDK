#include "camera_info.h"
#include "stdlib.h"
#include "debug_led.h"
#include "sd_card.h"
#include "gui_mbox.h"
#include "raw.h"
#include "gui_lang.h"
#include "lang.h"
#include "conf.h"

#include "raw_merge.h"
#include "module_def.h"

#define TEMP_FILE_NAME   "A/raw16.tmp"
#define TEMP_FILE_NAME_1 "A/raw16_1.tmp"

static int running = 0;
static int raw_action;
static int raw_count;
static unsigned short *row;
static unsigned char *rawrow;
static char namebuf[100];

// note: if processing with dcraw etc, zeros may get replaced with interpolated values
// this may or may not be what you want
static int raw_subtract_values(int from, int sub) {
/*    if ( sub > conf.sub_in_dark_value ) {
        int result = from - sub;
        if ( result < conf.sub_out_dark_value ) {
            return conf.sub_out_dark_value;
        }
        else {
            return result;
        }
    }
    else {
        return from;
    }*/

 int result;
 if ((from==0) || (sub==0)) return 0; // bad pixel
 result = from - sub + camera_sensor.black_level;
 if (result<camera_sensor.black_level) result=camera_sensor.black_level;
 if (result>camera_sensor.white_level) result=camera_sensor.white_level;
 return result;

}
/* subtract "sub" from "from" and store the result in "dest"*/
/* TODO allow replacing if dest == from or sub*/
int raw_subtract(const char *from, const char *sub, const char *dest) {
    unsigned req=(camera_sensor.raw_size>>10) + 1;
    unsigned avail=GetFreeCardSpaceKb();
    FILE *ffrom = NULL, *fsub = NULL, *fdest = NULL;
    char *baccum = 0,*bsub = 0;
    int status = 0;
    unsigned short s,d;
    int i,j;

    static struct utimbuf t;

    struct stat st;

    if (stat((char *)from,&st) != 0 || st.st_size!=camera_sensor.raw_size) 
        return 0;

    if (stat((char *)sub,&st) != 0 || st.st_size!=camera_sensor.raw_size) 
        return 0;

    running = 1;

     if( (baccum=malloc(camera_sensor.raw_rowlen)) &&
        (bsub=malloc(camera_sensor.raw_rowlen)) &&
        (ffrom=fopen(from, "rb")) &&
        (fsub=fopen(sub, "rb")) &&
        (fdest=fopen(dest, "wb")) &&
        avail > req)
    {
        started();
        for (j = 0; j < camera_sensor.raw_rows; j++) {
            fread(baccum,1, camera_sensor.raw_rowlen,ffrom);
            fread(bsub,1, camera_sensor.raw_rowlen,fsub);

#if CAM_MODULE_SENSOR_BITS_PER_PIXEL==10

            for(i = 0;i<camera_sensor.raw_rowlen; i+=10) {
                s =((0x3fc&(((unsigned short)bsub[i+1])<<2)) | (bsub[i+0] >> 6));
                d =((0x3fc&(((unsigned short)baccum[i+1])<<2)) | (baccum[i+0] >> 6));
                d = raw_subtract_values(d,s);
                baccum[i]=(baccum[i]&0x3F)|(d<<6); 
                baccum[i+1]=d>>2;

                s =((0x3f0&(((unsigned short)bsub[i+0])<<4)) | (bsub[i+3] >> 4));
                d =((0x3f0&(((unsigned short)baccum[i+0])<<4)) | (baccum[i+3] >> 4));
                d = raw_subtract_values(d,s);
                baccum[i]=(baccum[i]&0xC0)|(d>>4);
                baccum[i+3]=(baccum[i+3]&0x0F)|(d<<4);

                s =((0x3c0&(((unsigned short)bsub[i+3])<<6)) | (bsub[i+2] >> 2));
                d =((0x3c0&(((unsigned short)baccum[i+3])<<6)) | (baccum[i+2] >> 2));
                d = raw_subtract_values(d,s);
                baccum[i+2]=(baccum[i+2]&0x03)|(d<<2);
                baccum[i+3]=(baccum[i+3]&0xF0)|(d>>6);

                s =((0x300&(((unsigned short)bsub[i+2])<<8)) | (bsub[i+5])); 
                d =((0x300&(((unsigned short)baccum[i+2])<<8)) | (baccum[i+5])); 
                d = raw_subtract_values(d,s);
                baccum[i+2]=(baccum[i+2]&0xFC)|(d>>8); 
                baccum[i+5]=d;


                s =((0x3fc&(((unsigned short)bsub[i+4])<<2)) | (bsub[i+7] >> 6)); 
                d =((0x3fc&(((unsigned short)baccum[i+4])<<2)) | (baccum[i+7] >> 6)); 
                d = raw_subtract_values(d,s);
                baccum[i+4]=d>>2;
                baccum[i+7]=(baccum[i+7]&0x3F)|(d<<6);


                s =((0x3f0&(((unsigned short)bsub[i+7])<<4)) | (bsub[i+6] >> 4)); 
                d =((0x3f0&(((unsigned short)baccum[i+7])<<4)) | (baccum[i+6] >> 4)); 
                d = raw_subtract_values(d,s);
                baccum[i+6]=(baccum[i+6]&0x0F)|(d<<4);
                baccum[i+7]=(baccum[i+7]&0xC0)|(d>>4);

                s =((0x3c0&(((unsigned short)bsub[i+6])<<6)) | (bsub[i+9] >> 2)); 
                d =((0x3c0&(((unsigned short)baccum[i+6])<<6)) | (baccum[i+9] >> 2)); 
                d = raw_subtract_values(d,s);
                baccum[i+6]=(baccum[i+6]&0xF0)|(d>>6);
                baccum[i+9]=(baccum[i+9]&0x03)|(d<<2);


                s =((0x300&(((unsigned short)bsub[i+9])<<8)) | (bsub[i+8])); 
                d =((0x300&(((unsigned short)baccum[i+9])<<8)) | (baccum[i+8])); 
                d = raw_subtract_values(d,s);
                baccum[i+8]=d;
                baccum[i+9]=(baccum[i+9]&0xFC)|(d>>8);
            }

#elif CAM_MODULE_SENSOR_BITS_PER_PIXEL==12

            for(i = 0;i<camera_sensor.raw_rowlen; i+=6) {

                s=((0xFF0&(((unsigned short)bsub[i+1])<<4))   | (bsub[i+0] >> 4));
                d=((0xFF0&(((unsigned short)baccum[i+1])<<4)) | (baccum[i+0] >> 4));
                d = raw_subtract_values(d,s);
                baccum[i+0]=(baccum[i+0]&0x0F)|(d<<4);
                baccum[i+1]=d>>4;

                s=((0xF00&(((unsigned short)bsub[i+0])<<8))   | (bsub[i+3]     ));
                d=((0xF00&(((unsigned short)baccum[i+0])<<8)) | (baccum[i+3]   ));
                d = raw_subtract_values(d,s);
                baccum[i+0]=(baccum[i+0]&0xF0)|(d>>8);
                baccum[i+3]=d;

                s=((0xFF0&(((unsigned short)bsub[i+2])<<4))   | (bsub[i+5] >> 4));
                d=((0xFF0&(((unsigned short)baccum[i+2])<<4)) | (baccum[i+5] >> 4));
                d = raw_subtract_values(d,s);
                baccum[i+2]=d>>4;
                baccum[i+5]=(baccum[i+5]&0x0F)|(d<<4);

                s=((0xF00&(((unsigned short)bsub[i+5])<<8))   | (bsub[i+4]     ));
                d=((0xF00&(((unsigned short)baccum[i+5])<<8)) | (baccum[i+4]     ));
                d = raw_subtract_values(d,s);
                baccum[i+4]=d;
                baccum[i+5]=(baccum[i+5]&0xF0)|(d>>8);
            }

#else 
 #error define set_raw_pixel for sensor bit depth
#endif

            fwrite(baccum,1,camera_sensor.raw_rowlen,fdest);
            if ( (j & 0x1F) == 0 ) {
                gui_browser_progress_show((char *)dest, j*100/camera_sensor.raw_rows);
            }
        }
        gui_browser_progress_show((char *)dest, 100);
        finished();
        status = 1;
    }
    free(baccum);
    free(bsub);
    if(ffrom)
        fclose(ffrom);
    if(fsub)
        fclose(fsub);
    if(fdest) {
        fclose(fdest);
        t.actime = t.modtime = time(NULL);
        utime((char *)dest, &t);
    }
    running = 0;
    return status;
}

int raw_merge_start(int action){
  unsigned int req, avail;
  req=((camera_sensor.raw_rowpix*camera_sensor.raw_rows)>>18)+1;
  avail=GetFreeCardSpaceKb()>>10;
  if (avail<req) {
    sprintf(namebuf,lang_str(LANG_AVERAGE_NO_CARD_SPACE),req,avail);
    gui_mbox_init((int)"", (int)namebuf, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
    return 0;
  }
  raw_action=action;
  raw_count=0;
  row=malloc(camera_sensor.raw_rowpix*sizeof(unsigned short));
  if (!row)
    return 0;
  rawrow=malloc(camera_sensor.raw_rowlen);
  if (!rawrow) {
    free(row);
    return 0;
  }
	running = 1;
  return 1;
}

int raw_merge_add_file(const char * filename) {
  int  src,i,j,nrow;
  FILE *fbrawin=NULL,*fbrawout,*fcraw;
  struct stat st;

  if (!filename)
    return 0;

  stat(filename,&st);
  if (st.st_size!=camera_sensor.raw_size)
    return 0;

  started();

  fcraw=fopen(filename,"rb");
  if (fcraw) {
    if (raw_count)
      fbrawin=fopen(TEMP_FILE_NAME,"rb");
    if (!raw_count || fbrawin){
      fbrawout=fopen(TEMP_FILE_NAME_1,"w+b");
      if (fbrawout){
        for (nrow=0,j=0;nrow<camera_sensor.raw_rows;nrow++,j++){
          if (raw_count)
            fread(row, 1, camera_sensor.raw_rowpix*sizeof(unsigned short), fbrawin);
          else
            for (i=0;i<camera_sensor.raw_rowpix;i++)
              row[i]=0;
          fread(rawrow, 1, camera_sensor.raw_rowlen, fcraw);

#if CAM_MODULE_SENSOR_BITS_PER_PIXEL==10

          for (i=0,src=0; i<camera_sensor.raw_rowpix; i+=8, src+=10){
            row[i+0]+=((0x3fc&(((unsigned short)rawrow[src+1])<<2)) | (rawrow[src+0] >> 6));
            row[i+1]+=((0x3f0&(((unsigned short)rawrow[src+0])<<4)) | (rawrow[src+3] >> 4));
            row[i+2]+=((0x3c0&(((unsigned short)rawrow[src+3])<<6)) | (rawrow[src+2] >> 2));
            row[i+3]+=((0x300&(((unsigned short)rawrow[src+2])<<8)) | (rawrow[src+5])); 
            row[i+4]+=((0x3fc&(((unsigned short)rawrow[src+4])<<2)) | (rawrow[src+7] >> 6)); 
            row[i+5]+=((0x3f0&(((unsigned short)rawrow[src+7])<<4)) | (rawrow[src+6] >> 4)); 
            row[i+6]+=((0x3c0&(((unsigned short)rawrow[src+6])<<6)) | (rawrow[src+9] >> 2)); 
            row[i+7]+=((0x300&(((unsigned short)rawrow[src+9])<<8)) | (rawrow[src+8])); 
          }

#elif CAM_MODULE_SENSOR_BITS_PER_PIXEL==12

          for (i=0,src=0; i<camera_sensor.raw_rowpix; i+=4, src+=6){
            row[i+0]+=((0xFF0&(((unsigned short)rawrow[src+1])<<4)) | (rawrow[src+0] >> 4));
            row[i+1]+=((0xF00&(((unsigned short)rawrow[src+0])<<8)) | (rawrow[src+3]     ));
            row[i+2]+=((0xFF0&(((unsigned short)rawrow[src+2])<<4)) | (rawrow[src+5] >> 4));
            row[i+3]+=((0xF00&(((unsigned short)rawrow[src+5])<<8)) | (rawrow[src+4]     ));
          }

#else
 #error define set_raw_pixel for sensor bit depth
#endif

          fwrite(row, 1, camera_sensor.raw_rowpix*sizeof(unsigned short), fbrawout);
          if (j>=camera_sensor.raw_rows/10) {
            j-=camera_sensor.raw_rows/10;
            gui_browser_progress_show(filename, nrow*100/camera_sensor.raw_rows);
          }
        }
        raw_count++;
        strcpy(namebuf,filename);
        fclose(fbrawout);
      }
      if (fbrawin)
        fclose(fbrawin);
    }
    fclose(fcraw);
  } 
  remove(TEMP_FILE_NAME);
  rename(TEMP_FILE_NAME_1,TEMP_FILE_NAME);
  finished();
  return 1;
}

void raw_merge_end(void) {
  int src,i,j,nrow;
  FILE *fbraw, *fcraw;
  static struct utimbuf t;
  if (!raw_count) {
    free(rawrow);
    free(row);
    return;
  } 
  i=strlen(namebuf)-3;
  if (strncmp(namebuf+i,"CR",2)==0)
    strcpy(namebuf+i,"WAV");
  else
    strcpy(namebuf+i,"CRW");

  started();
  fbraw=fopen(TEMP_FILE_NAME,"r+b");
  if (fbraw) {
    fcraw=fopen(namebuf,"w+b");
    if (fcraw) {
      for (nrow=0,j=0;nrow<camera_sensor.raw_rows;nrow++,j++) {
        fread(row, 1, camera_sensor.raw_rowpix*sizeof(unsigned short), fbraw);

        if (raw_count>1) {
          for (i=0;i<camera_sensor.raw_rowpix;i++) {
            if (raw_action==RAW_OPERATION_AVERAGE)
              row[i]/=raw_count;
            else {
              if (row[i]>camera_sensor.black_level*(raw_count-1))
                row[i]-=camera_sensor.black_level*(raw_count-1);
              else
                row[i]=0;
              if (row[i]>camera_sensor.white_level)
                row[i]=camera_sensor.white_level;
            }
          }  
        }
#if CAM_MODULE_SENSOR_BITS_PER_PIXEL==10
        for (i=0,src=0;i<camera_sensor.raw_rowpix;i+=8,src+=10) {
          rawrow[src+0]=(row[i+0]<<6)|(row[i+1]>>4);
          rawrow[src+1]=(row[i+0]>>2);
          rawrow[src+2]=(row[i+2]<<2)|(row[i+3]>>8);
          rawrow[src+3]=(row[i+1]<<4)|(row[i+2]>>6);
          rawrow[src+4]=(row[i+4]>>2);
          rawrow[src+5]=(row[i+3]);
          rawrow[src+6]=(row[i+5]<<4)|(row[i+6]>>6);
          rawrow[src+7]=(row[i+4]<<6)|(row[i+5]>>4);
          rawrow[src+8]=(row[i+7]);
          rawrow[src+9]=(row[i+6]<<2)|(row[i+7]>>8);
        }
#elif CAM_MODULE_SENSOR_BITS_PER_PIXEL==12
        for (i=0,src=0; i<camera_sensor.raw_rowpix; i+=4, src+=6){
          rawrow[src+0]=(row[i+0]<<4)|(row[i+1]>>8);
          rawrow[src+1]=(row[i+0]>>4);
          rawrow[src+2]=(row[i+2]>>4);
          rawrow[src+3]= row[i+1];
          rawrow[src+4]= row[i+3];
          rawrow[src+5]=(row[i+2]<<4)|(row[i+3]>>8);
        }
#else 
 #error define set_raw_pixel for sensor bit depth
#endif

        fwrite(rawrow, 1, camera_sensor.raw_rowlen, fcraw);
        if (j>=camera_sensor.raw_rows/5) {
          j-=camera_sensor.raw_rows/5;
          gui_browser_progress_show(namebuf, nrow*100/camera_sensor.raw_rows);
        }
      }
      fclose(fcraw);
    }
    fclose(fbraw);
  }

  t.actime = t.modtime = time(NULL);
  utime(namebuf, &t);
  remove(TEMP_FILE_NAME);

  finished();
  free(rawrow);
  free(row);

    running = 0;
}


// =========  MODULE INIT =================

/***************** BEGIN OF AUXILARY PART *********************
  ATTENTION: DO NOT REMOVE OR CHANGE SIGNATURES IN THIS SECTION
 **************************************************************/

int _module_can_unload()
{
    return running == 0;
}

/******************** Module Information structure ******************/

librawop_sym _librawop = 
{
    {
         0, 0, _module_can_unload, 0, 0
    },

    raw_merge_start,
    raw_merge_add_file,
    raw_merge_end,
    raw_subtract
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    {2,0},						// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

#if CAM_MODULE_SENSOR_BITS_PER_PIXEL==10
    (int32_t)"RAW operations-10bpp(dll)",// Module name
#else
    (int32_t)"RAW operations-12bpp(dll)",// Module name
#endif
#if CAM_MODULE_SENSOR_BITS_PER_PIXEL==10
    (int32_t)"Implementation of RAW operations\n(Avg, Sum, Sub) for 10bit sensor",
#else
    (int32_t)"Implementation of RAW operations\n(Avg, Sum, Sub) for 12bit sensor",
#endif

    &_librawop.base,

    {0,0},                      // GUI version
    {0,0},                      // CONF version
    {1,0},                      // CAM SENSOR version
    {0,0},                      // CAM INFO version
};

/*************** END OF AUXILARY PART *******************/
