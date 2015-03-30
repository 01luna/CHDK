#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0x5A80;

#include "../../../generic/capt_seq.c"


void __attribute__((naked,noinline)) sub_FFD17E50_my() {
 asm volatile (

        "STMFD   SP!, {R0-R8,LR}\n"
        "MOV     R4, R0\n"
        "BL      sub_FFD18948    \n"
		"MOV     R1, #0xFFFFFFFF\n"
        "BL      sub_FFC28C18\n"
        "LDR     R5, =0x5A80\n"
        "LDR     R0, [R5,#0xC]\n"
        "CMP     R0, #0\n"
        "BNE     loc_FFD17EA0\n"
        "MOV     R1, #1\n"
        "MOV     R0, #0\n"
        "BL      sub_FFC0F41C    \n"
        "STR     R0, [R5,#0xC]\n"
        "MOV     R3, #0\n"
        "STR     R3, [SP]\n"
        "LDR     R3, =0xFFD1788C \n"
        "LDR     R0, =0xFFD180B4\n"
        "MOV     R2, #0x400\n"
        "MOV     R1, #0x17\n"
        "BL      sub_FFC0F3E8    \n"
"loc_FFD17EA0:\n"
        "MOV     R2, #4\n"
        "ADD     R1, SP, #8\n"
        "MOV     R0, #0x8A\n"
        "BL      sub_FFC6C614    \n"
        "TST     R0, #1\n"
        "LDRNE   R1, =0x3BA\n"
        "LDRNE   R0, =0xFFD17B10\n"
        "BLNE    sub_FFC0F5E8\n"
        "LDR     R6, =0x34720\n"
        "LDR     R7, =0x3465C\n"
        "LDR     R3, [R6]\n"
        "LDRSH   R2, [R6,#0xC]\n"
        "LDRSH   R1, [R6,#0xE]\n"
        "LDR     R0, [R7,#0x88]\n"
        "BL      sub_FFCE9E0C\n"
        "BL      sub_FFC4660C    \n"
        "LDR     R3, =0x5A88\n"
        "STRH    R0, [R4,#0xA4]\n"
        "SUB     R2, R3, #4\n"
        "STRD    R2, [SP]\n"
        "MOV     R1, R0\n"
        "LDRH    R0, [R7,#0x5C]\n"
        "LDRSH   R2, [R6,#0xC]\n"
        "SUB     R3, R3, #8\n"
        "BL      sub_FFD18FAC\n"
		"BL      wait_until_remote_button_is_released\n" // untested!
		"BL      capt_seq_hook_set_nr\n"
		"B       sub_FFD17F04\n" // -> continue in firmware
 );
}
void __attribute__((naked,noinline)) sub_FFC5C588_my() {
 asm volatile (
        "STMFD   SP!, {R4-R6,LR}\n"
        "LDR     R4, [R0,#0xC]\n"
        "LDR     R6, =0x3465C\n"
        "LDR     R0, [R4,#8]\n"
        "MOV     R5, #0\n"
        "ORR     R0, R0, #1\n"
        "STR     R0, [R4,#8]\n"
        "LDR     R0, [R6,#0x24]\n"
        "CMP     R0, #0\n"
        "MOVEQ   R0, #2\n"
        "BLEQ    sub_FFC58A9C\n"
        "BL      sub_FFC5CA84\n"
        "LDR     R0, [R6,#0x24]\n"
        "CMP     R0, #0\n"
        "BNE     loc_FFC5C624\n"
        "MOV     R0, R4\n"
        "BL      sub_FFC5CE24\n"
        "MOV     R0, R4\n"
        "BL      sub_FFD169F8\n"
        "CMP     R0, #0\n"
        "MOV     R0, R4\n"
        "BEQ     loc_FFC5C5FC\n"
        "BL      sub_FFD16A84    \n"
        "TST     R0, #1\n"
        "MOVNE   R2, R4\n"
        "LDMNEFD SP!, {R4-R6,LR}\n"
        "MOVNE   R1, #1\n"
        "BNE     sub_FFC5A71C    \n"
        "B       loc_FFC5C600\n"
"loc_FFC5C5FC:\n"
        "BL      sub_FFD16A48\n"
"loc_FFC5C600:\n"
        "MOV     R0, R4\n"
        "BL      sub_FFC5BCD4\n"
        "MOV     R0, R4\n"
        "BL      sub_FFD17D88    \n"
        "BL      sub_FFD187B4    \n"
        "MOV     R0, R4\n"
        //"BL      sub_FFD17E50    \n"
		"BL      sub_FFD17E50_my    \n"   // ---> nr setup
        "MOV     R5, R0\n"
        "B       loc_FFC5C634\n"
"loc_FFC5C624:\n"
        "LDR     R0, =0x27FC\n"
        "LDR     R0, [R0,#0x10]\n"
        "CMP     R0, #0\n"
        "MOVNE   R5, #0x1D\n"
"loc_FFC5C634:\n"
		"BL      capt_seq_hook_raw_here\n" // ++++->
        "BL      sub_FFC5F0F4\n"
        "BL      sub_FFC5F13C\n"
        "BL      sub_FFC5F17C\n"
        "MOV     R2, R4\n"
        "MOV     R1, #1\n"
        "MOV     R0, R5\n"
        "BL      sub_FFC5A71C    \n"
        "BL      sub_FFD180E8\n"
        "CMP     R0, #0\n"
        "LDRNE   R0, [R4,#8]\n"
        "ORRNE   R0, R0, #0x2000\n"
        "STRNE   R0, [R4,#8]\n"
        "LDMFD   SP!, {R4-R6,PC}\n"
  );
}

void __attribute__((naked,noinline)) task_CaptSeqTask_my() {
	asm volatile (
        "STMFD   SP!, {R3-R9,LR}\n"
        "LDR     R6, =0x27FC\n"
        "LDR     R4, =0x3465C\n"
        "MOV     R9, #1\n"
        "MOV     R7, #0\n"
"loc_FFC5C1AC:\n"
        "LDR     R0, [R6,#4]\n"
        "MOV     R2, #0\n"
        "MOV     R1, SP\n"
        "BL      sub_FFC28E74    \n"
        "TST     R0, #1\n"
        "BEQ     loc_FFC5C1D8\n"
        "LDR     R1, =0x5B4\n"
        "LDR     R0, =0xFFC5BD50\n"
        "BL      sub_FFC0F5E8\n"
        "BL      sub_FFC0F3A0    \n"
        "LDMFD   SP!, {R3-R9,PC}\n"
"loc_FFC5C1D8:\n"
        "LDR     R0, [SP]\n"
        "LDR     R1, [R0]\n"
        "CMP     R1, #0x1D\n"
        "ADDLS   PC, PC, R1,LSL#2\n"
        "B       loc_FFC5C460\n"
"loc_FFC5C1EC:\n"
        "B       loc_FFC5C264\n"
"loc_FFC5C1F0:\n"
        "B       loc_FFC5C2C8\n"
"loc_FFC5C1F4:\n"
        "B       loc_FFC5C304\n"
"loc_FFC5C1F8:\n"
        "B       loc_FFC5C318\n"
"loc_FFC5C1FC:\n"
        "B       loc_FFC5C310\n"
"loc_FFC5C200:\n"
        "B       loc_FFC5C320\n"
"loc_FFC5C204:\n"
        "B       loc_FFC5C328\n"
"loc_FFC5C208:\n"
        "B       loc_FFC5C330\n"
"loc_FFC5C20C:\n"
        "B       loc_FFC5C388\n"
"loc_FFC5C210:\n"
        "B       loc_FFC5C3B0\n"
"loc_FFC5C214:\n"
        "B       loc_FFC5C394\n"
"loc_FFC5C218:\n"
        "B       loc_FFC5C3A0\n"
"loc_FFC5C21C:\n"
        "B       loc_FFC5C3A8\n"
"loc_FFC5C220:\n"
        "B       loc_FFC5C3B8\n"
"loc_FFC5C224:\n"
        "B       loc_FFC5C3C0\n"
"loc_FFC5C228:\n"
        "B       loc_FFC5C3C8\n"
"loc_FFC5C22C:\n"
        "B       loc_FFC5C3D0\n"
"loc_FFC5C230:\n"
        "B       loc_FFC5C3D8\n"
"loc_FFC5C234:\n"
        "B       loc_FFC5C3E4\n"
"loc_FFC5C238:\n"
        "B       loc_FFC5C3EC\n"
"loc_FFC5C23C:\n"
        "B       loc_FFC5C3F4\n"
"loc_FFC5C240:\n"
        "B       loc_FFC5C3FC\n"
"loc_FFC5C244:\n"
        "B       loc_FFC5C404\n"
"loc_FFC5C248:\n"
        "B       loc_FFC5C410\n"
"loc_FFC5C24C:\n"
        "B       loc_FFC5C418\n"
"loc_FFC5C250:\n"
        "B       loc_FFC5C420\n"
"loc_FFC5C254:\n"
        "B       loc_FFC5C428\n"
"loc_FFC5C258:\n"
        "B       loc_FFC5C430\n"
"loc_FFC5C25C:\n"
        "B       loc_FFC5C43C\n"
"loc_FFC5C260:\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C264:\n"
        "BL      sub_FFC5CA94\n"
		// TODO do we need the short press hack ?
		"BL      shooting_expo_param_override\n"  // +
        "BL      sub_FFC5A2A8\n"
        "LDR     R0, [R4,#0x24]\n"
        "CMP     R0, #0\n"
        "BEQ     loc_FFC5C46C\n"
        "BL      sub_FFC5BA30\n"
        "MOV     R5, R0\n"
        "LDR     R0, [R4,#0x24]\n"
        "CMP     R0, #0\n"
        "BEQ     loc_FFC5C2AC\n"
        "MOV     R0, #0xC\n"
        "BL      sub_FFC60824\n"
        "TST     R0, #1\n"
        "STRNE   R9, [R6,#0x10]\n"
        "LDRNE   R0, [R5,#8]\n"
        "ORRNE   R0, R0, #0x40000000\n"
        "STRNE   R0, [R5,#8]\n"
        "BNE     loc_FFC5C46C\n"
"loc_FFC5C2AC:\n"
        "MOV     R0, R5\n"
        "BL      sub_FFC5BCD4\n"
        "MOV     R0, R5\n"
		// "BL      sub_FFD17E50\n"
        "BL      sub_FFD17E50_my\n" // -> nr setup (quick press)
        "TST     R0, #1\n"
        "STRNE   R9, [R6,#0x10]\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C2C8:\n"
        "LDR     R0, [R4,#0x24]\n"
        "CMP     R0, #0\n"
        "BNE     loc_FFC5C2F4\n"
        "MOV     R0, #0xC\n"
        "BL      sub_FFC60824\n"
        "TST     R0, #1\n"
        "LDRNE   R0, [SP]\n"
        "MOVNE   R1, #1\n"
        "LDRNE   R2, [R0,#0xC]\n"
        "MOVNE   R0, #1\n"
        "BNE     loc_FFC5C380\n"
"loc_FFC5C2F4:\n"
        "LDR     R0, [SP]\n"
        //"BL      sub_FFC5C588\n"
		"BL      sub_FFC5C588_my\n" // ---->
"loc_FFC5C2FC:\n"
        "STR     R7, [R4,#0x24]\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C304:\n"
        "MOV     R0, #1\n"
        "BL      sub_FFC5CD1C    \n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C310:\n"
        "BL      sub_FFC5C700\n"
        "B       loc_FFC5C2FC\n"
"loc_FFC5C318:\n"
        "BL      sub_FFC5CA74\n"
        "B       loc_FFC5C2FC\n"
"loc_FFC5C320:\n"
        "BL      sub_FFC5CA7C\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C328:\n"
        "BL      sub_FFC5CC2C\n"
        "B       loc_FFC5C38C\n"
"loc_FFC5C330:\n"
        "LDR     R5, [R0,#0xC]\n"
        "BL      sub_FFC5CA84\n"
        "MOV     R0, R5\n"
        "BL      sub_FFD16D8C    \n"
        "TST     R0, #1\n"
        "MOV     R8, R0\n"
        "BNE     loc_FFC5C370\n"
        "BL      sub_FFC6C7A4    \n"
        "STR     R0, [R5,#0x18]\n"
        "MOV     R0, R5\n"
        "BL      sub_FFD17D88    \n"
        "MOV     R0, R5\n"
        "BL      sub_FFD18134    \n"
        "MOV     R8, R0\n"
        "LDR     R0, [R5,#0x18]\n"
        "BL      sub_FFC6C9DC    \n"
"loc_FFC5C370:\n"
        "BL      sub_FFC5CA74\n"
        "MOV     R2, R5\n"
        "MOV     R1, #9\n"
        "MOV     R0, R8\n"
"loc_FFC5C380:\n"
        "BL      sub_FFC5A71C    \n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C388:\n"
        "BL      sub_FFC5CC94\n"
"loc_FFC5C38C:\n"
        "BL      sub_FFC5A2A8\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C394:\n"
        "LDR     R0, [R4,#0x54]\n"
        "BL      sub_FFC5D07C    \n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C3A0:\n"
        "BL      sub_FFC5D32C\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C3A8:\n"
        "BL      sub_FFC5D3C0\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C3B0:\n"
        "BL      sub_FFC5CA74\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C3B8:\n"
        "BL      sub_FFD16FB8\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C3C0:\n"
        "BL      sub_FFD171B0\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C3C8:\n"
        "BL      sub_FFD17244\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C3D0:\n"
        "BL      sub_FFD17304\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C3D8:\n"
        "MOV     R0, #0\n"
        "BL      sub_FFD174FC\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C3E4:\n"
        "BL      sub_FFD1764C\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C3EC:\n"
        "BL      sub_FFD176DC\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C3F4:\n"
        "BL      sub_FFD1779C\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C3FC:\n"
        "BL      sub_FFC5CE70\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C404:\n"
        "BL      sub_FFC5CF04\n"
        "BL      sub_FFC26E20\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C410:\n"
        "BL      sub_FFD173D0\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C418:\n"
        "BL      sub_FFD17414\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C420:\n"
        "BL      sub_FFC5F074\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C428:\n"
        "BL      sub_FFC5F0F4\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C430:\n"
        "BL      sub_FFC5F150\n"
        "BL      sub_FFC5F110\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C43C:\n"
        "LDRH    R0, [R4,#0x94]\n"
        "CMP     R0, #4\n"
        "LDRNEH  R0, [R4]\n"
        "SUBNE   R12, R0, #0x8200\n"
        "SUBNES  R12, R12, #0x2A\n"
        "BNE     loc_FFC5C46C\n"
        "BL      sub_FFC5F0F4\n"
        "BL      sub_FFC5F494\n"
        "B       loc_FFC5C46C\n"
"loc_FFC5C460:\n"
        "LDR     R1, =0x70B\n"
        "LDR     R0, =0xFFC5BD50\n"
        "BL      sub_FFC0F5E8\n"
"loc_FFC5C46C:\n"
        "LDR     R0, [SP]\n"
        "LDR     R1, [R0,#4]\n"
        "LDR     R0, [R6]\n"
        "BL      sub_FFC28BE4\n"
        "LDR     R5, [SP]\n"
        "LDR     R0, [R5,#8]\n"
        "CMP     R0, #0\n"
        "LDREQ   R1, =0x132\n"
        "LDREQ   R0, =0xFFC5BD50\n"
        "BLEQ    sub_FFC0F5E8\n"
        "STR     R7, [R5,#8]\n"
        "B       loc_FFC5C1AC\n"
    );
}
void __attribute__((naked,noinline)) exp_drv_task(){
 asm volatile(
        "STMFD   SP!, {R4-R8,LR}\n"
        "SUB     SP, SP, #0x20\n"
        "LDR     R8, =0xBB8\n"
        "LDR     R7, =0x3A24\n"
        "LDR     R5, =0x3DA50\n"
        "MOV     R0, #0\n"
        "ADD     R6, SP, #0x10\n"
        "STR     R0, [SP,#0xC]\n"
"loc_FFC95018:\n"
        "LDR     R0, [R7,#0x20]\n"
        "MOV     R2, #0\n"
        "ADD     R1, SP, #0x1C\n"
        "BL      sub_FFC28E74    \n"
        "LDR     R0, [SP,#0xC]\n"
        "CMP     R0, #1\n"
        "BNE     loc_FFC95064\n"
        "LDR     R0, [SP,#0x1C]\n"
        "LDR     R0, [R0]\n"
        "CMP     R0, #0x13\n"
        "CMPNE   R0, #0x14\n"
        "CMPNE   R0, #0x15\n"
        "CMPNE   R0, #0x16\n"
        "BEQ     loc_FFC951C8\n"
        "CMP     R0, #0x28\n"
        "BEQ     loc_FFC95150\n"
        "ADD     R1, SP, #0xC\n"
        "MOV     R0, #0\n"
        "BL      sub_FFC94FA8    \n"
"loc_FFC95064:\n"
        "LDR     R0, [SP,#0x1C]\n"
        "LDR     R1, [R0]\n"
        "CMP     R1, #0x2E\n"
        "BNE     loc_FFC95094\n"
        "LDR     R0, [SP,#0x1C]\n"
        "BL      sub_FFC96300    \n"
        "LDR     R0, [R7,#0x1C]\n"
        "MOV     R1, #1\n"
        "BL      sub_FFC28BE4\n"
        "BL      sub_FFC0F3A0    \n"
        "ADD     SP, SP, #0x20\n"
        "LDMFD   SP!, {R4-R8,PC}\n"
"loc_FFC95094:\n"
        "CMP     R1, #0x2D\n"
        "BNE     loc_FFC950B0\n"
        "LDR     R2, [R0,#0x8C]!\n"
        "LDR     R1, [R0,#4]\n"
        "MOV     R0, R1\n"
        "BLX     R2\n"
        "B       loc_FFC955F0\n"
"loc_FFC950B0:\n"
        "CMP     R1, #0x26\n"
        "BNE     loc_FFC95100\n"
        "LDR     R0, [R7,#0x1C]\n"
        "MOV     R1, #0x80\n"
        "BL      sub_FFC28C18\n"
        "LDR     R0, =0xFFC91774\n"
        "MOV     R1, #0x80\n"
        "BL      sub_FFD0C67C    \n"
        "LDR     R0, [R7,#0x1C]\n"
        "MOV     R2, R8\n"
        "MOV     R1, #0x80\n"
        "BL      sub_FFC28B24    \n"
        "TST     R0, #1\n"
        "LDRNE   R1, =0xE5F\n"
        "BNE     loc_FFC951BC\n"
"loc_FFC950EC:\n"
        "LDR     R1, [SP,#0x1C]\n"
        "LDR     R0, [R1,#0x90]\n"
        "LDR     R1, [R1,#0x8C]\n"
        "BLX     R1\n"
        "B       loc_FFC955F0\n"
"loc_FFC95100:\n"
        "CMP     R1, #0x27\n"
        "BNE     loc_FFC95148\n"
        "ADD     R1, SP, #0xC\n"
        "BL      sub_FFC94FA8    \n"
        "LDR     R0, [R7,#0x1C]\n"
        "MOV     R1, #0x100\n"
        "BL      sub_FFC28C18\n"
        "LDR     R0, =0xFFC91784\n"
        "MOV     R1, #0x100\n"
        "BL      sub_FFD0C904    \n"
        "LDR     R0, [R7,#0x1C]\n"
        "MOV     R2, R8\n"
        "MOV     R1, #0x100\n"
        "BL      sub_FFC28B24    \n"
        "TST     R0, #1\n"
        "BEQ     loc_FFC950EC\n"
        "LDR     R1, =0xE69\n"
        "B       loc_FFC951BC\n"
"loc_FFC95148:\n"
        "CMP     R1, #0x28\n"
        "BNE     loc_FFC95160\n"
"loc_FFC95150:\n"
        "LDR     R0, [SP,#0x1C]\n"
        "ADD     R1, SP, #0xC\n"
        "BL      sub_FFC94FA8    \n"
        "B       loc_FFC950EC\n"
"loc_FFC95160:\n"
        "CMP     R1, #0x2B\n"
        "BNE     loc_FFC95178\n"
        "BL      sub_FFC84ACC    \n"
        "BL      sub_FFC85710    \n"
        "BL      sub_FFC85260    \n"
        "B       loc_FFC950EC\n"
"loc_FFC95178:\n"
        "CMP     R1, #0x2C\n"
        "BNE     loc_FFC951C8\n"
        "LDR     R0, [R7,#0x1C]\n"
        "MOV     R1, #4\n"
        "BL      sub_FFC28C18\n"
        "LDR     R1, =0xFFC917A4\n"
        "LDR     R0, =0xFFFFF400\n"
        "MOV     R2, #4\n"
        "BL      sub_FFC84548\n"
        "BL      sub_FFC847D0    \n"
        "LDR     R0, [R7,#0x1C]\n"
        "MOV     R2, R8\n"
        "MOV     R1, #4\n"
        "BL      sub_FFC28A40    \n"
        "TST     R0, #1\n"
        "BEQ     loc_FFC950EC\n"
        "LDR     R1, =0xE91\n"
"loc_FFC951BC:\n"
        "LDR     R0, =0xFFC91DE4\n"
        "BL      sub_FFC0F5E8\n"
        "B       loc_FFC950EC\n"
"loc_FFC951C8:\n"
        "LDR     R0, [SP,#0x1C]\n"
        "MOV     R4, #1\n"
        "LDR     R1, [R0]\n"
        "CMP     R1, #0x11\n"
        "CMPNE   R1, #0x12\n"
        "BNE     loc_FFC95238\n"
        "LDR     R1, [R0,#0x7C]\n"
        "ADD     R1, R1, R1,LSL#1\n"
        "ADD     R1, R0, R1,LSL#2\n"
        "SUB     R1, R1, #8\n"
        "LDMIA   R1, {R2-R4}\n"
        "STMIA   R6, {R2-R4}\n"
        "BL      sub_FFC93934\n"
        "LDR     R0, [SP,#0x1C]\n"
        "LDR     R1, [R0,#0x7C]\n"
        "LDR     R3, [R0,#0x8C]\n"
        "LDR     R2, [R0,#0x90]\n"
        "ADD     R0, R0, #4\n"
        "BLX     R3\n"
        "LDR     R0, [SP,#0x1C]\n"
        "BL      sub_FFC966C8    \n"
        "LDR     R0, [SP,#0x1C]\n"
        "LDR     R1, [R0,#0x7C]\n"
        "LDR     R3, [R0,#0x94]\n"
        "LDR     R2, [R0,#0x98]\n"
        "ADD     R0, R0, #4\n"
        "BLX     R3\n"
        "B       loc_FFC95530\n"
"loc_FFC95238:\n"
        "CMP     R1, #0x13\n"
        "CMPNE   R1, #0x14\n"
        "CMPNE   R1, #0x15\n"
        "CMPNE   R1, #0x16\n"
        "BNE     loc_FFC952F0\n"
        "ADD     R3, SP, #0xC\n"
        "MOV     R2, SP\n"
        "ADD     R1, SP, #0x10\n"
        "BL      sub_FFC93C10    \n"
        "CMP     R0, #1\n"
        "MOV     R4, R0\n"
        "CMPNE   R4, #5\n"
        "BNE     loc_FFC9528C\n"
        "LDR     R0, [SP,#0x1C]\n"
        "MOV     R2, R4\n"
        "LDR     R1, [R0,#0x7C]!\n"
        "LDR     R12, [R0,#0x10]!\n"
        "LDR     R3, [R0,#4]\n"
        "MOV     R0, SP\n"
        "BLX     R12\n"
        "B       loc_FFC952C4\n"
"loc_FFC9528C:\n"
        "LDR     R0, [SP,#0x1C]\n"
        "CMP     R4, #2\n"
        "LDR     R3, [R0,#0x90]\n"
        "CMPNE   R4, #6\n"
        "BNE     loc_FFC952D8\n"
        "LDR     R12, [R0,#0x8C]\n"
        "MOV     R0, SP\n"
        "MOV     R2, R4\n"
        "MOV     R1, #1\n"
        "BLX     R12\n"
        "LDR     R0, [SP,#0x1C]\n"
        "MOV     R2, SP\n"
        "ADD     R1, SP, #0x10\n"
        "BL      sub_FFC94CB0    \n"
"loc_FFC952C4:\n"
        "LDR     R0, [SP,#0x1C]\n"
        "LDR     R2, [SP,#0xC]\n"
        "MOV     R1, R4\n"
        "BL      sub_FFC94F48    \n"
        "B       loc_FFC95530\n"
"loc_FFC952D8:\n"
        "LDR     R1, [R0,#0x7C]\n"
        "LDR     R12, [R0,#0x8C]\n"
        "ADD     R0, R0, #4\n"
        "MOV     R2, R4\n"
        "BLX     R12\n"
        "B       loc_FFC95530\n"
"loc_FFC952F0:\n"
        "CMP     R1, #0x22\n"
        "CMPNE   R1, #0x23\n"
        "BNE     loc_FFC9533C\n"
        "LDR     R1, [R0,#0x7C]\n"
        "ADD     R1, R1, R1,LSL#1\n"
        "ADD     R1, R0, R1,LSL#2\n"
        "SUB     R1, R1, #8\n"
        "LDMIA   R1, {R2-R4}\n"
        "STMIA   R6, {R2-R4}\n"
        "BL      sub_FFC92E84    \n"
        "LDR     R0, [SP,#0x1C]\n"
        "LDR     R1, [R0,#0x7C]\n"
        "LDR     R3, [R0,#0x8C]\n"
        "LDR     R2, [R0,#0x90]\n"
        "ADD     R0, R0, #4\n"
        "BLX     R3\n"
        "LDR     R0, [SP,#0x1C]\n"
        "BL      sub_FFC93178    \n"
        "B       loc_FFC95530\n"
"loc_FFC9533C:\n"
        "ADD     R1, R0, #4\n"
        "LDMIA   R1, {R2,R3,R12}\n"
        "STMIA   R6, {R2,R3,R12}\n"
        "LDR     R1, [R0]\n"
        "CMP     R1, #0x25\n"
        "ADDLS   PC, PC, R1,LSL#2\n"
        "B       loc_FFC95510\n"
"loc_FFC95358:\n"
        "B       loc_FFC953F0\n"
"loc_FFC9535C:\n"
        "B       loc_FFC953F0\n"
"loc_FFC95360:\n"
        "B       loc_FFC953F8\n"
"loc_FFC95364:\n"
        "B       loc_FFC95400\n"
"loc_FFC95368:\n"
        "B       loc_FFC95400\n"
"loc_FFC9536C:\n"
        "B       loc_FFC95400\n"
"loc_FFC95370:\n"
        "B       loc_FFC953F0\n"
"loc_FFC95374:\n"
        "B       loc_FFC953F8\n"
"loc_FFC95378:\n"
        "B       loc_FFC95400\n"
"loc_FFC9537C:\n"
        "B       loc_FFC95400\n"
"loc_FFC95380:\n"
        "B       loc_FFC95418\n"
"loc_FFC95384:\n"
        "B       loc_FFC95418\n"
"loc_FFC95388:\n"
        "B       loc_FFC95504\n"
"loc_FFC9538C:\n"
        "B       loc_FFC9550C\n"
"loc_FFC95390:\n"
        "B       loc_FFC9550C\n"
"loc_FFC95394:\n"
        "B       loc_FFC9550C\n"
"loc_FFC95398:\n"
        "B       loc_FFC9550C\n"
"loc_FFC9539C:\n"
        "B       loc_FFC95510\n"
"loc_FFC953A0:\n"
        "B       loc_FFC95510\n"
"loc_FFC953A4:\n"
        "B       loc_FFC95510\n"
"loc_FFC953A8:\n"
        "B       loc_FFC95510\n"
"loc_FFC953AC:\n"
        "B       loc_FFC95510\n"
"loc_FFC953B0:\n"
        "B       loc_FFC95510\n"
"loc_FFC953B4:\n"
        "B       loc_FFC95408\n"
"loc_FFC953B8:\n"
        "B       loc_FFC95410\n"
"loc_FFC953BC:\n"
        "B       loc_FFC95410\n"
"loc_FFC953C0:\n"
        "B       loc_FFC95424\n"
"loc_FFC953C4:\n"
        "B       loc_FFC95424\n"
"loc_FFC953C8:\n"
        "B       loc_FFC9542C\n"
"loc_FFC953CC:\n"
        "B       loc_FFC9545C\n"
"loc_FFC953D0:\n"
        "B       loc_FFC9548C\n"
"loc_FFC953D4:\n"
        "B       loc_FFC954BC\n"
"loc_FFC953D8:\n"
        "B       loc_FFC954EC\n"
"loc_FFC953DC:\n"
        "B       loc_FFC954EC\n"
"loc_FFC953E0:\n"
        "B       loc_FFC95510\n"
"loc_FFC953E4:\n"
        "B       loc_FFC95510\n"
"loc_FFC953E8:\n"
        "B       loc_FFC954F4\n"
"loc_FFC953EC:\n"
        "B       loc_FFC954FC\n"
"loc_FFC953F0:\n"
        "BL      sub_FFC91C8C\n"
        "B       loc_FFC95510\n"
"loc_FFC953F8:\n"
        "BL      sub_FFC91F10\n"
        "B       loc_FFC95510\n"
"loc_FFC95400:\n"
        "BL      sub_FFC92118\n"
        "B       loc_FFC95510\n"
"loc_FFC95408:\n"
        "BL      sub_FFC92390\n"
        "B       loc_FFC95510\n"
"loc_FFC95410:\n"
        "BL      sub_FFC92588\n"
        "B       loc_FFC95510\n"
"loc_FFC95418:\n"
		//; jumptable FFC953A0 entries 10,11
        //"BL      sub_FFC92844\n"
		"BL      sub_FFC92844_my\n"  //----------------------->
        "MOV     R4, #0\n"
        "B       loc_FFC95510\n"
"loc_FFC95424:\n"
        "BL      sub_FFC92984\n"
        "B       loc_FFC95510\n"
"loc_FFC9542C:\n"
        "LDRH    R1, [R0,#4]\n"
        "STRH    R1, [SP,#0x10]\n"
        "LDRH    R1, [R5,#2]\n"
        "STRH    R1, [SP,#0x12]\n"
        "LDRH    R1, [R5,#4]\n"
        "STRH    R1, [SP,#0x14]\n"
        "LDRH    R1, [R5,#6]\n"
        "STRH    R1, [SP,#0x16]\n"
        "LDRH    R1, [R0,#0xC]\n"
        "STRH    R1, [SP,#0x18]\n"
        "BL      sub_FFC96374    \n"
        "B       loc_FFC95510\n"
"loc_FFC9545C:\n"
        "LDRH    R1, [R0,#4]\n"
        "STRH    R1, [SP,#0x10]\n"
        "LDRH    R1, [R5,#2]\n"
        "STRH    R1, [SP,#0x12]\n"
        "LDRH    R1, [R5,#4]\n"
        "STRH    R1, [SP,#0x14]\n"
        "LDRH    R1, [R5,#6]\n"
        "STRH    R1, [SP,#0x16]\n"
        "LDRH    R1, [R5,#8]\n"
        "STRH    R1, [SP,#0x18]\n"
        "BL      sub_FFC964E0    \n"
        "B       loc_FFC95510\n"
"loc_FFC9548C:\n"
        "LDRH    R1, [R5]\n"
        "STRH    R1, [SP,#0x10]\n"
        "LDRH    R1, [R0,#6]\n"
        "STRH    R1, [SP,#0x12]\n"
        "LDRH    R1, [R5,#4]\n"
        "STRH    R1, [SP,#0x14]\n"
        "LDRH    R1, [R5,#6]\n"
        "STRH    R1, [SP,#0x16]\n"
        "LDRH    R1, [R5,#8]\n"
        "STRH    R1, [SP,#0x18]\n"
        "BL      sub_FFC9658C    \n"
        "B       loc_FFC95510\n"
"loc_FFC954BC:\n"
        "LDRH    R1, [R5]\n"
        "STRH    R1, [SP,#0x10]\n"
        "LDRH    R1, [R5,#2]\n"
        "STRH    R1, [SP,#0x12]\n"
        "LDRH    R1, [R5,#4]\n"
        "STRH    R1, [SP,#0x14]\n"
        "LDRH    R1, [R5,#6]\n"
        "STRH    R1, [SP,#0x16]\n"
        "LDRH    R1, [R0,#0xC]\n"
        "STRH    R1, [SP,#0x18]\n"
        "BL      sub_FFC9662C    \n"
        "B       loc_FFC95510\n"
"loc_FFC954EC:\n"
        "BL      sub_FFC92CDC\n"
        "B       loc_FFC95510\n"
"loc_FFC954F4:\n"
        "BL      sub_FFC9327C\n"
        "B       loc_FFC95510\n"
"loc_FFC954FC:\n"
        "BL      sub_FFC934B8\n"
        "B       loc_FFC95510\n"
"loc_FFC95504:\n"
        "BL      sub_FFC93634\n"
        "B       loc_FFC95510\n"
"loc_FFC9550C:\n"
        "BL      sub_FFC937D0\n"
"loc_FFC95510:\n"
        "LDR     R0, [SP,#0x1C]\n"
        "LDR     R1, [R0,#0x7C]\n"
        "LDR     R3, [R0,#0x8C]\n"
        "LDR     R2, [R0,#0x90]\n"
        "ADD     R0, R0, #4\n"
        "BLX     R3\n"
        "CMP     R4, #1\n"
        "BNE     loc_FFC95578\n"
"loc_FFC95530:\n"
        "LDR     R0, [SP,#0x1C]\n"
        "MOV     R2, #0xC\n"
        "LDR     R1, [R0,#0x7C]\n"
        "ADD     R1, R1, R1,LSL#1\n"
        "ADD     R0, R0, R1,LSL#2\n"
        "SUB     R4, R0, #8\n"
        "LDR     R0, =0x3DA50\n"
        "ADD     R1, SP, #0x10\n"
        "BL      sub_FFE8D51C\n"
        "LDR     R0, =0x3DA5C\n"
        "MOV     R2, #0xC\n"
        "ADD     R1, SP, #0x10\n"
        "BL      sub_FFE8D51C\n"
        "LDR     R0, =0x3DA68\n"
        "MOV     R2, #0xC\n"
        "MOV     R1, R4\n"
        "BL      sub_FFE8D51C\n"
        "B       loc_FFC955F0\n"
"loc_FFC95578:\n"
        "LDR     R0, [SP,#0x1C]\n"
        "LDR     R0, [R0]\n"
        "CMP     R0, #0xB\n"
        "BNE     loc_FFC955C0\n"
        "MOV     R3, #0\n"
        "STR     R3, [SP]\n"
        "MOV     R3, #1\n"
        "MOV     R2, #1\n"
        "MOV     R1, #1\n"
        "MOV     R0, #0\n"
        "BL      sub_FFC91A94\n"
        "MOV     R3, #0\n"
        "STR     R3, [SP]\n"
        "MOV     R3, #1\n"
        "MOV     R2, #1\n"
        "MOV     R1, #1\n"
        "MOV     R0, #0\n"
        "B       loc_FFC955EC\n"
"loc_FFC955C0:\n"
        "MOV     R3, #1\n"
        "MOV     R2, #1\n"
        "MOV     R1, #1\n"
        "MOV     R0, #1\n"
        "STR     R3, [SP]\n"
        "BL      sub_FFC91A94\n"
        "MOV     R3, #1\n"
        "MOV     R2, #1\n"
        "MOV     R1, #1\n"
        "MOV     R0, #1\n"
        "STR     R3, [SP]\n"
"loc_FFC955EC:\n"
        "BL      sub_FFC91BD4\n"
"loc_FFC955F0:\n"
        "LDR     R0, [SP,#0x1C]\n"
        "BL      sub_FFC96300    \n"
        "B       loc_FFC95018\n"

  );
}

void __attribute__((naked,noinline)) sub_FFC92844_my(){
 asm volatile(
        "STMFD   SP!, {R4-R8,LR}\n"
        "LDR     R7, =0x3A24\n"
        "MOV     R4, R0\n"
        "LDR     R0, [R7,#0x1C]\n"
        "MOV     R1, #0x3E\n"
        "BL      sub_FFC28C18\n"
        "LDRSH   R0, [R4,#4]\n"
        "MOV     R2, #0\n"
        "MOV     R1, #0\n"
        "BL      sub_FFC917F8\n"
        "MOV     R6, R0\n"
        "LDRSH   R0, [R4,#6]\n"
        "BL      sub_FFC91908\n"
        "LDRSH   R0, [R4,#8]\n"
        "BL      sub_FFC91960\n"
        "LDRSH   R0, [R4,#0xA]\n"
        "BL      sub_FFC919B8\n"
        "LDRSH   R0, [R4,#0xC]\n"
        "MOV     R1, #0\n"
        "BL      sub_FFC91A10\n"
        "MOV     R5, R0\n"
        "LDR     R0, [R4]\n"
        "LDR     R8, =0x3DA68\n"
        "CMP     R0, #0xB\n"
        "MOVEQ   R6, #0\n"
        "MOVEQ   R5, #0\n"
        "BEQ     loc_FFC928D8\n"
        "CMP     R6, #1\n"
        "BNE     loc_FFC928D8\n"
        "LDRSH   R0, [R4,#4]\n"
        "LDR     R1, =0xFFC91764\n"
        "MOV     R2, #2\n"
        "BL      sub_FFD0C7D0    \n"
        "STRH    R0, [R4,#4]\n"
        "MOV     R0, #0\n"
        "STR     R0, [R7,#0x28]\n"
        "B       loc_FFC928E0\n"
"loc_FFC928D8:\n"
        "LDRH    R0, [R8]\n"
        "STRH    R0, [R4,#4]\n"
"loc_FFC928E0:\n"
        "CMP     R5, #1\n"
        "LDRNEH  R0, [R8,#8]\n"
        "BNE     loc_FFC928FC\n"
        "LDRSH   R0, [R4,#0xC]\n"
        "LDR     R1, =0xFFC917E8\n"
        "MOV     R2, #0x20\n"
        "BL      sub_FFC96330\n"
"loc_FFC928FC:\n"
        "STRH    R0, [R4,#0xC]\n"
        "LDRSH   R0, [R4,#6]\n"
        //"BL      sub_FFC8483C    \n"
		"BL      sub_FFC8483C_my    \n"
        "LDRSH   R0, [R4,#8]\n"
        "MOV     R1, #1\n"
        "BL      sub_FFC84FA8    \n"
        "MOV     R1, #0\n"
        "ADD     R0, R4, #8\n"
        "BL      sub_FFC85030    \n"
        "LDRSH   R0, [R4,#0xE]\n"
        "BL      sub_FFC8CAF0    \n"
        "LDR     R4, =0xBB8\n"
        "CMP     R6, #1\n"
        "BNE     loc_FFC92954\n"
        "LDR     R0, [R7,#0x1C]\n"
        "MOV     R2, R4\n"
        "MOV     R1, #2\n"
        "BL      sub_FFC28B24    \n"
        "TST     R0, #1\n"
        "LDRNE   R1, =0x5A3\n"
        "LDRNE   R0, =0xFFC91DE4\n"
        "BLNE    sub_FFC0F5E8\n"
"loc_FFC92954:\n"
        "CMP     R5, #1\n"
        "LDMNEFD SP!, {R4-R8,PC}\n"
        "LDR     R0, [R7,#0x1C]\n"
        "MOV     R2, R4\n"
        "MOV     R1, #0x20\n"
        "BL      sub_FFC28B24    \n"
        "TST     R0, #1\n"
        "LDRNE   R1, =0x5A8\n"
        "LDRNE   R0, =0xFFC91DE4\n"
        "LDMNEFD SP!, {R4-R8,LR}\n"
        "BNE     sub_FFC0F5E8\n"
        "LDMFD   SP!, {R4-R8,PC}\n"
  );
}

void __attribute__((naked,noinline)) sub_FFC8483C_my(){
 asm volatile(
        "STMFD   SP!, {R4-R6,LR}\n"
        "LDR     R5, =0x3718\n"
        "MOV     R4, R0\n"
        "LDR     R0, [R5,#4]\n"
        "CMP     R0, #1\n"
        "LDRNE   R1, =0x146\n"
        "LDRNE   R0, =0xFFC84640\n"
        "BLNE    sub_FFC0F5E8\n"
        "CMN     R4, #0xC00\n"
        "LDREQSH R4, [R5,#2]\n"
        "CMN     R4, #0xC00\n"
        "MOVEQ   R1, #0x14C\n"
        "LDREQ   R0, =0xFFC84640\n"
        "STRH    R4, [R5,#2]\n"
        "BLEQ    sub_FFC0F5E8\n"
        "MOV     R0, R4\n"
        //"BL      sub_FFD8803C\n"
		 "BL      apex2us\n"  // +

        "MOV     R4, R0\n"
        "BL      sub_FFCB7520\n"
        "MOV     R0, R4\n"
        "BL      sub_FFCBBBB0\n"
        "TST     R0, #1\n"
        "LDRNE   R1, =0x151\n"
        "LDMNEFD SP!, {R4-R6,LR}\n"
        "LDRNE   R0, =0xFFC84640\n"
        "BNE     sub_FFC0F5E8\n"
        "LDMFD   SP!, {R4-R6,PC}\n"
  );
}
