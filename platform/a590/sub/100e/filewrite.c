/*
 * filewrite.c - auto-generated by CHDK code_gen.
 */
#include "lolevel.h"
#include "platform.h"

typedef struct {
    unsigned int address;
    unsigned int length;
} cam_ptp_data_chunk; //camera specific structure

#define MAX_CHUNKS_FOR_FWT 3 //filewritetask is prepared for this many chunks
/*
 * fwt_data_struct: defined here as it's camera dependent
 * unneeded members are designated with unkn
 * file_offset, full_size, seek_flag only needs to be defined for DryOS>=r50 generation cameras
 * pdc is always required
 * name is not currently used
 */
typedef struct
{
    int unkn1[5];                                //
    cam_ptp_data_chunk pdc[MAX_CHUNKS_FOR_FWT];
    char name[32];                               // open stage: sub_FFDD66A4 (1.01b) --> "ADD     R0, R0, #0x2C"
                                                 // offset of 'name' from start = 0x2C = 44 bytes = 11 words
} fwt_data_struct;

#include "../../../generic/filewrite.c"

/*************************************************************/
//** filewritetask @ 0xFFDD6408 - 0xFFDD64E8, length=57
void __attribute__((naked,noinline)) filewritetask() {
asm volatile (
"    STMFD   SP!, {R1-R5,LR} \n"
"    LDR     R4, =0xAD10 \n"

"loc_FFDD6410:\n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #8 \n"
"    BL      sub_FFC17B08 /*_ReceiveMessageQueue*/ \n"
"    CMP     R0, #0 \n"
"    BNE     loc_FFDD6440 \n"
"    LDR     R0, [SP, #8] \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #1 \n"
"    BNE     loc_FFDD6448 \n"
"    LDR     R0, [R4, #8] \n"
"    BL      _GiveSemaphore \n"

"loc_FFDD6440:\n"
"    BL      _ExitTask \n"
"    LDMFD   SP!, {R1-R5,PC} \n"

"loc_FFDD6448:\n"
"    SUB     R1, R1, #2 \n"
"    CMP     R1, #5 \n"
"    ADDLS   PC, PC, R1, LSL#2 \n"
"    B       loc_FFDD6410 \n"
"    B       loc_FFDD6470 \n"
"    B       loc_FFDD64D4 \n"
"    B       loc_FFDD64DC \n"
"    B       loc_FFDD64DC \n"
"    B       loc_FFDD64DC \n"
"    B       loc_FFDD64E4 \n"

"loc_FFDD6470:\n"
"    MOV     R0, #0 \n"
"    STR     R0, [SP] \n"

"loc_FFDD6478:\n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R1, SP \n"
"    BL      sub_FFC17D0C /*_GetNumberOfPostedMessages*/ \n"
"    LDR     R0, [SP] \n"
"    CMP     R0, #0 \n"
"    BEQ     loc_FFDD64A4 \n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #4 \n"
"    BL      sub_FFC17B08 /*_ReceiveMessageQueue*/ \n"
"    B       loc_FFDD6478 \n"

"loc_FFDD64A4:\n"
"    LDR     R0, [R4] \n"
"    CMN     R0, #1 \n"
"    BEQ     loc_FFDD64C8 \n"
"    BL      fwt_close \n"  // --> Patched. Old value = _Close.
"    MVN     R0, #0 \n"
"    STR     R0, [R4] \n"
"    LDR     R0, =0x7B508 \n"
"    BL      sub_FFC4178C \n"
"    BL      sub_FFC43040 \n"

"loc_FFDD64C8:\n"
"    LDR     R0, [R4, #0xC] \n"
"    BL      _GiveSemaphore \n"
"    B       loc_FFDD6410 \n"

"loc_FFDD64D4:\n"
"    BL      sub_FFDD66A8_my \n"  // --> Patched. Old value = 0xFFDD66A8. Open stage
"    B       loc_FFDD6410 \n"

"loc_FFDD64DC:\n"
"    BL      sub_FFDD67E8_my \n"  // --> Patched. Old value = 0xFFDD67E8. Write stage
"    B       loc_FFDD6410 \n"

"loc_FFDD64E4:\n"
"    BL      sub_FFDD68E4_my \n"  // --> Patched. Old value = 0xFFDD68E4. Close stage
"    B       loc_FFDD6410 \n"
);
}

/*************************************************************/
//** sub_FFDD66A8_my @ 0xFFDD66A8 - 0xFFDD66E8, length=17
void __attribute__((naked,noinline)) sub_FFDD66A8_my() {
asm volatile (
"    STMFD   SP!, {R4-R8,LR} \n"
"    MOV     R4, R0 \n"
"    ADD     R0, R0, #0x2C \n"
"    SUB     SP, SP, #0x38 \n"
"    BL      sub_FFC4178C \n"
"    MOV     R1, #0 \n"
"    BL      sub_FFC42FF0 \n"
"    LDR     R0, [R4, #0xC] \n"
"    BL      sub_FFC438E0 \n"
"    LDR     R7, [R4, #8] \n"
"    LDR     R8, =0x1B6 \n"
"    ADD     R6, R4, #0x2C \n"
"    LDR     R5, [R4, #0xC] \n"
//hook start
"    STMFD SP!, {R4-R12,LR}\n"
"    MOV R0, R4\n"
"    BL filewrite_main_hook\n"
"    LDMFD SP!, {R4-R12,LR}\n"
//hook end
"    MOV     R0, R6 \n"
"    MOV     R1, R7 \n"
"    MOV     R2, R8 \n"
"    BL      fwt_open \n"  // --> Patched. Old value = _Open.
"    LDR     PC, =0xFFDD66EC \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FFDD67E8_my @ 0xFFDD67E8 - 0xFFDD68E0, length=63
void __attribute__((naked,noinline)) sub_FFDD67E8_my() {
asm volatile (
"    STMFD   SP!, {R4-R10,LR} \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R0] \n"
"    CMP     R0, #4 \n"
"    LDREQ   R6, [R4, #0x18] \n"
"    LDREQ   R7, [R4, #0x14] \n"
"    BEQ     loc_FFDD6824 \n"
"    CMP     R0, #5 \n"
"    LDREQ   R6, [R4, #0x20] \n"
"    LDREQ   R7, [R4, #0x1C] \n"
"    BEQ     loc_FFDD6824 \n"
"    CMP     R0, #6 \n"
"    BNE     loc_FFDD6838 \n"
"    LDR     R6, [R4, #0x28] \n"
"    LDR     R7, [R4, #0x24] \n"

"loc_FFDD6824:\n"
"    CMP     R6, #0 \n"
"    BNE     loc_FFDD6848 \n"

"loc_FFDD682C:\n"
"    MOV     R1, R4 \n"
"    MOV     R0, #7 \n"
"    B       loc_FFDD68DC \n"

"loc_FFDD6838:\n"
"    LDR     R1, =0x1E2 \n"
"    LDR     R0, =0xFFDD67C8 /*'dwFWrite.c'*/ \n"
"    BL      _DebugAssert \n"
"    B       loc_FFDD682C \n"

"loc_FFDD6848:\n"
"    LDR     R9, =0xAD10 \n"
"    MOV     R5, R6 \n"

"loc_FFDD6850:\n"
"    LDR     R0, [R4, #4] \n"
"    CMP     R5, #0x1000000 \n"
"    MOVLS   R8, R5 \n"
"    MOVHI   R8, #0x1000000 \n"
"    BIC     R1, R0, #0xFF000000 \n"
"    CMP     R1, #0 \n"
"    BICNE   R0, R0, #0xFF000000 \n"
"    RSBNE   R0, R0, #0x1000000 \n"
"    CMPNE   R8, R0 \n"
"    MOVHI   R8, R0 \n"
"    LDR     R0, [R9] \n"
"    MOV     R2, R8 \n"
"    MOV     R1, R7 \n"
"    BL      fwt_write \n"  // --> Patched. Old value = _Write.
"    LDR     R1, [R4, #4] \n"
"    CMP     R8, R0 \n"
"    ADD     R1, R1, R0 \n"
"    STR     R1, [R4, #4] \n"
"    BEQ     loc_FFDD68B0 \n"
"    LDR     R0, =0x10B1 \n"
"    BL      sub_FFC61E48 /*_IsControlEventActive_FW*/ \n"
"    LDR     R1, =0x9200005 \n"
"    STR     R1, [R4, #0x10] \n"
"    B       loc_FFDD682C \n"

"loc_FFDD68B0:\n"
"    SUB     R5, R5, R0 \n"
"    CMP     R5, R6 \n"
"    ADD     R7, R7, R0 \n"
"    LDRCS   R1, =0x211 \n"
"    LDRCS   R0, =0xFFDD67C8 /*'dwFWrite.c'*/ \n"
"    BLCS    _DebugAssert \n"
"    CMP     R5, #0 \n"
"    BNE     loc_FFDD6850 \n"
"    LDR     R0, [R4] \n"
"    MOV     R1, R4 \n"
"    ADD     R0, R0, #1 \n"

"loc_FFDD68DC:\n"
"    LDMFD   SP!, {R4-R10,LR} \n"
"    B       sub_FFDD6360 \n"
);
}

/*************************************************************/
//** sub_FFDD68E4_my @ 0xFFDD68E4 - 0xFFDD6900, length=8
void __attribute__((naked,noinline)) sub_FFDD68E4_my() {
asm volatile (
"    STMFD   SP!, {R4,R5,LR} \n"
"    LDR     R5, =0xAD10 \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R5] \n"
"    SUB     SP, SP, #0x1C \n"
"    CMN     R0, #1 \n"
"    BEQ     sub_FFDD6918 \n"
"    BL      fwt_close \n"  // --> Patched. Old value = _Close.
"    LDR     PC, =0xFFDD6904 \n"  // Continue in firmware
);
}
