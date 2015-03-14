#include "lolevel.h"
#include "platform.h"
#include "keyboard.h"
#include "kbd_common.h"

long kbd_new_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
long kbd_prev_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
long kbd_mod_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

extern void _GetKbdState(long*);

int get_usb_bit()
{
        long usb_physw[3];
        usb_physw[USB_IDX] = 0;
        _kbd_read_keys_r2(usb_physw);
        return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ;
}

KeyMap keymap[] = {
	
	/* tiny bug: key order matters. see kbd_get_pressed_key() */
    { 0, KEY_PLAYBACK        ,0x01000000 }, // Found @0xffb561dc, levent 0x601	
	{ 0, KEY_MENU            ,0x04000000 }, // Found @0xffb561e4 (1.00B), levent 0x09
	{ 0, KEY_FACE            ,0x00800000 },
	{ 1, KEY_UP              ,0x00001000 }, // Found @0xffb56214 (1.00B), levent 0x04
	{ 1, KEY_RIGHT           ,0x00002000 }, // Found @0xffb5621c (1.00B), levent 0x07
	{ 1, KEY_DOWN            ,0x00004000 }, // Found @0xffb56224 (1.00B), levent 0x05
	{ 1, KEY_LEFT            ,0x00008000 }, // Found @0xffb5622c (1.00B), levent 0x06
	{ 1, KEY_ZOOM_OUT        ,0x00010000 }, // Found @0xffb56234 (1.00B), levent 0x03
	{ 1, KEY_ZOOM_IN         ,0x00020000 }, // Found @0xffb5623c (1.00B), levent 0x02
	{ 1, KEY_SET             ,0x00040000 }, // Found @0xffb56244 (1.00B), levent 0x08
	{ 1, KEY_DISPLAY         ,0x00080000 }, // Found @0xffb5624c (1.00B), levent 0x0a
	{ 1, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffb5620c (1.00B), levent 0x01
	{ 1, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffb5620c (1.00B), levent 0x01
	{ 1, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffb56204 (1.00B), levent 0x00
//    { 0, KEY_POWER           ,0x02000000 }, // Found @0xffb561e4 (1.00D), levent 0x600
	{ 0, 0, 0 }
};

long __attribute__((naked,noinline)) wrap_kbd_p1_f() {
	
	//FF8346D4
	asm volatile(
		"STMFD	SP!, {R1-R7,LR} \n"
		"MOV	R5, #0 \n"
		//"BL		_kbd_read_keys \n"
		"BL		my_kbd_read_keys \n"	// pached
		"B		_kbd_p1_f_cont \n"
	);
	
	return 0; // shut up the compiler
}

void __attribute__((noinline)) mykbd_task() {
	while (physw_run) {
		_SleepTask(physw_sleep_delay);
		
		if (wrap_kbd_p1_f() == 1) {   // autorepeat ?
			_kbd_p2_f();
		}
	}

	_ExitTask();
}

// NOP
void kbd_set_alt_mode_key_mask(long key) { }

void my_kbd_read_keys() {
    kbd_update_key_state();
    kbd_update_physw_bits();
}

void kbd_fetch_data(long *dst) 
{
	_GetKbdState(dst);
	_kbd_read_keys_r2(dst);
}	
