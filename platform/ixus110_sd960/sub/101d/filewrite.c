/*
 * filewrite.c - auto-generated by CHDK code_gen.
 */
#include "lolevel.h"
#include "platform.h"

typedef struct {
    unsigned int address;
    unsigned int length;
} cam_ptp_data_chunk; //camera specific structure

#define MAX_CHUNKS_FOR_FWT 3 // filewritetask is prepared for this many chunks
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
    cam_ptp_data_chunk pdc[MAX_CHUNKS_FOR_FWT];
    char name[32];
} fwt_data_struct;

#include "../../../generic/filewrite.c"

/*************************************************************/
//** filewritetask @ 0xFFA38DD4 - 0xFFA38EB4, length=57
void __attribute__((naked,noinline)) filewritetask() {
asm volatile (
"    STMFD   SP!, {R1-R5,LR} \n"
"    LDR     R4, =0x9824 \n"

"loc_FFA38DDC:\n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #8 \n"
"    BL      sub_FF826A0C /*_ReceiveMessageQueue*/ \n"
"    CMP     R0, #0 \n"
"    BNE     loc_FFA38E0C \n"
"    LDR     R0, [SP, #8] \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #1 \n"
"    BNE     loc_FFA38E14 \n"
"    LDR     R0, [R4, #8] \n"
"    BL      _GiveSemaphore \n"

"loc_FFA38E0C:\n"
"    BL      _ExitTask \n"
"    LDMFD   SP!, {R1-R5,PC} \n"

"loc_FFA38E14:\n"
"    SUB     R1, R1, #2 \n"
"    CMP     R1, #5 \n"
"    ADDLS   PC, PC, R1, LSL#2 \n"
"    B       loc_FFA38DDC \n"
"    B       loc_FFA38E3C \n"
"    B       loc_FFA38EA0 \n"
"    B       loc_FFA38EA8 \n"
"    B       loc_FFA38EA8 \n"
"    B       loc_FFA38EA8 \n"
"    B       loc_FFA38EB0 \n"

"loc_FFA38E3C:\n"
"    MOV     R0, #0 \n"
"    STR     R0, [SP] \n"

"loc_FFA38E44:\n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R1, SP \n"
"    BL      sub_FF826C50 /*_GetNumberOfPostedMessages*/ \n"
"    LDR     R0, [SP] \n"
"    CMP     R0, #0 \n"
"    BEQ     loc_FFA38E70 \n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #4 \n"
"    BL      sub_FF826A0C /*_ReceiveMessageQueue*/ \n"
"    B       loc_FFA38E44 \n"

"loc_FFA38E70:\n"
"    LDR     R0, [R4] \n"
"    CMN     R0, #1 \n"
"    BEQ     loc_FFA38E94 \n"
"    BL      fwt_close \n"  // --> Patched. Old value = _Close.
"    MVN     R0, #0 \n"
"    STR     R0, [R4] \n"
"    LDR     R0, =0xD0468 \n"
"    BL      sub_FF8536E8 \n"
"    BL      sub_FF851C74 \n"

"loc_FFA38E94:\n"
"    LDR     R0, [R4, #0xC] \n"
"    BL      _GiveSemaphore \n"
"    B       loc_FFA38DDC \n"

"loc_FFA38EA0:\n"
"    BL      sub_FFA39088_my \n"  // --> Patched. Old value = 0xFFA39088. Open stage
"    B       loc_FFA38DDC \n"

"loc_FFA38EA8:\n"
"    BL      sub_FFA391D4_my \n"  // --> Patched. Old value = 0xFFA391D4. Write stage
"    B       loc_FFA38DDC \n"

"loc_FFA38EB0:\n"
"    BL      sub_FFA392D0_my \n"  // --> Patched. Old value = 0xFFA392D0. Close stage
"    B       loc_FFA38DDC \n"
);
}

/*************************************************************/
//** sub_FFA39088_my @ 0xFFA39088 - 0xFFA390C8, length=17
void __attribute__((naked,noinline)) sub_FFA39088_my() {
asm volatile (
"    STMFD   SP!, {R4-R8,LR} \n"
"    MOV     R4, R0 \n"
"    ADD     R0, R0, #0x2C \n"
"    SUB     SP, SP, #0x38 \n"
"    BL      sub_FF8536E8 \n"
"    MOV     R1, #0 \n"
"    BL      sub_FF851C24 \n"
"    LDR     R0, [R4, #0xC] \n"
"    BL      sub_FF8500CC \n"
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
"    LDR     PC, =0xFFA390CC \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FFA391D4_my @ 0xFFA391D4 - 0xFFA392CC, length=63
void __attribute__((naked,noinline)) sub_FFA391D4_my() {
asm volatile (
"    STMFD   SP!, {R4-R10,LR} \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R0] \n"
"    CMP     R0, #4 \n"
"    LDREQ   R6, [R4, #0x18] \n"
"    LDREQ   R7, [R4, #0x14] \n"
"    BEQ     loc_FFA39210 \n"
"    CMP     R0, #5 \n"
"    LDREQ   R6, [R4, #0x20] \n"
"    LDREQ   R7, [R4, #0x1C] \n"
"    BEQ     loc_FFA39210 \n"
"    CMP     R0, #6 \n"
"    BNE     loc_FFA39224 \n"
"    LDR     R6, [R4, #0x28] \n"
"    LDR     R7, [R4, #0x24] \n"

"loc_FFA39210:\n"
"    CMP     R6, #0 \n"
"    BNE     loc_FFA39234 \n"

"loc_FFA39218:\n"
"    MOV     R1, R4 \n"
"    MOV     R0, #7 \n"
"    B       loc_FFA392C8 \n"

"loc_FFA39224:\n"
"    LDR     R1, =0x20D \n"
"    LDR     R0, =0xFFA391B4 /*'dwFWrite.c'*/ \n"
"    BL      _DebugAssert \n"
"    B       loc_FFA39218 \n"

"loc_FFA39234:\n"
"    LDR     R9, =0x9824 \n"
"    MOV     R5, R6 \n"

"loc_FFA3923C:\n"
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
"    BEQ     loc_FFA3929C \n"
"    LDR     R0, =0x10B1 \n"
"    BL      sub_FF876C60 /*_IsControlEventActive_FW*/ \n"
"    LDR     R1, =0x9200005 \n"
"    STR     R1, [R4, #0x10] \n"
"    B       loc_FFA39218 \n"

"loc_FFA3929C:\n"
"    SUB     R5, R5, R0 \n"
"    CMP     R5, R6 \n"
"    ADD     R7, R7, R0 \n"
"    LDRCS   R0, =0xFFA391B4 /*'dwFWrite.c'*/ \n"
"    MOVCS   R1, #0x23C \n"
"    BLCS    _DebugAssert \n"
"    CMP     R5, #0 \n"
"    BNE     loc_FFA3923C \n"
"    LDR     R0, [R4] \n"
"    MOV     R1, R4 \n"
"    ADD     R0, R0, #1 \n"

"loc_FFA392C8:\n"
"    LDMFD   SP!, {R4-R10,LR} \n"
"    B       sub_FFA38D2C \n"
);
}

/*************************************************************/
//** sub_FFA392D0_my @ 0xFFA392D0 - 0xFFA392EC, length=8
void __attribute__((naked,noinline)) sub_FFA392D0_my() {
asm volatile (
"    STMFD   SP!, {R4,R5,LR} \n"
"    LDR     R5, =0x9824 \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R5] \n"
"    SUB     SP, SP, #0x1C \n"
"    CMN     R0, #1 \n"
"    BEQ     sub_FFA39304 \n"
"    BL      fwt_close \n"  // --> Patched. Old value = _Close.
"    LDR     PC, =0xFFA392F0 \n"  // Continue in firmware
);
}
