#ifndef PLATFORM_KBD_H
#define PLATFORM_KBD_H
// override key and feather bits to avoid feather osd messing up chdk display in ALT mode
#define KEYS_MASK0         (0x00003000) //Logic OR of group 0 Keymap values
#define KEYS_MASK1         (0xBFF00000) //Logic OR of group 1 Keymap values
#define KEYS_MASK2         (0x00000000) //Logic OR of group 2 Keymap values

#define SD_READONLY_FLAG    0x00020000 // Found @0xffb0fa84, levent 0x20a a2300 b101
#define SD_READONLY_IDX     2
#define USB_MASK            0x00040000 // Found @0xffb0fa8c, levent 0x202 a2300 b101
#define USB_IDX             2
#endif
