//DNG related stuff

#ifndef DNG_H
#define DNG_H

// This is to minimize export list to different modules
struct libdng_sym {
	int  size;                             // simple guard to detect changing list of exported by library symbols
	void (*create_badpixel_bin)();
	int  (*raw_init_badpixel_bin)();
	void (*capture_data_for_exif)(void);
	void (*load_bad_pixels_list_b)(char* filename);
	int  (*badpixel_list_loaded_b)(void);

	void (*convert_dng_to_chdk_raw)(char* fn);
	void (*write_dng)(int fd, char* rawadr, char* altrawadr, unsigned long uncachedbit);
};

// Defines of exported to chdk symbols
#ifdef THIS_IS_CHDK_CORE

	// This section is for CHDK core
	extern struct libdng_sym libdng;
#else
	
	extern void create_badpixel_bin();
    extern int raw_init_badpixel_bin();
    extern void capture_data_for_exif(void);
	extern void load_bad_pixels_list_b(char* filename);
	extern int  badpixel_list_loaded_b(void);

    extern void convert_dng_to_chdk_raw(char* fn);
	extern void write_dng(int fd, char* rawadr, char* altrawadr, unsigned long uncachedbit);

extern void unload_bad_pixels_list_b(void);

#endif

#endif
