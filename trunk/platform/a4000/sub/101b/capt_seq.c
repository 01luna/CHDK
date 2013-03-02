#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "stdlib.h"

static long *nrflag = (long*)(0x8868+0x00);  // Found @ ff9e40b0 & ff9e40f8
#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

#define PAUSE_FOR_FILE_COUNTER 200           // Enable delay in capt_seq_hook_raw_here to ensure file counter is updated
#include "../../../generic/capt_seq.c"

//** capt_seq_task  @ 0xFF870DB0 

void __attribute__((naked,noinline)) capt_seq_task(  ) { 
asm volatile (
      "STMFD   SP!, {R3-R9,LR}\n"
      "LDR     R4, =0x36D9C\n"
      "LDR     R7, =0x2B64\n"
      "MOV     R6, #0\n"
"loc_FF870DC0:\n"
      "LDR     R0, [R7, #4]\n"
      "MOV     R2, #0\n"
      "MOV     R1, SP\n"
      "BL      sub_003F7218\n"
      "TST     R0, #1\n"
      "BEQ     loc_FF870DEC\n"
      "LDR     R1, =0x493\n"
      "LDR     R0, =0xFF87091C \n" // "SsShootTask.c"
      "BL      _DebugAssert \n"
      "BL      _ExitTask \n"
      "LDMFD   SP!, {R3-R9,PC}\n"
"loc_FF870DEC:\n"
      "LDR     R0, [SP]\n"
      "LDR     R1, [R0]\n"
      "CMP     R1, #0x20\n"
      "ADDCC   PC, PC, R1, LSL #2\n"
      "B       loc_FF871048\n"
      "B       loc_FF870E80\n"
      "B       loc_FF870E98\n"
      "B       loc_FF870EFC\n"
      "B       loc_FF870F10\n"
      "B       loc_FF870F08\n"
      "B       loc_FF870F1C\n"
      "B       loc_FF870F24\n"
      "B       loc_FF870F2C\n"
      "B       loc_FF870F48\n"
      "B       loc_FF870F74\n"
      "B       loc_FF870F54\n"
      "B       loc_FF870F60\n"
      "B       loc_FF870F68\n"
      "B       loc_FF870F7C\n"
      "B       loc_FF870F84\n"
      "B       loc_FF870F8C\n"
      "B       loc_FF870F94\n"
      "B       loc_FF870F9C\n"
      "B       loc_FF870FA8\n"
      "B       loc_FF870FB0\n"
      "B       loc_FF870FB8\n"
      "B       loc_FF870FC0\n"
      "B       loc_FF870FC8\n"
      "B       loc_FF870FD4\n"
      "B       loc_FF870FDC\n"
      "B       loc_FF870FE4\n"
      "B       loc_FF870FEC\n"
      "B       loc_FF870FF4\n"
      "B       loc_FF871000\n"
      "B       loc_FF871008\n"
      "B       loc_FF871014\n"
      "B       loc_FF871054\n"
"loc_FF870E80:\n"
      "    BL      shooting_expo_iso_override \n" // added
      "BL      sub_FF8715C8\n"
      "    BL      shooting_expo_param_override \n" // added
      "BL      sub_FF86EBBC\n"
//      "LDR     R0, [R4, #0x28]\n"
//      "CMP     R0, #0\n"
//      "BLNE    sub_FF9647C8\n" // above 3 lines removed - redundant with added lines below
      "    MOV     R0, #0 \n"         // patch added
      "    STR     R0, [R4,#0x28] \n" //fixes overrides behavior at short shutter press
      "B       loc_FF871054\n"
"loc_FF870E98:\n"
      "LDR     R5, [R0, #0x10]\n"
      "LDR     R0, [R4, #0x28]\n"
      "CMP     R0, #0\n"
      "BNE     loc_FF870ED4\n"
      "BL      sub_FF87249C\n"
      "MOV     R1, R5\n"
      "BL      sub_FF8724F4\n"
      "LDR     R0, =0x10F\n"
      "MOV     R2, #4\n"
      "ADD     R1, R5, #0x24\n"
      "BL      _SetPropertyCase \n"
      "MOV     R2, #4\n"
      "ADD     R1, R5, #0x28\n"
      "MOV     R0, #0x2C\n"
      "BL      _SetPropertyCase \n"
"loc_FF870ED4:\n"
      "MOV     R0, R5\n"
//      "BL      sub_FF96472C\n" //original
      "BL      sub_FF96472C_my\n" //patch
      "BL      capt_seq_hook_raw_here \n" // patch
      "MOV     R8, R0\n"
      "MOV     R2, R5\n"
      "MOV     R1, #1\n"
      "BL      sub_FF86F06C\n"
      "TST     R8, #1\n"
      "MOVEQ   R0, R5\n"
      "BLEQ    sub_FF9640A8\n"
      "B       loc_FF871054\n"
"loc_FF870EFC:\n"
      "MOV     R0, #1\n"
      "BL      sub_FF871898\n"
      "B       loc_FF871054\n"
"loc_FF870F08:\n"
      "BL      sub_FF87121C\n"
      "B       loc_FF870F14\n"
"loc_FF870F10:\n"
      "BL      sub_FF8715A8\n"
"loc_FF870F14:\n"
      "STR     R6, [R4, #0x28]\n"
      "B       loc_FF871054\n"
"loc_FF870F1C:\n"
      "BL      sub_FF8715B0\n"
      "B       loc_FF871054\n"
"loc_FF870F24:\n"
      "BL      sub_FF871780\n"
      "B       loc_FF870F4C\n"
"loc_FF870F2C:\n"
      "LDR     R5, [R0, #0x10]\n"
      "MOV     R0, R5\n"
      "BL      sub_FF964860\n"
      "MOV     R2, R5\n"
      "MOV     R1, #9\n"
      "BL      sub_FF86F06C\n"
      "B       loc_FF871054\n"
"loc_FF870F48:\n"
      "BL      sub_FF871800\n"
"loc_FF870F4C:\n"
      "BL      sub_FF86EBBC\n"
      "B       loc_FF871054\n"
"loc_FF870F54:\n"
      "LDR     R0, [R4, #0x58]\n"
      "BL      sub_FF871C88\n"
      "B       loc_FF871054\n"
"loc_FF870F60:\n"
      "BL      sub_FF872038\n"
      "B       loc_FF871054\n"
"loc_FF870F68:\n"
      "MOV     R0, #0\n"
      "BL      sub_FF87209C\n"
      "B       loc_FF871054\n"
"loc_FF870F74:\n"
      "BL      sub_FF8715A8\n"
      "B       loc_FF871054\n"
"loc_FF870F7C:\n"
      "BL      sub_FF963454\n"
      "B       loc_FF871054\n"
"loc_FF870F84:\n"
      "BL      sub_FF9636B4\n"
      "B       loc_FF871054\n"
"loc_FF870F8C:\n"
      "BL      sub_FF96376C\n"
      "B       loc_FF871054\n"
"loc_FF870F94:\n"
      "BL      sub_FF963840\n"
      "B       loc_FF871054\n"
"loc_FF870F9C:\n"
      "MOV     R0, #0\n"
      "BL      sub_FF963AA0\n"
      "B       loc_FF871054\n"
"loc_FF870FA8:\n"
      "BL      sub_FF963C10\n"
      "B       loc_FF871054\n"
"loc_FF870FB0:\n"
      "BL      sub_FF963CA4\n"
      "B       loc_FF871054\n"
"loc_FF870FB8:\n"
      "BL      sub_FF963D60\n"
      "B       loc_FF871054\n"
"loc_FF870FC0:\n"
      "BL      sub_FF871A0C\n"
      "B       loc_FF871054\n"
"loc_FF870FC8:\n"
      "BL      sub_FF871A90\n"
      "BL      sub_FF832298\n"
      "B       loc_FF871054\n"
"loc_FF870FD4:\n"
      "BL      sub_FF963910\n"
      "B       loc_FF871054\n"
"loc_FF870FDC:\n"
      "BL      sub_FF963950\n"
      "B       loc_FF871054\n"
"loc_FF870FE4:\n"
      "BL      sub_FF873944\n"
      "B       loc_FF871054\n"
"loc_FF870FEC:\n"
      "BL      sub_FF8739B8\n"
      "B       loc_FF871054\n"
"loc_FF870FF4:\n"
      "LDR     R0, [R0, #0xC]\n"
      "BL      sub_FF963E88\n"
      "B       loc_FF871054\n"
"loc_FF871000:\n"
      "BL      sub_FF963EF8\n"
      "B       loc_FF871054\n"
"loc_FF871008:\n"
      "BL      sub_FF873A20\n"
      "BL      sub_FF8739D8\n"
      "B       loc_FF871054\n"
"loc_FF871014:\n"
      "MOV     R0, #1\n"
      "BL      sub_FF964F60\n"
      "MOV     R0, #1\n"
      "BL      sub_FF965088\n"
      "LDRH    R0, [R4, #0x9C]\n"
      "CMP     R0, #4\n"
      "LDRNEH  R0, [R4]\n"
      "SUBNE   R1, R0, #0x8200\n"
      "SUBNES  R1, R1, #0x2E\n"
      "BNE     loc_FF871054\n"
      "BL      sub_FF8739B8\n"
      "BL      sub_FF873E7C\n"
      "B       loc_FF871054\n"
"loc_FF871048:\n"
      "LDR     R1, =0x5F4\n"
      "LDR     R0, =0xFF87091C \n" // "SsShootTask.c"
      "BL      _DebugAssert \n"
"loc_FF871054:\n"
      "LDR     R0, [SP]\n"
      "LDR     R1, [R0, #4]\n"
      "LDR     R0, [R7]\n"
      "BL      sub_003FAC6C\n"
      "LDR     R5, [SP]\n"
      "LDR     R0, [R5, #8]\n"
      "CMP     R0, #0\n"
      "LDREQ   R1, =0x117\n"
      "LDREQ   R0, =0xFF87091C \n" // "SsShootTask.c"
      "BLEQ    _DebugAssert \n"
      "STR     R6, [R5, #8]\n"
      "B       loc_FF870DC0\n"
	);
}


//** sub_FF9646A0_my  @ 0xFF96472C
//CHECK THIS!!!
void __attribute__((naked,noinline)) sub_FF96472C_my(  ) {
asm volatile (
      "STMFD   SP!, {R4-R6,LR}\n"
      "LDR     R5, =0x36D9C\n"
      "MOV     R6, R0\n"
      "LDR     R0, [R5, #0x28]\n"
      "MOV     R4, #0\n"
      "CMP     R0, #0\n"
      "BNE     loc_FF96475C\n"
      "MOV     R0, #0xC\n"
      "BL      sub_FF87551C\n"
      "TST     R0, #1\n"
      "MOVNE   R0, #1\n"
      "LDMNEFD SP!, {R4-R6,PC}\n"
"loc_FF96475C:\n"
      "BL      sub_FF8715B8\n"
      "LDR     R0, [R5, #0x28]\n"
      "CMP     R0, #0\n"
      "BNE     loc_FF9647AC\n"
      "MOV     R0, R6\n"
      "BL      sub_FF963FE8\n"
      "TST     R0, #1\n"
      "LDMNEFD SP!, {R4-R6,PC}\n"
      "MOV     R0, R6\n"
      "BL      sub_FF96437C\n"
      "BL      sub_FF964D40\n"

//This was not tested:
//begin patch
      "BL      wait_until_remote_button_is_released\n"
      "BL      capt_seq_hook_set_nr\n"
//end patch
      "MOV     R0, #2\n"
      "BL      sub_FF876C34\n"
      "LDR     R0, [R5, #0x8C]\n"
      "TST     R0, #0x10\n"
      "BNE     loc_FF9647BC\n"
      "MOV     R0, R6\n"
      "BL      sub_FFA72A70\n"
//      "BL      sub_FFA72A70_my\n" //This function calls "SsStandardCaptureSeq.c"
      "MOV     R4, R0\n"
      "B       loc_FF9647C0\n"
"loc_FF9647AC:\n"
      "LDR     R0, =0x684C\n"
      "LDR     R0, [R0]\n"
      "CMP     R0, #0\n"
      "BEQ     loc_FF9647C0\n"
"loc_FF9647BC:\n"
      "MOV     R4, #0x1D\n"
"loc_FF9647C0:\n"
      "MOV     R0, R4\n"
      "LDMFD   SP!, {R4-R6,PC}\n"
	);
}


//** exp_drv_task  @ 0xFF8AFB60 

void __attribute__((naked,noinline)) exp_drv_task(  ) { 
asm volatile (
      "STMFD   SP!, {R4-R9,LR}\n"
      "SUB     SP, SP, #0x2C\n"
      "LDR     R6, =0x3DDC\n"
      "LDR     R7, =0xBB8\n"
      "LDR     R4, =0x53D4C\n"
      "MOV     R0, #0\n"
      "ADD     R5, SP, #0x1C\n"
      "STR     R0, [SP, #0xC]\n"
"loc_FF8AFB80:\n"
      "LDR     R0, [R6, #0x20]\n"
      "MOV     R2, #0\n"
      "ADD     R1, SP, #0x28\n"
      "BL      sub_003F7218\n"
      "LDR     R0, [SP, #0xC]\n"
      "CMP     R0, #1\n"
      "BNE     loc_FF8AFBCC\n"
      "LDR     R0, [SP, #0x28]\n"
      "LDR     R0, [R0]\n"
      "CMP     R0, #0x14\n"
      "CMPNE   R0, #0x15\n"
      "CMPNE   R0, #0x16\n"
      "CMPNE   R0, #0x17\n"
      "BEQ     loc_FF8AFD2C\n"
      "CMP     R0, #0x2A\n"
      "BEQ     loc_FF8AFCB4\n"
      "ADD     R1, SP, #0xC\n"
      "MOV     R0, #0\n"
      "BL      sub_FF8AFB10\n"
"loc_FF8AFBCC:\n"
      "LDR     R0, [SP, #0x28]\n"
      "LDR     R1, [R0]\n"
      "CMP     R1, #0x30\n"
      "BNE     loc_FF8AFBF8\n"
      "BL      sub_FF8B0F40\n"
      "LDR     R0, [R6, #0x1C]\n"
      "MOV     R1, #1\n"
      "BL      sub_003FAC6C\n"
      "BL      _ExitTask \n"
      "ADD     SP, SP, #0x2C\n"
      "LDMFD   SP!, {R4-R9,PC}\n"
"loc_FF8AFBF8:\n"
      "CMP     R1, #0x2F\n"
      "BNE     loc_FF8AFC14\n"
      "LDR     R2, [R0, #0x8C]!\n"
      "LDR     R1, [R0, #4]\n"
      "MOV     R0, R1\n"
      "BLX     R2\n"
      "B       loc_FF8B01E8\n"
"loc_FF8AFC14:\n"
      "CMP     R1, #0x28\n"
      "BNE     loc_FF8AFC64\n"
      "LDR     R0, [R6, #0x1C]\n"
      "MOV     R1, #0x80\n"
      "BL      sub_003FACA0\n"
      "LDR     R0, =0xFF8AB474\n"
      "MOV     R1, #0x80\n"
      "BL      sub_FF9559C0\n"
      "LDR     R0, [R6, #0x1C]\n"
      "MOV     R2, R7\n"
      "MOV     R1, #0x80\n"
      "BL      sub_003FABAC\n"
      "TST     R0, #1\n"
      "LDRNE   R1, =0x157A\n"
      "BNE     loc_FF8AFD20\n"
"loc_FF8AFC50:\n"
      "LDR     R1, [SP, #0x28]\n"
      "LDR     R0, [R1, #0x90]\n"
      "LDR     R1, [R1, #0x8C]\n"
      "BLX     R1\n"
      "B       loc_FF8B01E8\n"
"loc_FF8AFC64:\n"
      "CMP     R1, #0x29\n"
      "BNE     loc_FF8AFCAC\n"
      "ADD     R1, SP, #0xC\n"
      "BL      sub_FF8AFB10\n"
      "LDR     R0, [R6, #0x1C]\n"
      "MOV     R1, #0x100\n"
      "BL      sub_003FACA0\n"
      "LDR     R0, =0xFF8AB484\n"
      "MOV     R1, #0x100\n"
      "BL      sub_FF955B60\n"
      "LDR     R0, [R6, #0x1C]\n"
      "MOV     R2, R7\n"
      "MOV     R1, #0x100\n"
      "BL      sub_003FABAC\n"
      "TST     R0, #1\n"
      "BEQ     loc_FF8AFC50\n"
      "LDR     R1, =0x1584\n"
      "B       loc_FF8AFD20\n"
"loc_FF8AFCAC:\n"
      "CMP     R1, #0x2A\n"
      "BNE     loc_FF8AFCC4\n"
"loc_FF8AFCB4:\n"
      "LDR     R0, [SP, #0x28]\n"
      "ADD     R1, SP, #0xC\n"
      "BL      sub_FF8AFB10\n"
      "B       loc_FF8AFC50\n"
"loc_FF8AFCC4:\n"
      "CMP     R1, #0x2D\n"
      "BNE     loc_FF8AFCDC\n"
      "BL      sub_FF89C6CC\n"
      "BL      sub_FF89D3B4\n"
      "BL      sub_FF89CF1C\n"
      "B       loc_FF8AFC50\n"
"loc_FF8AFCDC:\n"
      "CMP     R1, #0x2E\n"
      "BNE     loc_FF8AFD2C\n"
      "LDR     R0, [R6, #0x1C]\n"
      "MOV     R1, #4\n"
      "BL      sub_003FACA0\n"
      "LDR     R1, =0xFF8AB4A4\n"
      "LDR     R0, =0xFFFFF400\n"
      "MOV     R2, #4\n"
      "BL      sub_FF89C11C\n"
      "BL      sub_FF89C3AC\n"
      "LDR     R0, [R6, #0x1C]\n"
      "MOV     R2, R7\n"
      "MOV     R1, #4\n"
      "BL      sub_003FAAC8\n"
      "TST     R0, #1\n"
      "BEQ     loc_FF8AFC50\n"
      "LDR     R1, =0x15AC\n"
"loc_FF8AFD20:\n"
      "LDR     R0, =0xFF8ABB98\n"
      "BL      _DebugAssert \n"
      "B       loc_FF8AFC50\n"
"loc_FF8AFD2C:\n"
      "LDR     R0, [SP, #0x28]\n"
      "MOV     R8, #1\n"
      "LDR     R1, [R0]\n"
      "CMP     R1, #0x12\n"
      "CMPNE   R1, #0x13\n"
      "BNE     loc_FF8AFD94\n"
      "LDR     R1, [R0, #0x7C]\n"
      "ADD     R1, R1, R1, LSL #1\n"
      "ADD     R1, R0, R1, LSL #2\n"
      "SUB     R1, R1, #8\n"
      "LDMIA   R1, {R2,R3,R9}\n"
      "STMIA   R5, {R2,R3,R9}\n"
      "BL      sub_FF8AE0B0\n"
      "LDR     R0, [SP, #0x28]\n"
      "LDR     R1, [R0, #0x7C]\n"
      "LDR     R3, [R0, #0x8C]\n"
      "LDR     R2, [R0, #0x90]\n"
      "ADD     R0, R0, #4\n"
      "BLX     R3\n"
      "LDR     R0, [SP, #0x28]\n"
      "BL      sub_FF8B1344\n"
      "LDR     R0, [SP, #0x28]\n"
      "LDR     R1, [R0, #0x7C]\n"
      "LDR     R2, [R0, #0x98]\n"
      "LDR     R3, [R0, #0x94]\n"
      "B       loc_FF8B00AC\n"
"loc_FF8AFD94:\n"
      "CMP     R1, #0x14\n"
      "CMPNE   R1, #0x15\n"
      "CMPNE   R1, #0x16\n"
      "CMPNE   R1, #0x17\n"
      "BNE     loc_FF8AFE4C\n"
      "ADD     R3, SP, #0xC\n"
      "MOV     R2, SP\n"
      "ADD     R1, SP, #0x1C\n"
      "BL      sub_FF8AE310\n"
      "CMP     R0, #1\n"
      "MOV     R9, R0\n"
      "CMPNE   R9, #5\n"
      "BNE     loc_FF8AFDE8\n"
      "LDR     R0, [SP, #0x28]\n"
      "MOV     R2, R9\n"
      "LDR     R1, [R0, #0x7C]!\n"
      "LDR     R12, [R0, #0x10]!\n"
      "LDR     R3, [R0, #4]\n"
      "MOV     R0, SP\n"
      "BLX     R12\n"
      "B       loc_FF8AFE20\n"
"loc_FF8AFDE8:\n"
      "LDR     R0, [SP, #0x28]\n"
      "CMP     R9, #2\n"
      "LDR     R3, [R0, #0x90]\n"
      "CMPNE   R9, #6\n"
      "BNE     loc_FF8AFE34\n"
      "LDR     R12, [R0, #0x8C]\n"
      "MOV     R2, R9\n"
      "MOV     R1, #1\n"
      "MOV     R0, SP\n"
      "BLX     R12\n"
      "LDR     R0, [SP, #0x28]\n"
      "MOV     R2, SP\n"
      "ADD     R1, SP, #0x1C\n"
      "BL      sub_FF8AF800\n"
"loc_FF8AFE20:\n"
      "LDR     R0, [SP, #0x28]\n"
      "LDR     R2, [SP, #0xC]\n"
      "MOV     R1, R9\n"
      "BL      sub_FF8AFA50\n"
      "B       loc_FF8B00B4\n"
"loc_FF8AFE34:\n"
      "LDR     R1, [R0, #0x7C]\n"
      "LDR     R12, [R0, #0x8C]\n"
      "MOV     R2, R9\n"
      "ADD     R0, R0, #4\n"
      "BLX     R12\n"
      "B       loc_FF8B00B4\n"
"loc_FF8AFE4C:\n"
      "CMP     R1, #0x24\n"
      "CMPNE   R1, #0x25\n"
      "BNE     loc_FF8AFE98\n"
      "LDR     R1, [R0, #0x7C]\n"
      "ADD     R1, R1, R1, LSL #1\n"
      "ADD     R1, R0, R1, LSL #2\n"
      "SUB     R1, R1, #8\n"
      "LDMIA   R1, {R2,R3,R9}\n"
      "STMIA   R5, {R2,R3,R9}\n"
      "BL      sub_FF8AD09C\n"
      "LDR     R0, [SP, #0x28]\n"
      "LDR     R1, [R0, #0x7C]\n"
      "LDR     R3, [R0, #0x8C]\n"
      "LDR     R2, [R0, #0x90]\n"
      "ADD     R0, R0, #4\n"
      "BLX     R3\n"
      "LDR     R0, [SP, #0x28]\n"
      "BL      sub_FF8AD4DC\n"
      "B       loc_FF8B00B4\n"
"loc_FF8AFE98:\n"
      "ADD     R1, R0, #4\n"
      "LDMIA   R1, {R2,R3,R9}\n"
      "STMIA   R5, {R2,R3,R9}\n"
      "LDR     R1, [R0]\n"
      "CMP     R1, #0x28\n"
      "ADDCC   PC, PC, R1, LSL #2\n"
      "B       loc_FF8B009C\n"
      "B       loc_FF8AFF54\n"
      "B       loc_FF8AFF54\n"
      "B       loc_FF8AFF5C\n"
      "B       loc_FF8AFF64\n"
      "B       loc_FF8AFF64\n"
      "B       loc_FF8AFF64\n"
      "B       loc_FF8AFF54\n"
      "B       loc_FF8AFF5C\n"
      "B       loc_FF8AFF64\n"
      "B       loc_FF8AFF64\n"
      "B       loc_FF8AFF7C\n"
      "B       loc_FF8AFF7C\n"
      "B       loc_FF8B0088\n"
      "B       loc_FF8B0090\n"
      "B       loc_FF8B0090\n"
      "B       loc_FF8B0090\n"
      "B       loc_FF8B0090\n"
      "B       loc_FF8B0098\n"
      "B       loc_FF8B009C\n"
      "B       loc_FF8B009C\n"
      "B       loc_FF8B009C\n"
      "B       loc_FF8B009C\n"
      "B       loc_FF8B009C\n"
      "B       loc_FF8B009C\n"
      "B       loc_FF8AFF6C\n"
      "B       loc_FF8AFF74\n"
      "B       loc_FF8AFF74\n"
      "B       loc_FF8AFF74\n"
      "B       loc_FF8AFF88\n"
      "B       loc_FF8AFF88\n"
      "B       loc_FF8AFF90\n"
      "B       loc_FF8AFFC8\n"
      "B       loc_FF8B0000\n"
      "B       loc_FF8B0038\n"
      "B       loc_FF8B0070\n"
      "B       loc_FF8B0070\n"
      "B       loc_FF8B009C\n"
      "B       loc_FF8B009C\n"
      "B       loc_FF8B0078\n"
      "B       loc_FF8B0080\n"
"loc_FF8AFF54:\n"
      "BL      sub_FF8ABA1C\n"
      "B       loc_FF8B009C\n"
"loc_FF8AFF5C:\n"
      "BL      sub_FF8ABCC0\n"
      "B       loc_FF8B009C\n"
"loc_FF8AFF64:\n"
      "BL      sub_FF8ABEE8\n"
      "B       loc_FF8B009C\n"
"loc_FF8AFF6C:\n"
      "BL      sub_FF8AC20C\n"
      "B       loc_FF8B009C\n"
"loc_FF8AFF74:\n"
      "BL      sub_FF8AC424\n"
      "B       loc_FF8B009C\n"
"loc_FF8AFF7C:\n"
//      "BL      sub_FF8AC7D0\n"  //original
      "BL      sub_FF8AC7D0_my\n" //patched
      "MOV     R8, #0\n"
      "B       loc_FF8B009C\n"
"loc_FF8AFF88:\n"
      "BL      sub_FF8AC910\n"
      "B       loc_FF8B009C\n"
"loc_FF8AFF90:\n"
      "LDRH    R1, [R0, #4]\n"
      "STRH    R1, [SP, #0x1C]\n"
      "LDRH    R1, [R4, #2]\n"
      "STRH    R1, [SP, #0x1E]\n"
      "LDRH    R1, [R4, #4]\n"
      "STRH    R1, [SP, #0x20]\n"
      "LDRH    R1, [R4, #6]\n"
      "STRH    R1, [SP, #0x22]\n"
      "LDRH    R1, [R0, #0xC]\n"
      "STRH    R1, [SP, #0x24]\n"
      "LDRH    R1, [R4, #0xA]\n"
      "STRH    R1, [SP, #0x26]\n"
      "BL      sub_FF8B0FD4\n"
      "B       loc_FF8B009C\n"
"loc_FF8AFFC8:\n"
      "LDRH    R1, [R0, #4]\n"
      "STRH    R1, [SP, #0x1C]\n"
      "LDRH    R1, [R4, #2]\n"
      "STRH    R1, [SP, #0x1E]\n"
      "LDRH    R1, [R4, #4]\n"
      "STRH    R1, [SP, #0x20]\n"
      "LDRH    R1, [R4, #6]\n"
      "STRH    R1, [SP, #0x22]\n"
      "LDRH    R1, [R4, #8]\n"
      "STRH    R1, [SP, #0x24]\n"
      "LDRH    R1, [R4, #0xA]\n"
      "STRH    R1, [SP, #0x26]\n"
      "BL      sub_FF8B1144\n"
      "B       loc_FF8B009C\n"
"loc_FF8B0000:\n"
      "LDRH    R1, [R4]\n"
      "STRH    R1, [SP, #0x1C]\n"
      "LDRH    R1, [R0, #6]\n"
      "STRH    R1, [SP, #0x1E]\n"
      "LDRH    R1, [R4, #4]\n"
      "STRH    R1, [SP, #0x20]\n"
      "LDRH    R1, [R4, #6]\n"
      "STRH    R1, [SP, #0x22]\n"
      "LDRH    R1, [R4, #8]\n"
      "STRH    R1, [SP, #0x24]\n"
      "LDRH    R1, [R4, #0xA]\n"
      "STRH    R1, [SP, #0x26]\n"
      "BL      sub_FF8B11F8\n"
      "B       loc_FF8B009C\n"
"loc_FF8B0038:\n"
      "LDRH    R1, [R4]\n"
      "STRH    R1, [SP, #0x1C]\n"
      "LDRH    R1, [R4, #2]\n"
      "STRH    R1, [SP, #0x1E]\n"
      "LDRH    R1, [R4, #4]\n"
      "STRH    R1, [SP, #0x20]\n"
      "LDRH    R1, [R4, #6]\n"
      "STRH    R1, [SP, #0x22]\n"
      "LDRH    R1, [R0, #0xC]\n"
      "STRH    R1, [SP, #0x24]\n"
      "LDRH    R1, [R4, #0xA]\n"
      "STRH    R1, [SP, #0x26]\n"
      "BL      sub_FF8B12A0\n"
      "B       loc_FF8B009C\n"
"loc_FF8B0070:\n"
      "BL      sub_FF8ACE50\n"
      "B       loc_FF8B009C\n"
"loc_FF8B0078:\n"
      "BL      sub_FF8AD5E0\n"
      "B       loc_FF8B009C\n"
"loc_FF8B0080:\n"
      "BL      sub_FF8AD8C4\n"
      "B       loc_FF8B009C\n"
"loc_FF8B0088:\n"
      "BL      sub_FF8ADB84\n"
      "B       loc_FF8B009C\n"
"loc_FF8B0090:\n"
      "BL      sub_FF8ADD40\n"
      "B       loc_FF8B009C\n"
"loc_FF8B0098:\n"
      "BL      sub_FF8ADEA8\n"
"loc_FF8B009C:\n"
      "LDR     R0, [SP, #0x28]\n"
      "LDR     R1, [R0, #0x7C]\n"
      "LDR     R2, [R0, #0x90]\n"
      "LDR     R3, [R0, #0x8C]\n"
"loc_FF8B00AC:\n"
      "ADD     R0, R0, #4\n"
      "BLX     R3\n"
"loc_FF8B00B4:\n"
      "LDR     R0, [SP, #0x28]\n"
      "LDR     R0, [R0]\n"
      "CMP     R0, #0x10\n"
      "BEQ     loc_FF8B00EC\n"
      "BGT     loc_FF8B00DC\n"
      "CMP     R0, #1\n"
      "CMPNE   R0, #4\n"
      "CMPNE   R0, #0xE\n"
      "BNE     loc_FF8B0120\n"
      "B       loc_FF8B00EC\n"
"loc_FF8B00DC:\n"
      "CMP     R0, #0x13\n"
      "CMPNE   R0, #0x17\n"
      "CMPNE   R0, #0x1A\n"
      "BNE     loc_FF8B0120\n"
"loc_FF8B00EC:\n"
      "LDRSH   R0, [R4]\n"
      "CMN     R0, #0xC00\n"
      "LDRNESH R1, [R4, #8]\n"
      "CMNNE   R1, #0xC00\n"
      "STRNEH  R0, [SP, #0x1C]\n"
      "STRNEH  R1, [SP, #0x24]\n"
      "BNE     loc_FF8B0120\n"
      "ADD     R0, SP, #0x10\n"
      "BL      sub_FF8B1550\n"
      "LDRH    R0, [SP, #0x10]\n"
      "STRH    R0, [SP, #0x1C]\n"
      "LDRH    R0, [SP, #0x18]\n"
      "STRH    R0, [SP, #0x24]\n"
"loc_FF8B0120:\n"
      "LDR     R0, [SP, #0x28]\n"
      "CMP     R8, #1\n"
      "BNE     loc_FF8B0170\n"
      "LDR     R1, [R0, #0x7C]\n"
      "MOV     R2, #0xC\n"
      "ADD     R1, R1, R1, LSL #1\n"
      "ADD     R0, R0, R1, LSL #2\n"
      "SUB     R8, R0, #8\n"
      "LDR     R0, =0x53D4C\n"
      "ADD     R1, SP, #0x1C\n"
      "BL      sub_003FC17C\n"
      "LDR     R0, =0x53D58\n"
      "MOV     R2, #0xC\n"
      "ADD     R1, SP, #0x1C\n"
      "BL      sub_003FC17C\n"
      "LDR     R0, =0x53D64\n"
      "MOV     R2, #0xC\n"
      "MOV     R1, R8\n"
      "BL      sub_003FC17C\n"
      "B       loc_FF8B01E8\n"
"loc_FF8B0170:\n"
      "LDR     R0, [R0]\n"
      "MOV     R3, #1\n"
      "CMP     R0, #0xB\n"
      "BNE     loc_FF8B01B4\n"
      "MOV     R2, #0\n"
      "STRD    R2, [SP]\n"
      "MOV     R2, R3\n"
      "MOV     R1, R3\n"
      "MOV     R0, #0\n"
      "BL      sub_FF8AB7FC\n"
      "MOV     R3, #1\n"
      "MOV     R2, #0\n"
      "STRD    R2, [SP]\n"
      "MOV     R2, R3\n"
      "MOV     R1, R3\n"
      "MOV     R0, #0\n"
      "B       loc_FF8B01E4\n"
"loc_FF8B01B4:\n"
      "MOV     R2, #1\n"
      "STRD    R2, [SP]\n"
      "MOV     R3, R2\n"
      "MOV     R1, R2\n"
      "MOV     R0, R2\n"
      "BL      sub_FF8AB7FC\n"
      "MOV     R3, #1\n"
      "MOV     R2, R3\n"
      "MOV     R1, R3\n"
      "MOV     R0, R3\n"
      "STR     R3, [SP]\n"
      "STR     R3, [SP, #4]\n"
"loc_FF8B01E4:\n"
      "BL      sub_FF8AB968\n"
"loc_FF8B01E8:\n"
      "LDR     R0, [SP, #0x28]\n"
      "BL      sub_FF8B0F40\n"
      "B       loc_FF8AFB80\n"
	);
}


//** sub_FF8AC74C_my  @ 0xFF8AC7D0 

void __attribute__((naked,noinline)) sub_FF8AC7D0_my(  ) {
asm volatile (
      "STMFD   SP!, {R4-R8,LR}\n"
      "LDR     R7, =0x3DDC\n"
      "MOV     R4, R0\n"
      "LDR     R0, [R7, #0x1C]\n"
      "MOV     R1, #0x3E\n"
      "BL      sub_003FACA0\n"
      "MOV     R2, #0\n"
      "LDRSH   R0, [R4, #4]\n"
      "MOV     R1, R2\n"
      "BL      sub_FF8AB504\n"
      "MOV     R6, R0\n"
      "LDRSH   R0, [R4, #6]\n"
      "BL      sub_FF8AB654\n"
      "LDRSH   R0, [R4, #8]\n"
      "BL      sub_FF8AB6AC\n"
      "LDRSH   R0, [R4, #0xA]\n"
      "BL      sub_FF8AB704\n"
      "LDRSH   R0, [R4, #0xC]\n"
      "MOV     R1, #0\n"
      "BL      sub_FF8AB75C\n"
      "MOV     R5, R0\n"
      "LDR     R0, [R4]\n"
      "LDR     R8, =0x53D64\n"
      "CMP     R0, #0xB\n"
      "MOVEQ   R6, #0\n"
      "MOVEQ   R5, R6\n"
      "BEQ     loc_FF8AC864\n"
      "CMP     R6, #1\n"
      "BNE     loc_FF8AC864\n"
      "LDRSH   R0, [R4, #4]\n"
      "LDR     R1, =0xFF8AB464\n"
      "MOV     R2, #2\n"
      "BL      sub_FF955A44\n"
      "STRH    R0, [R4, #4]\n"
      "MOV     R0, #0\n"
      "STR     R0, [R7, #0x28]\n"
      "B       loc_FF8AC86C\n"
"loc_FF8AC864:\n"
      "LDRH    R0, [R8]\n"
      "STRH    R0, [R4, #4]\n"
"loc_FF8AC86C:\n"
      "CMP     R5, #1\n"
      "LDRNEH  R0, [R8, #8]\n"
      "BNE     loc_FF8AC888\n"
      "LDRSH   R0, [R4, #0xC]\n"
      "LDR     R1, =0xFF8AB4E8\n"
      "MOV     R2, #0x20\n"
      "BL      sub_FF8B0F90\n"
"loc_FF8AC888:\n"
      "STRH    R0, [R4, #0xC]\n"
      "LDRSH   R0, [R4, #6]\n"
//      "BL      sub_FF89C418\n"  //original
      "BL      sub_FF89C418_my\n" //patch
      "B       sub_FF8AC894 \n" // continue in firmware
	);
}


//** sub_FF89C418_my  @ 0xFF89C418 

void __attribute__((naked,noinline)) sub_FF89C418_my(  ) { 
asm volatile (
      "STMFD   SP!, {R4-R6,LR}\n"
      "LDR     R5, =0x3A68\n"
      "MOV     R4, R0\n"
      "LDR     R0, [R5, #4]\n"
      "CMP     R0, #1\n"
      "LDRNE   R1, =0x14D\n"
      "LDRNE   R0, =0xFF89C250\n"
      "BLNE    _DebugAssert \n"
      "CMN     R4, #0xC00\n"
      "LDREQSH R4, [R5, #2]\n"
      "CMN     R4, #0xC00\n"
      "LDREQ   R1, =0x153\n"
      "LDREQ   R0, =0xFF89C250\n"
      "STRH    R4, [R5, #2]\n"
      "BLEQ    _DebugAssert \n"
      "MOV     R0, R4\n"
//      "BL      _apex2us \n" //original apex2us function
      "BL      apex2us \n"    //patch
      "MOV     R4, R0\n"
      "BL      sub_FF8EA614\n"
      "MOV     R0, R4\n"
      "BL      sub_FF8F2E1C\n"
      "TST     R0, #1\n"
      "LDMEQFD SP!, {R4-R6,PC}\n"
      "LDMFD   SP!, {R4-R6,LR}\n"
      "MOV     R1, #0x158\n"
      "LDR     R0, =0xFF89C250\n"
      "B       _DebugAssert \n"
	);
}
