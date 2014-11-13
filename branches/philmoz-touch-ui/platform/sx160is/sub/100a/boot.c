/*
 * boot.c - auto-generated by CHDK code_gen.
 */
#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

// Forward declarations
extern volatile int jogdial_stopped;
void JogDial_task_my(void);

extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_RotaryEncoder();
extern void task_MovieRecord();
extern void task_ExpDrv();
extern void task_FileWrite();

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

/*----------------------------------------------------------------------
    boot()

    Main entry point for the CHDK code
-----------------------------------------------------------------------*/

/*************************************************************/
//** boot @ 0xFF81000C - 0xFF81017C, length=93
void __attribute__((naked,noinline)) boot() {
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
"    LDR     R0, =0xFFCD8B18 \n"
"    LDR     R1, =0x431000 \n"
"    LDR     R3, =0x44059C \n"

"loc_FF81013C:\n"
"    CMP     R1, R3 \n"
"    LDRCC   R2, [R0], #4 \n"
"    STRCC   R2, [R1], #4 \n"
"    BCC     loc_FF81013C \n"
"    LDR     R0, =0xFFCCAAEC \n"
"    LDR     R1, =0x1900 \n"
"    LDR     R3, =0xF92C \n"

"loc_FF810158:\n"
"    CMP     R1, R3 \n"
"    LDRCC   R2, [R0], #4 \n"
"    STRCC   R2, [R1], #4 \n"
"    BCC     loc_FF810158 \n"
"    LDR     R1, =0x1639D4 \n"
"    MOV     R2, #0 \n"

"loc_FF810170:\n"
"    CMP     R3, R1 \n"
"    STRCC   R2, [R3], #4 \n"
"    BCC     loc_FF810170 \n"
/* Install task hooks via 0x193x is not possible with this new dryos version
   So the below code patches the CreateTask function in RAM to install our
   hook -- ERR99
*/
// Install CreateTask patch
"    LDR     R0, =patch_CreateTask\n"   // Patch data
"    LDM     R0, {R1,R2}\n"             // Get two patch instructions
"    LDR     R0, =hook_CreateTask\n"    // Address to patch
"    STM     R0, {R1,R2}\n"             // Store patch instructions

"    B       sub_FF810380_my \n"  // --> Patched. Old value = 0xFF810380.

"patch_CreateTask:\n"
"    LDR     PC, [PC,#-0x4]\n"          // Do jump to absolute address CreateTask_my
"    .long   CreateTask_my\n"
);
}

/*************************************************************/
//** CreateTask_my @ 0x004368B0 - 0x004368B4, length=2
void __attribute__((naked,noinline)) CreateTask_my() {
asm volatile (
"    STMFD   SP!, {R0}\n"
//R3 = Pointer to task function to create

/*** INSTALL capt_seq_task() hook ***/
"    LDR     R0, =task_CaptSeq\n"       // DryOS original code function ptr.
"    CMP     R0, R3\n"                  // is the given taskptr equal to our searched function?
"    LDREQ   R3, =capt_seq_task\n"      // if so replace with our task function base ptr.
"    BEQ     exitHook\n"                // below compares not necessary if this check has found something.

/*** INSTALL exp_drv_task() hook ***/
"    LDR     R0, =task_ExpDrv\n"
"    CMP     R0, R3\n"
"    LDREQ   R3, =exp_drv_task\n"
"    BEQ     exitHook\n"

/*** INSTALL filewrite() hook ***/
"    LDR     R0, =task_FileWrite\n"
"    CMP     R0, R3\n"
"    LDREQ   R3, =filewritetask\n"
"    BEQ     exitHook\n"

/*** INSTALL JogDial() hook ***/
"    LDR     R0, =task_RotaryEncoder\n"
"    CMP     R0, R3\n"
"    LDREQ   R3, =JogDial_task_my\n"
"    BEQ     exitHook\n"

/*** INSTALL movie_record_task() hook ***/
"    LDR     R0, =task_MovieRecord\n"
"    CMP     R0, R3\n"
"    LDREQ   R3, =movie_record_task\n"
"    BEQ     exitHook\n"

/*** INSTALL init_file_modules_task() hook ***/
"    LDR     R0, =task_InitFileModules\n"
"    CMP     R0, R3\n"
"    LDREQ   R3, =init_file_modules_task\n"

"exitHook:\n" 
// restore overwritten registers
"    LDMFD   SP!, {R0}\n"
// Execute overwritten instructions from original code, then jump to firmware
"    STMFD   SP!, {R1-R9,LR} \n"
"    MOV     R4, R0 \n"
"    LDR     PC, =0x004368B8 \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FF810380_my @ 0xFF810380 - 0xFF8103E8, length=27
void __attribute__((naked,noinline)) sub_FF810380_my() {

    //Replacement of sub_FF865694 for correct power-on.
    //(short press = playback mode, long press = record mode)
    if ((*(int*) 0xC0220114) & 1)       // look at power-on switch sub_ff828ec8
        *(int*)(0x2AF4+0x4) = 0x200000; // Playmode
    else
        *(int*)(0x2AF4+0x4) = 0x100000; // Shootingmode

asm volatile (
"    LDR     R0, =0xFF8103F8 \n"
"    MOV     R1, #0 \n"
"    LDR     R3, =0xFF810430 \n"

"loc_FF81038C:\n"
"    CMP     R0, R3 \n"
"    LDRCC   R2, [R0], #4 \n"
"    STRCC   R2, [R1], #4 \n"
"    BCC     loc_FF81038C \n"
"    LDR     R0, =0xFF810430 \n"
"    MOV     R1, #0x4B0 \n"
"    LDR     R3, =0xFF810618 \n"

"loc_FF8103A8:\n"
"    CMP     R0, R3 \n"
"    LDRCC   R2, [R0], #4 \n"
"    STRCC   R2, [R1], #4 \n"
"    BCC     loc_FF8103A8 \n"
"    MOV     R0, #0xD2 \n"
"    MSR     CPSR_cxsf, R0 \n"
"    MOV     SP, #0x1000 \n"
"    MOV     R0, #0xD3 \n"
"    MSR     CPSR_cxsf, R0 \n"
"    MOV     SP, #0x1000 \n"
"    LDR     R0, =0x698 \n"
"    LDR     R2, =0xEEEEEEEE \n"
"    MOV     R3, #0x1000 \n"

"loc_FF8103DC:\n"
"    CMP     R0, R3 \n"
"    STRCC   R2, [R0], #4 \n"
"    BCC     loc_FF8103DC \n"
"    BL      sub_FF811160_my \n"  // --> Patched. Old value = 0xFF811160.
);
}

/*************************************************************/
//** sub_FF811160_my @ 0xFF811160 - 0xFF81120C, length=44
void __attribute__((naked,noinline)) sub_FF811160_my() {
asm volatile (
"    STR     LR, [SP, #-4]! \n"
"    SUB     SP, SP, #0x74 \n"
"    MOV     R1, #0x74 \n"
"    MOV     R0, SP \n"
"    BL      sub_0043C3A0 \n"
"    MOV     R0, #0x57000 \n"
"    STR     R0, [SP, #4] \n"

#if defined(CHDK_NOT_IN_CANON_HEAP) // use original heap offset if CHDK is loaded in high memory
"    LDR     R0, =0x1639D4 \n"
#else
"    LDR     R0, =new_sa\n"   // otherwise use patched value
"    LDR     R0, [R0]\n"      //
#endif

"    LDR     R2, =0x32D440 \n"
"    STR     R0, [SP, #8] \n"
"    SUB     R0, R2, R0 \n"
"    STR     R0, [SP, #0xC] \n"
"    MOV     R0, #0x22 \n"
"    STR     R0, [SP, #0x18] \n"
"    MOV     R0, #0x7C \n"
"    STR     R0, [SP, #0x1C] \n"
"    LDR     R1, =0x335C00 \n"
"    LDR     R0, =0x1CD \n"
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
"    LDR     R1, =sub_FF814210_my \n"  // --> Patched. Old value = 0xFF814210.
"    MOV     R2, #0 \n"
"    MOV     R0, SP \n"
"    BL      sub_004327E8 \n"
"    ADD     SP, SP, #0x74 \n"
"    LDR     PC, [SP], #4 \n"
);
}

/*************************************************************/
//** sub_FF814210_my @ 0xFF814210 - 0xFF814284, length=30
void __attribute__((naked,noinline)) sub_FF814210_my() {
asm volatile (
"    STMFD   SP!, {R4,LR} \n"
"    BL      sub_FF810ADC \n"
"    BL      sub_FF8150FC \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF814324 /*'dmSetup'*/ \n"
"    BLLT    _err_init_task \n"
"    BL      sub_FF813E48 \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF81432C /*'termDriverInit'*/ \n"
"    BLLT    _err_init_task \n"
"    LDR     R0, =0xFF81433C /*'/_term'*/ \n"
"    BL      sub_FF813F30 \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF814344 /*'termDeviceCreate'*/ \n"
"    BLLT    _err_init_task \n"
"    LDR     R0, =0xFF81433C /*'/_term'*/ \n"
"    BL      sub_FF812950 \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF814358 /*'stdioSetup'*/ \n"
"    BLLT    _err_init_task \n"
"    BL      sub_FF814A98 \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF814364 /*'stdlibSetup'*/ \n"
"    BLLT    _err_init_task \n"
"    BL      sub_FF811650 \n"
"    CMP     R0, #0 \n"
"    LDRLT   R0, =0xFF814370 /*'armlib_setup'*/ \n"
"    BLLT    _err_init_task \n"
"    LDMFD   SP!, {R4,LR} \n"
"    B       sub_FF81A21C_my \n"  // --> Patched. Old value = 0xFF81A21C.
);
}

/*************************************************************/
//** sub_FF81A21C_my @ 0xFF81A21C - 0xFF81A298, length=32
void __attribute__((naked,noinline)) sub_FF81A21C_my() {
asm volatile (
"    STMFD   SP!, {R3,LR} \n"
"    BL      sub_FF830550 \n"
"    CMP     R0, #0 \n"
"    BNE     loc_FF81A23C \n"
"    BL      sub_FF82AA28 /*_IsNormalCameraMode_FW*/ \n"
"    CMP     R0, #0 \n"
"    MOVNE   R0, #1 \n"
"    BNE     loc_FF81A240 \n"

"loc_FF81A23C:\n"
"    MOV     R0, #0 \n"

"loc_FF81A240:\n"
"    BL      sub_FF828EC8_my \n"  // --> Patched. Old value = 0xFF828EC8.
"    CMP     R0, #0 \n"
"    BNE     loc_FF81A264 \n"
"    BL      sub_FF828540 \n"
"    LDR     R1, =0xC0220000 \n"
"    MOV     R0, #0x44 \n"
"    STR     R0, [R1, #0x12C] \n"
"    BL      sub_FF828684 \n"

"loc_FF81A260:\n"
"    B       loc_FF81A260 \n"

"loc_FF81A264:\n"
"    BL      sub_0043786C \n"
"    LDR     R1, =0x38E000 \n"
"    MOV     R0, #0 \n"
"    BL      sub_FF82EB8C \n"
"    BL      sub_00437A84 \n"
"    MOV     R3, #0 \n"
"    STR     R3, [SP] \n"
"    LDR     R3, =task_Startup_my \n"  // --> Patched. Old value = 0xFF81A1B4.
"    MOV     R2, #0 \n"
"    MOV     R1, #0x19 \n"
"    LDR     R0, =0xFF81A2A8 /*'Startup'*/ \n"
"    BL      _CreateTask \n"
"    MOV     R0, #0 \n"
"    LDMFD   SP!, {R3,PC} \n"
);
}

/*************************************************************/
//** sub_FF828EC8_my @ 0xFF828EC8 - 0xFF828F20, length=23
void __attribute__((naked,noinline)) sub_FF828EC8_my() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    MOV     R6, R0 \n"
//"  BL      _sub_FF86568C \n"  // --> Nullsub call removed.
"    LDR     R0, =0xC0220114 \n"
"    BL      sub_FF865ED8 \n"
"    MOV     R4, #1 \n"
"    BIC     R5, R4, R0 \n"
"    LDR     R0, =0xC022010C \n"
"    BL      sub_FF865ED8 \n"
"    CMP     R6, #0 \n"
"    BIC     R4, R4, R0 \n"
"    BEQ     loc_FF828F00 \n"
"    ORRS    R0, R5, R4 \n"
"    LDMEQFD SP!, {R4-R6,PC} \n"

"loc_FF828F00:\n"
"    BL      sub_FF830550 \n"
"    MOV     R2, R0 \n"
"    MOV     R3, #0 \n"
"    MOV     R1, R4 \n"
"    MOV     R0, R5 \n"
//"  BL      _sub_FF865694 \n"  // Disable StartUpChecks
//"  BL      _sub_FF865690 \n"  // --> Nullsub call removed.
"    MOV     R0, #1 \n"
"    LDMFD   SP!, {R4-R6,PC} \n"
);
}

/*************************************************************/
//** task_Startup_my @ 0xFF81A1B4 - 0xFF81A218, length=26
void __attribute__((naked,noinline)) task_Startup_my() {
asm volatile (
"    STMFD   SP!, {R4,LR} \n"
"    BL      sub_FF814850 \n"
"    BL      sub_FF82A04C \n"
"    BL      sub_FF8281EC \n"
//"  BL      _sub_FF865EEC \n"  // --> Nullsub call removed.
"    BL      sub_FF830784 \n"
//"  BL      _sub_FF83062C \n"  // load DISKBOOT.BIN
"    BL      sub_FF83090C \n"
"    BL      sub_FF830AD8 \n"
"    BL      sub_FF8308D0 \n"
"    BL      sub_FF8307B4 \n"
"    BL      sub_FF82EAC0 \n"
"    BL      sub_FF830AE0 \n"
"    BL      CreateTask_spytask\n" // added
"    BL      taskcreatePhySw_my \n"  // --> Patched. Old value = 0xFF828D68.
"    BL      sub_FF82C830 \n"
"    BL      sub_FF8A774C \n"
"    BL      sub_FF826214 \n"
"    BL      sub_FF827C0C \n"
"    BL      sub_FF83030C \n"
"    BL      sub_FF8281A0 \n"
"    BL      sub_FF827BAC \n"
"    BL      sub_FF853E74 \n"
"    BL      sub_FF826EA4 \n"
"    BL      sub_FF827B70 \n"
"    LDMFD   SP!, {R4,LR} \n"
"    B       sub_FF814970 \n"
);
}

/*************************************************************/
//** taskcreatePhySw_my @ 0xFF828D68 - 0xFF828DBC, length=22
void __attribute__((naked,noinline)) taskcreatePhySw_my() {
asm volatile (
"    STMFD   SP!, {R3-R5,LR} \n"
"    LDR     R4, =0x1D30 \n"
"    LDR     R0, [R4, #4] \n"
"    CMP     R0, #0 \n"
"    BNE     loc_FF828D9C \n"
"    MOV     R3, #0 \n"
"    STR     R3, [SP] \n"
"    LDR     R3, =mykbd_task \n"  // --> Patched. Old value = 0xFF828D34.
"    MOV     R2, #0x2000 \n"  // --> Patched. Old value = 0x800. stack size for new task_PhySw so we don't have to do stack switch
"    MOV     R1, #0x17 \n"
"    LDR     R0, =0xFF829018 /*'PhySw'*/ \n"
"    BL      sub_00437ADC /*_CreateTaskStrictly*/ \n"
"    STR     R0, [R4, #4] \n"

"loc_FF828D9C:\n"
"    BL      sub_FF866348 \n"
"    BL      sub_FF8934C8 \n"
"    BL      sub_FF82A978 /*_IsFactoryMode_FW*/ \n"
"    CMP     R0, #0 \n"
"    BNE     loc_FF828DBC \n"
"    LDR     R1, =0x33964 \n"
"    MOV     R0, #0 \n"
"    BL      sub_FF893434 /*_OpLog.Start_FW*/ \n"

"loc_FF828DBC:\n"
"    LDMFD   SP!, {R3-R5,PC} \n"
);
}

/*************************************************************/
//** init_file_modules_task @ 0xFF856B18 - 0xFF856B4C, length=14
void __attribute__((naked,noinline)) init_file_modules_task() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    BL      sub_FF895A08 \n"
"    LDR     R5, =0x5006 \n"
"    MOVS    R4, R0 \n"
"    MOVNE   R1, #0 \n"
"    MOVNE   R0, R5 \n"
"    BLNE    _PostLogicalEventToUI \n"
"    BL      sub_FF895A34 \n"
"    BL      core_spytask_can_start\n"  // CHDK: Set "it's-safe-to-start" flag for spytask
"    CMP     R4, #0 \n"
"    LDMNEFD SP!, {R4-R6,PC} \n"
"    MOV     R0, R5 \n"
"    LDMFD   SP!, {R4-R6,LR} \n"
"    MOV     R1, #0 \n"
"    B       _PostLogicalEventToUI \n"
);
}

/*************************************************************/
//** JogDial_task_my @ 0xFF86601C - 0xFF866344, length=203
void __attribute__((naked,noinline)) JogDial_task_my() {
asm volatile (
"    STMFD   SP!, {R4-R11,LR} \n"
"    SUB     SP, SP, #0x1C \n"
"    BL      sub_FF8663B4 \n"
"    LDR     R12, =0x2B08 \n"
"    LDR     R6, =0xFFBA4C34 \n"
"    MOV     R0, #0 \n"
"    ADD     R10, SP, #8 \n"
"    ADD     R9, SP, #0xC \n"

// Save pointer for kbd.c routine
"    LDR     R2, =jog_position \n"
"    STR     R9, [R2] \n"


"loc_FF86603C:\n"
"    ADD     R2, SP, #0x14 \n"
"    MOV     R1, #0 \n"
"    ADD     R4, R2, R0, LSL#1 \n"
"    ADD     R3, SP, #0x10 \n"
"    STRH    R1, [R4] \n"
"    ADD     R4, R3, R0, LSL#1 \n"
"    STRH    R1, [R4] \n"
"    STR     R1, [R9, R0, LSL#2] \n"
"    STR     R1, [R10, R0, LSL#2] \n"
"    ADD     R0, R0, #1 \n"
"    CMP     R0, #1 \n"
"    BLT     loc_FF86603C \n"

"loc_FF86606C:\n"
"    LDR     R0, =0x2B08 \n"
"    MOV     R2, #0 \n"
"    LDR     R0, [R0, #8] \n"
"    MOV     R1, SP \n"
"    BL      sub_004372A4 /*_ReceiveMessageQueue*/ \n"
"    CMP     R0, #0 \n"
"    LDRNE   R1, =0x20B \n"
"    LDRNE   R0, =0xFF8662CC /*'RotaryEncoder.c'*/ \n"
"    BLNE    _DebugAssert \n"
"    LDR     R0, [SP] \n"
"    AND     R4, R0, #0xFF \n"
"    AND     R0, R0, #0xFF00 \n"
"    CMP     R0, #0x100 \n"
"    BEQ     loc_FF8660DC \n"
"    CMP     R0, #0x200 \n"
"    BEQ     loc_FF866114 \n"
"    CMP     R0, #0x300 \n"
"    BEQ     loc_FF866318 \n"
"    CMP     R0, #0x400 \n"
"    BNE     loc_FF86606C \n"
"    CMP     R4, #0 \n"
"    LDRNE   R1, =0x285 \n"
"    LDRNE   R0, =0xFF8662CC /*'RotaryEncoder.c'*/ \n"
"    BLNE    _DebugAssert \n"
"    RSB     R0, R4, R4, LSL#3 \n"
"    LDR     R0, [R6, R0, LSL#2] \n"

"loc_FF8660D4:\n"
"    BL      sub_FF866398 \n"
"    B       loc_FF86606C \n"

"loc_FF8660DC:\n"
//------------------  added code ---------------------
"labelA:\n"
"    LDR     R0, =jogdial_stopped\n"
"    LDR     R0, [R0]\n"
"    CMP     R0, #1\n"
"    BNE     labelB\n"
"    MOV     R0, #40\n"
"    BL      _SleepTask\n"
"    B       labelA\n"
"labelB:\n"
//------------------  original code ------------------
"    LDR     R0, =0x2B14 \n"
"    LDR     R0, [R0, R4, LSL#2] \n"
"    BL      sub_FF82F104 /*_CancelTimer*/ \n"
"    LDR     R2, =0xFF865F68 \n"
"    ORR     R3, R4, #0x200 \n"
"    MOV     R1, R2 \n"
"    MOV     R0, #0x28 \n"
"    BL      sub_FF82F020 /*_SetTimerAfter*/ \n"
"    TST     R0, #1 \n"
"    CMPNE   R0, #0x15 \n"
"    STR     R0, [R10, R4, LSL#2] \n"
"    BEQ     loc_FF86606C \n"
"    LDR     R1, =0x21D \n"
"    B       loc_FF8662B8 \n"

"loc_FF866114:\n"
"    RSB     R5, R4, R4, LSL#3 \n"
"    LDR     R0, [R6, R5, LSL#2] \n"
"    LDR     R1, =0xC0240000 \n"
"    ADD     R0, R1, R0, LSL#8 \n"
"    LDR     R0, [R0, #0x104] \n"
"    MOV     R1, R0, ASR#16 \n"
"    ADD     R0, SP, #0x14 \n"
"    ADD     R11, R0, R4, LSL#1 \n"
"    ADD     R0, SP, #0x10 \n"
"    ADD     R0, R0, R4, LSL#1 \n"
"    STRH    R1, [R11] \n"
"    STR     R0, [SP, #0x18] \n"
"    LDRSH   R3, [R0] \n"
"    SUB     R2, R1, R3 \n"
"    CMP     R2, #0 \n"
"    BNE     loc_FF866198 \n"
"    LDR     R0, [R9, R4, LSL#2] \n"
"    CMP     R0, #0 \n"
"    BEQ     loc_FF866274 \n"
"    LDR     R7, =0x2B14 \n"
"    LDR     R0, [R7, R4, LSL#2] \n"
"    BL      sub_FF82F104 /*_CancelTimer*/ \n"
"    LDR     R2, =0xFF865F74 \n"
"    ORR     R3, R4, #0x300 \n"
"    MOV     R1, R2 \n"
"    MOV     R0, #0x1F4 \n"
"    BL      sub_FF82F020 /*_SetTimerAfter*/ \n"
"    TST     R0, #1 \n"
"    CMPNE   R0, #0x15 \n"
"    STR     R0, [R7, R4, LSL#2] \n"
"    BEQ     loc_FF866274 \n"
"    LDR     R1, =0x236 \n"
"    B       loc_FF86626C \n"

"loc_FF866198:\n"
"    MOV     R0, R2 \n"
"    RSBLT   R0, R0, #0 \n"
"    MOVLE   R7, #0 \n"
"    MOVGT   R7, #1 \n"
"    CMP     R0, #0xFF \n"
"    BLS     loc_FF8661D4 \n"
"    LDR     R0, =0x7FFF \n"
"    CMP     R2, #0 \n"
"    SUBLE   R0, R0, R3 \n"
"    ADDLE   R0, R0, R1 \n"
"    SUBGT   R0, R0, R1 \n"
"    ADDGT   R0, R0, R3 \n"
"    MVN     R1, #0x8000 \n"
"    SUB     R0, R0, R1 \n"
"    EOR     R7, R7, #1 \n"

"loc_FF8661D4:\n"
"    STR     R0, [SP, #4] \n"
"    LDR     R0, [R9, R4, LSL#2] \n"
"    CMP     R0, #0 \n"
"    ADDEQ   R0, R6, R5, LSL#2 \n"
"    LDREQ   R0, [R0, #8] \n"
"    BEQ     loc_FF86620C \n"
"    ADD     R8, R6, R5, LSL#2 \n"
"    ADD     R1, R8, R7, LSL#2 \n"
"    LDR     R1, [R1, #0x10] \n"
"    CMP     R1, R0 \n"
"    BEQ     loc_FF866210 \n"
"    LDR     R0, [R8, #0xC] \n"
"    BL      sub_FF828DC0 \n"
"    LDR     R0, [R8, #8] \n"

"loc_FF86620C:\n"
"    BL      sub_FF828DC0 \n"

"loc_FF866210:\n"
"    ADD     R0, R6, R5, LSL#2 \n"
"    ADD     R7, R0, R7, LSL#2 \n"
"    LDR     R0, [R7, #0x10] \n"
"    LDR     R1, [SP, #4] \n"
"    BL      sub_FF828DD0 \n"
"    LDR     R0, [R7, #0x10] \n"
"    LDR     R7, =0x2B14 \n"
"    STR     R0, [R9, R4, LSL#2] \n"
"    LDRH    R1, [R11] \n"
"    LDR     R0, [SP, #0x18] \n"
"    STRH    R1, [R0] \n"
"    LDR     R0, [R7, R4, LSL#2] \n"
"    BL      sub_FF82F104 /*_CancelTimer*/ \n"
"    LDR     R2, =0xFF865F74 \n"
"    ORR     R3, R4, #0x300 \n"
"    MOV     R1, R2 \n"
"    MOV     R0, #0x1F4 \n"
"    BL      sub_FF82F020 /*_SetTimerAfter*/ \n"
"    TST     R0, #1 \n"
"    CMPNE   R0, #0x15 \n"
"    STR     R0, [R7, R4, LSL#2] \n"
"    BEQ     loc_FF866274 \n"
"    LDR     R1, =0x267 \n"

"loc_FF86626C:\n"
"    LDR     R0, =0xFF8662CC /*'RotaryEncoder.c'*/ \n"
"    BL      _DebugAssert \n"

"loc_FF866274:\n"
"    ADD     R0, R6, R5, LSL#2 \n"
"    LDR     R0, [R0, #0x18] \n"
"    CMP     R0, #1 \n"
"    BNE     loc_FF866310 \n"
"    LDR     R0, =0x2B08 \n"
"    LDR     R0, [R0, #0x10] \n"
"    CMP     R0, #0 \n"
"    BEQ     loc_FF866310 \n"
"    LDR     R2, =0xFF865F68 \n"
"    ORR     R3, R4, #0x400 \n"
"    MOV     R1, R2 \n"
"    BL      sub_FF82F020 /*_SetTimerAfter*/ \n"
"    TST     R0, #1 \n"
"    CMPNE   R0, #0x15 \n"
"    STR     R0, [R10, R4, LSL#2] \n"
"    BEQ     loc_FF86606C \n"
"    LDR     R1, =0x26E \n"

"loc_FF8662B8:\n"
"    LDR     R0, =0xFF8662CC /*'RotaryEncoder.c'*/ \n"
"    BL      _DebugAssert \n"
"    B       loc_FF86606C \n"

"loc_FF866310:\n"
"    LDR     R0, [R6, R5, LSL#2] \n"
"    B       loc_FF8660D4 \n"

"loc_FF866318:\n"
"    LDR     R0, [R9, R4, LSL#2] \n"
"    CMP     R0, #0 \n"
"    MOVEQ   R1, #0x278 \n"
"    LDREQ   R0, =0xFF8662CC /*'RotaryEncoder.c'*/ \n"
"    BLEQ    _DebugAssert \n"
"    RSB     R0, R4, R4, LSL#3 \n"
"    ADD     R0, R6, R0, LSL#2 \n"
"    LDR     R0, [R0, #0xC] \n"
"    BL      sub_FF828DC0 \n"
"    MOV     R0, #0 \n"
"    STR     R0, [R9, R4, LSL#2] \n"
"    B       loc_FF86606C \n"
);
}
