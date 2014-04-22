// TODO this holds and exposure count of some kind, but it only updates when rebooting or switching to play!
#define PARAM_FILE_COUNTER      0x1

#include "platform.h"

// TODO:Taken from ixus140
// These F-numbers are the "mock" values shown by the cam.
// They're linked to FL (zoom) and ND filter.
// aperture_sizes_table[].id is just a serial number.
// note av96 varies continously with zoom, the following values are just representative
const ApertureSize aperture_sizes_table[] = { // PROPCASE 23
    {  9, 328, "3.2" },
    { 10, 331, "3.5" }, 
    { 11, 379, "4.0" }, 
    { 12, 425, "4.5" },
    { 13, 463, "5.0" },
    { 14, 474, "5.6" },
    { 15, 502, "6.3" },
    { 16, 541, "6.9" },

// The rest are the same physical apertures as above, but with ND:
    { 17, 604, "9.0" },
    { 18, 613, "10.0" },
    { 19, 657, "11.0" },
    { 20, 687, "13.0" },
    { 21, 710, "14.0" },
    { 22, 750, "16.0" },
    { 23, 790, "18.0" },
    { 24, 817, "20.0" },
};

// OLD copied comment! Taken from ixus140
// TODO copied from 850
// Another set of "mock" values, which can probably
// be derived from the table found at FFB4E258 in FW.
// At the moment, I see no reason to amend it.
const ShutterSpeed shutter_speeds_table[] = {
    { -12, -384, "15", 15000000 },
    { -11, -352, "13", 13000000 },
    { -10, -320, "10", 10000000 },
    {  -9, -288, "8",   8000000 },
    {  -8, -256, "6",   6000000 },
    {  -7, -224, "5",   5000000 },
    {  -6, -192, "4",   4000000 },
    {  -5, -160, "3.2", 3200000 },
    {  -4, -128, "2.5", 2500000 },
    {  -3,  -96, "2",   2000000 },
    {  -2,  -64, "1.6", 1600000 },
    {  -1,  -32, "1.3", 1300000 },
    {   0,    0, "1",   1000000 },
    {   1,   32, "0.8",  800000 },
    {   2,   64, "0.6",  600000 },
    {   3,   96, "0.5",  500000 },
    {   4,  128, "0.4",  400000 },
    {   5,  160, "0.3",  300000 },
    {   6,  192, "1/4",  250000 },
    {   7,  224, "1/5",  200000 },
    {   8,  256, "1/6",  166667 },
    {   9,  288, "1/8",  125000 },
    {  10,  320, "1/10", 100000 },
    {  11,  352, "1/13",  76923 },
    {  12,  384, "1/15",  66667 },
    {  13,  416, "1/20",  50000 },
    {  14,  448, "1/25",  40000 },
    {  15,  480, "1/30",  33333 },
    {  16,  512, "1/40",  25000 },
    {  17,  544, "1/50",  20000 },
    {  18,  576, "1/60",  16667 },
    {  19,  608, "1/80",  12500 },
    {  20,  640, "1/100", 10000 },
    {  21,  672, "1/125",  8000 },
    {  22,  704, "1/160",  6250 },
    {  23,  736, "1/200",  5000 },
    {  24,  768, "1/250",  4000 },
    {  25,  800, "1/320",  3125 },
    {  26,  832, "1/400",  2500 },
    {  27,  864, "1/500",  2000 },
    {  28,  896, "1/640",  1563 },
    {  29,  928, "1/800",  1250 },
    {  30,  960, "1/1000", 1000 },
    {  31,  992, "1/1250",  800 },
    {  32, 1021, "1/1600",  625 },
};

const ISOTable iso_table[] = {
    {  0,     0,  "Auto", -1},
    {  1,    80,    "80", -1},
    {  2,   100,   "100", -1},
    {  3,   200,   "200", -1},
    {  4,   400,   "400", -1},
    {  5,   800,   "800", -1},
    {  6,  1600,  "1600", -1},
    {  7,  3200,  "3200", -1},
};

//http://chdk.setepontos.com/index.php?topic=5051.msg77808#msg77808
//PROP 49
const CapturemodeMap modemap[] = {
    { MODE_VIDEO_STD,            2633 },
    { MODE_VIDEO_SUPER_SLOW,     2638 },
    { MODE_SCN_SUPER_VIVID,      8748 },
    { MODE_SCN_POSTER_EFFECT,    8749 },
    { MODE_SCN_FISHEYE,          8753 },
    { MODE_SCN_MINIATURE,        8754 },
    { MODE_SCN_TOY_CAMERA,       8757 },
    { MODE_SCN_MONOCHROME,       8761 },
    { MODE_SCN_HIGHSPEED_BURST, 16392 },
    { MODE_PORTRAIT,            16403 },
    { MODE_SCN_LOWLIGHT,        16423 },
    { MODE_SCN_FACE_SELF_TIMER, 16942 },
    { MODE_SCN_SNOW,            16411 },
    { MODE_SCN_FIREWORK,        16413 },
    { MODE_AUTO,                32768 },
    { MODE_M,                   32769 },
    { MODE_AV,                  32770 },
    { MODE_TV,                  32771 },
    { MODE_P,                   32772 },
    { MODE_DISCREET,            32824 },
    { MODE_SCN_NIGHT_SCENE,     33331 }, // This mode is not listed in Canon menu
    { MODE_LIVE,                33339 },
    { MODE_VIDEO_MOVIE_DIGEST,  33340 },
};

#include "../generic/shooting.c"

long get_file_next_counter() {
    return get_file_counter();
}

long get_target_file_num() {
    return get_exposure_counter();
}
#if defined(CAM_DATE_FOLDER_NAMING)
// ELPH130 camera uses date to name directory
// TODO currently returns something like A/DCIM/101___09/ETC_0112.TMP
// may need different params
void get_target_dir_name(char *out)
{
    static char buf[32];
    extern void _GetImageFolder(char*,int,int,int);
    _GetImageFolder(buf,get_file_next_counter(),CAM_DATE_FOLDER_NAMING,time(NULL));
    strncpy(out,buf,15);
    out[15] = 0;
}
#else
long get_target_dir_num() 
{
    return 0;
}
#endif

// TODO
int circle_of_confusion = 6;

