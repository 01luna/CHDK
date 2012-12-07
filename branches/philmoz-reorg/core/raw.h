#ifndef RAW_H
#define RAW_H

//-------------------------------------------------------------------
#define RAW_PREFIX_IMG          0
#define RAW_PREFIX_CRW          1
#define RAW_PREFIX_SND          2

#define RAW_EXT_JPG             0
#define RAW_EXT_CRW             1
#define RAW_EXT_CR2             2
#define RAW_EXT_THM             3
#define RAW_EXT_WAV             4

//-------------------------------------------------------------------
extern int raw_savefile();
extern void raw_postprocess();
extern void raw_prepare_develop(const char* filename);
extern int make_pixel_list(char * ptr, int size);
extern unsigned short get_raw_pixel(unsigned int x,unsigned  int y);
extern char* get_raw_image_addr(void);
extern void patch_bad_pixel(unsigned int x,unsigned  int y);


// = mult * pow ( x/xdiv, y/ydiv)
extern int pow_calc( int mult, int x, int x_div, int y, int y_div);
extern int pow_calc_2( int mult, int x, int x_div, double y, int y_div);

//-------------------------------------------------------------------
#endif
