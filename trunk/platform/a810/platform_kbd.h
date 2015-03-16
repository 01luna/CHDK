#ifndef PLATFORM_KBD_H
#define PLATFORM_KBD_H
#define KEYS_MASK0         (0x00003000) //Logic OR of group 0 Keymap values
#define KEYS_MASK1         (0xBFF00000) //Logic OR of group 1 Keymap values
#define KEYS_MASK2         (0x00000000) //Logic OR of group 2 Keymap values

#define SD_READONLY_IDX 2
#define SD_READONLY_FLAG 0x20000

#define USB_MASK (0x40000)
#define USB_IDX  2
#endif
