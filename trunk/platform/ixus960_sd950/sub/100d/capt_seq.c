/*
 * capt_seq.c - auto-generated by CHDK code_gen.
 */
#include "lolevel.h"
#include "platform.h"
#include "core.h"

#define USE_STUBS_NRFLAG 1          // see stubs_entry.S

#include "../../../generic/capt_seq.c"

/*************************************************************/
//** capt_seq_task @ 0xFF85C038 - 0xFF85C2A0, length=155
void __attribute__((naked,noinline)) capt_seq_task() {
asm volatile (
"    STMFD   SP!, {R3-R9,LR} \n"
"    LDR     R6, =0x1DAF4 \n"
"    LDR     R5, =0x5648 \n"
"    MOV     R9, #1 \n"
"    MOV     R7, #0 \n"

"loc_FF85C04C:\n"
"    LDR     R0, [R5, #0xC] \n"
"    MOV     R2, #0 \n"
"    MOV     R1, SP \n"
"    BL      sub_FF8290D8 /*_ReceiveMessageQueue*/ \n"
"    TST     R0, #1 \n"
"    BEQ     loc_FF85C078 \n"
"    LDR     R1, =0x43F \n"
"    LDR     R0, =0xFF85BDD0 /*'SsShootTask.c'*/ \n"
"    BL      _DebugAssert \n"
"    BL      _ExitTask \n"
"    LDMFD   SP!, {R3-R9,PC} \n"

"loc_FF85C078:\n"
"    LDR     R0, [SP] \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #0x17 \n"
"    ADDLS   PC, PC, R1, LSL#2 \n"
"    B       loc_FF85C268 \n"
"    B       loc_FF85C0EC \n"
"    B       loc_FF85C154 \n"
"    B       loc_FF85C15C \n"
"    B       loc_FF85C174 \n"
"    B       loc_FF85C168 \n"
"    B       loc_FF85C17C \n"
"    B       loc_FF85C184 \n"
"    B       loc_FF85C18C \n"
"    B       loc_FF85C1E4 \n"
"    B       loc_FF85C1F0 \n"
"    B       loc_FF85C1F8 \n"
"    B       loc_FF85C200 \n"
"    B       loc_FF85C208 \n"
"    B       loc_FF85C210 \n"
"    B       loc_FF85C218 \n"
"    B       loc_FF85C220 \n"
"    B       loc_FF85C228 \n"
"    B       loc_FF85C234 \n"
"    B       loc_FF85C23C \n"
"    B       loc_FF85C244 \n"
"    B       loc_FF85C24C \n"
"    B       loc_FF85C258 \n"
"    B       loc_FF85C260 \n"
"    B       loc_FF85C274 \n"

"loc_FF85C0EC:\n"
"    BL      sub_FF9325D8 \n"

// only do quick press hack if overrides are active
"    BL      captseq_hack_override_active\n" // returns 1 if tv or sv override in effect
"    STR     R0,[SP,#-4]!\n" // push return value
"    BL      shooting_expo_param_override\n"      // added

"    BL      sub_FF85A2BC \n"

"    LDR     R0, [SP], #4\n" // pop override hack
"    CMP     R0, #1\n"     // +
"    MOVEQ   R0, #0\n"     // +
"    STREQ   R0, [R6, #0x24]\n"  // fixes overrides behavior at short shutter press
"    LDRNE   R0, [R6, #0x24]\n" // modified NE
"    CMPNE   R0, #0\n"         // modified NE

//"  LDR     R0, [R6, #0x24] \n"  // above patch makes these lines redundant
//"  CMP     R0, #0 \n"
"    BEQ     loc_FF85C274 \n"
"    BL      sub_FF85BA9C \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R6, #0x24] \n"
"    CMP     R0, #0 \n"
"    BEQ     loc_FF85C134 \n"
"    MOV     R0, #0xC \n"
"    BL      sub_FF85F170 \n"
"    TST     R0, #1 \n"
"    STRNE   R9, [R5, #4] \n"
"    LDRNE   R0, [R4, #8] \n"
"    ORRNE   R0, R0, #0x40000000 \n"
"    STRNE   R0, [R4, #8] \n"
"    BNE     loc_FF85C274 \n"

"loc_FF85C134:\n"
"    BL      sub_FF9471B8 \n"
"    BL      sub_FF869984 \n"
"    STR     R0, [R4, #0x14] \n"
"    MOV     R0, R4 \n"
"    BL      sub_FF933C30_my \n"  // --> Patched. Old value = 0xFF933C30.
"    TST     R0, #1 \n"
"    STRNE   R9, [R5, #4] \n"
"    B       loc_FF85C274 \n"

"loc_FF85C154:\n"
"    BL      sub_FF85C37C_my \n"  // --> Patched. Old value = 0xFF85C37C.
"    B       loc_FF85C16C \n"

"loc_FF85C15C:\n"
"    MOV     R0, #1 \n"
"    BL      sub_FF93277C \n"
"    B       loc_FF85C274 \n"

"loc_FF85C168:\n"
"    BL      sub_FF932274 \n"

"loc_FF85C16C:\n"
"    STR     R7, [R6, #0x24] \n"
"    B       loc_FF85C274 \n"

"loc_FF85C174:\n"
"    BL      sub_FF9325A4 \n"
"    B       loc_FF85C16C \n"

"loc_FF85C17C:\n"
"    BL      sub_FF9325AC \n"
"    B       loc_FF85C274 \n"

"loc_FF85C184:\n"
"    BL      sub_FF93269C \n"
"    B       loc_FF85C1E8 \n"

"loc_FF85C18C:\n"
"    LDR     R4, [R0, #0xC] \n"
"    BL      sub_FF9325B4 \n"
"    MOV     R0, R4 \n"
"    BL      sub_FF932DC8 \n"
"    TST     R0, #1 \n"
"    MOV     R8, R0 \n"
"    BNE     loc_FF85C1CC \n"
"    BL      sub_FF869984 \n"
"    STR     R0, [R4, #0x14] \n"
"    MOV     R0, R4 \n"
"    BL      sub_FF933B48 \n"
"    MOV     R0, R4 \n"
"    BL      sub_FF934098 \n"
"    MOV     R8, R0 \n"
"    LDR     R0, [R4, #0x14] \n"
"    BL      sub_FF869B98 \n"

"loc_FF85C1CC:\n"
"    BL      sub_FF9325A4 \n"
"    MOV     R2, R4 \n"
"    MOV     R1, #8 \n"
"    MOV     R0, R8 \n"
"    BL      sub_FF85A868 \n"
"    B       loc_FF85C274 \n"

"loc_FF85C1E4:\n"
"    BL      sub_FF9326F8 \n"

"loc_FF85C1E8:\n"
"    BL      sub_FF85A2BC \n"
"    B       loc_FF85C274 \n"

"loc_FF85C1F0:\n"
"    BL      sub_FF9325A4 \n"
"    B       loc_FF85C274 \n"

"loc_FF85C1F8:\n"
"    BL      sub_FF933034 \n"
"    B       loc_FF85C274 \n"

"loc_FF85C200:\n"
"    BL      sub_FF9331EC \n"
"    B       loc_FF85C274 \n"

"loc_FF85C208:\n"
"    BL      sub_FF93327C \n"
"    B       loc_FF85C274 \n"

"loc_FF85C210:\n"
"    BL      sub_FF933330 \n"
"    B       loc_FF85C274 \n"

"loc_FF85C218:\n"
"    BL      sub_FF933518 \n"
"    B       loc_FF85C274 \n"

"loc_FF85C220:\n"
"    BL      sub_FF933568 \n"
"    B       loc_FF85C274 \n"

"loc_FF85C228:\n"
"    MOV     R0, #0 \n"
"    BL      sub_FF9335EC \n"
"    B       loc_FF85C274 \n"

"loc_FF85C234:\n"
"    BL      sub_FF93372C \n"
"    B       loc_FF85C274 \n"

"loc_FF85C23C:\n"
"    BL      sub_FF9337C0 \n"
"    B       loc_FF85C274 \n"

"loc_FF85C244:\n"
"    BL      sub_FF933880 \n"
"    B       loc_FF85C274 \n"

"loc_FF85C24C:\n"
"    BL      sub_FF9328A0 \n"
"    BL      sub_FF825B44 \n"
"    B       loc_FF85C274 \n"

"loc_FF85C258:\n"
"    BL      sub_FF9333EC \n"
"    B       loc_FF85C274 \n"

"loc_FF85C260:\n"
"    BL      sub_FF933458 \n"
"    B       loc_FF85C274 \n"

"loc_FF85C268:\n"
"    LDR     R1, =0x523 \n"
"    LDR     R0, =0xFF85BDD0 /*'SsShootTask.c'*/ \n"
"    BL      _DebugAssert \n"

"loc_FF85C274:\n"
"    LDR     R0, [SP] \n"
"    LDR     R1, [R0, #4] \n"
"    LDR     R0, [R5, #8] \n"
"    BL      sub_FF828E54 /*_SetEventFlag*/ \n"
"    LDR     R4, [SP] \n"
"    LDR     R0, [R4, #8] \n"
"    CMP     R0, #0 \n"
"    LDREQ   R0, =0xFF85BDD0 /*'SsShootTask.c'*/ \n"
"    MOVEQ   R1, #0xFC \n"
"    BLEQ    _DebugAssert \n"
"    STR     R7, [R4, #8] \n"
"    B       loc_FF85C04C \n"
);
}

/*************************************************************/
//** sub_FF933C30_my @ 0xFF933C30 - 0xFF933CA0, length=29
void __attribute__((naked,noinline)) sub_FF933C30_my() {
asm volatile (
"    STMFD   SP!, {R0-R10,LR} \n"
"    MOV     R6, #0 \n"
"    MOV     R4, R0 \n"
"    BL      sub_FF93475C \n"
"    MVN     R1, #0 \n"
"    BL      sub_FF828E88 /*_ClearEventFlag*/ \n"
"    MOV     R2, #4 \n"
"    ADD     R1, SP, #8 \n"
"    MOV     R0, #0x8A \n"
"    BL      _GetPropertyCase \n"
"    TST     R0, #1 \n"
"    LDRNE   R1, =0x20A \n"
"    LDRNE   R0, =0xFF933E04 /*'SsCaptureSeq.c'*/ \n"
"    BLNE    _DebugAssert \n"
"    LDR     R8, =0x1DBA8 \n"
"    LDR     R5, =0x1DAF4 \n"
"    LDRSH   R1, [R8, #0xE] \n"
"    LDR     R0, [R5, #0x7C] \n"
"    BL      sub_FF9E2458 \n"
"    BL      _GetCCDTemperature \n"
"    LDR     R2, =0xE220 \n"
"    ADD     R3, R4, #0x8C \n"
"    STRH    R0, [R4, #0x88] \n"
"    STRD    R2, [SP] \n"
"    MOV     R1, R0 \n"
"    LDRH    R0, [R5, #0x54] \n"
"    LDRSH   R2, [R8, #0xC] \n"
"    LDR     R3, =0xE21C \n"
"    BL      sub_FF934C50 \n"
"    BL      wait_until_remote_button_is_released\n" // added
"    BL      capt_seq_hook_set_nr\n"                 // added
"    LDR     PC, =0xFF933CA4 \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FF85C37C_my @ 0xFF85C37C - 0xFF85C430, length=46
void __attribute__((naked,noinline)) sub_FF85C37C_my() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    LDR     R4, [R0, #0xC] \n"
"    LDR     R6, =0x1DAF4 \n"
"    LDR     R0, [R4, #8] \n"
"    MOV     R5, #0 \n"
"    ORR     R0, R0, #1 \n"
"    STR     R0, [R4, #8] \n"
"    LDR     R0, [R6, #0x24] \n"
"    CMP     R0, #0 \n"
"    MOVEQ   R0, #2 \n"
"    BLEQ    sub_FF8569D8 \n"
"    BL      sub_FF9325B4 \n"
"    LDR     R0, [R6, #0x24] \n"
"    CMP     R0, #0 \n"
"    BNE     loc_FF85C3FC \n"
"    MOV     R0, R4 \n"
"    BL      sub_FF932A48 \n"
"    TST     R0, #1 \n"
"    MOVNE   R2, R4 \n"
"    LDMNEFD SP!, {R4-R6,LR} \n"
"    MOVNE   R1, #1 \n"
"    BNE     sub_FF85A868 \n"
"    BL      sub_FF9471B8 \n"
"    BL      sub_FF869984 \n"
"    STR     R0, [R4, #0x14] \n"
"    MOV     R0, R4 \n"
"    BL      sub_FF933B48 \n"
"    BL      sub_FF9345F0 \n"
"    MOV     R0, R4 \n"
"    BL      sub_FF933C30_my \n"  // --> Patched. Old value = 0xFF933C30.
"    MOV     R5, R0 \n"
"    B       loc_FF85C40C \n"

"loc_FF85C3FC:\n"
"    LDR     R0, =0x5648 \n"
"    LDR     R0, [R0, #4] \n"
"    CMP     R0, #0 \n"
"    MOVNE   R5, #0x1D \n"

"loc_FF85C40C:\n"
"    BL      capt_seq_hook_raw_here \n"         // added
"    MOV     R2, R4 \n"
"    MOV     R1, #1 \n"
"    MOV     R0, R5 \n"
"    BL      sub_FF85A868 \n"
"    BL      sub_FF934038 \n"
"    CMP     R0, #0 \n"
"    LDRNE   R0, [R4, #8] \n"
"    ORRNE   R0, R0, #0x2000 \n"
"    STRNE   R0, [R4, #8] \n"
"    LDMFD   SP!, {R4-R6,PC} \n"
);
}

/*************************************************************/
//** exp_drv_task @ 0xFF8AF7B0 - 0xFF8AFE08, length=407
void __attribute__((naked,noinline)) exp_drv_task() {
asm volatile (
"    STMFD   SP!, {R4-R8,LR} \n"
"    SUB     SP, SP, #0x20 \n"
"    LDR     R8, =0xBB8 \n"
"    LDR     R7, =0x6E88 \n"
"    LDR     R5, =0x457AC \n"
"    MOV     R0, #0 \n"
"    ADD     R6, SP, #0x10 \n"
"    STR     R0, [SP, #0xC] \n"

"loc_FF8AF7D0:\n"
"    LDR     R0, [R7, #0x20] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #0x1C \n"
"    BL      sub_FF8290D8 /*_ReceiveMessageQueue*/ \n"
"    LDR     R0, [SP, #0xC] \n"
"    CMP     R0, #1 \n"
"    BNE     loc_FF8AF818 \n"
"    LDR     R0, [SP, #0x1C] \n"
"    LDR     R0, [R0] \n"
"    CMP     R0, #0x13 \n"
"    CMPNE   R0, #0x14 \n"
"    CMPNE   R0, #0x15 \n"
"    BEQ     loc_FF8AF998 \n"
"    CMP     R0, #0x26 \n"
"    BEQ     loc_FF8AF904 \n"
"    ADD     R1, SP, #0xC \n"
"    MOV     R0, #0 \n"
"    BL      sub_FF8AF760 \n"

"loc_FF8AF818:\n"
"    LDR     R0, [SP, #0x1C] \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #0x2B \n"
"    BNE     loc_FF8AF848 \n"
"    LDR     R0, [SP, #0x1C] \n"
"    BL      sub_FF8B0A98 \n"
"    LDR     R0, [R7, #0x1C] \n"
"    MOV     R1, #1 \n"
"    BL      sub_FF828E54 /*_SetEventFlag*/ \n"
"    BL      _ExitTask \n"
"    ADD     SP, SP, #0x20 \n"
"    LDMFD   SP!, {R4-R8,PC} \n"

"loc_FF8AF848:\n"
"    CMP     R1, #0x2A \n"
"    BNE     loc_FF8AF864 \n"
"    LDR     R2, [R0, #0x88]! \n"
"    LDR     R1, [R0, #4] \n"
"    MOV     R0, R1 \n"
"    BLX     R2 \n"
"    B       loc_FF8AFE00 \n"

"loc_FF8AF864:\n"
"    CMP     R1, #0x24 \n"
"    BNE     loc_FF8AF8B4 \n"
"    LDR     R0, [R7, #0x1C] \n"
"    MOV     R1, #0x80 \n"
"    BL      sub_FF828E88 /*_ClearEventFlag*/ \n"
"    LDR     R0, =0xFF8AC214 \n"
"    MOV     R1, #0x80 \n"
"    BL      sub_FF9272C0 \n"
"    LDR     R0, [R7, #0x1C] \n"
"    MOV     R2, R8 \n"
"    MOV     R1, #0x80 \n"
"    BL      sub_FF828D8C /*_WaitForAllEventFlag*/ \n"
"    TST     R0, #1 \n"
"    LDRNE   R1, =0xD07 \n"
"    BNE     loc_FF8AF974 \n"

"loc_FF8AF8A0:\n"
"    LDR     R1, [SP, #0x1C] \n"
"    LDR     R0, [R1, #0x8C] \n"
"    LDR     R1, [R1, #0x88] \n"
"    BLX     R1 \n"
"    B       loc_FF8AFE00 \n"

"loc_FF8AF8B4:\n"
"    CMP     R1, #0x25 \n"
"    BNE     loc_FF8AF8FC \n"
"    ADD     R1, SP, #0xC \n"
"    BL      sub_FF8AF760 \n"
"    LDR     R0, [R7, #0x1C] \n"
"    MOV     R1, #0x100 \n"
"    BL      sub_FF828E88 /*_ClearEventFlag*/ \n"
"    LDR     R0, =0xFF8AC224 \n"
"    MOV     R1, #0x100 \n"
"    BL      sub_FF927548 \n"
"    LDR     R0, [R7, #0x1C] \n"
"    MOV     R2, R8 \n"
"    MOV     R1, #0x100 \n"
"    BL      sub_FF828D8C /*_WaitForAllEventFlag*/ \n"
"    TST     R0, #1 \n"
"    BEQ     loc_FF8AF8A0 \n"
"    LDR     R1, =0xD11 \n"
"    B       loc_FF8AF974 \n"

"loc_FF8AF8FC:\n"
"    CMP     R1, #0x26 \n"
"    BNE     loc_FF8AF914 \n"

"loc_FF8AF904:\n"
"    LDR     R0, [SP, #0x1C] \n"
"    ADD     R1, SP, #0xC \n"
"    BL      sub_FF8AF760 \n"
"    B       loc_FF8AF8A0 \n"

"loc_FF8AF914:\n"
"    CMP     R1, #0x27 \n"
"    CMPNE   R1, #0x28 \n"
"    BNE     loc_FF8AF980 \n"
"    ADD     R1, SP, #0xC \n"
"    BL      sub_FF8AF760 \n"
"    LDR     R4, [SP, #0x1C] \n"
"    LDR     R0, [R7, #0x1C] \n"
"    MOV     R1, #0x40 \n"
"    BL      sub_FF828E88 /*_ClearEventFlag*/ \n"
"    LDR     R0, [R4] \n"
"    MOV     R1, #0x40 \n"
"    CMP     R0, #0x27 \n"
"    LDR     R0, =0xFF8AC288 \n"
"    BNE     loc_FF8AF954 \n"
"    BL      sub_FF92731C \n"
"    B       loc_FF8AF958 \n"

"loc_FF8AF954:\n"
"    BL      sub_FF927384 \n"

"loc_FF8AF958:\n"
"    LDR     R0, [R7, #0x1C] \n"
"    MOV     R2, R8 \n"
"    MOV     R1, #0x40 \n"
"    BL      sub_FF828D8C /*_WaitForAllEventFlag*/ \n"
"    TST     R0, #1 \n"
"    BEQ     loc_FF8AF8A0 \n"
"    LDR     R1, =0xD1F \n"

"loc_FF8AF974:\n"
"    LDR     R0, =0xFF8AC924 /*'ExpDrv.c'*/ \n"
"    BL      _DebugAssert \n"
"    B       loc_FF8AF8A0 \n"

"loc_FF8AF980:\n"
"    CMP     R1, #0x29 \n"
"    BNE     loc_FF8AF998 \n"
"    BL      sub_FF891760 \n"
"    BL      sub_FF8924E0 \n"
"    BL      sub_FF891FA0 \n"
"    B       loc_FF8AF8A0 \n"

"loc_FF8AF998:\n"
"    LDR     R0, [SP, #0x1C] \n"
"    MOV     R4, #1 \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #0x11 \n"
"    CMPNE   R1, #0x12 \n"
"    BNE     loc_FF8AFA08 \n"
"    LDR     R1, [R0, #0x7C] \n"
"    ADD     R1, R1, R1, LSL#1 \n"
"    ADD     R1, R0, R1, LSL#2 \n"
"    SUB     R1, R1, #8 \n"
"    LDMIA   R1, {R2-R4} \n"
"    STMIA   R6, {R2-R4} \n"
"    BL      sub_FF8AE27C \n"
"    LDR     R0, [SP, #0x1C] \n"
"    LDR     R1, [R0, #0x7C] \n"
"    LDR     R3, [R0, #0x88] \n"
"    LDR     R2, [R0, #0x8C] \n"
"    ADD     R0, R0, #4 \n"
"    BLX     R3 \n"
"    LDR     R0, [SP, #0x1C] \n"
"    BL      sub_FF8B0E6C \n"
"    LDR     R0, [SP, #0x1C] \n"
"    LDR     R1, [R0, #0x7C] \n"
"    LDR     R3, [R0, #0x90] \n"
"    LDR     R2, [R0, #0x94] \n"
"    ADD     R0, R0, #4 \n"
"    BLX     R3 \n"
"    B       loc_FF8AFD40 \n"

"loc_FF8AFA08:\n"
"    CMP     R1, #0x13 \n"
"    CMPNE   R1, #0x14 \n"
"    CMPNE   R1, #0x15 \n"
"    BNE     loc_FF8AFABC \n"
"    ADD     R3, SP, #0xC \n"
"    MOV     R2, SP \n"
"    ADD     R1, SP, #0x10 \n"
"    BL      sub_FF8AE4C4 \n"
"    CMP     R0, #1 \n"
"    MOV     R4, R0 \n"
"    CMPNE   R4, #5 \n"
"    BNE     loc_FF8AFA58 \n"
"    LDR     R0, [SP, #0x1C] \n"
"    MOV     R2, R4 \n"
"    LDR     R1, [R0, #0x7C]! \n"
"    LDR     R12, [R0, #0xC]! \n"
"    LDR     R3, [R0, #4] \n"
"    MOV     R0, SP \n"
"    BLX     R12 \n"
"    B       loc_FF8AFA90 \n"

"loc_FF8AFA58:\n"
"    LDR     R0, [SP, #0x1C] \n"
"    CMP     R4, #2 \n"
"    LDR     R3, [R0, #0x8C] \n"
"    CMPNE   R4, #6 \n"
"    BNE     loc_FF8AFAA4 \n"
"    LDR     R12, [R0, #0x88] \n"
"    MOV     R0, SP \n"
"    MOV     R2, R4 \n"
"    MOV     R1, #1 \n"
"    BLX     R12 \n"
"    LDR     R0, [SP, #0x1C] \n"
"    MOV     R2, SP \n"
"    ADD     R1, SP, #0x10 \n"
"    BL      sub_FF8AF474 \n"

"loc_FF8AFA90:\n"
"    LDR     R0, [SP, #0x1C] \n"
"    LDR     R2, [SP, #0xC] \n"
"    MOV     R1, R4 \n"
"    BL      sub_FF8AF700 \n"
"    B       loc_FF8AFD40 \n"

"loc_FF8AFAA4:\n"
"    LDR     R1, [R0, #0x7C] \n"
"    LDR     R12, [R0, #0x88] \n"
"    ADD     R0, R0, #4 \n"
"    MOV     R2, R4 \n"
"    BLX     R12 \n"
"    B       loc_FF8AFD40 \n"

"loc_FF8AFABC:\n"
"    CMP     R1, #0x20 \n"
"    CMPNE   R1, #0x21 \n"
"    BNE     loc_FF8AFB08 \n"
"    LDR     R1, [R0, #0x7C] \n"
"    ADD     R1, R1, R1, LSL#1 \n"
"    ADD     R1, R0, R1, LSL#2 \n"
"    SUB     R1, R1, #8 \n"
"    LDMIA   R1, {R2-R4} \n"
"    STMIA   R6, {R2-R4} \n"
"    BL      sub_FF8AD80C \n"
"    LDR     R0, [SP, #0x1C] \n"
"    LDR     R1, [R0, #0x7C] \n"
"    LDR     R3, [R0, #0x88] \n"
"    LDR     R2, [R0, #0x8C] \n"
"    ADD     R0, R0, #4 \n"
"    BLX     R3 \n"
"    LDR     R0, [SP, #0x1C] \n"
"    BL      sub_FF8ADAFC \n"
"    B       loc_FF8AFD40 \n"

"loc_FF8AFB08:\n"
"    ADD     R1, R0, #4 \n"
"    LDMIA   R1, {R2,R3,R12} \n"
"    STMIA   R6, {R2,R3,R12} \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #0x23 \n"
"    ADDLS   PC, PC, R1, LSL#2 \n"
"    B       loc_FF8AFD20 \n"
"    B       loc_FF8AFBB4 \n"
"    B       loc_FF8AFBB4 \n"
"    B       loc_FF8AFC08 \n"
"    B       loc_FF8AFC10 \n"
"    B       loc_FF8AFC10 \n"
"    B       loc_FF8AFC10 \n"
"    B       loc_FF8AFBB4 \n"
"    B       loc_FF8AFC08 \n"
"    B       loc_FF8AFC10 \n"
"    B       loc_FF8AFC10 \n"
"    B       loc_FF8AFC28 \n"
"    B       loc_FF8AFC28 \n"
"    B       loc_FF8AFD14 \n"
"    B       loc_FF8AFD1C \n"
"    B       loc_FF8AFD1C \n"
"    B       loc_FF8AFD1C \n"
"    B       loc_FF8AFD1C \n"
"    B       loc_FF8AFD20 \n"
"    B       loc_FF8AFD20 \n"
"    B       loc_FF8AFD20 \n"
"    B       loc_FF8AFD20 \n"
"    B       loc_FF8AFD20 \n"
"    B       loc_FF8AFC18 \n"
"    B       loc_FF8AFC20 \n"
"    B       loc_FF8AFC20 \n"
"    B       loc_FF8AFC34 \n"
"    B       loc_FF8AFC3C \n"
"    B       loc_FF8AFC6C \n"
"    B       loc_FF8AFC9C \n"
"    B       loc_FF8AFCCC \n"
"    B       loc_FF8AFCFC \n"
"    B       loc_FF8AFCFC \n"
"    B       loc_FF8AFD20 \n"
"    B       loc_FF8AFD20 \n"
"    B       loc_FF8AFD04 \n"
"    B       loc_FF8AFD0C \n"

"loc_FF8AFBB4:\n"
"    BL      sub_FF8AC70C \n"
"    B       loc_FF8AFD20 \n"
//SKIP DATA

"loc_FF8AFC08:\n"
"    BL      sub_FF8AC994 \n"
"    B       loc_FF8AFD20 \n"

"loc_FF8AFC10:\n"
"    BL      sub_FF8ACB98 \n"
"    B       loc_FF8AFD20 \n"

"loc_FF8AFC18:\n"
"    BL      sub_FF8ACE00 \n"
"    B       loc_FF8AFD20 \n"

"loc_FF8AFC20:\n"
"    BL      sub_FF8ACFF4 \n"
"    B       loc_FF8AFD20 \n"

"loc_FF8AFC28:\n"
"    BL      sub_FF8AD258_my \n"  // --> Patched. Old value = 0xFF8AD258.
"    MOV     R4, #0 \n"
"    B       loc_FF8AFD20 \n"

"loc_FF8AFC34:\n"
"    BL      sub_FF8AD394 \n"
"    B       loc_FF8AFD20 \n"

"loc_FF8AFC3C:\n"
"    LDRH    R1, [R0, #4] \n"
"    STRH    R1, [SP, #0x10] \n"
"    LDRH    R1, [R5, #2] \n"
"    STRH    R1, [SP, #0x12] \n"
"    LDRH    R1, [R5, #4] \n"
"    STRH    R1, [SP, #0x14] \n"
"    LDRH    R1, [R5, #6] \n"
"    STRH    R1, [SP, #0x16] \n"
"    LDRH    R1, [R0, #0xC] \n"
"    STRH    R1, [SP, #0x18] \n"
"    BL      sub_FF8B0B0C \n"
"    B       loc_FF8AFD20 \n"

"loc_FF8AFC6C:\n"
"    LDRH    R1, [R0, #4] \n"
"    STRH    R1, [SP, #0x10] \n"
"    LDRH    R1, [R5, #2] \n"
"    STRH    R1, [SP, #0x12] \n"
"    LDRH    R1, [R5, #4] \n"
"    STRH    R1, [SP, #0x14] \n"
"    LDRH    R1, [R5, #6] \n"
"    STRH    R1, [SP, #0x16] \n"
"    LDRH    R1, [R5, #8] \n"
"    STRH    R1, [SP, #0x18] \n"
"    BL      sub_FF8B0C88 \n"
"    B       loc_FF8AFD20 \n"

"loc_FF8AFC9C:\n"
"    LDRH    R1, [R5] \n"
"    STRH    R1, [SP, #0x10] \n"
"    LDRH    R1, [R0, #6] \n"
"    STRH    R1, [SP, #0x12] \n"
"    LDRH    R1, [R5, #4] \n"
"    STRH    R1, [SP, #0x14] \n"
"    LDRH    R1, [R5, #6] \n"
"    STRH    R1, [SP, #0x16] \n"
"    LDRH    R1, [R5, #8] \n"
"    STRH    R1, [SP, #0x18] \n"
"    BL      sub_FF8B0D34 \n"
"    B       loc_FF8AFD20 \n"

"loc_FF8AFCCC:\n"
"    LDRH    R1, [R5] \n"
"    STRH    R1, [SP, #0x10] \n"
"    LDRH    R1, [R5, #2] \n"
"    STRH    R1, [SP, #0x12] \n"
"    LDRH    R1, [R5, #4] \n"
"    STRH    R1, [SP, #0x14] \n"
"    LDRH    R1, [R5, #6] \n"
"    STRH    R1, [SP, #0x16] \n"
"    LDRH    R1, [R0, #0xC] \n"
"    STRH    R1, [SP, #0x18] \n"
"    BL      sub_FF8B0DD4 \n"
"    B       loc_FF8AFD20 \n"

"loc_FF8AFCFC:\n"
"    BL      sub_FF8AD5EC \n"
"    B       loc_FF8AFD20 \n"

"loc_FF8AFD04:\n"
"    BL      sub_FF8ADC00 \n"
"    B       loc_FF8AFD20 \n"

"loc_FF8AFD0C:\n"
"    BL      sub_FF8ADE34 \n"
"    B       loc_FF8AFD20 \n"

"loc_FF8AFD14:\n"
"    BL      sub_FF8ADFAC \n"
"    B       loc_FF8AFD20 \n"

"loc_FF8AFD1C:\n"
"    BL      sub_FF8AE144 \n"

"loc_FF8AFD20:\n"
"    LDR     R0, [SP, #0x1C] \n"
"    LDR     R1, [R0, #0x7C] \n"
"    LDR     R3, [R0, #0x88] \n"
"    LDR     R2, [R0, #0x8C] \n"
"    ADD     R0, R0, #4 \n"
"    BLX     R3 \n"
"    CMP     R4, #1 \n"
"    BNE     loc_FF8AFD88 \n"

"loc_FF8AFD40:\n"
"    LDR     R0, [SP, #0x1C] \n"
"    MOV     R2, #0xC \n"
"    LDR     R1, [R0, #0x7C] \n"
"    ADD     R1, R1, R1, LSL#1 \n"
"    ADD     R0, R0, R1, LSL#2 \n"
"    SUB     R4, R0, #8 \n"
"    LDR     R0, =0x457AC \n"
"    ADD     R1, SP, #0x10 \n"
"    BL      sub_FFA919C0 \n"
"    LDR     R0, =0x457B8 \n"
"    MOV     R2, #0xC \n"
"    ADD     R1, SP, #0x10 \n"
"    BL      sub_FFA919C0 \n"
"    LDR     R0, =0x457C4 \n"
"    MOV     R2, #0xC \n"
"    MOV     R1, R4 \n"
"    BL      sub_FFA919C0 \n"
"    B       loc_FF8AFE00 \n"

"loc_FF8AFD88:\n"
"    LDR     R0, [SP, #0x1C] \n"
"    LDR     R0, [R0] \n"
"    CMP     R0, #0xB \n"
"    BNE     loc_FF8AFDD0 \n"
"    MOV     R3, #0 \n"
"    STR     R3, [SP] \n"
"    MOV     R3, #1 \n"
"    MOV     R2, #1 \n"
"    MOV     R1, #1 \n"
"    MOV     R0, #0 \n"
"    BL      sub_FF8AC514 \n"
"    MOV     R3, #0 \n"
"    STR     R3, [SP] \n"
"    MOV     R3, #1 \n"
"    MOV     R2, #1 \n"
"    MOV     R1, #1 \n"
"    MOV     R0, #0 \n"
"    B       loc_FF8AFDFC \n"

"loc_FF8AFDD0:\n"
"    MOV     R3, #1 \n"
"    MOV     R2, #1 \n"
"    MOV     R1, #1 \n"
"    MOV     R0, #1 \n"
"    STR     R3, [SP] \n"
"    BL      sub_FF8AC514 \n"
"    MOV     R3, #1 \n"
"    MOV     R2, #1 \n"
"    MOV     R1, #1 \n"
"    MOV     R0, #1 \n"
"    STR     R3, [SP] \n"

"loc_FF8AFDFC:\n"
"    BL      sub_FF8AC654 \n"

"loc_FF8AFE00:\n"
"    LDR     R0, [SP, #0x1C] \n"
"    BL      sub_FF8B0A98 \n"
"    B       loc_FF8AF7D0 \n"
);
}

/*************************************************************/
//** sub_FF8AD258_my @ 0xFF8AD258 - 0xFF8AD314, length=48
void __attribute__((naked,noinline)) sub_FF8AD258_my() {
asm volatile (
"    STMFD   SP!, {R4-R8,LR} \n"
"    LDR     R7, =0x6E88 \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R7, #0x1C] \n"
"    MOV     R1, #0x3E \n"
"    BL      sub_FF828E88 /*_ClearEventFlag*/ \n"
"    LDRSH   R0, [R4, #4] \n"
"    MOV     R2, #0 \n"
"    MOV     R1, #0 \n"
"    BL      sub_FF8AC2A8 \n"
"    MOV     R6, R0 \n"
"    LDRSH   R0, [R4, #6] \n"
"    BL      sub_FF8AC3B4 \n"
"    LDRSH   R0, [R4, #8] \n"
"    BL      sub_FF8AC40C \n"
"    LDRSH   R0, [R4, #0xA] \n"
"    BL      sub_FF8AC464 \n"
"    LDRSH   R0, [R4, #0xC] \n"
"    BL      sub_FF8AC4BC \n"
"    MOV     R5, R0 \n"
"    LDR     R0, [R4] \n"
"    LDR     R8, =0x457C4 \n"
"    CMP     R0, #0xB \n"
"    MOVEQ   R6, #0 \n"
"    MOVEQ   R5, #0 \n"
"    BEQ     loc_FF8AD2E8 \n"
"    CMP     R6, #1 \n"
"    BNE     loc_FF8AD2E8 \n"
"    LDRSH   R0, [R4, #4] \n"
"    LDR     R1, =0xFF8AC204 \n"
"    MOV     R2, #2 \n"
"    BL      sub_FF927414 \n"
"    STRH    R0, [R4, #4] \n"
"    MOV     R0, #0 \n"
"    STR     R0, [R7, #0x28] \n"
"    B       loc_FF8AD2F0 \n"

"loc_FF8AD2E8:\n"
"    LDRH    R0, [R8] \n"
"    STRH    R0, [R4, #4] \n"

"loc_FF8AD2F0:\n"
"    CMP     R5, #1 \n"
"    LDRNEH  R0, [R8, #8] \n"
"    BNE     loc_FF8AD30C \n"
"    LDRSH   R0, [R4, #0xC] \n"
"    LDR     R1, =0xFF8AC298 \n"
"    MOV     R2, #0x20 \n"
"    BL      sub_FF8B0AC8 \n"

"loc_FF8AD30C:\n"
"    STRH    R0, [R4, #0xC] \n"
"    LDRSH   R0, [R4, #6] \n"
"    BL      sub_FF891504_my \n"  // --> Patched. Old value = 0xFF891504.
"    LDR     PC, =0xFF8AD318 \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FF891504_my @ 0xFF891504 - 0xFF89156C, length=27
void __attribute__((naked,noinline)) sub_FF891504_my() {
asm volatile (
"    STMFD   SP!, {R4-R6,LR} \n"
"    LDR     R5, =0x6964 \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R5, #4] \n"
"    CMP     R0, #1 \n"
"    MOVNE   R1, #0x16C \n"
"    LDRNE   R0, =0xFF89129C /*'Shutter.c'*/ \n"
"    BLNE    _DebugAssert \n"
"    CMN     R4, #0xC00 \n"
"    LDREQSH R4, [R5, #2] \n"
"    CMN     R4, #0xC00 \n"
"    LDREQ   R1, =0x172 \n"
"    LDREQ   R0, =0xFF89129C /*'Shutter.c'*/ \n"
"    STRH    R4, [R5, #2] \n"
"    BLEQ    _DebugAssert \n"
"    MOV     R0, R4 \n"
"    BL      apex2us \n"  // --> Patched. Old value = _apex2us.
"    MOV     R4, R0 \n"
//"  BL      _sub_FF8BF7F4 \n"  // --> Nullsub call removed.
"    MOV     R0, R4 \n"
"    BL      sub_FF8C3398 \n"
"    TST     R0, #1 \n"
"    LDRNE   R1, =0x177 \n"
"    LDMNEFD SP!, {R4-R6,LR} \n"
"    LDRNE   R0, =0xFF89129C /*'Shutter.c'*/ \n"
"    BNE     _DebugAssert \n"
"    LDMFD   SP!, {R4-R6,PC} \n"
);
}