#include "lolevel.h"
#include "platform.h"
#include "keyboard.h"
#include "kbd_common.h"

long kbd_new_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
long kbd_prev_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
long kbd_mod_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

extern void _platformsub_kbd_fetch_data(long*);


#if 0
void my_blinkk(void) {
	int i;
//	while(1) {
		*((volatile int *) 0xC02200B6) = 0x46; // Turn on LED
		for (i=0; i<0x200000; i++) { asm volatile ( "nop\n" ); }

		*((volatile int *) 0xC02200B6) = 0x44; // Turn off LED
		for (i=0; i<0x200000; i++) { asm volatile ( "nop\n" ); }

		*((volatile int *) 0xC02200B6) = 0x46; // Turn on LED
		for (i=0; i<0x200000; i++) { asm volatile ( "nop\n" ); }

		*((volatile int *) 0xC02200B6) = 0x44; // Turn off LED
		for (i=0; i<0x900000; i++) { asm volatile ( "nop\n" ); }
//	}
}
#endif 

#define NEW_SS (0x2000)

int get_usb_bit() 
{
	long usb_physw[3];
	usb_physw[USB_IDX] = 0;
	_kbd_read_keys_r2(usb_physw);
	return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ; 
}

static char kbd_stack[NEW_SS];

KeyMap keymap[] = {
	/* tiny bug: key order matters. see kbd_get_pressed_key()
	 * for example
	 */

	{ 0, KEY_SHOOT_FULL     , 0x00000003 },
    { 0, KEY_SHOOT_FULL_ONLY, 0x00000002 },
	{ 0, KEY_SHOOT_HALF     , 0x00000001 },

	{ 1, KEY_UP             , 0x00000400 },
	{ 1, KEY_DOWN           , 0x00000800 },
	{ 1, KEY_LEFT           , 0x00002000 },
	{ 1, KEY_RIGHT          , 0x00001000 },
	{ 1, KEY_SET            , 0x00000100 },
	{ 1, KEY_ZOOM_IN        , 0x00008000 },
	{ 1, KEY_ZOOM_OUT       , 0x00040000 },
	{ 1, KEY_MENU           , 0x00004000 },
	{ 1, KEY_DISPLAY        , 0x00000200 },
	{ 1, KEY_PRINT          , 0x00800000 },
	{ 1, KEY_ERASE          , 0x00000080 },
	{ 1, KEY_EXPO_CORR      , 0x00000040 },
	{ 1, KEY_FLASH          , 0x00100000 },
	{ 1, KEY_VIDEO          , 0x00000020 },
	{ 0, 0, 0 } 
};


long __attribute__((naked)) wrap_kbd_p1_f();


static void __attribute__((noinline)) mykbd_task_proceed()
{
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
