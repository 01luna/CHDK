#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_MovieRecord();
extern void task_ExpDrv();
extern void task_PhySw();

void taskHook(context_t **context) {
	
	task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));
	
	// Replace firmware task addresses with ours
	if(tcb->entry == (void*)task_PhySw)				tcb->entry = (void*)mykbd_task;
	if(tcb->entry == (void*)task_CaptSeq)			tcb->entry = (void*)capt_seq_task;
	if(tcb->entry == (void*)task_InitFileModules)	tcb->entry = (void*)init_file_modules_task;
	if(tcb->entry == (void*)task_MovieRecord)		tcb->entry = (void*)movie_record_task;
	if(tcb->entry == (void*)task_ExpDrv)			tcb->entry = (void*)exp_drv_task;
}

//** boot  @ 0xFF81000C 

void __attribute__((naked,noinline)) boot(  ) { 
asm volatile (
"    LDR     R1, =0xC0410000 \n" 
"    MOV     R0, #0 \n" 
"    STR     R0, [R1] \n" 
"    MOV     R1, #0x78 \n" 
"    MCR     p15, 0, R1, c1, c0 \n" 
"    MOV     R1, #0 \n" 
"    MCR     p15, 0, R1, c7, c10, 4 \n" 
"    MCR     p15, 0, R1, c7, c5 \n" 
"    MCR     p15, 0, R1, c7, c6 \n" 
"    MOV     R0, #0x3D \n" 
"    MCR     p15, 0, R0, c6, c0 \n" 
"    MOV     R0, #0xC000002F \n" 
"    MCR     p15, 0, R0, c6, c1 \n" 
"    MOV     R0, #0x33 \n" 
"    MCR     p15, 0, R0, c6, c2 \n" 
"    MOV     R0, #0x40000033 \n" 
"    MCR     p15, 0, R0, c6, c3 \n" 
"    MOV     R0, #0x80000017 \n" 
"    MCR     p15, 0, R0, c6, c4 \n" 
"    LDR     R0, =0xFF80002D \n" 
"    MCR     p15, 0, R0, c6, c5 \n" 
"    MOV     R0, #0x34 \n" 
"    MCR     p15, 0, R0, c2, c0 \n" 
"    MOV     R0, #0x34 \n" 
"    MCR     p15, 0, R0, c2, c0, 1 \n" 
"    MOV     R0, #0x34 \n" 
"    MCR     p15, 0, R0, c3, c0 \n" 
"    LDR     R0, =0x3333330 \n" 
"    MCR     p15, 0, R0, c5, c0, 2 \n" 
"    LDR     R0, =0x3333330 \n" 
"    MCR     p15, 0, R0, c5, c0, 3 \n" 
"    MRC     p15, 0, R0, c1, c0 \n" 
"    ORR     R0, R0, #0x1000 \n" 
"    ORR     R0, R0, #4 \n" 
"    ORR     R0, R0, #1 \n" 
"    MCR     p15, 0, R0, c1, c0 \n" 
"    MOV     R1, #0x80000006 \n" 
"    MCR     p15, 0, R1, c9, c1 \n" 
"    MOV     R1, #6 \n" 
"    MCR     p15, 0, R1, c9, c1, 1 \n" 
"    MRC     p15, 0, R1, c1, c0 \n" 
"    ORR     R1, R1, #0x50000 \n" 
"    MCR     p15, 0, R1, c1, c0 \n" 
"    LDR     R2, =0xC0200000 \n" 
"    MOV     R1, #1 \n" 
"    STR     R1, [R2, #0x10C] \n" 
"    MOV     R1, #0xFF \n" 
"    STR     R1, [R2, #0xC] \n" 
"    STR     R1, [R2, #0x1C] \n" 
"    STR     R1, [R2, #0x2C] \n" 
"    STR     R1, [R2, #0x3C] \n" 
"    STR     R1, [R2, #0x4C] \n" 
"    STR     R1, [R2, #0x5C] \n" 
"    STR     R1, [R2, #0x6C] \n" 
"    STR     R1, [R2, #0x7C] \n" 
"    STR     R1, [R2, #0x8C] \n" 
"    STR     R1, [R2, #0x9C] \n" 
"    STR     R1, [R2, #0xAC] \n" 
"    STR     R1, [R2, #0xBC] \n" 
"    STR     R1, [R2, #0xCC] \n" 
"    STR     R1, [R2, #0xDC] \n" 
"    STR     R1, [R2, #0xEC] \n" 
"    STR     R1, [R2, #0xFC] \n" 
"    LDR     R1, =0xC0400008 \n" 
"    LDR     R2, =0x430005 \n" 
"    STR     R2, [R1] \n" 
"    MOV     R1, #1 \n" 
"    LDR     R2, =0xC0243100 \n" 
"    STR     R2, [R1] \n" 
"    LDR     R2, =0xC0242010 \n" 
"    LDR     R1, [R2] \n" 
"    ORR     R1, R1, #1 \n" 
"    STR     R1, [R2] \n" 
"    LDR     R0, =0xFFC29E9C \n" 
"    LDR     R1, =0x1900 \n" 
"    LDR     R3, =0xECB4 \n" 
"loc_FF81013C:\n"
"    CMP     R1, R3 \n" 
"    LDRCC   R2, [R0], #4 \n" 
"    STRCC   R2, [R1], #4 \n" 
"    BCC     loc_FF81013C \n" 
"    LDR     R1, =0x1698CC \n" 
"    MOV     R2, #0 \n" 
"loc_FF810154:\n"
"    CMP     R3, R1 \n" 
"    STRCC   R2, [R3], #4 \n" 
"    BCC     loc_FF810154 \n" 
//"	 B		 loc_FF810358 \n"            
"	 B		 sub_FF810358_my \n"					// patched  
	);
}

void __attribute__((naked,noinline)) sub_FF810358_my() {
	
	*(int*)0x1938=(int)taskHook;
	*(int*)0x193C=(int)taskHook;
	
	// FF81FC8C + FF85FC4C
	if ((*(int*) 0xC0220064) & 1)				// look at play switch
		*(int*)(0x24F8) = 0x200000;				// start in play mode
	else
		*(int*)(0x24F8) = 0x100000;				// start in rec mode
	
	// sub_FF810358
	asm volatile (
"    LDR     R0, =0xFF8103D0 \n" 
"    MOV     R1, #0 \n" 
"    LDR     R3, =0xFF810408 \n" 
"loc_FF810364:\n"
"    CMP     R0, R3 \n" 
"    LDRCC   R2, [R0], #4 \n" 
"    STRCC   R2, [R1], #4 \n" 
"    BCC     loc_FF810364 \n" 
"    LDR     R0, =0xFF810408 \n" 
"    MOV     R1, #0x4B0 \n" 
"    LDR     R3, =0xFF81061C \n" 
"loc_FF810380:\n"
"    CMP     R0, R3 \n" 
"    LDRCC   R2, [R0], #4 \n" 
"    STRCC   R2, [R1], #4 \n" 
"    BCC     loc_FF810380 \n" 
"    MOV     R0, #0xD2 \n" 
"    MSR     CPSR_cxsf, R0 \n" 
"    MOV     SP, #0x1000 \n" 
"    MOV     R0, #0xD3 \n" 
"    MSR     CPSR_cxsf, R0 \n" 
"    MOV     SP, #0x1000 \n" 
"    LDR     R0, =0x6C4 \n" 
"    LDR     R2, =0xEEEEEEEE \n" 
"    MOV     R3, #0x1000 \n" 
"loc_FF8103B4:\n"
"    CMP     R0, R3 \n" 
"    STRCC   R2, [R0], #4 \n" 
"    BCC     loc_FF8103B4 \n" 
//"	 BL		 sub_FF8111B0 \n"
"	 BL		 sub_FF8111B0_my \n"					// patched
	);
}


//** sub_FF8111B0_my  @ 0xFF8111B0 

void __attribute__((naked,noinline)) sub_FF8111B0_my(  ) { 
asm volatile (
"    STR     LR, [SP, #-4]! \n" 
"    SUB     SP, SP, #0x74 \n" 
"    MOV     R1, #0x74 \n" 
"    MOV     R0, SP \n" 
"    BL      sub_FFB51098 \n" 
"    MOV     R0, #0x53000 \n" 
"    STR     R0, [SP, #4] \n" 
#if defined(OPT_CHDK_IN_EXMEM)
"	 LDR	 R0, =0x1698CC \n"				// use original heap offset since CHDK is loaded in high memory
#else			 
"	 LDR	 R0, =new_sa \n"				// otherwise use patched value
"	 LDR	 R0, [R0] \n"					// 
#endif	
"    LDR     R2, =0x2F1F80 \n" 
"    STR     R0, [SP, #8] \n" 
"    SUB     R0, R2, R0 \n" 
"    STR     R0, [SP, #0xC] \n" 
"    MOV     R0, #0x22 \n" 
"    STR     R0, [SP, #0x18] \n" 
"    MOV     R0, #0x68 \n" 
"    STR     R0, [SP, #0x1C] \n" 
"    LDR     R1, =0x2F9C00 \n" 
"    LDR     R0, =0x19B \n" 
"    STR     R1, [SP] \n" 
"    STR     R0, [SP, #0x20] \n" 
"    MOV     R0, #0x96 \n" 
"    STR     R2, [SP, #0x10] \n" 
"    STR     R1, [SP, #0x14] \n" 
"    STR     R0, [SP, #0x24] \n" 
"    STR     R0, [SP, #0x28] \n" 
"    MOV     R0, #0x64 \n" 
"    STR     R0, [SP, #0x2C] \n" 
"    MOV     R0, #0 \n" 
"    STR     R0, [SP, #0x30] \n" 
"    STR     R0, [SP, #0x34] \n" 
"    MOV     R0, #0x10 \n" 
"    STR     R0, [SP, #0x5C] \n" 
"    MOV     R0, #0x800 \n" 
"    STR     R0, [SP, #0x60] \n" 
"    MOV     R0, #0xA0 \n" 
"    STR     R0, [SP, #0x64] \n" 
"    MOV     R0, #0x280 \n" 
"    STR     R0, [SP, #0x68] \n" 
//"	 LDR	 R1, =sub_FF815EE0 \n"
"	 LDR	 R1, =sub_FF815EE0_my \n"       //patched
"    MOV     R2, #0 \n" 
"    MOV     R0, SP \n" 
"    BL      sub_FF8134C4 \n" 
"    ADD     SP, SP, #0x74 \n" 
"    LDR     PC, [SP], #4 \n" 
	);
}


//** sub_FF815EE0_my  @ 0xFF815EE0 

void __attribute__((naked,noinline)) sub_FF815EE0_my(  ) { 
asm volatile (
"    STMFD   SP!, {R4,LR} \n" 
"    BL      sub_FF810B28 \n" 
"    BL      sub_FF81A374 \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF815FF4 \n" 
"    BLLT    sub_FF815FD4 \n" 
"    BL      sub_FF815B18 \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF815FFC \n" 
"    BLLT    sub_FF815FD4 \n" 
"    LDR     R0, =0xFF81600C \n" 
"    BL      sub_FF815C00 \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF816014 \n" 
"    BLLT    sub_FF815FD4 \n" 
"    LDR     R0, =0xFF81600C \n" 
"    BL      sub_FF813CA8 \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF816028 \n" 
"    BLLT    sub_FF815FD4 \n" 
"    BL      sub_FF819D00 \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF816034 \n" 
"    BLLT    sub_FF815FD4 \n" 
"    BL      sub_FF811690 \n" 
"    CMP     R0, #0 \n" 
"    LDRLT   R0, =0xFF816040 \n" 
"    BLLT    sub_FF815FD4 \n" 
"    LDMFD   SP!, {R4,LR} \n" 
//"	 B		 loc_FF81FC58 \n"
"	 B		 taskcreate_Startup_my \n" 			// patched
	);
}


//** taskcreate_Startup_my  @ 0xFF81FC58 

void __attribute__((naked,noinline)) taskcreate_Startup_my(  ) { 
asm volatile (
"    STMFD   SP!, {R3-R9,LR} \n" 
"    MOV     R6, #0 \n" 
"    BL      sub_FF834380 \n" 
"    BL      sub_FF83BF64 \n" 
"    LDR     R9, =0xC0220000 \n" 
"    MOVS    R7, R0 \n" 
"    MOV     R8, #1 \n" 
"    BNE     loc_FF81FCC0 \n" 
"    BL      sub_FF835C84 \n" 
"    CMP     R0, #0 \n" 
"    BEQ     loc_FF81FCC0 \n" 
"    LDR     R0, [R9, #0x60] \n" 
"    BIC     R5, R8, R0 \n" 
"    LDR     R0, [R9, #0x64] \n" 
"    BIC     R4, R8, R0 \n" 
"    BL      sub_FF83363C \n" 
"    CMP     R0, #1 \n" 
"    MOVEQ   R6, #1 \n" 
"    ORR     R0, R4, R5 \n" 
"    ORRS    R0, R0, R6 \n" 
"    BNE     loc_FF81FCD0 \n" 
"    BL      sub_FF833A00 \n" 
"    MOV     R0, #0x44 \n" 
"    STR     R0, [R9, #0x1C] \n" 
"    BL      sub_FF833BEC \n" 
"loc_FF81FCBC:\n"
"    B       loc_FF81FCBC \n" 
"loc_FF81FCC0:\n"
"    LDR     R0, [R9, #0x64] \n" 
"    BIC     R4, R8, R0 \n" 
"    LDR     R0, [R9, #0x60] \n" 
"    BIC     R5, R8, R0 \n" 
"loc_FF81FCD0:\n"
"    MOV     R3, R6 \n" 
"    MOV     R2, R7 \n" 
"    MOV     R1, R5 \n" 
"    MOV     R0, R4 \n" 
//"	 BL		 sub_FF834388 \n"				// we must remove this for power-on mode handling to work
"    BL      sub_FF834384 \n" 
"    BL      sub_FF83A134 \n" 
"    LDR     R1, =0x34E000 \n" 
"    MOV     R0, #0 \n" 
"    BL      sub_FF83A5A4 \n" 
"    BL      sub_FF83A34C \n" 
"    MOV     R3, #0 \n" 
"    STR     R3, [SP] \n" 
//"	 LDR	 R3, =0xFF81FBF4 \n"
"	 LDR	 R3, =task_Startup_my \n"		//patched
"    MOV     R2, #0 \n" 
"    MOV     R1, #0x19 \n" 
"    LDR     R0, =0xFF81FD2C \n" 
"    BL      sub_FF81E9B0 \n" 
"    MOV     R0, #0 \n" 
"    LDMFD   SP!, {R3-R9,PC} \n" 
	);
}


//** task_Startup_my  @ 0xFF81FBF4 

void __attribute__((naked,noinline)) task_Startup_my(  ) { 
asm volatile (
"    STMFD   SP!, {R4,LR} \n" 
"    BL      sub_FF816588 \n" 
"    BL      sub_FF8354F4 \n" 
"    BL      sub_FF83364C \n" 
"    BL      sub_FF83BFAC \n" 
"    BL      sub_FF83C198 \n" 
//"	 BL		 sub_FF83C040 \n"				// skip starting diskboot.bin again
"    BL      sub_FF83C338 \n" 
"    BL      sub_FF832208 \n" 
"    BL      sub_FF83C1C8 \n" 
"    BL      sub_FF8398D8 \n" 
"    BL      sub_FF83C33C \n" 
"	 BL		 CreateTask_spytask \n"				// added
//"	 BL		 sub_FF834248 \n"
"	 BL		 taskcreatePhySw_my \n"				// patched
"    BL      sub_FF837BC4 \n" 
"    BL      sub_FF83C354 \n" 
"    BL      sub_FF831600 \n" 
"    BL      sub_FF832FB0 \n" 
"    BL      sub_FF83BD20 \n" 
"    BL      sub_FF8335EC \n" 
"    BL      sub_FF832F4C \n" 
"    BL      sub_FF83223C \n" 
"    BL      sub_FF83CDF4 \n" 
"    BL      sub_FF832F10 \n" 
"    LDMFD   SP!, {R4,LR} \n" 
"    B       sub_FF8166A8 \n" 
	);
}


//** taskcreatePhySw_my  @ 0xFF834248 

void __attribute__((naked,noinline)) taskcreatePhySw_my(  ) { 
asm volatile (
"    STMFD   SP!, {R3-R5,LR} \n" 
"    LDR     R4, =0x1C30 \n" 
"    LDR     R0, [R4, #4] \n" 
"    CMP     R0, #0 \n" 
"    BNE     loc_FF83427C \n" 
"    MOV     R3, #0 \n" 
"    STR     R3, [SP] \n" 
//"    LDR     R3, =0xFF834214 \n" 
"	 LDR     R3, =mykbd_task\n"			//added
//"    MOV     R2, #0x800 \n"
"    MOV     R2, #0x2000 \n" 			// stack size for new task_PhySw so we don't have to do stack switch
"    MOV     R1, #0x17 \n" 
"    LDR     R0, =0xFF83449C \n" 
"    BL      sub_FF83A3A4 \n" 
"    STR     R0, [R4, #4] \n" 
"loc_FF83427C:\n"
"    BL      sub_FF888EC0 \n" 
"    BL      sub_FF835BD4 \n" 
"    CMP     R0, #0 \n" 
"    BNE     loc_FF834298 \n" 
"    LDR     R1, =0x32920 \n" 
"    MOV     R0, #0 \n" 
"    BL      sub_FF888E34 \n" 
"loc_FF834298:\n"
"    LDMFD   SP!, {R3-R5,PC} \n" 
	);
}

void spytask(long ua, long ub, long uc, long ud, long ue, long uf) {
	
	core_spytask();
}

void CreateTask_spytask() {
        
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
}

void __attribute__((naked,noinline)) init_file_modules_task() {
	
	// sub_FF8933BC
	asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n" 
"    BL      sub_FF88B35C \n" 
"    LDR     R5, =0x5006 \n" 
"    MOVS    R4, R0 \n" 
"    MOVNE   R1, #0 \n" 
"    MOVNE   R0, R5 \n" 
"    BLNE    sub_FF88F1F4 \n" 
"    BL      sub_FF88B388 \n" 
"	 BL		 core_spytask_can_start \n"      	// added, CHDK: Set "it's-safe-to-start"-Flag for spytask
"    CMP     R4, #0 \n" 
"    LDMNEFD SP!, {R4-R6,PC} \n" 
"    MOV     R0, R5 \n" 
"    LDMFD   SP!, {R4-R6,LR} \n" 
"    MOV     R1, #0 \n" 
"    B       sub_FF88F1F4 \n" 
	);
}