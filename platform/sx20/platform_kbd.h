#ifndef PLATFORM_KBD_H
#define PLATFORM_KBD_H
#define KEYS_MASK0 (0x00000003)
#define KEYS_MASK1 (0x0094FFE0)
#define KEYS_MASK2 (0x00000000) 

#define SD_READONLY_FLAG (0x20000)
#define SD_READONLY_IDX 2

#define USB_MASK (0x40000)
#define USB_IDX  2

#define HOTSHOE_FLAG        0x10000000 // Found @0xffb44bb4, levent 0x904
#define HOTSHOE_IDX         2
#endif
