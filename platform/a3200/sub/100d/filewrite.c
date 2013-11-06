/*
 * filewrite.c - auto-generated by CHDK code_gen.
 */
#include "lolevel.h"
#include "platform.h"

typedef struct {
    unsigned int address;
    unsigned int length;
} cam_ptp_data_chunk; //camera specific structure

#define MAX_CHUNKS_FOR_JPEG 7 // filewritetask is prepared for this many chunks
/*
 * fwt_data_struct: defined here as it's camera dependent
 * unneeded members are designated with unkn
 * file_offset, full_size, seek_flag only needs to be defined for DryOS>=r50 generation cameras
 * pdc is always required
 * name is not currently used
 */

typedef struct
{
    int unkn1[5];
    cam_ptp_data_chunk pdc[MAX_CHUNKS_FOR_JPEG];
    int unkn6;
    char name[32];
} fwt_data_struct;

#include "../../../generic/filewrite.c"

/*************************************************************/
//** filewritetask @ 0xFFA8EA9C - 0xFFA8EB7C, length=57
void __attribute__((naked,noinline)) filewritetask() {
asm volatile (
"    STMFD   SP!, {R1-R5,LR} \n"
"    LDR     R5, =0xABA8 \n"

"loc_FFA8EAA4:\n"
"    MOV     R2, #0 \n"
"    LDR     R0, [R5, #0x10] \n"
"    ADD     R1, SP, #8 \n"
"    BL      sub_FF839B84 /*_ReceiveMessageQueue*/ \n"
"    CMP     R0, #0 \n"
"    LDRNE   R1, =0x33F \n"
"    LDRNE   R0, =0xFFA8EB90 \n"
"    BLNE    _DebugAssert \n"
"    LDR     R0, [SP, #8] \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #0xA \n"
"    ADDCC   PC, PC, R1, LSL#2 \n"
"    B       loc_FFA8EAA4 \n"
"    B       loc_FFA8EB70 \n"
"    B       loc_FFA8EB70 \n"
"    B       loc_FFA8EB70 \n"
"    B       loc_FFA8EB70 \n"
"    B       loc_FFA8EB70 \n"
"    B       loc_FFA8EB70 \n"
"    B       loc_FFA8EB70 \n"
"    B       loc_FFA8EB78 \n"
"    B       loc_FFA8EB00 \n"
"    B       loc_FFA8EB68 \n"

"loc_FFA8EB00:\n"
"    MOV     R0, #0 \n"
"    MOV     R4, R5 \n"
"    STR     R0, [SP] \n"

"loc_FFA8EB0C:\n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R1, SP \n"
"    BL      sub_FF839DC8 /*_GetNumberOfPostedMessages*/ \n"
"    LDR     R0, [SP] \n"
"    CMP     R0, #0 \n"
"    BEQ     loc_FFA8EB38 \n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #4 \n"
"    BL      sub_FF839B84 /*_ReceiveMessageQueue*/ \n"
"    B       loc_FFA8EB0C \n"

"loc_FFA8EB38:\n"
"    LDR     R0, [R4, #4] \n"
"    CMN     R0, #1 \n"
"    BEQ     loc_FFA8EB5C \n"
"    BL      fwt_close \n"  // --> Patched. Old value = _Close.
"    MVN     R0, #0 \n"
"    STR     R0, [R4, #4] \n"
"    LDR     R0, =0xF93DC \n"
"    BL      sub_FF86FE70 \n"
"    BL      sub_FF86E09C \n"

"loc_FFA8EB5C:\n"
"    LDR     R0, [R4, #0xC] \n"
"    BL      _GiveSemaphore \n"
"    B       loc_FFA8EAA4 \n"

"loc_FFA8EB68:\n"
"    BL      sub_FFA8ED78_my \n"  // --> Patched. Old value = 0xFFA8ED78. Open stage
"    B       loc_FFA8EAA4 \n"

"loc_FFA8EB70:\n"
"    BL      sub_FFA8EEC0_my \n"  // --> Patched. Old value = 0xFFA8EEC0. Write stage
"    B       loc_FFA8EAA4 \n"

"loc_FFA8EB78:\n"
"    BL      sub_FFA8E928_my \n"  // --> Patched. Old value = 0xFFA8E928. Close stage
"    B       loc_FFA8EAA4 \n"
);
}

/*************************************************************/
//** sub_FFA8ED78_my @ 0xFFA8ED78 - 0xFFA8EDCC, length=22
void __attribute__((naked,noinline)) sub_FFA8ED78_my() {
asm volatile (
"    STMFD   SP!, {R4-R8,LR} \n"
"    MOV     R4, R0 \n"
"    SUB     SP, SP, #0x38 \n"
"    ADD     R0, R0, #0x50 \n"
"    BL      sub_FF86FE70 \n"
"    MOV     R1, #0 \n"
"    BL      sub_FF86E034 \n"
"    LDR     R0, [R4, #0xC] \n"
"    BL      sub_FF81033C \n"
"    LDR     R0, [R4, #0x4C] \n"
"    LDR     R8, =0x1B6 \n"
"    CMP     R0, #1 \n"
"    LDREQ   R0, [R4, #8] \n"
"    ADD     R6, R4, #0x50 \n"
"    ORREQ   R0, R0, #0x8000 \n"
"    STREQ   R0, [R4, #8] \n"
//hook start
"    MOV     R0, R4 \n"
"    BL      filewrite_main_hook \n"
//hook end
"    LDR     R7, [R4, #8] \n"
"    LDR     R5, [R4, #0xC] \n"
"    MOV     R2, R8 \n"
"    MOV     R1, R7 \n"
"    MOV     R0, R6 \n"
"    BL      fwt_open \n"  // --> Patched. Old value = _Open.
"    LDR     PC, =0xFFA8EDD0 \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FFA8EEC0_my @ 0xFFA8EEC0 - 0xFFA8EFC8, length=67
void __attribute__((naked,noinline)) sub_FFA8EEC0_my() {
asm volatile (
"    STMFD   SP!, {R4-R10,LR} \n"
"    MOV     R5, R0 \n"
"    LDR     R0, [R0] \n"
"    CMP     R0, #6 \n"
"    BHI     loc_FFA8EEEC \n"
"    ADD     R0, R5, R0, LSL#3 \n"
"    LDR     R8, [R0, #0x14]! \n"
"    LDR     R7, [R0, #4] \n"
"    CMP     R7, #0 \n"
"    BNE     loc_FFA8EF04 \n"
"    B       loc_FFA8EEF8 \n"

"loc_FFA8EEEC:\n"
"    LDR     R1, =0x299 \n"
"    LDR     R0, =0xFFA8EB90 \n"
"    BL      _DebugAssert \n"

"loc_FFA8EEF8:\n"
"    MOV     R1, R5 \n"
"    MOV     R0, #7 \n"
"    B       loc_FFA8EF98 \n"

"loc_FFA8EF04:\n"
"    LDR     R9, =0xABA8 \n"
"    MOV     R4, R7 \n"

"loc_FFA8EF0C:\n"
"    LDR     R0, [R5, #4] \n"
"    CMP     R4, #0x1000000 \n"
"    MOVLS   R6, R4 \n"
"    MOVHI   R6, #0x1000000 \n"
"    BIC     R1, R0, #0xFF000000 \n"
"    CMP     R1, #0 \n"
"    BICNE   R0, R0, #0xFF000000 \n"
"    RSBNE   R0, R0, #0x1000000 \n"
"    CMPNE   R6, R0 \n"
"    MOVHI   R6, R0 \n"
"    LDR     R0, [R9, #4] \n"
"    MOV     R2, R6 \n"
"    MOV     R1, R8 \n"
"    BL      fwt_write \n"  // --> Patched. Old value = _Write.
"    LDR     R1, [R5, #4] \n"
"    CMP     R6, R0 \n"
"    ADD     R1, R1, R0 \n"
"    STR     R1, [R5, #4] \n"
"    BEQ     loc_FFA8EF6C \n"
"    CMN     R0, #1 \n"
"    LDRNE   R0, =0x9200015 \n"
"    LDREQ   R0, =0x9200005 \n"
"    STR     R0, [R5, #0x10] \n"
"    B       loc_FFA8EEF8 \n"

"loc_FFA8EF6C:\n"
"    SUB     R4, R4, R0 \n"
"    CMP     R4, R7 \n"
"    ADD     R8, R8, R0 \n"
"    MOVCS   R1, #0x2C4 \n"
"    LDRCS   R0, =0xFFA8EB90 \n"
"    BLCS    _DebugAssert \n"
"    CMP     R4, #0 \n"
"    BNE     loc_FFA8EF0C \n"
"    LDR     R0, [R5] \n"
"    MOV     R1, R5 \n"
"    ADD     R0, R0, #1 \n"

"loc_FFA8EF98:\n"
"    LDMFD   SP!, {R4-R10,LR} \n"
"    B       sub_FFA8E878 \n"
);
}

/*************************************************************/
//** sub_FFA8E928_my @ 0xFFA8E928 - 0xFFA8E95C, length=14
void __attribute__((naked,noinline)) sub_FFA8E928_my() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    LDR     R5, =0xABA8 \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R5, #4] \n"
"    SUB     SP, SP, #0x38 \n"
"    CMN     R0, #1 \n"
"    BEQ     sub_FFA8E970 \n"
"    LDR     R1, [R4, #8] \n"
"    LDR     R6, =0x9200003 \n"
"    TST     R1, #0x8000 \n"
"    BEQ     loc_FFA8E95C \n"
//mod start
"    LDR R3, =current_write_ignored\n"
"    LDR R3, [R3]\n"
"    CMP R3, #0\n"
"    BNE loc_D\n" // jump over the next block
//mod end
"    BL      sub_FF836D20 \n"
"    B       sub_FFA8E960 \n"

"loc_FFA8E95C:\n"
"loc_D:\n"
"    BL      fwt_close \n"  // --> Patched. Old value = _Close.
"    LDR     PC, =0xFFA8E960 \n"  // Continue in firmware
);
}
