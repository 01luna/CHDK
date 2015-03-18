#ifndef PLATFORM_KBD_H
#define PLATFORM_KBD_H
// platform code handles reading, updating physw
#define KBD_CUSTOM_UPDATE_KEY_STATE 1
#define KBD_CUSTOM_UPDATE_PHYSW_BITS 1

// key masks, used for press, release
#define KEYS_MASK0 0x00000000
#define KEYS_MASK1 0x00002FFE
#define KEYS_MASK2 0x00000000


// PHYSW_BITS is custom, but these are used for get_usb_bit
#define USB_MASK 0x40 
#define USB_IDX  1

// MMIO to read USB +5v directly, for get_usb_bit
#define USB_MMIO 0xc0220204
#endif
