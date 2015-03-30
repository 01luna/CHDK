/*
 * filewrite.c - auto-generated by CHDK code_gen.
 */
#include "lolevel.h"
#include "platform.h"

typedef struct {
    unsigned int address;
    unsigned int length;
} cam_ptp_data_chunk; //camera specific structure

#define MAX_CHUNKS_FOR_JPEG 4 // filewritetask is prepared for this many chunks
/*
 * fwt_data_struct: defined here as it's camera dependent
 * unneeded members are designated with unkn
 * file_offset, full_size, seek_flag only needs to be defined for DryOS>=r50 generation cameras
 * cameras with possible multipass JPEG writes need oflags
 * pdc is always required
 * name is not currently used
 */
typedef struct
{
    int unkn1[2];
    int oflags;
    int unkn2[2];
    cam_ptp_data_chunk pdc[MAX_CHUNKS_FOR_JPEG];
    int unkn6;
    char name[32];
} fwt_data_struct;

#include "../../../generic/filewrite.c"

/*************************************************************/
//** filewritetask @ 0xFFE03B60 - 0xFFE03C44, length=58
void __attribute__((naked,noinline)) filewritetask() {
asm volatile (
"    STMFD   SP!, {R1-R5,LR} \n"
"    LDR     R4, =0x8AA0 \n"

"loc_FFE03B68:\n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #8 \n"
"    BL      sub_FFC2936C /*_ReceiveMessageQueue*/ \n"
"    CMP     R0, #0 \n"
"    BNE     loc_FFE03B98 \n"
"    LDR     R0, [SP, #8] \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #1 \n"
"    BNE     loc_FFE03BA0 \n"
"    LDR     R0, [R4, #8] \n"
"    BL      _GiveSemaphore \n"

"loc_FFE03B98:\n"
"    BL      _ExitTask \n"
"    LDMFD   SP!, {R1-R5,PC} \n"

"loc_FFE03BA0:\n"
"    SUB     R1, R1, #2 \n"
"    CMP     R1, #6 \n"
"    ADDLS   PC, PC, R1, LSL#2 \n"
"    B       loc_FFE03B68 \n"
"    B       loc_FFE03BCC \n"
"    B       loc_FFE03C30 \n"
"    B       loc_FFE03C38 \n"
"    B       loc_FFE03C38 \n"
"    B       loc_FFE03C38 \n"
"    B       loc_FFE03C38 \n"
"    B       loc_FFE03C40 \n"

"loc_FFE03BCC:\n"
"    MOV     R0, #0 \n"
"    STR     R0, [SP] \n"

"loc_FFE03BD4:\n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R1, SP \n"
"    BL      sub_FFC295B0 /*_GetNumberOfPostedMessages*/ \n"
"    LDR     R0, [SP] \n"
"    CMP     R0, #0 \n"
"    BEQ     loc_FFE03C00 \n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #4 \n"
"    BL      sub_FFC2936C /*_ReceiveMessageQueue*/ \n"
"    B       loc_FFE03BD4 \n"

"loc_FFE03C00:\n"
"    LDR     R0, [R4] \n"
"    CMN     R0, #1 \n"
"    BEQ     loc_FFE03C24 \n"
"    BL      fwt_close \n"  // --> Patched. Old value = _Close.
"    MVN     R0, #0 \n"
"    STR     R0, [R4] \n"
"    LDR     R0, =0xC431C \n"
"    BL      sub_FFC55D04 \n"
"    BL      sub_FFC53FA0 \n"

"loc_FFE03C24:\n"
"    LDR     R0, [R4, #0xC] \n"
"    BL      _GiveSemaphore \n"
"    B       loc_FFE03B68 \n"

"loc_FFE03C30:\n"
"    BL      sub_FFE03E50_my \n"  // --> Patched. Old value = 0xFFE03E50. Open stage
"    B       loc_FFE03B68 \n"

"loc_FFE03C38:\n"
"    BL      sub_FFE03F84_my \n"  // --> Patched. Old value = 0xFFE03F84. Write stage
"    B       loc_FFE03B68 \n"

"loc_FFE03C40:\n"
"    BL      sub_FFE039EC_my \n"  // --> Patched. Old value = 0xFFE039EC. Close stage
"    B       loc_FFE03B68 \n"
);
}

/*************************************************************/
//** sub_FFE03E50_my @ 0xFFE03E50 - 0xFFE03E90, length=17
void __attribute__((naked,noinline)) sub_FFE03E50_my() {
asm volatile (
"    STMFD   SP!, {R4-R8,LR} \n"
"    MOV     R4, R0 \n"
"    ADD     R0, R0, #0x38 \n"
"    SUB     SP, SP, #0x38 \n"
"    BL      sub_FFC55D04 \n"
"    MOV     R1, #0 \n"
"    BL      sub_FFC53F50 \n"
"    LDR     R0, [R4, #0xC] \n"
"    BL      sub_FFC00338 \n"
"    LDR     R7, [R4, #8] \n"
"    LDR     R8, =0x1B6 \n"
"    ADD     R6, R4, #0x38 \n"
"    LDR     R5, [R4, #0xC] \n"
//hook start
// "    STMFD SP!, {R4-R12,LR}\n"
"    MOV R0, R4\n"
"    BL filewrite_main_hook\n"
// "    LDMFD SP!, {R4-R12,LR}\n"
//hook end
"    MOV     R0, R6 \n"
"    MOV     R1, R7 \n"
"    MOV     R2, R8 \n"
"    BL      fwt_open \n"  // --> Patched. Old value = _Open.
"    LDR     PC, =0xFFE03E94 \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FFE03F84_my @ 0xFFE03F84 - 0xFFE0408C, length=67
void __attribute__((naked,noinline)) sub_FFE03F84_my() {
asm volatile (
"    STMFD   SP!, {R4-R10,LR} \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R0] \n"
"    CMP     R0, #4 \n"
"    LDREQ   R6, [R4, #0x18] \n"
"    LDREQ   R7, [R4, #0x14] \n"
"    BEQ     loc_FFE03FD0 \n"
"    CMP     R0, #5 \n"
"    LDREQ   R6, [R4, #0x20] \n"
"    LDREQ   R7, [R4, #0x1C] \n"
"    BEQ     loc_FFE03FD0 \n"
"    CMP     R0, #6 \n"
"    LDREQ   R6, [R4, #0x28] \n"
"    LDREQ   R7, [R4, #0x24] \n"
"    BEQ     loc_FFE03FD0 \n"
"    CMP     R0, #7 \n"
"    BNE     loc_FFE03FE4 \n"
"    LDR     R6, [R4, #0x30] \n"
"    LDR     R7, [R4, #0x2C] \n"

"loc_FFE03FD0:\n"
"    CMP     R6, #0 \n"
"    BNE     loc_FFE03FF4 \n"

"loc_FFE03FD8:\n"
"    MOV     R1, R4 \n"
"    MOV     R0, #8 \n"
"    B       loc_FFE04088 \n"

"loc_FFE03FE4:\n"
"    LDR     R1, =0x29F \n"
"    LDR     R0, =0xFFE03C58 /*'dwFWrite.c'*/ \n"
"    BL      _DebugAssert \n"
"    B       loc_FFE03FD8 \n"

"loc_FFE03FF4:\n"
"    LDR     R9, =0x8AA0 \n"
"    MOV     R5, R6 \n"

"loc_FFE03FFC:\n"
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
"    BEQ     loc_FFE0405C \n"
"    CMN     R0, #1 \n"
"    LDRNE   R0, =0x9200015 \n"
"    LDREQ   R0, =0x9200005 \n"
"    STR     R0, [R4, #0x10] \n"
"    B       loc_FFE03FD8 \n"

"loc_FFE0405C:\n"
"    SUB     R5, R5, R0 \n"
"    CMP     R5, R6 \n"
"    ADD     R7, R7, R0 \n"
"    LDRCS   R0, =0xFFE03C58 /*'dwFWrite.c'*/ \n"
"    LDRCS   R1, =0x2CA \n"
"    BLCS    _DebugAssert \n"
"    CMP     R5, #0 \n"
"    BNE     loc_FFE03FFC \n"
"    LDR     R0, [R4] \n"
"    MOV     R1, R4 \n"
"    ADD     R0, R0, #1 \n"

"loc_FFE04088:\n"
"    LDMFD   SP!, {R4-R10,LR} \n"
"    B       sub_FFE0392C \n"
);
}

/*************************************************************/
//** sub_FFE039EC_my @ 0xFFE039EC - 0xFFE03A20, length=14
void __attribute__((naked,noinline)) sub_FFE039EC_my() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    LDR     R5, =0x8AA0 \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R5] \n"
"    SUB     SP, SP, #0x38 \n"
"    CMN     R0, #1 \n"
"    BEQ     sub_FFE03A34 \n"
"    LDR     R1, [R4, #8] \n"
"    LDR     R6, =0x9200003 \n"
"    TST     R1, #0x8000 \n"
"    BEQ     loc_FFE03A20 \n"
//mod start
"    LDR R3, =current_write_ignored\n"
"    LDR R3, [R3]\n"
"    CMP R3, #0\n"
"    BNE loc_D\n" // jump over the next block
//mod end

"    BL      sub_FFC52FFC \n"
"    B       sub_FFE03A24 \n"

"loc_FFE03A20:\n"
"loc_D:\n"
"    BL      fwt_close \n"  // --> Patched. Old value = _Close.
"    LDR     PC, =0xFFE03A24 \n"  // Continue in firmware
);
}