#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"

typedef struct {
    short grp;
    short hackkey;
    long canonkey;
} KeyMap;

long kbd_new_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_prev_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static long kbd_mod_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

static KeyMap keymap[];

#define KEYS_MASK0 (0x0000090F)     // physw_status[0]
// override key and feather bits to avoid feather osd messing up chdk display in ALT mode
#define KEYS_MASK1 (0x00000FF0)     // physw_status[1], override 0xF0 (keys) + 0xF00 (feather)
#define KEYS_MASK2 (0x00000000)     // physw_status[2]
static long alt_mode_key_mask = 0x00000000;

#define SD_READONLY_FLAG    (0x00020000)    // SD-Card Lock Status (locked / unlocked)
#define SD_READONLY_IDX     2

#define USB_MASK            (0x00080000)    // USB-Power (triggered around 3,5V)
#define USB_IDX  2

extern void usb_remote_key( void ) ;
int get_usb_bit() 
{
	long usb_physw[3];
	usb_physw[USB_IDX] = 0;
	_kbd_read_keys_r2(usb_physw);
	return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ; 
}

volatile int jogdial_stopped=0;

long __attribute__((naked)) wrap_kbd_p1_f();

static void __attribute__((noinline)) mykbd_task_proceed() {
    while (physw_run) {
        _SleepTask(10);

        if (wrap_kbd_p1_f() == 1) {   // autorepeat ?
            _kbd_p2_f();
        }
    }
}

// no stack manipulation needed here, since we create the task directly
void __attribute__((naked,noinline)) mykbd_task() {
    mykbd_task_proceed();
    _ExitTask();
}

// ROM:FF83484C, like SX110
long __attribute__((naked,noinline)) wrap_kbd_p1_f() {
    asm volatile(
        "STMFD   SP!, {R1-R5,LR}\n"
        "MOV     R4, #0\n"
        "BL      _kbd_read_keys\n"       // replaces kbd_fetch_data()
        "BL      my_kbd_read_keys\n"     // +
        "B       _kbd_p1_f_cont\n"       // continue at ROM:FF834858
    );
    return 0;   // shut up the compiler
}

// like SX110
void my_kbd_read_keys() {
    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
    //kbd_prev_state[2] = kbd_new_state[2];   // nothing to override

    // The following three lines replace the call to kbd_fetch_data()
    kbd_new_state[0] = physw_status[0];
    kbd_new_state[1] = physw_status[1];
    //kbd_new_state[2] = physw_status[2];

    if (kbd_process() == 0) {
        // we read keyboard state with _kbd_read_keys()
        jogdial_stopped=0;
    } else {
        // override keys
        physw_status[0] = (kbd_new_state[0] | KEYS_MASK0) & (~KEYS_MASK0 | kbd_mod_state[0]);
        physw_status[1] = (kbd_new_state[1] | KEYS_MASK1) & (~KEYS_MASK1 | kbd_mod_state[1]);
        //physw_status[2] = (kbd_new_state[2] | KEYS_MASK2) & (~KEYS_MASK2 | kbd_mod_state[2]);

        if ((jogdial_stopped==0) && !state_kbd_script_run) {
            jogdial_stopped=1;
            get_jogdial_direction();
        } else if (jogdial_stopped && state_kbd_script_run)
            jogdial_stopped=0;
    }

	usb_remote_key() ;

	if (conf.remote_enable) {
		physw_status[USB_IDX] = physw_status[USB_IDX] & ~(SD_READONLY_FLAG | USB_MASK);
	} else {
		physw_status[USB_IDX] = physw_status[USB_IDX] & ~SD_READONLY_FLAG;
	}
 		
}

void kbd_set_alt_mode_key_mask(long key)
{
        int i;
        for (i=0; keymap[i].hackkey; ++i) {
                if (keymap[i].hackkey == key) {
                        alt_mode_key_mask = keymap[i].canonkey;
                        return;
                }
        }
}

void kbd_key_press(long key) {
    int i;
    for (i=0; keymap[i].hackkey; i++) {
        if (keymap[i].hackkey == key) {
            kbd_mod_state[keymap[i].grp] &= ~keymap[i].canonkey;
            return;
        }
    }
}

void kbd_key_release(long key) {
    int i;
    for (i=0; keymap[i].hackkey; i++) {
        if (keymap[i].hackkey == key) {
            kbd_mod_state[keymap[i].grp] |= keymap[i].canonkey;
            return;
        }
    }
}

void kbd_key_release_all() {
    kbd_mod_state[0] |= KEYS_MASK0;
    kbd_mod_state[1] |= KEYS_MASK1;
    //kbd_mod_state[2] |= KEYS_MASK2;
}

long kbd_is_key_pressed(long key) {
    int i;
    for (i=0; keymap[i].hackkey; i++) {
        if (keymap[i].hackkey == key) {
            return ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0) ? 1:0;
        }
    }
    return 0;
}

long kbd_is_key_clicked(long key) {
    int i;
    for (i=0; keymap[i].hackkey; i++) {
        if (keymap[i].hackkey == key) {
            return ((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) &&
                   ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0);
        }
    }
    return 0;
}

long kbd_get_pressed_key() {
    int i;
    for (i=0; keymap[i].hackkey; i++) {
        if ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0) {
            return keymap[i].hackkey;
        }
    }
    return 0;
}

long kbd_get_clicked_key() {
    int i;
    for (i=0; keymap[i].hackkey; i++) {
        if (((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) && ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0)) {
            return keymap[i].hackkey;
        }
    }
    return 0;
}

// ToDo
#ifdef CAM_USE_ZOOM_FOR_MF
long kbd_use_zoom_as_mf() {
    static long v;
    static long zoom_key_pressed = 0;

    if (kbd_is_key_pressed(KEY_ZOOM_IN) && (mode_get()&MODE_MASK) == MODE_REC) {
        get_property_case(PROPCASE_FOCUS_MODE, &v, 4);
        if (v) {
            kbd_key_release_all();
            kbd_key_press(KEY_RIGHT);
            zoom_key_pressed = KEY_ZOOM_IN;
            return 1;
        }
    } else {
        if (zoom_key_pressed==KEY_ZOOM_IN) {
            kbd_key_release(KEY_RIGHT);
            zoom_key_pressed = 0;
            return 1;
        }
    }
    if (kbd_is_key_pressed(KEY_ZOOM_OUT) && (mode_get()&MODE_MASK) == MODE_REC) {
        get_property_case(PROPCASE_FOCUS_MODE, &v, 4);
        if (v) {
            kbd_key_release_all();
            kbd_key_press(KEY_LEFT);
            zoom_key_pressed = KEY_ZOOM_OUT;
            return 1;
        }
    } else {
        if (zoom_key_pressed==KEY_ZOOM_OUT) {
            kbd_key_release(KEY_LEFT);
            zoom_key_pressed = 0;
            return 1;
        }
    }
    return 0;
}
#endif

// ROM:FF861F98
int Get_JogDial(void) {
    return (*(int*)0xC0240104)>>16;     // 0xC0240000 + 0x104
}

static int new_jogdial=0, old_jogdial=0;

long get_jogdial_direction(void) {
    old_jogdial=new_jogdial;
    new_jogdial=Get_JogDial();

    if (old_jogdial<new_jogdial) {
        //return JOGDIAL_LEFT;
        return JOGDIAL_RIGHT;
    } else if (old_jogdial>new_jogdial) {
        return JOGDIAL_LEFT;
        //return JOGDIAL_RIGHT;
    } else {
        return 0;
    }
}

// Base values in Play Mode
// physw_status[0] = 0x800C91F      // 1
// physw_status[1] = 0xFFE          // 2 (Mode Switch: Auto)
// physw_status[2] = 0x400000       // 3
// Mode Switch:
// physw_status[1] 0x1 Auto Mode
// physw_status[1] 0x0 Photo Mode
// physw_status[1] 0x2 Video Mode
// physw_status[2] 0x20000 SD-Card READONLY
static KeyMap keymap[] = {
    { 0, KEY_UP         , 0x00000004 },
    { 0, KEY_DOWN       , 0x00000001 },
    { 0, KEY_LEFT       , 0x00000008 },
    { 0, KEY_RIGHT      , 0x00000002 },
//    { 0, KEY_POWER      , 0x00000010 },
    { 0, KEY_PLAYBACK   , 0x00004000 },    
    { 0, KEY_PRINT      , 0x00004000 },   // ALT Key = PLAYBACK - other workaround: KEY_UP + KEY_LEFT (camera has no print key)
    { 0, KEY_SHOOT_FULL , 0x00000900 },   // 0x00000800 (KEY_SHOOT_FULL_ONLY) + 0x00000100 (KEY_SHOOT_HALF)
    { 0, KEY_SHOOT_FULL_ONLY, 0x00000800 },
    { 0, KEY_SHOOT_HALF , 0x00000100 },
    { 1, KEY_SET        , 0x00000040 },
    { 1, KEY_ZOOM_IN    , 0x00000010 },
    { 1, KEY_ZOOM_OUT   , 0x00000020 },
    { 1, KEY_MENU       , 0x00000080 },
    { 0, 0, 0 }
};
