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
    int unkn1[5];                                   // 101a sub_FFAB7444 --> "LDR     R7, [R0, #0x14]!"
    cam_ptp_data_chunk pdc[MAX_CHUNKS_FOR_FWT];
    int unkn2;
    char name[32];                                  // 101a sub_FFAB7304 --> "ADD     R0, R0, #0x50"
                                                    // offset of 'name' from start = 0x50 = 80 bytes = 20 words
} fwt_data_struct;

#include "../../../generic/filewrite.c"

/*************************************************************/
//** filewritetask @ 0xFFAB702C - 0xFFAB7108, length=56
void __attribute__((naked,noinline)) filewritetask() {
asm volatile (
"    STMFD   SP!, {R1-R5,LR} \n"
"    LDR     R4, =0xBDC0 \n"

"loc_FFAB7034:\n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #8 \n"
"    BL      sub_FF83AE20 /*_ReceiveMessageQueue*/ \n"
"    CMP     R0, #0 \n"
"    LDRNE   R1, =0x33F \n"
"    LDRNE   R0, =0xFFAB711C /*'dwFWrite.c'*/ \n"
"    BLNE    _DebugAssert \n"
"    LDR     R0, [SP, #8] \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #9 \n"
"    ADDLS   PC, PC, R1, LSL#2 \n"
"    B       loc_FFAB7034 \n"
"    B       loc_FFAB70FC \n"
"    B       loc_FFAB70FC \n"
"    B       loc_FFAB70FC \n"
"    B       loc_FFAB70FC \n"
"    B       loc_FFAB70FC \n"
"    B       loc_FFAB70FC \n"
"    B       loc_FFAB70FC \n"
"    B       loc_FFAB7104 \n"
"    B       loc_FFAB7090 \n"
"    B       loc_FFAB70F4 \n"

"loc_FFAB7090:\n"
"    MOV     R0, #0 \n"
"    STR     R0, [SP] \n"

"loc_FFAB7098:\n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R1, SP \n"
"    BL      sub_FF83B064 /*_GetNumberOfPostedMessages*/ \n"
"    LDR     R0, [SP] \n"
"    CMP     R0, #0 \n"
"    BEQ     loc_FFAB70C4 \n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #4 \n"
"    BL      sub_FF83AE20 /*_ReceiveMessageQueue*/ \n"
"    B       loc_FFAB7098 \n"

"loc_FFAB70C4:\n"
"    LDR     R0, [R4, #4] \n"
"    CMN     R0, #1 \n"
"    BEQ     loc_FFAB70E8 \n"
"    BL      fwt_close \n"  // --> Patched. Old value = _Close.
"    MVN     R0, #0 \n"
"    STR     R0, [R4, #4] \n"
"    LDR     R0, =0x1000E0 \n"
"    BL      sub_FF8759D4 \n"
"    BL      sub_FF873C30 \n"

"loc_FFAB70E8:\n"
"    LDR     R0, [R4, #0xC] \n"
"    BL      _GiveSemaphore \n"
"    B       loc_FFAB7034 \n"

"loc_FFAB70F4:\n"
"    BL      sub_FFAB7304_my \n"  // --> Patched. Old value = 0xFFAB7304.
"    B       loc_FFAB7034 \n"

"loc_FFAB70FC:\n"
"    BL      sub_FFAB7444_my \n"  // --> Patched. Old value = 0xFFAB7444.
"    B       loc_FFAB7034 \n"

"loc_FFAB7104:\n"
"    BL      sub_FFAB6EB8_my \n"  // --> Patched. Old value = 0xFFAB6EB8.
"    B       loc_FFAB7034 \n"
);
}

/*************************************************************/
//** sub_FFAB7304_my @ 0xFFAB7304 - 0xFFAB7358, length=22
void __attribute__((naked,noinline)) sub_FFAB7304_my() {
asm volatile (
"    STMFD   SP!, {R4-R8,LR} \n"
"    MOV     R4, R0 \n"
"    ADD     R0, R0, #0x50 \n"
"    SUB     SP, SP, #0x38 \n"
"    BL      sub_FF8759D4 \n"
"    MOV     R1, #0 \n"
"    BL      sub_FF873BC8 \n"
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
"    LDR     PC, =0xFFAB735C \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FFAB7444_my @ 0xFFAB7444 - 0xFFAB74C4, length=33
void __attribute__((naked,noinline)) sub_FFAB7444_my() {
asm volatile (
"    STMFD   SP!, {R4-R10,LR} \n"
"    MOV     R5, R0 \n"
"    LDR     R0, [R0] \n"
"    CMP     R0, #6 \n"
"    BHI     loc_FFAB7478 \n"
"    ADD     R0, R5, R0, LSL#3 \n"
"    LDR     R7, [R0, #0x14]! \n"
"    LDR     R6, [R0, #4] \n"
"    CMP     R6, #0 \n"
"    BNE     loc_FFAB7488 \n"

"loc_FFAB746C:\n"
"    MOV     R1, R5 \n"
"    MOV     R0, #7 \n"
"    B       sub_FFAB751C \n"

"loc_FFAB7478:\n"
"    LDR     R1, =0x299 \n"
"    LDR     R0, =0xFFAB711C /*'dwFWrite.c'*/ \n"
"    BL      _DebugAssert \n"
"    B       loc_FFAB746C \n"

"loc_FFAB7488:\n"
"    LDR     R9, =0xBDC0 \n"
"    MOV     R4, R6 \n"
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
"    LDR     PC, =0xFFAB74C8 \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FFAB6EB8_my @ 0xFFAB6EB8 - 0xFFAB6EEC, length=14
void __attribute__((naked,noinline)) sub_FFAB6EB8_my() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    LDR     R5, =0xBDC0 \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R5, #4] \n"
"    SUB     SP, SP, #0x38 \n"
"    CMN     R0, #1 \n"
"    BEQ     sub_FFAB6F00 \n"
"    LDR     R1, [R4, #8] \n"
"    LDR     R6, =0x9200003 \n"
"    TST     R1, #0x8000 \n"
"    BEQ     loc_FFAB6EEC \n"
"    BL      sub_FF872C74 \n"
"    B       sub_FFAB6EF0 \n"

"loc_FFAB6EEC:\n"
"    BL      fwt_close \n"  // --> Patched. Old value = _Close.
"    LDR     PC, =0xFFAB6EF0 \n"  // Continue in firmware
);
}
