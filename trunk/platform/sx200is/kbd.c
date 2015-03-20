#include "lolevel.h"
#include "platform.h"
#include "keyboard.h"
#include "kbd_common.h"

long kbd_new_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
long kbd_prev_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
long kbd_mod_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

KeyMap keymap[] = {
//         KEY_ZOOM_IN_SLOW   , 0x00000040 },
//         KEY_ZOOM_OUT_SLOW  , 0x00000010 },

    { 0, KEY_SHOOT_FULL     , 0x00000300 },
    { 0, KEY_SHOOT_FULL_ONLY, 0x00000200 },
    { 0, KEY_SHOOT_HALF     , 0x00000100 },

    { 1, KEY_ZOOM_OUT       , 0x00000030 }, //method taken from the SX220 port
    { 1, KEY_ZOOM_OUT       , 0x00000010 },
    { 1, KEY_ZOOM_OUT       , 0x00000020 },
    { 1, KEY_ZOOM_IN        , 0x000000C0 },
    { 1, KEY_ZOOM_IN        , 0x00000040 },
    { 1, KEY_ZOOM_IN        , 0x00000080 },

    { 1, KEY_UP             , 0x00000100 },
    { 1, KEY_DOWN           , 0x00001000 },
    { 1, KEY_LEFT           , 0x00000200 },
    { 1, KEY_RIGHT          , 0x00002000 },
    { 1, KEY_SET            , 0x00000400 },
//    { 1, KEY_ZOOM_IN        , 0x00000080 },
//    { 1, KEY_ZOOM_OUT       , 0x00000020 },
    { 1, KEY_MENU           , 0x00000800 },
    { 1, KEY_DISPLAY        , 0x00008000 },
    { 1, KEY_PRINT          , 0x00004000 },
        { 0, 0, 0 }
};

extern void _platformsub_kbd_fetch_data(long*);

#define NEW_SS (0x2000)

int get_usb_bit() 
{
	long usb_physw[3];
	usb_physw[USB_IDX] = 0;
	_kbd_read_keys_r2(usb_physw);
	return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ; 
}

static char kbd_stack[NEW_SS];


long __attribute__((naked)) wrap_kbd_p1_f();

static void __attribute__((noinline)) mykbd_task_proceed()
{
	kbd_new_state[0] = physw_status[0];
	kbd_new_state[1] = physw_status[1];
	kbd_new_state[2] = physw_status[2];
	while (physw_run){
		_SleepTask(10);
		
		if (wrap_kbd_p1_f() == 1){ // autorepeat ?
			_kbd_p2_f();
		}
	}
}

void __attribute__((naked,noinline)) mykbd_task()
{
    /* WARNING
     * Stack pointer manipulation performed here!
     * This means (but not limited to):
     *	function arguments destroyed;
     *	function CAN NOT return properly;
     *	MUST NOT call or use stack variables before stack
     *	is setup properly;
     *
     */

	register int i;
	register long *newstack;

	newstack = (void*)kbd_stack;

	for (i=0;i<NEW_SS/4;i++)
		newstack[i]=0xdededede;

	asm volatile (
		"MOV	SP, %0"
		:: "r"(((char*)newstack)+NEW_SS)
		: "memory"
	);

	mykbd_task_proceed();

	/* function can be modified to restore SP here...
	 */

	_ExitTask();
}


long __attribute__((naked,noinline)) wrap_kbd_p1_f()
{

	asm volatile(
		"STMFD   SP!, {R1-R5,LR}\n"
		"MOV     R4, #0\n"
		"BL      my_kbd_read_keys\n"
		"B       _kbd_p1_f_cont\n"
	);
	return 0; // shut up the compiler
}

int jogdial_stopped=0;

void my_kbd_read_keys()
{
   kbd_update_key_state();

   _kbd_read_keys_r2(physw_status);

   kbd_update_physw_bits();
}

void kbd_fetch_data(long *dst) 
{
    _platformsub_kbd_fetch_data(dst);
}

void kbd_set_alt_mode_key_mask(long key) { }

void jogdial_control(int n) {
    // this camera did not have jog_position defined
    /*
    if (jogdial_stopped && !n) {
        // If re-enabling jogdial set the task code current & previous positions to the actual
        // dial positions so that the change won't get processed by the firmware
        jog_position[0] = jog_position[2] = rear_dial_position;   // Rear dial
    }
    */
    jogdial_stopped = n;
}

static int new_jogdial=0, old_jogdial=0;

int Get_JogDial(void){
 return (*(int*)0xC0240104)>>16;
}

long get_jogdial_direction(void) { 
 old_jogdial=new_jogdial;
 new_jogdial=Get_JogDial();
 if (old_jogdial<new_jogdial) return JOGDIAL_LEFT; 
 else if (old_jogdial>new_jogdial) return JOGDIAL_RIGHT;
 else return 0;
}
