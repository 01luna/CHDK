#ifndef PLATFORM_KBD_H
#define PLATFORM_KBD_H
#define KEYS_MASK0 0
#define KEYS_MASK1 0
#define KEYS_MASK2 0x2FFE

#define SD_READONLY_FLAG (0x80000000)
#define SD_READONLY_IDX 1

#define USB_MASK 0x400000
#define USB_IDX  0

// NOTE original port had a TODO on this value, may not be verified
#define USB_MMIO 0xc0220200
#endif
