#ifndef PLATFORM_KBD_H
// no keys in 0 or 1
#define KEYS_MASK0 (0x00000000)
#define KEYS_MASK1 (0x00000000)
#define KEYS_MASK2 (0x77FE)

#define SD_READONLY_FLAG    0x02000000 // Found @0xff4fb478, levent 0x20a
#define SD_READONLY_IDX     2
#define USB_MASK            0x10000000 // Found @0xff4fb488, levent 0x202
#define USB_IDX             2
#endif
