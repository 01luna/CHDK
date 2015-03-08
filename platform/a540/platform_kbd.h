#ifndef PLATFORM_KBD_H
#define PLATFORM_KBD_H

#define KEYS_MASK0 0x00000000
#define KEYS_MASK1 0x00000000
#define KEYS_MASK2 0x00001FFF

#define SD_READONLY_IDX 2
#define SD_READONLY_FLAG 0x20000
#define USB_IDX 2
#define USB_MASK 0x4000

// MMIO to read USB +5v directly, for get_usb_bit
#define USB_MMIO 0xc0220208

#endif
