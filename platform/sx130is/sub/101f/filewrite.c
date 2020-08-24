/*
 * filewrite.c - auto-generated by CHDK code_gen.
 */
#include "lolevel.h"
#include "platform.h"

typedef struct {
    unsigned int address;
    unsigned int length;
} cam_ptp_data_chunk; //camera specific structure

#define MAX_CHUNKS_FOR_FWT 7   // filewritetask is prepared for this many chunks
/*
 * fwt_data_struct: defined here as it's camera dependent
 * unneeded members are designated with unkn
 * pdc is required, everything after that is optional (DryOS < R50)
 * file_offset, full_size, seek_flag only needs to be defined for DryOS>=r50 generation cameras
 */
typedef struct
{
    int unkn1[5];
    cam_ptp_data_chunk pdc[MAX_CHUNKS_FOR_FWT];
    int unkn2;
    char name[32];
} fwt_data_struct;

#include "../../../generic/filewrite.c"

/*************************************************************/
//** filewritetask @ 0xFFA8A35C - 0xFFA8A438, length=56
void __attribute__((naked,noinline)) filewritetask() {
asm volatile (
"    STMFD   SP!, {R1-R5,LR} \n"
"    LDR     R4, =0xAC00 \n"

"loc_FFA8A364:\n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #8 \n"
"    BL      sub_FF839B8C /*_ReceiveMessageQueue*/ \n"
"    CMP     R0, #0 \n"
"    LDRNE   R1, =0x33F \n"
"    LDRNE   R0, =0xFFA8A44C /*'dwFWrite.c'*/ \n"
"    BLNE    _DebugAssert \n"
"    LDR     R0, [SP, #8] \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #9 \n"
"    ADDLS   PC, PC, R1, LSL#2 \n"
"    B       loc_FFA8A364 \n"
"    B       loc_FFA8A42C \n"
"    B       loc_FFA8A42C \n"
"    B       loc_FFA8A42C \n"
"    B       loc_FFA8A42C \n"
"    B       loc_FFA8A42C \n"
"    B       loc_FFA8A42C \n"
"    B       loc_FFA8A42C \n"
"    B       loc_FFA8A434 \n"
"    B       loc_FFA8A3C0 \n"
"    B       loc_FFA8A424 \n"

"loc_FFA8A3C0:\n"
"    MOV     R0, #0 \n"
"    STR     R0, [SP] \n"

"loc_FFA8A3C8:\n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R1, SP \n"
"    BL      sub_FF839DD0 /*_GetNumberOfPostedMessages*/ \n"
"    LDR     R0, [SP] \n"
"    CMP     R0, #0 \n"
"    BEQ     loc_FFA8A3F4 \n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #4 \n"
"    BL      sub_FF839B8C /*_ReceiveMessageQueue*/ \n"
"    B       loc_FFA8A3C8 \n"

"loc_FFA8A3F4:\n"
"    LDR     R0, [R4, #4] \n"
"    CMN     R0, #1 \n"
"    BEQ     loc_FFA8A418 \n"
"    BL      fwt_close \n"  // --> Patched. Old value = _Close.
"    MVN     R0, #0 \n"
"    STR     R0, [R4, #4] \n"
"    LDR     R0, =0xF4984 \n"
"    BL      sub_FF870BA4 \n"
"    BL      sub_FF86EE44 \n"

"loc_FFA8A418:\n"
"    LDR     R0, [R4, #0xC] \n"
"    BL      _GiveSemaphore \n"
"    B       loc_FFA8A364 \n"

"loc_FFA8A424:\n"
"    BL      sub_FFA8A634_my \n"  // --> Patched. Old value = 0xFFA8A634.
"    B       loc_FFA8A364 \n"

"loc_FFA8A42C:\n"
"    BL      sub_FFA8A774_my \n"  // --> Patched. Old value = 0xFFA8A774.
"    B       loc_FFA8A364 \n"

"loc_FFA8A434:\n"
"    BL      sub_FFA8A1E8_my \n"  // --> Patched. Old value = 0xFFA8A1E8.
"    B       loc_FFA8A364 \n"
);
}

/*************************************************************/
//** sub_FFA8A634_my @ 0xFFA8A634 - 0xFFA8A6E8, length=46
void __attribute__((naked,noinline)) sub_FFA8A634_my() {
asm volatile (
"    STMFD   SP!, {R4-R8,LR} \n"
"    MOV     R4, R0 \n"
"    ADD     R0, R0, #0x50 \n"
"    SUB     SP, SP, #0x38 \n"
"    BL      sub_FF870BA4 \n"
"    MOV     R1, #0 \n"
"    BL      sub_FF86EDDC \n"
"    LDR     R0, [R4, #0xC] \n"
"    BL      sub_FF810338 \n"
"    LDR     R0, [R4, #0x4C] \n"
"    LDR     R8, =0x1B6 \n"
"    CMP     R0, #1 \n"
"    LDREQ   R0, [R4, #8] \n"
"    ADD     R6, R4, #0x50 \n"
"    ORREQ   R0, R0, #0x8000 \n"
"    STREQ   R0, [R4, #8] \n"
"    LDR     R7, [R4, #8] \n"
"    LDR     R5, [R4, #0xC] \n"
//hook start
"    STMFD   SP!, {R4-R12,LR} \n"
"    MOV     R0, R4 \n"
"    BL      filewrite_main_hook \n"
"    LDMFD   SP!, {R4-R12,LR} \n"
//hook end
"    MOV     R0, R6 \n"
"    MOV     R2, R8 \n"
"    MOV     R1, R7 \n"
"    BL      fwt_open \n"  // --> Patched. Old value = _Open.
"    CMN     R0, #1 \n"
"    BNE     sub_FFA8A6EC \n"
"    MOV     R0, R6 \n"
"    BL      sub_FF837090 \n"
"    MOV     R2, #0xF \n"
"    MOV     R1, R6 \n"
"    MOV     R0, SP \n"
"    BL      sub_FFB49F28 \n"
"    LDR     R0, =0x41FF \n"
"    MOV     R1, #0 \n"
"    STRB    R1, [SP, #0xF] \n"
"    STR     R0, [SP, #0x20] \n"
"    MOV     R0, #0x10 \n"
"    ADD     R2, SP, #0x24 \n"
"    STMIA   R2, {R0,R1,R5} \n"
"    ADD     R1, SP, #0x20 \n"
"    MOV     R0, SP \n"
"    STR     R5, [SP, #0x30] \n"
"    STR     R5, [SP, #0x34] \n"
"    BL      sub_FF86E74C \n"
"    MOV     R2, R8 \n"
"    MOV     R1, R7 \n"
"    MOV     R0, R6 \n"
"    BL      fwt_open \n"  // --> Patched. Old value = _Open.
"    LDR     PC, =0xFFA8A6EC \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FFA8A774_my @ 0xFFA8A774 - 0xFFA8A83C, length=51
void __attribute__((naked,noinline)) sub_FFA8A774_my() {
asm volatile (
"    STMFD   SP!, {R4-R10,LR} \n"
"    MOV     R5, R0 \n"
"    LDR     R0, [R0] \n"
"    CMP     R0, #6 \n"
"    BHI     loc_FFA8A7A8 \n"
"    ADD     R0, R5, R0, LSL#3 \n"
"    LDR     R7, [R0, #0x14]! \n"
"    LDR     R6, [R0, #4] \n"
"    CMP     R6, #0 \n"
"    BNE     loc_FFA8A7B8 \n"

"loc_FFA8A79C:\n"
"    MOV     R1, R5 \n"
"    MOV     R0, #7 \n"
"    B       sub_FFA8A84C \n"

"loc_FFA8A7A8:\n"
"    LDR     R1, =0x299 \n"
"    LDR     R0, =0xFFA8A44C /*'dwFWrite.c'*/ \n"
"    BL      _DebugAssert \n"
"    B       loc_FFA8A79C \n"

"loc_FFA8A7B8:\n"
"    LDR     R9, =0xAC00 \n"
"    MOV     R4, R6 \n"

"loc_FFA8A7C0:\n"
"    LDR     R0, [R5, #4] \n"
"    CMP     R4, #0x1000000 \n"
"    MOVLS   R8, R4 \n"
"    MOVHI   R8, #0x1000000 \n"
"    BIC     R1, R0, #0xFF000000 \n"
"    CMP     R1, #0 \n"
"    BICNE   R0, R0, #0xFF000000 \n"
"    RSBNE   R0, R0, #0x1000000 \n"
"    CMPNE   R8, R0 \n"
"    MOVHI   R8, R0 \n"
"    LDR     R0, [R9, #4] \n"
"    MOV     R2, R8 \n"
"    MOV     R1, R7 \n"
"    BL      fwt_write \n"  // --> Patched. Old value = _Write.
"    LDR     R1, [R5, #4] \n"
"    CMP     R8, R0 \n"
"    ADD     R1, R1, R0 \n"
"    STR     R1, [R5, #4] \n"
"    BEQ     loc_FFA8A820 \n"
"    CMN     R0, #1 \n"
"    LDRNE   R0, =0x9200015 \n"
"    LDREQ   R0, =0x9200005 \n"
"    STR     R0, [R5, #0x10] \n"
"    B       loc_FFA8A79C \n"

"loc_FFA8A820:\n"
"    SUB     R4, R4, R0 \n"
"    CMP     R4, R6 \n"
"    ADD     R7, R7, R0 \n"
"    LDRCS   R0, =0xFFA8A44C /*'dwFWrite.c'*/ \n"
"    MOVCS   R1, #0x2C4 \n"
"    BLCS    _DebugAssert \n"
"    CMP     R4, #0 \n"
"    BNE     loc_FFA8A7C0 \n"
"    LDR     PC, =0xFFA8A840 \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FFA8A1E8_my @ 0xFFA8A1E8 - 0xFFA8A21C, length=14
void __attribute__((naked,noinline)) sub_FFA8A1E8_my() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    LDR     R5, =0xAC00 \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R5, #4] \n"
"    SUB     SP, SP, #0x38 \n"
"    CMN     R0, #1 \n"
"    BEQ     sub_FFA8A230 \n"
"    LDR     R1, [R4, #8] \n"
"    LDR     R6, =0x9200003 \n"
"    TST     R1, #0x8000 \n"
"    BEQ     loc_FFA8A21C \n"
//mod start
"    LDR R3, =current_write_ignored\n"
"    LDR R3, [R3]\n"
"    CMP R3, #0\n"
"    BNE loc_D\n" // jump over the next block
//mod end
"    BL      sub_FF86DE88 \n"
"    B       sub_FFA8A220 \n"

"loc_FFA8A21C:\n"
"loc_D:\n"
"    BL      fwt_close \n"  // --> Patched. Old value = _Close.
"    LDR     PC, =0xFFA8A220 \n"  // Continue in firmware
);
}
