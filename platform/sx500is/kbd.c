#include "lolevel.h"
#include "platform.h"
#include "keyboard.h"
#include "kbd_common.h"

long kbd_new_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
long kbd_prev_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
long kbd_mod_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

extern void _GetKbdState(long*);

int get_usb_bit() {
    long usb_physw[3];
    usb_physw[USB_IDX] = 0;
    _kbd_read_keys_r2(usb_physw);
    return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ;
}

KeyMap keymap[] = {
    // Order IS important. kbd_get_pressed_key will walk down this table
    // and take the first matching mask. Notice that KEY_SHOOT_HALF is
    // always pressed if KEY_SHOOT_FULL is. --MarcusSt
    { 0, KEY_ERASE           ,0x00080000 }, // Found @0xff39e3a8, levent 0x0a
    { 0, KEY_DISPLAY         ,0x00040000 }, // Found @0xff39e3a8, levent 0x0a
    { 0, KEY_VIDEO           ,0x00020000 }, // Found @0xff39e3a8, levent 0x0a
    { 0, KEY_LEFT            ,0x00010000 }, // Found @0xff39e398, levent 0x06
    { 0, KEY_MENU            ,0x00008000 }, // Found @0xff39e390, levent 0x09
    { 0, KEY_SET             ,0x00001000 }, // Found @0xff39e378, levent 0x08
    { 0, KEY_RIGHT           ,0x00002000 }, // Found @0xff39e380, levent 0x07
    { 0, KEY_DOWN            ,0x00000800 }, // Found @0xff39e370, levent 0x05
    { 0, KEY_UP              ,0x00000400 }, // Found @0xff39e368, levent 0x04
    { 2, KEY_SHOOT_FULL      ,0x00000600 }, // Found @0xff39e3e0, levent 0x01
    { 2, KEY_SHOOT_FULL_ONLY ,0x00000400 }, // Found @0xff39e3e0, levent 0x01
    { 2, KEY_SHOOT_HALF      ,0x00000200 }, // Found @0xff39e3d8, levent 0x00
    { 2, KEY_PLAYBACK        ,0x00000008 }, // Found @0xff39e3d0, levent 0x101
    { 2, KEY_POWER           ,0x00000002 }, // Found @0xff39e3c8, levent 0x100
    { 0, 0, 0 }
};

void kbd_set_alt_mode_key_mask(long key) { }

int jogdial_stopped=0;

long __attribute__((naked,noinline)) wrap_kbd_p1_f() {

    //SX500IS 100C @ 0xff019558
    asm volatile(
                "STMFD   SP!, {R1-R7,LR}\n"
                "MOV     R5, #0\n"
                "BL      my_kbd_read_keys\n"
                "B       _kbd_p1_f_cont\n"
    );

    return 0;
}

// no stack manipulation needed here, since we create the task directly
void __attribute__((noinline)) mykbd_task() {
    while (physw_run) {
        _SleepTask(physw_sleep_delay);

        if (wrap_kbd_p1_f() == 1) {             // autorepeat ?
            _kbd_p2_f();
        }
    }

    _ExitTask();
}

// Pointer to stack location where jogdial task records previous and current
// jogdial positions
extern short* jog_position;
extern short rear_dial_position;

void jogdial_control(int n) {
    if (jogdial_stopped && !n) {
        // If re-enabling jogdial set the task code current & previous positions to the actual
        // dial positions so that the change won't get processed by the firmware
        jog_position[0] = jog_position[2] = rear_dial_position;   // Rear dial
    }
    jogdial_stopped = n;
}

void my_kbd_read_keys()
{
    kbd_update_key_state();
    kbd_update_physw_bits();
}

void kbd_fetch_data(long *dst)
{
    _GetKbdState(dst);
    _kbd_read_keys_r2(dst);
}

static short new_jogdial = 0, old_jogdial = 0;

long get_jogdial_direction(void)
{
    old_jogdial = new_jogdial;
    new_jogdial = rear_dial_position;

    if      (old_jogdial > new_jogdial)     return JOGDIAL_LEFT;
    else if (old_jogdial < new_jogdial)     return JOGDIAL_RIGHT;
    else                                    return 0;
}
