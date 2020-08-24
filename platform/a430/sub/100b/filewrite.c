/*
 * filewrite.c - auto-generated by CHDK code_gen.
 */
#include "lolevel.h"
#include "platform.h"

typedef struct {
    unsigned int address;
    unsigned int length;
} cam_ptp_data_chunk; //camera specific structure

#define MAX_CHUNKS_FOR_FWT 3 //model specific
/*
 * fwt_data_struct: defined here as it's camera dependent
 * unneeded members are designated with unkn
 * file_offset, full_size, seek_flag only needs to be defined for DryOS>=r50 generation cameras
 * pdc is always required
 * name is not currently used
 */
typedef struct
{
    int unkn1;
    cam_ptp_data_chunk pdc[MAX_CHUNKS_FOR_FWT];
    char name[32];
} fwt_data_struct;
#define CAM_HAS_COMPLETEFILEWRITE_REPLACEMENT 1

#include "../../../generic/filewrite.c"

/*************************************************************/
//** filewritetask @ 0xFFC5586C - 0xFFC558FC, length=37
void __attribute__((naked,noinline)) filewritetask() {
asm volatile (
"    STMFD   SP!, {R4,LR} \n"
"    LDR     R4, =0x1B2A4 \n"
"    SUB     SP, SP, #4 \n"
"    B       loc_FFC558A0 \n"

"loc_FFC5587C:\n"
"    TST     R3, #4 \n"
"    BEQ     loc_FFC5589C \n"
"    LDR     R0, [R4] \n"
"    BL      sub_FFC0FB48 /*_ClearEventFlag*/ \n"
"    LDR     R0, [R4] \n"
"    MOV     R1, #8 \n"
"    BL      sub_FFC0F9AC /*_SetEventFlag*/ \n"
"    B       loc_FFC558A0 \n"

"loc_FFC5589C:\n"
"    BL      sub_FFC557B4_my \n"  // --> Patched. Old value = 0xFFC557B4.

"loc_FFC558A0:\n"
"    MOV     R1, #7 \n"
"    LDR     R0, [R4] \n"
"    MOV     R2, #0 \n"
"    BL      sub_FFC0F98C /*_WaitForAnyEventFlag*/ \n"
"    CMP     R0, #0 \n"
"    MOV     R1, SP \n"
"    BEQ     loc_FFC558D0 \n"
"    MOV     R1, #0x2B0 \n"
"    LDR     R0, =0xFFC55708 /*'dwFWrite.c'*/ \n"
"    ADD     R1, R1, #1 \n"
"    BL      _DebugAssert \n"
"    B       loc_FFC558E8 \n"

"loc_FFC558D0:\n"
"    LDR     R0, [R4] \n"
"    BL      sub_FFC0FB98 /*_GetEventFlagValue*/ \n"
"    LDR     R3, [SP] \n"
"    TST     R3, #2 \n"
"    MOV     R1, #5 \n"
"    BEQ     loc_FFC5587C \n"

"loc_FFC558E8:\n"
"    LDR     R3, =0x1B2A8 \n"
"    LDR     R0, [R3] \n"
"    BL      _GiveSemaphore \n"
"    BL      _ExitTask \n"
"    ADD     SP, SP, #4 \n"
"    LDMFD   SP!, {R4,PC} \n"
);
}

/*************************************************************/
//** sub_FFC557B4_my @ 0xFFC557B4 - 0xFFC55850, length=40
void __attribute__((naked,noinline)) sub_FFC557B4_my() {
asm volatile (
"    STMFD   SP!, {R4,R5,LR} \n"
"    LDR     R2, =0x1B288 \n"
"    LDRH    R3, [R2] \n"
"    SUB     R3, R3, #1 \n"
"    CMP     R3, #3 \n"
"    LDRLS   PC, [PC, R3, LSL#2] \n"
"    B       loc_FFC55800 \n"
"    .long   loc_FFC557E0 \n"
"    .long   loc_FFC557F0 \n"
"    .long   loc_FFC557F0 \n"
"    .long   loc_FFC557F0 \n"

"loc_FFC557E0:\n"
"    LDR     R0, =0x1B248 \n"
"    BL      sub_FFC55660_my \n"  // --> Patched. Old value = 0xFFC55660.
"    MOV     R4, R0 \n"
"    B       loc_FFC55804 \n"

"loc_FFC557F0:\n"
"    LDR     R0, =0x1B248 \n"
"    BL      sub_FFC55714 \n"
"    MOV     R4, R0 \n"
"    B       loc_FFC55804 \n"

"loc_FFC55800:\n"
"    MOV     R4, #1 \n"

"loc_FFC55804:\n"
"    CMP     R4, #0 \n"
"    MOV     R1, #1 \n"
"    LDMEQFD SP!, {R4,R5,PC} \n"
"    LDR     R3, =0x1B2A4 \n"
"    LDR     R0, [R3] \n"
"    BL      sub_FFC0FB48 /*_ClearEventFlag*/ \n"
"    LDR     R3, =0x1B2B0 \n"
"    LDR     R5, [R3] \n"
"    LDR     R1, =0x1B2AC \n"
"    LDR     R12, =0x2778 \n"
"    MOV     R3, #1 \n"
"    MOV     R2, #0 \n"
"    CMP     R5, #0 \n"
"    STR     R3, [R1] \n"
"    MOV     R0, R4 \n"
"    STR     R2, [R12] \n"
"    LDMEQFD SP!, {R4,R5,PC} \n"
"    MOV     LR, PC \n"
"    MOV     PC, R5 \n"
"    BL      fwt_after_close\n" //+
"    LDMFD   SP!, {R4,R5,PC} \n"
);
}

/*************************************************************/
//** sub_FFC55660_my @ 0xFFC55660 - 0xFFC556F8, length=39
void __attribute__((naked,noinline)) sub_FFC55660_my() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    MOV     R4, R0 \n"
"    ADD     R5, R4, #0x1C \n"
"    MOV     R0, R5 \n"
"    BL      sub_FFC55338 \n"
"    LDR     R0, [R4, #0x3C] \n"
"    BL      sub_FFC5E3B0 \n"
"    LDR     R3, [R4] \n"
"    MOV     R1, #0x600 \n"
"    TST     R3, #0x10000 \n"
"    ADD     R1, R1, #1 \n"
"    MOV     R2, #0x1B4 \n"
"    ORRNE   R1, R1, #0x8000 \n"
"    LDR     R3, [R4, #0x3C] \n"
"    ADD     R2, R2, #2 \n"
//place hook here
//the task's data block is at [r4] at this point, filename starts at [r4+0x1c]
//the block can be captured here for a (new) camera with unknown data block structure
//for ptp remote capture, pass '/null' as filename
//if writing does not need to be prevented, just continue
"    STMFD SP!, {R1-R12,LR}\n"
"    MOV R0, R4\n"
"    BL filewrite_main_hook\n"
"    BL filewrite_file_complete\n"
"    CMP R0, #0\n"
"    LDRNE R0, =loc_mynull\n" // /null as file name (works only on VxWorks)
"    LDMFD SP!, {R1-R12,LR}\n"
"    MOVEQ R0, R5\n" //canon file name
//hook end
//"  MOV     R0, R5 \n"  // - file name
"    BL      sub_FFC5543C \n"
"    MOV     R1, R4 \n"
"    MOV     R2, R0 \n"
"    MOV     R4, #0 \n"
"    LDR     R3, =0x1B28C \n"
"    CMP     R2, R4 \n"
"    LDR     R6, =0x1B288 \n"
"    MOV     R0, R5 \n"
"    STR     R2, [R3] \n"
"    BGT     loc_FFC556E0 \n"
"    BL      sub_FFC5534C \n"
"    MOV     R0, #0x8000001 \n"
"    ADD     R0, R0, #0x1200000 \n"
"    BL      sub_FFC53040 \n"
"    MOV     R0, #2 \n"
"    LDMFD   SP!, {R4-R6,PC} \n"

"loc_FFC556E0:\n"
"    LDR     R3, =0x1B290 \n"
"    LDRH    R0, [R6] \n"
"    STR     R4, [R3] \n"
"    BL      sub_FFC555B0 \n"
"    STRH    R0, [R6] \n"
"    MOV     R0, R4 \n"
"    LDMFD   SP!, {R4-R6,PC} \n"
//mod start
"loc_mynull:\n"
".long   0x6c756e2f\n" // "/null"
".long   0x0000006c\n"
//mod end
);
}
