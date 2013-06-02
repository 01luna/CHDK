#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;

// Forward declarations
void CreateTask_spytask();
void CreateTask_PhySw();

void boot();


/*#define DP (void*)0xC02200C4					// direct-print (blue)
#define DELAY 3000000

void debug_my_blink()
{
	volatile long *p = (void*)DP;       		// turned off later, so assumed to be power
	int counter;

	// DEBUG: blink led
	counter = DELAY; *p = 0x46;
	while (counter--) { asm("nop\n nop\n"); };
	counter = DELAY; *p = 0x44;
	while (counter--) { asm("nop\n nop\n"); };
}*/

void taskCreateHook(int *p) { //function taken from the ixus80 port, adapted of course
 p-=16;
 if (p[0]==0xffc98f18)  p[0]=(int)exp_drv_task;
} 

//#define DEBUG_LED 0xC02200C4
void boot() { //#fs
    long *canon_data_src = (void*)0xFFEBE450;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xf6c4 - 0x1900;		// data_end - data_start
    long *canon_bss_start = (void*)0xf6c4;		// just after data
    long canon_bss_len = 0x9F498 - 0xf6c4;

    long i;

	// Code taken from VxWorks CHDK. Changes CPU speed?
    asm volatile (
	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n"
	"ORR     R0, R0, #4\n"
	"ORR     R0, R0, #1\n"
	"MCR     p15, 0, R0,c1,c0\n"
    :::"r0");

    for(i=0;i<canon_data_len/4;i++)
	canon_data_dst[i]=canon_data_src[i];

    for(i=0;i<canon_bss_len/4;i++)
	canon_bss_start[i]=0;

    *(int*)0x1930=(int)taskCreateHook; //from ixus80 port
    *(int*)0x1934=(int)taskCreateHook; //from ixus80 port (was taskCreateHook2...)

    *(int*)0x2578= (*(int*)0xC02200B8)&1 ? 0x100000: 0x200000; // replacement of sub_FFC12E38

//	debug_my_blink();

    // jump to init-sequence that follows the data-copy-routine
    asm volatile ("B      sub_FFC001a4_my\n");	// <---------------
//    asm volatile ("B      sub_FFC001A4\n");
}; //#fe

void __attribute__((naked,noinline)) sub_FFC001a4_my() { //#fs
	asm volatile (
		 "LDR	R0, =0xFFC0021C\n"
		 "MOV	R1, #0\n"
		 "LDR	R3, =0xFFC00254\n"

	"loc_FFC001B0:\n"
		 "CMP	R0, R3\n"
		 "LDRCC	R2, [R0],#4\n"
		 "STRCC	R2, [R1],#4\n"
		 "BCC	loc_FFC001B0\n"

		 "LDR	R0, =0xFFC00254\n"
		 "MOV	R1, #0x4B0\n"
		 "LDR	R3, =0xFFC00468\n"

	"loc_FFC001CC:\n"
		 "CMP	R0, R3\n"
		 "LDRCC	R2, [R0],#4\n"
		 "STRCC	R2, [R1],#4\n"
		 "BCC	loc_FFC001CC\n"
		 "MOV	R0, #0xD2\n"
		 "MSR	CPSR_cxsf, R0\n"
		 "MOV	SP, #0x1000\n"
		 "MOV	R0, #0xD3\n"
		 "MSR	CPSR_cxsf, R0\n"
		 "MOV	SP, #0x1000\n"
		 "LDR	R0, =0x6C4\n"
		 "LDR	R2, =0xEEEEEEEE\n"
		 "MOV	R3, #0x1000\n"

	"loc_FFC00200:\n"
		 "CMP	R0, R3\n"
		 "STRCC	R2, [R0],#4\n"
		 "BCC	loc_FFC00200\n"

		 "BL	sub_FFC00FB8_my\n"				// <----------
	);
} //#fe

void __attribute__((naked,noinline)) sub_FFC00FB8_my() { //#fs
	asm volatile (
		 "STR	LR, [SP,#-4]!\n"
		 "SUB	SP, SP,	#0x74\n"
		 "MOV	R0, SP\n"
		 "MOV	R1, #0x74\n"
		 "BL	sub_FFE56D68\n"
		 "MOV	R0, #0x53000\n"
		 "STR	R0, [SP,#0x74-0x70]\n"

		 "LDR	R0, =new_sa\n"					// <--------
		 "LDR	R0, [R0]\n"						// <--------

		 "LDR	R2, =0x2ABC00\n"
		 "LDR	R1, =0x2A4968\n"
		 "STR	R0, [SP,#0x74-0x6C]\n"
		 "SUB	R0, R1,	R0\n"
		 "ADD	R3, SP,	#0x74-0x68\n"
		 "STR	R2, [SP,#0x74-0x74]\n"
		 "STMIA	R3, {R0-R2}\n"
		 "MOV	R0, #0x22\n"
		 "STR	R0, [SP,#0x74-0x5C]\n"
		 "MOV	R0, #0x68\n"
		 "STR	R0, [SP,#0x74-0x58]\n"
		 "LDR	R0, =0x19B\n"
		 "MOV	R1, #0x64\n"
//		 "STRD	R0, [SP,#0x74-0x54]\n"
		"STR      R0, [SP,#0x74-0x54]\n"		// split in two single-word STRs
		"STR      R1, [SP,#0x74-0x50]\n"
		 "MOV	R0, #0x78\n"
//		 "STRD	R0, [SP,#0x74-0x4C]\n"
		"STR      R0, [SP,#0x74-0x4C]\n"		// split in two single-word STRs
		"STR      R1, [SP,#0x74-0x48]\n"
		 "MOV	R0, #0\n"
		 "STR	R0, [SP,#0x74-0x44]\n"
		 "STR	R0, [SP,#0x74-0x40]\n"
		 "MOV	R0, #0x10\n"
		 "STR	R0, [SP,#0x74-0x18]\n"
		 "MOV	R0, #0x800\n"
		 "STR	R0, [SP,#0x74-0x14]\n"
		 "MOV	R0, #0xA0\n"
		 "STR	R0, [SP,#0x74-0x10]\n"
		 "MOV	R0, #0x280\n"
		 "STR	R0, [SP,#0x74-0xC]\n"
//		 "LDR	R1, =0xFFC04DBC\n"				// original uHwSetup
		 "LDR	R1, =uHwSetup_my\n"				// followup to own function

		 "MOV	R0, SP\n"
		 "MOV	R2, #0\n"
		 "BL	sub_FFC02D70\n"
		 "ADD	SP, SP,	#0x74\n"
		 "LDR	PC, [SP],#4\n"
	);
}; //#fe

//		 "BL	debug_my_blink\n"

void __attribute__((naked,noinline)) uHwSetup_my() { //#fs
	asm volatile (
		 "STMFD	SP!, {R4,LR}\n"
		 "BL	sub_FFC0095C\n"
		 "BL	sub_FFC09A10\n"					// dmSetup
		 "CMP	R0, #0\n"
		 "LDRLT	R0, =0xFFC04ED0\n"				// aDmsetup
		 "BLLT	sub_FFC04EB0\n"					// err_init_task
		 "BL	sub_FFC049E0\n"					// termDriverInit
		 "CMP	R0, #0\n"
		 "LDRLT	R0, =0xFFC04ED8\n"				// aTermdriverinit
		 "BLLT	sub_FFC04EB0\n"					// err_init_task
		 "LDR	R0, =0xFFC04EE8\n"				// a_term
		 "BL	sub_FFC04ACC\n"					// termDeviceCreate
		 "CMP	R0, #0\n"
		 "LDRLT	R0, =0xFFC04EF0\n"				// aTermdevicecrea
		 "BLLT	sub_FFC04EB0\n"					// err_init_task
		 "LDR	R0, =0xFFC04EE8\n"				// a_term
		 "BL	sub_FFC0357C\n"					// stdioSetup
		 "CMP	R0, #0\n"
		 "LDRLT	R0, =0xFFC04F04\n"				// aStdiosetup
		 "BLLT	sub_FFC04EB0\n"					// err_init_task
		 "BL	sub_FFC09598\n"					// stdlibSetup
		 "CMP	R0, #0\n"
		 "LDRLT	R0, =0xFFC04F10\n"				// aStdlibsetup
		 "BLLT	sub_FFC04EB0\n"					// err_init_task
		 "BL	sub_FFC014D0\n"					// armlib_setup
		 "CMP	R0, #0\n"
		 "LDRLT	R0, =0xFFC04F1C\n"				// aArmlib_setup
		 "BLLT	sub_FFC04EB0\n"					// err_init_task
		 "LDMFD	SP!, {R4,LR}\n"
//		 "B	sub_FFC0DCD4\n"						// taskcreate_Startup
		"B	taskcreate_Startup_my\n"			// <-----------------
		".ltorg\n"
	);
}; //#fe

void __attribute__((naked,noinline)) taskcreate_Startup_my() { //#fs
	asm volatile (
		 "STMFD	SP!, {R3,LR}\n"
//		 "BL	sub_FFC12E30\n"					// nullsub_3
		 "BL	sub_FFC1BFA4\n"
		 "CMP	R0, #0\n"
		 "LDREQ	R2, =0xC0220000\n"
		 "LDREQ	R0, [R2,#0xB8]\n"
		 "LDREQ	R1, [R2,#0xDC]\n"
		 "ORREQ	R0, R0,	R1\n"
		 "TSTEQ	R0, #1\n"
		 "BNE	loc_FFC0DD08\n"
		 "MOV	R0, #0x44\n"
		 "STR	R0, [R2,#0x4C]\n"
	"loc_FFC0DD04:\n"
		 "B	loc_FFC0DD04\n"
	"loc_FFC0DD08:\n"
//		 "BL	sub_FFC12E38\n"        //------------> removed here to fast camera switching on
//		 "BL	sub_FFC12E34\n"					// nullsub_4
		 "BL	sub_FFC19B30\n"
		 "MOV	R1, #0x300000\n"
		 "MOV	R0, #0\n"

		 "BL	sub_FFC19D78\n"
		 "BL	sub_FFC19D24\n"
		 "MOV	R3, #0\n"
		 "STR	R3, [SP,#8-0x8]\n"

//		 "LDR	R3, =0xFFC0DC78\n"				// task_Startup
		 "LDR	R3, =task_Startup_my\n"			// task_Startup_my

		 "MOV	R2, #0\n"
		 "MOV	R1, #0x19\n"
		 "LDR	R0, =0xFFC0DD4C\n"				// aStartup
		 "BL	sub_FFC0BBB8\n"					// CreateTask
		 "MOV	R0, #0\n"
		 "LDMFD	SP!, {R12,PC}\n"
	);
}; //#fe

void __attribute__((naked,noinline)) task_Startup_my() { //#fs
	asm volatile (
		 "STMFD	SP!, {R4,LR}\n"
		 "BL	sub_FFC051CC\n"					// taskcreate_ClockSave
		 "BL	sub_FFC13FC8\n"
		 "BL	sub_FFC10EC8\n"
		 "BL	sub_FFC1BFE4\n"					// j_kbd_pwr_on_short
		 "BL	sub_FFC1C184\n"

//		 "BL	StartDiskboot\n"
	);

	CreateTask_spytask();

	asm volatile (
		 "BL	sub_FFC1C34C\n"
		 "BL	sub_FFC1C1D4\n"
		 "BL	sub_FFC19074\n"
		 "BL	sub_FFC1C350\n"
	);

	CreateTask_PhySw();

	asm volatile (
//		 "BL	sub_FFC12DD0\n"					// taskcreate_PhySw

		 "BL	sub_FFC15CAC_my\n"                              // jump to taskcreate_CaptSeqTask
		 "BL	sub_FFC1C368\n"
//		 "BL	sub_FFC10BBC\n"					// nullsub_2
		 "BL	sub_FFC12160\n"
		 "BL	sub_FFC1BD50\n"					// taskcreate_Bye
		 "BL	sub_FFC128FC\n"
		 "BL	sub_FFC1206C\n"					// taskcreate_TempCheck
		 "BL	sub_FFC1CDE0_my\n"				// SDHC-bootdisk-support	// <---------------
		 "BL	sub_FFC12028\n"
		 "BL	sub_FFC05088\n"					//
		 "LDMFD	SP!, {R4,PC}\n"					// to PC instead of LR to return to caller
//		"LDMFD	SP!, {R4,LR}\n"
//		"B	sub_FFC05088\n"
	);
}; //#fe

void CreateTask_spytask() { //#fs
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);

}; //#fe

void CreateTask_PhySw() { //#fs
        _CreateTask("PhySw", 0x18, 0x800, mykbd_task, 0);
        asm volatile (
			"BL		sub_FFC38128_my\n"  //----------> create 'JogDial' task
        );
}; //#fe


void __attribute__((naked,noinline)) sub_FFC15CAC_my() { 
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "LDR     R4, =0x1CB8\n"
                "MOV     R0, #0\n"
                "MOV     R1, #4\n"
                "STR     R0, [R4,#0xC]\n"
                "BL      sub_FFC0BEE8\n"
                "STR     R0, [R4,#4]\n"
                "MOV     R0, #0\n"
                "MOV     R1, #1\n"
                "BL      sub_FFC0BF0C\n"
                "STR     R0, [R4,#8]\n"
                "BL      sub_FFC51638\n"
                "BL      sub_FFC5055C\n"
                "BL      sub_FFC4D260_my\n"  //---------------->
                "BL      sub_FFC51900\n"
                "LDR     R0, [R4,#4]\n"
                "LDMFD   SP!, {R4,LR}\n"
                "MOV     R1, #0x1000\n"
                "B       sub_FFC193D4\n"
 );
}

void __attribute__((naked,noinline)) sub_FFC4D260_my() { 
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "LDR     R4, =0x5648\n"
                "LDR     R0, [R4,#8]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC4D2CC\n"
           //   "BL      nullsub_30\n"
                "MOV     R1, #1\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC0BF0C\n"
                "STR     R0, [R4,#0x1C]\n"
                "MOV     R0, #0\n"
                "MOV     R1, #0\n"
                "BL      sub_FFC0BEE8\n"
                "STR     R0, [R4,#0x20]\n"
                "BL      sub_FFC4D654\n"
                "BL      sub_FFC4D47C\n"        //taskcreate_ShootSeqTask
                "MOV     R0, #0\n"
                "STR     R0, [R4,#0x18]\n"
                "ADD     R0, R4, #0x24\n"
                "MOV     R1, #0\n"
                "STR     R1, [R0],#4\n"
                "STR     R1, [R0]\n"
                "BL      sub_FFC4D9F8\n"
                "BL      sub_FFC51AAC\n"
                "BL      sub_FFC4FEF4\n"
                "BL      taskcreate_CaptSeqTask_my\n"
                "BL      sub_FFC4F9E8\n"  //taskcreate_MovieCtrlTask
"loc_FFC4D2CC:\n"
                "MOV     R0, #1\n"
                "STR     R0, [R4,#8]\n"
                "LDMFD   SP!, {R4,PC}\n"
 );
}

void __attribute__((naked,noinline)) taskcreate_CaptSeqTask_my() { 
	asm volatile (
                "STMFD   SP!, {R3-R5,LR}\n"
                "LDR     R2, =0x197FC\n"
                "MOV     R0, #0\n"
                "MOV     R1, #0\n"
"loc_FFC4E50C:\n"
                "ADD     R3, R2, R0,LSL#4\n"
                "ADD     R0, R0, #1\n"
                "CMP     R0, #5\n"
                "STR     R1, [R3,#8]\n"
                "BCC     loc_FFC4E50C\n"
                "LDR     R0, =0x1984C\n"
                "STR     R1, [R0,#8]\n"
                "ADD     R0, R0, #0x10\n"
                "STR     R1, [R0,#8]\n"
                "BL      sub_FFD14630\n"
                "BL      sub_FFD1665C\n"
                "MOV     R1, #5\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC0BEC4\n"
                "LDR     R4, =0x5698\n"
                "LDR     R1, =0x1001FF\n"
                "STR     R0, [R4,#0x10]\n"
                "MOV     R0, #0\n"
                "BL      sub_FFC0BEE8\n"
                "STR     R0, [R4,#0xC]\n"
                "MOV     R3, #0\n"
                "STR     R3, [SP]\n"
                "LDR     R3, =CaptSeqTask\n"
                "LDR     R0, =0xFFC4E718\n" // "Captseqtask"
                "MOV     R2, #0x1000\n"
                "MOV     R1, #0x17\n"
                "BL      sub_FFC0BE90\n"
                "LDMFD   SP!, {R3-R5,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FFC1CDE0_my() { //#fs
	asm volatile (
		"STMFD	SP!, {R4,LR}\n"
		"BL		sub_FFC6059C\n"
		"BL		sub_FFC3B420\n"					// IsFactoryMode
		"CMP	R0, #1\n"
		"BNE	loc_FFC1CE00\n"
		"BL	sub_FFC636E8\n"
		"LDMFD	SP!, {R4,LR}\n"
		"B		sub_FFC3B498\n"					// StartFactoryModeController
	"loc_FFC1CE00:\n"
		"BL		sub_FFC62574\n"
		"LDR	R4, =0x1DD0\n"
		"LDR	R0, [R4,#4]\n"
		"CMP	R0, #0\n"
		"LDMNEFD	SP!, {R4,PC}\n"
		"MOV	R1, #0\n"
		"LDR	R0, =sub_FFC1C934_my\n"			// <---------
		"BL		sub_FFC5CF34\n"					// CreateController
		"STR	R0, [R4,#4]\n"
		"LDMFD	SP!, {R4,PC}\n"
	);
}; //#fe

void __attribute__((naked,noinline)) sub_FFC1C934_my() { //#fs
	asm volatile (

		 "STMFD	SP!, {R3-R11,LR}\n"
		 "LDR	R6, =0x1DD0\n"
		 "MOV	R5, R1\n"
		 "LDR	R0, [R6,#0x14]\n"
		 "MOV	R4, R3\n"
		 "CMP	R0, #1\n"
		 "BNE	loc_FFC1C958\n"
		 "BL	sub_FFC60DA4\n"
		 "B		loc_FFC1C9E8\n"
 "loc_FFC1C958:\n"
		 "LDR	R10, =0x1005\n"
		 "MOV	R7, #0\n"
		 "ADD	R12, R10, #0xAD\n"
		 "CMP	R5, R12\n"
		 "MOVEQ	R1, R4\n"
		 "ADDEQ	R0, R10, #3\n"
		 "MOV	R8, #1\n"
		 "BEQ	loc_FFC1CD2C\n"
		 "BGT	loc_FFC1CAA0\n"
		 "LDR	R12, =0x1061\n"
		 "CMP	R5, R12\n"
		 "BEQ	loc_FFC1CDB8\n"
		 "BGT	loc_FFC1CA18\n"
		 "LDR	R12, =0x1003\n"
		 "CMP	R5, R12\n"
		 "BEQ	loc_FFC1CD24\n"
		 "BGT	loc_FFC1C9F0\n"
		 "SUB	R12, R5, #0x800\n"
		 "SUBS	R12, R12, #3\n"
		 "BEQ	loc_FFC1CC28\n"
		 "SUB	R12, R5, #0x800\n"
		 "SUBS	R12, R12, #0x158\n"
		 "BEQ	loc_FFC1CDC4\n"
		 "LDR	R4, =0x9A3\n"
		 "CMP	R5, R4\n"
		 "SUBNE	R12, R5, #0x900\n"
		 "SUBNES	R12, R12, #0xA5\n"
		 "BNE	loc_FFC1CD08\n"
		 "LDR	R0, [R6,#0xC]\n"
		 "SUB	R12, R0, #0x8000\n"
		 "SUBS	R12, R12, #2\n"
		 "BEQ	loc_FFC1C9E8\n"
		 "LDR	R0, =0x10A5\n"
		 "BL	sub_FFC5F410\n"					// IsControlEventActive
		 "CMP	R0, #0\n"
		 "BEQ	loc_FFC1CD00\n"
 "loc_FFC1C9E8:\n"
		 "MOV	R0, #0\n"
		 "LDMFD	SP!, {R3-R11,PC}\n"
 "loc_FFC1C9F0:\n"
		 "CMP	R5, R10\n"
		 "BEQ	loc_FFC1CD44\n"
		 "SUB	R12, R5, #0x1000\n"
		 "SUBS	R12, R12, #0x56\n"
		 "SUBNE	R12, R5, #0x1000\n"
		 "SUBNES	R12, R12, #0x5B\n"
		 "SUBNE	R12, R5, #0x1000\n"
		 "SUBNES	R12, R12, #0x5E\n"
		 "BNE	loc_FFC1CD08\n"
		 "B	loc_FFC1CDB8\n"
 "loc_FFC1CA18:\n"
		 "LDR	R0, =0x10A3\n"
		 "ADD	R12, R0, #7\n"
		 "CMP	R5, R12\n"
		 "BEQ	loc_FFC1CD34\n"
		 "BGT	loc_FFC1CA6C\n"
		 "SUB	R12, R5, #0x1000\n"
		 "SUBS	R12, R12, #0x62\n"
		 "SUBNE	R12, R5, #0x1000\n"
		 "SUBNES	R12, R12, #0x63\n"
		 "SUBNE	R12, R5, #0x1000\n"
		 "SUBNES	R12, R12, #0x65\n"
		 "BEQ	loc_FFC1CDB8\n"
		 "SUB	R12, R5, #0x1000\n"
		 "SUBS	R12, R12, #0xA9\n"
		 "BNE	loc_FFC1CD08\n"
		 "BL	sub_FFC5F410\n"					// IsControlEventActive
		 "CMP	R0, #0\n"
		 "BNE	loc_FFC1C9E8\n"
 "loc_FFC1CA60:\n"
		 "MOV	R0, R5\n"
		 "BL	sub_FFC1C688\n"
		 "LDMFD	SP!, {R3-R11,PC}\n"
 "loc_FFC1CA6C:\n"
		 "SUB	R12, R5, #0x1000\n"
		 "SUBS	R12, R12, #0xAD\n"
		 "BEQ	loc_FFC1CA60\n"
		 "SUB	R12, R5, #0x1000\n"
		 "SUBS	R12, R12, #0xAE\n"
		 "BEQ	loc_FFC1CD40\n"
		 "SUB	R12, R5, #0x1000\n"
		 "SUBS	R12, R12, #0xAF\n"
		 "BEQ	loc_FFC1CA60\n"
		 "SUB	R12, R5, #0x1000\n"
		 "SUBS	R12, R12, #0xB0\n"
		 "BNE	loc_FFC1CD08\n"
		 "B		loc_FFC1CD40\n"
 "loc_FFC1CAA0:\n"
		 "LDR	R11, =0x2004\n"
		 "LDR	R1, =0x1DD0\n"
		 "ADD	R12, R11, #0x15\n"
		 "LDR	R0, [R1,#0x20]\n"
		 "LDR	R1, [R1,#0x10]\n"
		 "CMP	R5, R12\n"
		 "BEQ	loc_FFC1CD64\n"
		 "BGT	loc_FFC1CB50\n"
		 "LDR	R9, =0x1168\n"
		 "CMP	R5, R9\n"
		 "BEQ	loc_FFC1CB08\n"
		 "BGT	loc_FFC1CB20\n"
		 "SUB	R12, R5, #0x1100\n"
		 "SUBS	R12, R12, #0x62\n"
		 "BEQ	loc_FFC1CD14\n"
		 "SUB	R12, R5, #0x1100\n"
		 "SUBS	R12, R12, #0x63\n"
		 "MOVEQ	R1, #0\n"
		 "MOVEQ	R0, #0x82\n"
		 "BEQ	loc_FFC1CCF8\n"
		 "SUB	R12, R5, #0x1100\n"
		 "SUBS	R12, R12, #0x65\n"
		 "BEQ	loc_FFC1CCF0\n"
		 "SUB	R12, R5, #0x1100\n"
		 "SUBS	R12, R12, #0x67\n"
		 "BNE	loc_FFC1CD08\n"
 "loc_FFC1CB08:\n"
		 "LDR	R4, =0x4508\n"
		 "CMP	R0, #0\n"
		 "STR	R8, [R6,#0x10]\n"
		 "BEQ	loc_FFC1CCB4\n"
		 "BL	sub_FFC60DD8\n"
		 "B		loc_FFC1CCC0\n"
 "loc_FFC1CB20:\n"
		 "LDR	R8, =0x116A\n"
		 "CMP	R5, R8\n"
		 "BEQ	loc_FFC1CCCC\n"
		 "SUB	R12, R5, #0x2000\n"
		 "SUBS	R12, R12, #2\n"
		 "BEQ	loc_FFC1CD84\n"
		 "CMP	R5, R11\n"
		 "BEQ	loc_FFC1CD90\n"
		 "SUB	R12, R5, #0x2000\n"
		 "SUBS	R12, R12, #5\n"
		 "BNE	loc_FFC1CD08\n"
		 "B		loc_FFC1CD84\n"
 "loc_FFC1CB50:\n"
		 "LDR	R12, =0x3110\n"
		 "CMP	R5, R12\n"
		 "BEQ	loc_FFC1CD44\n"
		 "BGT	loc_FFC1CB94\n"
		 "LDR	R8, =0x201B\n"
		 "CMP	R5, R8\n"
		 "BEQ	loc_FFC1CCE0\n"
		 "SUB	R12, R5, #0x2000\n"
		 "SUBS	R12, R12, #0x1D\n"
		 "BEQ	loc_FFC1CD84\n"
		 "ADD	R0, R8,	#0xC\n"
		 "CMP	R5, R0\n"
		 "BEQ	loc_FFC1CD4C\n"
		 "SUB	R12, R5, #0x3000\n"
		 "SUBS	R12, R12, #6\n"
		 "BNE	loc_FFC1CD08\n"
		 "B		loc_FFC1CD44\n"
 "loc_FFC1CB94:\n"
		 "SUB	R12, R5, #0x3100\n"
		 "SUBS	R12, R12, #0x11\n"
		 "BEQ	loc_FFC1CD44\n"
		 "CMP	R5, #0x3140\n"
		 "BEQ	loc_FFC1CDAC\n"
		 "SUB	R12, R5, #0x3200\n"
		 "SUBS	R12, R12, #1\n"
		 "BEQ	loc_FFC1CD08\n"
		 "SUB	R12, R5, #0x3200\n"
		 "SUBS	R12, R12, #2\n"
		 "BNE	loc_FFC1CD08\n"
		 "B		loc_FFC1CD44\n"
 "loc_FFC1CC28:\n"
		 "MOV	R4, #1\n"
		 "MOV	R0, #2\n"
		 "BL	sub_FFC60630\n"
		 "CMP	R0, #1\n"
		 "MOVEQ	R4, #2\n"
		 "MOV	R0, R4\n"
		 "BL	sub_FFC124D8\n"
		 "CMP	R0, #0\n"
		 "STRNE	R8, [R6,#0x14]\n"
		 "BNE	loc_FFC1CC80\n"
		 "BL	sub_FFC661D4\n"
		 "BL	sub_FFC6408C\n"
		 "BL	sub_FFC64CC0\n"
		 "BL	sub_FFC63978\n"
		 "BL	sub_FFC65264\n"				// GetVRAMHPixelsSize_1
		 "CMP	R0, #0\n"
		 "BEQ	loc_FFC1CC88\n"
		 "BL	sub_FFC1C5BC\n"
		 "BL	sub_FFC651C8\n"
		 "MOV	R1, R0\n"
		 "LDR	R0, =0x1167\n"
		 "BL	sub_FFC5D730\n" 			// PostLogicalEventToUI
 "loc_FFC1CC80:\n"
		 "MOV	R0, R7\n"
		 "LDMFD	SP!, {R3-R11,PC}\n"
 "loc_FFC1CC88:\n"
		 "BL	sub_FFC162E4\n"
		 "CMP	R0, #1\n"
		 "LDRNE	R0, =0x310B\n"
		 "LDREQ	R0, =0x310C\n"
		 "MOV	R1, #0\n"
		 "BL	sub_FFC5D730\n" 			// PostLogicalEventToUI
		 "BL	sub_FFC633B0_my\n"			// Continue here (possibility 1) for SDHC-boot
		 "B		loc_FFC1CC80\n"
 "loc_FFC1CCA8:\n"
		 "MOV	R0, R4\n"
		 "BL	sub_FFC4BB88\n"
		 "B		loc_FFC1C9E8\n"
 "loc_FFC1CCB4:\n"
		 "BL	sub_FFC644D4\n"
		 "BL	sub_FFC6429C\n"
		 "BL	sub_FFC15FE0\n"
 "loc_FFC1CCC0:\n"
		 "CMP	R5, R9\n"
		 "BNE	loc_FFC1C9E8\n"
		 "B		loc_FFC1CCA8\n"
 "loc_FFC1CCCC:\n"
		 "MOV	R0, #1\n"
		 "BL	sub_FFC60F04\n"
		 "MOV	R1, R8\n"
		 "MOV	R0, R10\n"
		 "B		loc_FFC1CD2C\n"
 "loc_FFC1CCE0:\n"
		 "CMP	R1, #1\n"
		 "BNE	loc_FFC1CD44\n"
		 "BL	sub_FFC60DD8\n"
		 "B		loc_FFC1C9E8\n"
 "loc_FFC1CCF0:\n"
		 "MOV	R1, #0\n"
		 "MOV	R0, #0x83\n"
 "loc_FFC1CCF8:\n"
		 "BL	sub_FFC64D88\n"
		 "B		loc_FFC1C9E8\n"
 "loc_FFC1CD00:\n"
		 "CMP	R5, R4\n"
		 "STREQ	R8, [R6,#0x30]\n"
 "loc_FFC1CD08:\n"
		 "MOV	R1, #0\n"
 "loc_FFC1CD0C:\n"
		 "MOV	R0, R5\n"
		 "B		loc_FFC1CD2C\n"
 "loc_FFC1CD14:\n"
		 "BL	sub_FFC687DC\n"
		 "CMP	R0, #0\n"
		 "BLNE	sub_FFC675B4\n"
		 "B		loc_FFC1CD44\n"
 "loc_FFC1CD24:\n"
		 "BL	sub_FFC1C898\n"
		 "MOV	R1, R4\n"
 "loc_FFC1CD2C:\n"
		 "BL	sub_FFC622B4_my\n"			// Continue here (possibility 2) for SDHC-boot
		 "LDMFD	SP!, {R3-R11,PC}\n"
 "loc_FFC1CD34:\n"
		 "BL	sub_FFC5F410\n"				// IsControlEventActive
		 "CMP	R0, #0\n"
		 "BNE	loc_FFC1C9E8\n"
 "loc_FFC1CD40:\n"
		 "BL	sub_FFC1D1EC\n"
 "loc_FFC1CD44:\n"
		 "MOV	R1, R4\n"
		 "B		loc_FFC1CD0C\n"
 "loc_FFC1CD4C:\n"
		 "MOV	R1, #0\n"
		 "BL	sub_FFC622B4_my\n"			// Continue here (possibility 2) for SDHC-boot
		 "MOV	R1, #0\n"
		 "MOV	R0, R8\n"
		 "BL	sub_FFC622B4_my\n"			// Continue here (possibility 2) for SDHC-boot
		 "B		loc_FFC1CD74\n"
 "loc_FFC1CD64:\n"
		 "CMP	R0, #0\n"
		 "BEQ	loc_FFC1C9E8\n"
		 "CMP	R1, #0\n"
		 "BNE	loc_FFC1C9E8\n"
 "loc_FFC1CD74:\n"
		 "MOV	R1, #0\n"
		 "MOV	R0, R11\n"
 "loc_FFC1CD7C:\n"
		 "BL	sub_FFC622B4_my\n"			// Continue here (possibility 2) for SDHC-boot
		 "B		loc_FFC1C9E8\n"
 "loc_FFC1CD84:\n"
		 "STR	R7, [R6,#0x20]\n"
		 "BL	sub_FFC1CFE4\n"
		 "B		loc_FFC1CD44\n"
 "loc_FFC1CD90:\n"
		 "STR	R7, [R6,#0x20]\n"
		 "BL	sub_FFC1CFE4\n"
		 "LDR	R0, [R6,#0x10]\n"
		 "CMP	R0, #1\n"
		 "BNE	loc_FFC1CD44\n"
		 "BL	sub_FFC60E1C\n"
		 "B		loc_FFC1C9E8\n"
 "loc_FFC1CDAC:\n"
		 "CMP	R0, #0\n"
		 "BLEQ	sub_FFC1CFE4\n"
		 "B		loc_FFC1C9E8\n"
 "loc_FFC1CDB8:\n"

//		 "MOVL	R0, 0xFFFFFFFF\n"			// gcc complains that it is bad instrustion
		"LDR	R0, =0xFFFFFFFF\n"			// I think this should help us

		 "MOV	R1, #0\n"
		 "B		loc_FFC1CD7C\n"
 "loc_FFC1CDC4:\n"
		 "TST	R4, #0x80000000\n"
		 "MOVNE	R0, #1\n"
		 "LDMNEFD	SP!, {R3-R11,PC}\n"
		 "BL	sub_FFC69B38\n"
		 "CMP	R0, #0\n"
		 "BLEQ	sub_FFC18F60\n"
		 "B		loc_FFC1C9E8\n"
	);
}; //#fe

void __attribute__((naked,noinline)) sub_FFC633B0_my() { //#fs
	asm volatile (
		"STMFD	SP!, {R4,LR}\n"
		"BL		sub_FFC1CFB0\n"
		"MOV	R4, R0\n"
		"BL		sub_FFC634D4\n"
		"MOV	R0, R4\n"
		"BL		sub_FFC63264\n"
		"BL		sub_FFC1CFB0\n"
		"MOV	R4, R0\n"
		"LDR	R0, =0x5EAC\n"
		"LDR	R0, [R0]\n"
		"TST	R0, #1\n"
		"TSTEQ	R0, #0x10\n"
		"BEQ	loc_FFC633F0\n"
	"loc_FFC633E4:\n"
		"MOV	R1, R4\n"
		"MOV	R0, #2\n"
		"B		loc_FFC63434\n"
	"loc_FFC633F0:\n"
		"TST	R0, #0x40\n"
		"BEQ	loc_FFC63404\n"
	"loc_FFC633F8:\n"
		"MOV	R1, R4\n"
		"MOV	R0, #1\n"
		"B		loc_FFC63434\n"
	"loc_FFC63404:\n"
		"TST	R0, #0x20\n"
		"BEQ	loc_FFC63420\n"
		"TST	R0, #0x4000\n"
		"BNE	loc_FFC63420\n"
	"loc_FFC63414:\n"
		"MOV	R1, R4\n"
		"MOV	R0, #0\n"
		"B		loc_FFC63434\n"
	"loc_FFC63420:\n"
		"LDR	R1, =0x102\n"
		"BICS	R1, R1,	R0\n"
		"BNE	loc_FFC6343C\n"
		"MOV	R1, R4\n"
		"MOV	R0, #6\n"
	"loc_FFC63434:\n"
		"LDMFD	SP!, {R4,LR}\n"
		"B		sub_FFC63200_my\n"			// <-------------- // cont. for SDHC-boot
	"loc_FFC6343C:\n"
		"TST	R0, #0x100\n"
		"BNE	loc_FFC633E4\n"
		"TST	R0, #0x4000\n"
		"TSTEQ	R0, #0x400\n"
		"BNE	loc_FFC633F8\n"
		"TST	R0, #0x200\n"
		"TSTEQ	R0, #2\n"
		"BNE	loc_FFC63414\n"
		"TST	R0, #0x40000\n"
		"BEQ	loc_FFC633E4\n"
		"TST	R0, #0x200000\n"
		"MOVEQ	R1, R4\n"
		"MOVEQ	R0, #1\n"
		"BLEQ	sub_FFC63200_my\n"			// <----------------
		"B		loc_FFC633E4\n"
	);
}; //#fe

void __attribute__((naked,noinline)) sub_FFC63200_my() { //#fs
	asm volatile (
		 "STMFD	SP!, {R4-R6,LR}\n"
		 "MOVS	R4, R0\n"
		 "MOV	R0, #1\n"
		 "MOV	R5, R1\n"
		 "BNE	loc_FFC63240\n"
		 "MOV	R1, #0\n"
		 "MOV	R0, #0\n"
		 "BL	sub_FFC605C0\n"
		 "BL	sub_FFC1CFB0\n"
		 "SUB	R12, R0, #0x1000\n"
		 "SUBS	R12, R12, #0x5B\n"
		 "BNE	loc_FFC63238\n"
 "loc_FFC63230:\n"
		 "BL	sub_FFC63134\n"
		 "B		loc_FFC63248\n"
 "loc_FFC63238:\n"
		 "BL	sub_FFC63194\n"
		 "B		loc_FFC63248\n"
 "loc_FFC63240:\n"
		 "CMP	R4, #5\n"
		 "BEQ	loc_FFC63230\n"
 "loc_FFC63248:\n"
		 "CMP	R0, #0\n"
		 "LDREQ	R5, =0x1162\n"
		 "MOVEQ	R4, #2\n"
		 "MOV	R0, R4\n"
		 "MOV	R1, R5\n"
		 "LDMFD	SP!, {R4-R6,LR}\n"
		 "B		sub_FFC622B4_my\n"			// <-----------
	);
}; //#fe

void __attribute__((naked,noinline)) sub_FFC622B4_my() { //#fs
	asm volatile (
		"STMFD	SP!, {R4-R8,LR}\n"
		"MOV	R8, R1\n"
		"MOV	R4, R0\n"
		"BL		sub_FFC65264\n"				// GetVRAMHPixelsSize_1
		"CMP	R0, #0\n"
		"BNE	loc_FFC6256C\n"
		"MOV	R1, R8\n"
		"MOV	R0, R4\n"
		"BL		sub_FFC61104\n"
		"LDR	R5, =0x5DE4\n"
		"MOV	R7, #1\n"
		"LDR	R0, [R5,#0x10]\n"
		"MOV	R6, #0\n"
		"CMP	R0, #0x16\n"
		"ADDLS	PC, PC,	R0,LSL#2\n"
		"B		loc_FFC6256C\n"
	"loc_FFC622F4:\n"
		"B		loc_FFC62350\n"
	"loc_FFC622F8:\n"
		"B		loc_FFC6236C\n"
	"loc_FFC622FC:\n"
		"B		loc_FFC623B0\n"
	"loc_FFC62300:\n"
		"B		loc_FFC6242C\n"
	"loc_FFC62304:\n"
		"B		loc_FFC6243C\n"
	"loc_FFC62308:\n"
		"B		loc_FFC6256C\n"
	"loc_FFC6230C:\n"
		"B		loc_FFC624B8\n"
	"loc_FFC62310:\n"
		"B		loc_FFC624C8\n"
	"loc_FFC62314:\n"
		"B		loc_FFC62360\n"
	"loc_FFC62318:\n"
		"B		loc_FFC6256C\n"
	"loc_FFC6231C:\n"
		"B		loc_FFC624C8\n"
	"loc_FFC62320:\n"
		"B		loc_FFC623A4\n"
	"loc_FFC62324:\n"
		"B		loc_FFC6256C\n"
	"loc_FFC62328:\n"
		"B		loc_FFC6256C\n"
	"loc_FFC6232C:\n"
		"B		loc_FFC623BC\n"
	"loc_FFC62330:\n"
		"B		loc_FFC623C8\n"
	"loc_FFC62334:\n"
		"B		loc_FFC62400\n"
	"loc_FFC62338:\n"
		"B		loc_FFC62378\n"
	"loc_FFC6233C:\n"
		"B		loc_FFC62554\n"
	"loc_FFC62340:\n"
		"B		loc_FFC624D4\n"
	"loc_FFC62344:\n"
		"B		loc_FFC62504\n"
	"loc_FFC62348:\n"
		"B		loc_FFC62504\n"
	"loc_FFC6234C:\n"
		"B		loc_FFC62448\n"
	"loc_FFC62350:\n"
		"MOV	R1, R8\n"
		"MOV	R0, R4\n"
		"LDMFD	SP!, {R4-R8,LR}\n"
		"B		sub_FFC61BBC_my\n"				// <----------// uAC_Boot // divert for SDHC-boot
	"loc_FFC62360:\n"
		"MOV	R0, R4\n"
		"LDMFD	SP!, {R4-R8,LR}\n"
		"B		sub_FFC62C7C\n"
	"loc_FFC6236C:\n"
		"MOV	R0, R4\n"
		"LDMFD	SP!, {R4-R8,LR}\n"
		"B		sub_FFC617A0\n"
	"loc_FFC62378:\n"
		"SUB	R12, R4, #0x1000\n"
		"SUBS	R12, R12, #0xA5\n"
		"STREQ	R7, [R5,#0x88]\n"
		"BEQ	loc_FFC62564\n"
		"SUB	R12, R4, #0x3000\n"
		"SUBS	R12, R12, #6\n"
		"BNE	loc_FFC6256C\n"
		"MOV	R0, #0\n"
		"BL		sub_FFC1C444\n"
		"BL		sub_FFC62B5C\n"
		"B		loc_FFC62564\n"
	"loc_FFC623A4:\n"
		"MOV	R0, R4\n"
		"LDMFD	SP!, {R4-R8,LR}\n"
		"B		sub_FFC62B94\n"
	"loc_FFC623B0:\n"
		"MOV	R0, R4\n"
		"LDMFD	SP!, {R4-R8,LR}\n"
		"B		sub_FFC61978\n"
	"loc_FFC623BC:\n"
		"MOV	R0, R4\n"
		"LDMFD	SP!, {R4-R8,LR}\n"
		"B		sub_FFC61FE0\n"
	"loc_FFC623C8:\n"
		"SUB	R12, R4, #0x3200\n"
		"SUBS	R12, R12, #2\n"
		"BNE	loc_FFC6256C\n"
		"MOV	R0, #3\n"
		"BL		sub_FFC60FE8\n"
		"MOV	R0, #8\n"
		"BL		sub_FFC1C3AC\n"
		"MOV	R1, #0\n"
		"MOV	R0, #0x19\n"
		"BL		sub_FFC2D9D0\n"
		"BL		sub_FFC644D4\n"
		"BL		sub_FFC64320\n"
		"BL		sub_FFC639E8\n"
		"B		loc_FFC62564\n"
	"loc_FFC62400:\n"
		"SUB	R12, R4, #0x3300\n"
		"SUBS	R12, R12, #1\n"
		"BNE	loc_FFC6256C\n"
		"LDR	R0, =0x4010\n"
		"STR	R6, [R5,#0x80]\n"
		"BL		sub_FFC1C3AC\n"
		"BL		sub_FFD69318\n"
		"BL		sub_FFC639E8\n"
		"MOV	R0, #4\n"
		"BL		sub_FFC60FE8\n"
		"B		loc_FFC62564\n"
	"loc_FFC6242C:\n"
		"MOV	R1, R8\n"
		"MOV	R0, R4\n"
		"LDMFD	SP!, {R4-R8,LR}\n"
		"B		sub_FFC62140\n"
	"loc_FFC6243C:\n"
		"MOV	R0, R4\n"
		"LDMFD	SP!, {R4-R8,LR}\n"
		"B		sub_FFC62DC0\n"
	"loc_FFC62448:\n"
		"LDR	R8, =0x1182\n"
		"CMP	R4, R8\n"
		"STREQ	R7, [R5,#0xB0]\n"
		"BEQ	loc_FFC62564\n"
		"SUB	R12, R4, #0x1000\n"
		"SUBS	R12, R12, #0x1AC\n"
		"BEQ	loc_FFC624A0\n"
		"SUB	R12, R4, #0x3000\n"
		"SUBS	R12, R12, #0x224\n"
		"BNE	loc_FFC6256C\n"
		"MOV	R0, #8\n"
		"BL		sub_FFC1C3AC\n"
		"MOV	R0, #3\n"
		"BL		sub_FFC60FE8\n"
		"STR	R6, [R5,#0xB4]\n"
		"LDR	R0, [R5,#0xB0]\n"
		"CMP	R0, #0\n"
		"MOVNE	R1, #0\n"
		"MOVNE	R0, R8\n"
		"STRNE	R6, [R5,#0xB0]\n"
		"BLNE	sub_FFC62140\n"
		"B		loc_FFC62564\n"
	"loc_FFC624A0:\n"
		"LDR	R0, [R5,#0xB4]\n"
		"CMP	R0, #0\n"
		"BNE	loc_FFC62564\n"
		"BL		sub_FFD67478\n"
		"STR	R7, [R5,#0xB4]\n"
		"B		loc_FFC62564\n"
	"loc_FFC624B8:\n"
		"MOV	R1, R8\n"
		"MOV	R0, R4\n"
		"LDMFD	SP!, {R4-R8,LR}\n"
		"B		sub_FFC62EA0\n"
	"loc_FFC624C8:\n"
		"MOV	R0, R4\n"
		"LDMFD	SP!, {R4-R8,LR}\n"
		"B		sub_FFC61ED8_my\n"	// <---------------	//NOTE this func is in movie_rec.c
	"loc_FFC624D4:\n"
		"LDR	R12, =0x10B0\n"
		"CMP	R4, R12\n"
		"BEQ	loc_FFC62500\n"
		"BGT	loc_FFC6250C\n"
		"CMP	R4, #4\n"
		"BEQ	loc_FFC62534\n"
		"SUB	R12, R4, #0x1000\n"
		"SUBS	R12, R12, #0xAA\n"
		"SUBNE	R12, R4, #0x1000\n"
		"SUBNES	R12, R12, #0xAE\n"
		"BNE	loc_FFC6256C\n"
	"loc_FFC62500:\n"
		"BL		sub_FFC60CC0\n"
	"loc_FFC62504:\n"
		"MOV	R0, R6\n"
		"LDMFD	SP!, {R4-R8,PC}\n"
	"loc_FFC6250C:\n"
		"SUB	R12, R4, #0x2000\n"
		"SUBS	R12, R12, #4\n"
		"BEQ	loc_FFC6254C\n"
		"SUB	R12, R4, #0x5000\n"
		"SUBS	R12, R12, #1\n"
		"SUBNE	R12, R4, #0x5000\n"
		"SUBNES	R12, R12, #6\n"
		"BNE	loc_FFC6256C\n"
		"BL		sub_FFC61740\n"
		"B		loc_FFC62564\n"
	"loc_FFC62534:\n"
		"LDR	R0, [R5,#0x2C]\n"
		"CMP	R0, #0\n"
		"BNE	loc_FFC6254C\n"
		"BL		sub_FFC62744\n"
		"BL		sub_FFC15F98\n"
		"B		loc_FFC62564\n"
	"loc_FFC6254C:\n"
		"BL		sub_FFC60CFC\n"
		"B		loc_FFC62564\n"
	"loc_FFC62554:\n"
		"SUB	R12, R4, #0x3000\n"
		"SUBS	R12, R12, #0x130\n"
		"BNE	loc_FFC6256C\n"
		"BL		sub_FFC60DA4\n"
	"loc_FFC62564:\n"
		"MOV	R0, #0\n"
		"LDMFD	SP!, {R4-R8,PC}\n"
	"loc_FFC6256C:\n"
		"MOV	R0, #1\n"
		"LDMFD	SP!, {R4-R8,PC}\n"
	);
}; //#fe

void __attribute__((naked,noinline)) sub_FFC61BBC_my() { //#fs uAC_Boot
	asm volatile (
		"STMFD	SP!, {R4-R8,LR}\n"
		"LDR	R7, =0x8002\n"
		"LDR	R4, =0x5DE4\n"
		"CMP	R0, #2\n"
		"MOV	R6, R1\n"
		"MOV	R5, #1\n"
		"BEQ	loc_FFC61C58\n"
		"BGT	loc_FFC61C40\n"
		"CMP	R0, #0\n"
		"BEQ	loc_FFC61C84\n"
		"CMP	R0, #1\n"
		"BNE	loc_FFC61D28\n"
		"MOV	R0, #8\n"
		"BL		sub_FFC60FE8\n"				// uCameraConState
		"BL		sub_FFC63618\n"				// taskcreate_CommonDrivers
		"BL		sub_FFC64170\n"				// uDispSwLock
		"LDR	R5, =0x4004\n"
		"MOV	R0, #0\n"
		"MOV	R1, R5\n"
		"BL		sub_FFC64D88\n"
		"LDR	R1, =0xFFC61D64\n"			// aAcBootpb //"AC:BootPB"
		"MOV	R0, #0x20\n"
		"BL		sub_FFC59F58\n"
		"BL		sub_FFC635DC_my\n"			// taskcreate_InitFileModules	// <----------------------
		"BL		sub_FFC636E8\n"
		"BL		sub_FFC1CEE8\n"
		"MOV	R0, R5\n"
		"BL		sub_FFC1C3AC\n"
		"LDR	R0, [R4,#0x68]\n"
		"CMP	R0, #0\n"
		"BNE	loc_FFC61D08\n"
		"BL		sub_FFC1C598\n"				// taskcreate_StartupImage
		"B		loc_FFC61D0C\n"
	"loc_FFC61C40:\n"
		"CMP	R0, #6\n"
		"STREQ	R5, [R4,#0x28]\n"
		"BEQ	loc_FFC61D1C\n"
		"SUB	R12, R0, #0x2000\n"
		"SUBS	R12, R12, #4\n"
		"BNE	loc_FFC61D28\n"
	"loc_FFC61C58:\n"
		"SUB	R12, R6, #0x1100\n"
		"SUBS	R12, R12, #0x62\n"
		"BNE	loc_FFC61C74\n"
		"MOV	R1, R7\n"
		"MOV	R0, #0\n"
		"BL		sub_FFC64D88\n"
		"STR	R5, [R4,#0x60]\n"
	"loc_FFC61C74:\n"
		"BL		sub_FFC644D4\n"
		"BL		sub_FFC64320\n"
		"BL		sub_FFC616A4\n"
		"B		loc_FFC61D20\n"
	"loc_FFC61C84:\n"
		"MOV	R0, #7\n"
		"BL		sub_FFC60FE8\n"
		"MOV	R0, R7\n"
		"BL		sub_FFC1C3AC\n"
		"BL		sub_FFC63618\n"				// taskcreate_CommonDrivers
		"BL		sub_FFC64170\n"
		"MOV	R1, R7\n"
		"MOV	R0, #0\n"
		"BL		sub_FFC64D88\n"
		"LDR	R1, =0xFFC61D70\n"			// aAcBootrec	"AC:BootRec"
		"MOV	R0, #0x20\n"
		"STR	R6, [R4,#0x18]\n"
		"BL		sub_FFC59F58\n"
		"LDR	R1, =0xFFC61D7C\n"			// aAcInitlens	"AC:InitLens"
		"MOV	R0, #0x20\n"
		"BL		sub_FFC59F58\n"
		"STR	R5, [R4,#0x28]\n"
		"BL		sub_FFC1C528\n"
		"BL		sub_FFC1C46C\n"
		"LDR	R0, [R4,#0x1C]\n"
		"LDR	R1, [R4,#0x20]\n"
		"ORRS	R0, R0,	R1\n"
		"BLNE	sub_FFC62720\n"
		"LDR	R0, [R4,#0x68]\n"
		"CMP	R0, #0\n"
		"BNE	loc_FFC61CF4\n"
		"BL		sub_FFC1C598\n"				// taskcreate_StartupImage
		"B		loc_FFC61CFC\n"
	"loc_FFC61CF4:\n"
		"BL		sub_FFC15D0C\n"
		"BL		sub_FFC1CF54\n"
	"loc_FFC61CFC:\n"
		"BL		sub_FFC635DC_my\n"			// taskcreate_InitFileModules // <---------------
		"BL		sub_FFC63654\n"
		"B		loc_FFC61D20\n"
	"loc_FFC61D08:\n"
		"BL		sub_FFC15D0C\n"
	"loc_FFC61D0C:\n"
		"BL		sub_FFC63684\n"
		"LDR	R0, [R4,#0x30]\n"
		"CMP	R0, #0\n"
		"BEQ	loc_FFC61D20\n"
	"loc_FFC61D1C:\n"
		"BL		sub_FFC62768\n"
	"loc_FFC61D20:\n"
		"MOV	R0, #0\n"
		"LDMFD	SP!, {R4-R8,PC}\n"
	"loc_FFC61D28:\n"
		"MOV	R0, #1\n"
		"LDMFD	SP!, {R4-R8,PC}\n"
	);
}; //#fe

void __attribute__((naked,noinline)) sub_FFC635DC_my() { //#fs taskcreate_InitFileModules
	asm volatile (
		 "LDR	R0, =0x5EB8\n"
		 "STMFD	SP!, {R3,LR}\n"
		 "LDR	R1, [R0,#4]\n"
		 "CMP	R1, #0\n"
		 "BNE	locret_FFC63614\n"
		 "MOV	R1, #1\n"
		 "STR	R1, [R0,#4]\n"
		 "MOV	R3, #0\n"
		 "STR	R3, [SP]\n"
		 "LDR	R3, =task_InitFileModules_my\n"	// continue for SDHC-boot (orig: FFC6358C)	// <---------------
		 "MOV	R1, #0x19\n"
		 "LDR	R0, =0xFFC63740\n"			// aInitfilemodule
		 "MOV	R2, #0x1000\n"
		 "BL	sub_FFC0BBB8\n"				// CreateTask
 "locret_FFC63614:\n"
		 "LDMFD	SP!, {R12,PC}\n"
	);
}; //#fe

void __attribute__((naked,noinline)) task_InitFileModules_my() { //#fs
	asm volatile (
		"STMFD	SP!, {R4-R6,LR}\n"
		"BL		sub_FFC5C550\n"
		"LDR	R5, =0x5006\n"
		"MOVS	R4, R0\n"
		"MOVNE	R1, #0\n"
		"MOVNE	R0, R5\n"
		"BLNE	sub_FFC5D730\n"				// PostLogicalEventToUI
		"BL		sub_FFC5C57C_my\n"			// continue to SDHC-hook here!

		"BL		core_spytask_can_start\n"	// CHDK: Set "it's-save-to-start"-Flag for spytask

		"CMP	R4, #0\n"
		"MOVEQ	R0, R5\n"
		"LDMEQFD	SP!, {R4-R6,LR}\n"
		"MOVEQ	R1, #0\n"
		"BEQ	sub_FFC5D730\n"				// PostLogicalEventToUI
		"LDMFD	SP!, {R4-R6,PC}\n"
	);
}; //#fe

void __attribute__((naked,noinline)) sub_FFC5C57C_my() { //#fs
	asm volatile (
		"STMFD	SP!, {R4,LR}\n"
		"BL		sub_FFC402A8_my\n"		// <--------	continue to SDHC-hook here!
		"LDR	R4, =0x5908\n"
		"LDR	R0, [R4,#4]\n"
		"CMP	R0, #0\n"
		"BNE	loc_FFC5C5AC\n"
		"BL		sub_FFC6BB60\n"
		"BL		sub_FFCE6D24\n"
		"BL		sub_FFC6BB60\n"
		"BL		sub_FFCF0804\n"
		"BL		sub_FFC6BB70\n"
		"BL		sub_FFCE6DC4\n"
	"loc_FFC5C5AC:\n"
		"MOV	R0, #1\n"
		"STR	R0, [R4]\n"
		"LDMFD	SP!, {R4,PC}\n"
	);
}; //#fe

void __attribute__((naked,noinline)) sub_FFC402A8_my() { //#fs
	asm volatile (
		"STMFD	SP!, {R4-R6,LR}\n"
		"MOV	R6, #0\n"
		"MOV	R0, R6\n"
		"BL		sub_FFC3FE78\n"
		"LDR	R4, =0x11DE0\n"
		"MOV	R5, #0\n"
		"LDR	R0, [R4,#0x38]\n"
		"BL		sub_FFC40840\n"
		"CMP	R0, #0\n"
		"LDREQ	R0, =0x2BB4\n"
		"STREQ	R5, [R0,#0xC]\n"
		"STREQ	R5, [R0,#0x10]\n"
		"STREQ	R5, [R0,#0x14]\n"
		"MOV	R0, R6\n"
		"BL		sub_FFC3FEB8\n"		// uMounter (u=unknown, just to prevent misunderstandings)
		"MOV	R0, R6\n"
		"BL		sub_FFC400E4_my\n"		// <------------	// continue to SDHC-hook here!
		"MOV	R5, R0\n"
		"MOV	R0, R6\n"
		"BL		sub_FFC40150\n"
		"LDR	R1, [R4,#0x3C]\n"
		"AND	R2, R5,	R0\n"
		"CMP	R1, #0\n"
		"MOV	R0, #0\n"
		"MOVEQ	R0, #0x80000001\n"
		"BEQ	loc_FFC4033C\n"
		"LDR	R3, [R4,#0x2C]\n"
		"CMP	R3, #2\n"
		"MOVEQ	R0, #4\n"
		"CMP	R1, #5\n"
		"ORRNE	R0, R0,	#1\n"
		"BICEQ	R0, R0,	#1\n"
		"CMP	R2, #0\n"
		"BICEQ	R0, R0,	#2\n"
		"ORREQ	R0, R0,	#0x80000000\n"
		"BICNE	R0, R0,	#0x80000000\n"
		"ORRNE	R0, R0,	#2\n"
	"loc_FFC4033C:\n"
		"STR	R0, [R4,#0x40]\n"
		"LDMFD	SP!, {R4-R6,PC}\n"
	);
}; //#fe

void __attribute__((naked,noinline)) sub_FFC400E4_my() { //#fs
	asm volatile (
		 "STMFD	SP!, {R4-R6,LR}\n"
		 "LDR	R5, =0x2BB4\n"
		 "MOV	R6, R0\n"
		 "LDR	R0, [R5,#0x10]\n"
		 "CMP	R0, #0\n"
		 "MOVNE	R0, #1\n"
		 "LDMNEFD	SP!, {R4-R6,PC}\n"
		 "MOV	R0, #0x17\n"
		 "MUL	R1, R0,	R6\n"
		 "LDR	R0, =0x11DE0\n"
		 "ADD	R4, R0,	R1,LSL#2\n"
		 "LDR	R0, [R4,#0x38]\n"
		 "MOV	R1, R6\n"
		 "BL	sub_FFC3FF7C_my\n"		// <-----------	continue to SDHC-hook here!
		 "CMP	R0, #0\n"
		 "LDMEQFD	SP!, {R4-R6,PC}\n"
		 "LDR	R0, [R4,#0x38]\n"
		 "MOV	R1, R6\n"
		 "BL	sub_FFC40958\n"
		 "CMP	R0, #0\n"
		 "LDMEQFD	SP!, {R4-R6,PC}\n"
		 "MOV	R0, R6\n"
		 "BL	sub_FFC3FA98\n"
		 "CMP	R0, #0\n"
		 "MOVNE	R1, #1\n"
		 "STRNE	R1, [R5,#0x10]\n"
		 "LDMFD	SP!, {R4-R6,PC}\n"
	);
}; //#fe

void __attribute__((naked,noinline)) sub_FFC3FF7C_my() { //#fs
	asm volatile (
		 "STMFD	SP!, {R4-R8,LR}\n"
		 "MOV	R8, R0\n"
		 "MOV	R0, #0x17\n"
		 "MUL	R1, R0,	R1\n"
		 "LDR	R0, =0x11DE0\n"
		 "MOV	R6, #0\n"
		 "ADD	R7, R0,	R1,LSL#2\n"
		 "LDR	R0, [R7,#0x3C]\n"
		 "MOV	R5, #0\n"
		 "CMP	R0, #6\n"
		 "ADDLS	PC, PC,	R0,LSL#2\n"
		 "B	loc_FFC400C8\n"
	"loc_FFC3FFAC:\n"
		 "B	loc_FFC3FFE0\n"
	"loc_FFC3FFB0:\n"
		 "B	loc_FFC3FFC8\n"
	"loc_FFC3FFB4:\n"
		 "B	loc_FFC3FFC8\n"
	"loc_FFC3FFB8:\n"
		 "B	loc_FFC3FFC8\n"
	"loc_FFC3FFBC:\n"
		 "B	loc_FFC3FFC8\n"
	"loc_FFC3FFC0:\n"
		 "B	loc_FFC400C0\n"
	"loc_FFC3FFC4:\n"
		 "B	loc_FFC3FFC8\n"
	"loc_FFC3FFC8:\n"
		 "MOV	R2, #0\n"
		 "MOV	R1, #0x200\n"
		 "MOV	R0, #3\n"
		 "BL	sub_FFC58A28\n"
		 "MOVS	R4, R0\n"
		 "BNE	loc_FFC3FFE8\n"
	"loc_FFC3FFE0:\n"
		 "MOV	R0, #0\n"
		 "LDMFD	SP!, {R4-R8,PC}\n"
	"loc_FFC3FFE8:\n"
		 "LDR	R12, [R7,#0x4C]\n"
		 "MOV	R3, R4\n"
		 "MOV	R2, #1\n"
		 "MOV	R1, #0\n"
		 "MOV	R0, R8\n"

//		"BLX	R12\n"				// !! Workaround !!
		"MOV	LR, PC\n"			// gcc won't compile "BLX R12" nor "BL R12".
		"MOV	PC, R12\n"			// workaround: make your own "BL" and hope we don't need the change to thumb-mode

		 "CMP	R0, #1\n"
		 "BNE	loc_FFC40014\n"
		 "MOV	R0, #3\n"
		 "BL	sub_FFC58B68\n"
		 "B	loc_FFC3FFE0\n"
	"loc_FFC40014:\n"
		 "MOV	R0, R8\n"
		 "BL	sub_FFCFF8B8\n"			// Add FAT32 autodetect-code after this line\n"

		 "MOV   R1, R4\n"           //  pointer to MBR in R1
		 "BL    mbr_read_dryos\n"   //  total sectors count in R0 before and after call

// Start of DataGhost's FAT32 autodetection code
// Policy: If there is a partition which has type W95 FAT32, use the first one of those for image storage
// According to the code below, we can use R1, R2, R3 and R12.
// LR wasn't really used anywhere but for storing a part of the partition signature. This is the only thing
// that won't work with an offset, but since we can load from LR+offset into LR, we can use this to do that :)
		"MOV     R12, R4\n"					// Copy the MBR start address so we have something to work with
		"MOV     LR, R4\n"					// Save old offset for MBR signature
		"MOV     R1, #1\n"					// Note the current partition number
		"B       dg_sd_fat32_enter\n"		// We actually need to check the first partition as well, no increments yet!
	"dg_sd_fat32:\n"
		"CMP     R1, #4\n"					// Did we already see the 4th partition?
		"BEQ     dg_sd_fat32_end\n"			// Yes, break. We didn't find anything, so don't change anything.
		"ADD     R12, R12, #0x10\n"			// Second partition
		"ADD     R1, R1, #1\n"				// Second partition for the loop
	"dg_sd_fat32_enter:\n"
		"LDRB    R2, [R12, #0x1BE]\n"		// Partition status
		"LDRB    R3, [R12, #0x1C2]\n"		// Partition type (FAT32 = 0xB)
		"CMP     R3, #0xB\n"				// Is this a FAT32 partition?
		"CMPNE   R3, #0xC\n"				// Not 0xB, is it 0xC (FAT32 LBA) then?
		"BNE     dg_sd_fat32\n"				// No, it isn't.
		"CMP     R2, #0x00\n"				// It is, check the validity of the partition type
		"CMPNE   R2, #0x80\n"
		"BNE     dg_sd_fat32\n"				// Invalid, go to next partition
											// This partition is valid, it's the first one, bingo!
		"MOV     R4, R12\n"					// Move the new MBR offset for the partition detection.

	"dg_sd_fat32_end:\n"
// End of DataGhost's FAT32 autodetection code





		 "LDRB	R1, [R4,#0x1C9]\n"		// Continue with firmware
		 "LDRB	R3, [R4,#0x1C8]\n"
		 "LDRB	R12, [R4,#0x1CC]\n"
		 "MOV	R1, R1,LSL#24\n"
		 "ORR	R1, R1,	R3,LSL#16\n"
		 "LDRB	R3, [R4,#0x1C7]\n"
		 "LDRB	R2, [R4,#0x1BE]\n"
//		"LDRB	LR, [R4,#0x1FF]\n"		// replaced, see below
		 "ORR	R1, R1,	R3,LSL#8\n"
		 "LDRB	R3, [R4,#0x1C6]\n"
		 "CMP	R2, #0\n"
		 "CMPNE	R2, #0x80\n"
		 "ORR	R1, R1,	R3\n"
		 "LDRB	R3, [R4,#0x1CD]\n"
		 "MOV	R3, R3,LSL#24\n"
		 "ORR	R3, R3,	R12,LSL#16\n"
		 "LDRB	R12, [R4,#0x1CB]\n"
		 "ORR	R3, R3,	R12,LSL#8\n"
		 "LDRB	R12, [R4,#0x1CA]\n"
		 "ORR	R3, R3,	R12\n"
//		"LDRB	R12, [R4,#0x1FE]\n"		// replaced, see below

		"LDRB    R12, [LR,#0x1FE]\n"            // New! First MBR signature byte (0x55)
		"LDRB    LR, [LR,#0x1FF]\n"             //      Last MBR signature byte (0xAA)


		 "MOV	R4, #0\n"
		 "BNE	loc_FFC4009C\n"
		 "CMP	R0, R1\n"
		 "BCC	loc_FFC4009C\n"
		 "ADD	R2, R1,	R3\n"
		 "CMP	R2, R0\n"
		 "CMPLS	R12, #0x55\n"
		 "CMPEQ	LR, #0xAA\n"
		 "MOVEQ	R6, R1\n"
		 "MOVEQ	R5, R3\n"
		 "MOVEQ	R4, #1\n"
	"loc_FFC4009C:\n"
		 "MOV	R0, #3\n"
		 "BL	sub_FFC58B68\n"
		 "CMP	R4, #0\n"
		 "BNE	loc_FFC400D4\n"
		 "MOV	R6, #0\n"
		 "MOV	R0, R8\n"
		 "BL	sub_FFCFF8B8\n"
		 "MOV	R5, R0\n"
		 "B	loc_FFC400D4\n"
	"loc_FFC400C0:\n"
		 "MOV	R5, #0x40\n"
		 "B	loc_FFC400D4\n"
	"loc_FFC400C8:\n"
		 "LDR	R1, =0x365\n"
		 "LDR	R0, =0xFFC3FF70\n"		// aMounter_c
		 "BL	sub_FFC0C090\n"		// DebugAssert
	"loc_FFC400D4:\n"
		 "STR	R6, [R7,#0x44]!\n"
		 "MOV	R0, #1\n"
		 "STR	R5, [R7,#4]\n"
		 "LDMFD	SP!, {R4-R8,PC}\n"
		 ".LTORG\n"
	);
}; //#fe

void __attribute__((naked,noinline)) sub_FFC38128_my() { 
 asm volatile(
                "STMFD   SP!, {R3-R5,LR}\n"
                "LDR     R4, =0x2590\n"
                "LDR     R0, [R4,#8]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC3815C\n"
                "MOV     R3, #0\n"
                "STR     R3, [SP]\n"
                "LDR     R3, =JogDial_task_my\n"
                "MOV     R2, #0x800\n"
                "MOV     R1, #0x18\n"
                "LDR     R0, =0xFFC38288\n"
                "BL      sub_FFC0BE90\n"
                "STR     R0, [R4,#8]\n"
"loc_FFC3815C:\n"
                "LDMFD   SP!, {R3-R5,PC}\n"
 );
}

void __attribute__((naked,noinline)) JogDial_task_my() { 
 asm volatile(
                "STMFD   SP!, {R3-R11,LR}\n"
                "BL      sub_FFC382A8\n"
                "LDR     R11, =0x80000B01\n"
                "LDR     R8, =0xFFE5FAA4\n"
                "LDR     R7, =0xC0240000\n"
                "LDR     R6, =0x2590\n"
                "MOV     R9, #1\n"
                "MOV     R10, #0\n"
"loc_FFC3804C:\n"
                "LDR     R3, =0x191\n"
                "LDR     R0, [R6,#0x10]\n"
                "LDR     R2, =0xFFC38278\n"
                "MOV     R1, #0\n"
                "BL      sub_FFC0BF78\n"
                "MOV     R0, #40\n"
                "BL      _SleepTask\n"

//------------------  added code ---------------------
"labelA:\n"
                "LDR     R0, =jogdial_stopped\n"
                "LDR     R0, [R0]\n"
                "CMP     R0, #1\n"
                "BNE     labelB\n"
                "MOV     R0, #40\n"
                "BL      _SleepTask\n"
                "B       labelA\n"
"labelB:\n"
//------------------  original code ------------------

                "LDR     R0, [R7,#0x304]\n"
                "MOV     R0, R0,ASR#16\n"
                "STRH    R0, [R6]\n"
                "LDRSH   R2, [R6,#2]\n"
                "SUB     R1, R0, R2\n"
                "CMP     R1, #0\n"
                "BEQ     loc_FFC38110\n"
                "MOV     R5, R1\n"
                "RSBLT   R5, R5, #0\n"
                "MOVLE   R4, #0\n"
                "MOVGT   R4, #1\n"
                "CMP     R5, #0xFF\n"
                "BLS     loc_FFC380C4\n"
                "CMP     R1, #0\n"
                "RSBLE   R1, R2, #0xFF\n"
                "ADDLE   R1, R1, #0x7F00\n"
                "ADDLE   R0, R1, R0\n"
                "RSBGT   R0, R0, #0xFF\n"
                "ADDGT   R0, R0, #0x7F00\n"
                "ADDGT   R0, R0, R2\n"
                "ADD     R5, R0, #0x8000\n"
                "ADD     R5, R5, #1\n"
                "EOR     R4, R4, #1\n"
"loc_FFC380C4:\n"
                "LDR     R0, [R6,#0x18]\n"
                "CMP     R0, #0\n"
                "BEQ     loc_FFC38108\n"
                "LDR     R0, [R6,#0x20]\n"
                "CMP     R0, #0\n"
                "BEQ     loc_FFC380F0\n"
                "LDR     R1, [R8,R4,LSL#2]\n"
                "CMP     R1, R0\n"
                "BEQ     loc_FFC380F8\n"
                "LDR     R0, =0xB01\n"
                "BL      sub_FFC5F408\n"
 "loc_FFC380F0:\n"
                 "MOV     R0, R11\n"
                 "BL      sub_FFC5F408\n"
 "loc_FFC380F8:\n"
                 "LDR     R0, [R8,R4,LSL#2]\n"
                 "MOV     R1, R5\n"
                 "STR     R0, [R6,#0x20]\n"
                 "BL      sub_FFC5F364\n"
 "loc_FFC38108:\n"
                 "LDRH    R0, [R6]\n"
                 "STRH    R0, [R6,#2]\n"
 "loc_FFC38110:\n"
                 "STR     R10, [R7,#0x300]\n"
                 "STR     R9, [R7,#0x308]\n"
                 "LDR     R0, [R6,#0x14]\n"
                 "CMP     R0, #0\n"
                 "BLNE    _SleepTask\n"
                 "B       loc_FFC3804C\n"
 );
}
