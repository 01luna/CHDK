#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

/*----------------------------------------------------------------------
    CreateTask_spytask
-----------------------------------------------------------------------*/
void CreateTask_spytask()
{
    _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
}

///*----------------------------------------------------------------------
// Pointer to stack location where jogdial task records previous and current
// jogdial positions
short *jog_position;


#define GREEN_LED       0xC0220120
#define AF_LED          0xC0223030
//debug use only

int debug_blink(int save_R0) {
	int i;
	*((volatile int *) AF_LED) = 0x46; // Turn on LED
	for (i=0; i<800000; i++) // Wait a while
		{
    		asm volatile ( "nop\n" );
		}

	*((volatile int *) AF_LED) = 0x44; // Turn off LED
	for (i=0; i<800000; i++) // Wait a while
		{
    		asm volatile ( "nop\n" );
		}
	return save_R0;
};

void __attribute__((naked,noinline)) my_blinker(int n) {
	asm volatile (
      "            STMFD   SP!, {R0-R9,LR}\n"
);
	int i, j;
	for (j=0; j<n; j++)
	{
		*((volatile int *) GREEN_LED) = 0x46; // Turn on LED
		for (i=0; i<0x200000; i++) { asm volatile ( "nop \n" ); }

		*((volatile int *) GREEN_LED) = 0x44; // Turn off LED
		for (i=0; i<0x400000; i++) { asm volatile ( "nop \n" ); }
	}
	for (i=0; i<0x900000; i++) { asm volatile ( "nop \n" ); }
	asm volatile (
      "            LDMFD   SP!, {R0-R9,PC}\n"
	);
}

/*----------------------------------------------------------------------
    boot()

    Main entry point for the CHDK code
-----------------------------------------------------------------------*/
