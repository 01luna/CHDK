#include "lolevel.h"
#include "platform.h"
#include "keyboard.h"
#include "kbd_common.h"

long kbd_new_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
long kbd_prev_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
long kbd_mod_state[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

KeyMap keymap[] = {
    /* tiny bug: key order matters. see kbd_get_pressed_key()
     * for example
     */
    { 1, KEY_UP,                0x00100000 },
    { 1, KEY_DOWN,              0x00080000 },
    { 1, KEY_LEFT,              0x00010000 },
    { 1, KEY_RIGHT,             0x00040000 },
    { 1, KEY_SET,               0x00020000 },
    { 0, KEY_SHOOT_FULL,        0xC0000000 },
    { 0, KEY_SHOOT_FULL_ONLY,   0x80000000 },
    { 0, KEY_SHOOT_HALF,        0x40000000 },
    { 1, KEY_ZOOM_IN,           0x00000010 },
    { 1, KEY_ZOOM_OUT,          0x00000008 },
    { 1, KEY_MENU,              0x08000000 },
    { 1, KEY_DISPLAY,           0x04000000 },
    { 1, KEY_PRINT,             0x00001000 },
    { 1, KEY_ERASE,             0x01000000 },
    { 1, KEY_EXPO_CORR,         0x02000000 },
    { 1, KEY_MICROPHONE,        0x10000000 },
    { 0, 0, 0 }
};

static int new_jogdial=0, old_jogdial=0;

#define NEW_SS (0x2000)

int get_usb_bit() 
{
	long usb_physw[3];
	usb_physw[USB_IDX] = 0;
	_kbd_read_keys_r2(usb_physw);
	return(( usb_physw[USB_IDX] & USB_MASK)==USB_MASK) ; 
}

static char kbd_stack[NEW_SS];

extern void _platformsub_kbd_fetch_data(long*);
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

void __attribute__((naked,noinline))
mykbd_task(long ua, long ub, long uc, long ud, long ue, long uf)
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
                "STMFD   SP!, {R4-R7,LR}\n"
                "SUB     SP, SP, #0xC\n"
                "BL      my_kbd_read_keys\n"
		"B	 _kbd_p1_f_cont\n"
    );
    return 0; // shut up the compiler
}

static int handle_taskTouchW = 0;

int jogdial_stopped=0;

void jogdial_control(int n) {
    // assumes jogdial task is started by the time this gets called
    if (handle_taskTouchW == 0) {
        handle_taskTouchW = _taskNameToId("tJogDial");
    }

    if (jogdial_stopped) {
        if(!n) {
            // if stopped and un-stopping, resume TouchW task
            _taskResume(handle_taskTouchW);
        }
    } else {
        if(n) {
            // if not stopped and stopping, halt TouchW task
		    _taskSuspend(handle_taskTouchW);
        }
    }
    jogdial_stopped = n;
}


void my_kbd_read_keys()
{
    // not called in original port
    //_kbd_pwr_on();

    kbd_update_key_state();

    _kbd_read_keys_r2(physw_status);

    kbd_update_physw_bits();

    _kbd_pwr_off();
}

void kbd_fetch_data(long *dst)
{
    _platformsub_kbd_fetch_data(dst);
}

void kbd_set_alt_mode_key_mask(long key) { }


int Get_JogDial(void){
 return (*(int*)0xC0240304)>>16;
}

long get_jogdial_direction(void) { 
 old_jogdial=new_jogdial;
 new_jogdial=Get_JogDial();
 if (old_jogdial<new_jogdial) return JOGDIAL_LEFT; 
 else if (old_jogdial>new_jogdial) return JOGDIAL_RIGHT;
 else return 0;
}

