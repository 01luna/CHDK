#include "conf.h"
#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

void change_video_tables(int a, int b){
}


void  set_quality(int *x){ // -17 highest; +12 lowest
 if (conf.video_mode) *x=12-((conf.video_quality-1)*(12+17)/(99-1));
}

// ASM1989, rereview 19.09.10 FF986650
void __attribute__((naked,noinline)) movie_record_task(){
 asm volatile(
"		STMFD	SP!, {R2-R10,LR}\n"
"		LDR     R10, =0x5EE\n" // not in 100F
"		LDR	R9, =0x2710\n"
"		LDR	R7, =0xFF98580C\n" //nullsub_357


//looks like it is the one to work with?
//"		LDR	R6, =0xFF986044\n" //__MovieRecorder.c__0 ;	LOCATION: MovieRecorder.c:0
"		LDR	R6, =sub_FF986044_my\n" //__MovieRecorder.c__0 ;	LOCATION: MovieRecorder.c:0

"		LDR	R4, =0x7898\n" //diferent order in 100F
"		MOV	R8, #1\n"  //diferent order in 100F
"		MOV	R5, #0\n"
"loc_FF986670:\n"
"		LDR	R0, [R4,#0x24]\n"
"		MOV	R2, #0\n"
"		ADD	R1, SP,	#0x4\n"
"		BL	sub_FF83AE20\n"  //__KerQueue.c__0 ; LOCATION: KerQueue.c:0
"		LDR	R0, [R4,#0x2C]\n"
"		CMP	R0, #0\n"
"		LDRNE	R0, [R4,#0xC]\n"
"		CMPNE	R0, #2\n"
"		LDRNE	R0, [R4,#0x44]\n"
"		CMPNE	R0, #6\n"
"		BNE	loc_FF986794\n"
"		LDR	R0, [SP,#0x4]\n"
"		LDR	R1, [R0]\n"
"		SUB	R1, R1,	#2\n"
"		CMP	R1, #0xA\n"
"		ADDLS	PC, PC,	R1,LSL#2\n"
"		B	loc_FF986794\n"
"loc_FF9866B4:\n"
"		B	loc_FF986744\n"
"loc_FF9866B8:\n"
"		B	loc_FF986768\n"
"loc_FF9866BC:\n"
"		B	loc_FF986778\n"
"loc_FF9866C0:\n"
"		B	loc_FF986780\n"
"loc_FF9866C4:\n"
"		B	loc_FF98674C\n"
"loc_FF9866C8:\n"
"		B	loc_FF986788\n"
"loc_FF9866CC:\n"
"		B	loc_FF986758\n"
"loc_FF9866D0:\n"
"		B	loc_FF986794\n"
"loc_FF9866D4:\n"
"		B	loc_FF986790\n"
"loc_FF9866D8:\n"
"		B	loc_FF986710\n"
"loc_FF9866DC:\n"
"		B	loc_FF9866E0\n"
"loc_FF9866E0:\n"
"		STR	R5, [R4,#0x40]\n"
"		STR	R5, [R4,#0x30]\n"
"		STR	R5, [R4,#0x34]\n"
"		STRH	R5, [R4,#6]\n"
"		STR	R6, [R4,#0xCC]\n"
"		STR	R7, [R4,#0xB4]\n"
"		LDR	R0, [R4,#0xC]\n"
"		ADD	R0, R0,	#1\n"
"		STR	R0, [R4,#0xC]\n"
"		MOV	R0, #6\n"
"		STR	R0, [R4,#0x44]\n"
"		B	loc_FF986730\n"
"loc_FF986710:\n"
"		STR	R5, [R4,#0x40]\n"
"		STR	R5, [R4,#0x30]\n"
"		STR	R6, [R4,#0xCC]\n"
"		STR	R7, [R4,#0xB4]\n"
"		LDR	R0, [R4,#0xC]\n"
"		ADD	R0, R0,	#1\n"
"		STR	R0, [R4,#0xC]\n"
"		STR	R8, [R4,#0x44]\n"
"loc_FF986730:\n"
"		LDR	R2, =0xFF984FE0\n"
"		LDR	R1, =0xB0300\n"
"		LDR	R0, =0xFF9850F4\n"
"		BL	sub_FF853088\n"
"		B	loc_FF986794\n"
"loc_FF986744:\n"
  //     "BL      unlock_optical_zoom\n" 		  -----------> inserted to unlock the zoom, dont need in sx210
"		BL	sub_FF985D20\n" //__MovieRecorder.c__0
"		B	loc_FF986794\n"
"loc_FF98674C:\n"
"		LDR	R1, [R4,#0xCC]\n"
"		BLX	R1\n"
"		B	loc_FF986794\n"
"loc_FF986758:\n"
"		LDR	R1, [R0,#0x18]\n"
"		LDR	R0, [R0,#4]\n"
"		BL	sub_FFAD9B40\n" //__MovWriter.c__0 ;	LOCATION: MovWriter.c:0
"		B	loc_FF986794\n"
"loc_FF986768:\n"
"		LDR	R0, [R4,#0x44]\n"
"		CMP	R0, #5\n"
"		STRNE	R8, [R4,#0x34]\n"
"		B	loc_FF986794\n"
"loc_FF986778:\n"
"		BL	sub_FF9854B8\n"  //__MovieRecorder.c__1000
"		B	loc_FF986794\n"
"loc_FF986780:\n"
"		BL	sub_FF985140\n"  //__MovieRecorder.c__0
"		B	loc_FF986794\n"
"loc_FF986788:\n"
"		BL	sub_FF984F6C\n"  //__MovieRecorder.c__100
"		B	loc_FF986794\n"
"loc_FF986790:\n"
"		BL	sub_FF986B90\n"  //__MovieRecorder.c__100
"loc_FF986794:\n"
"		LDR	R1, [SP,#0x4]\n"
"		LDR	R3, =0xFF984C34\n"  //aMovierecorder_c  ,changed order in 100D
//"		MOV	R3, #0x5F0\n"  //Not present in 100D
"		STR	R5, [R1]\n"
"		STR	R3, [SP]\n"
"		LDR	R0, [R4,#0x28]\n"
"		MOV	R2, R9\n"
"		BL	sub_FF83B774\n"
"		B	loc_FF986670\n"

 );
}  //asm1989 14.11.10 done

void __attribute__((naked,noinline)) sub_FF986044_my(){      // in sx200:sub_FF937C70_my
 asm volatile(
"		STMFD	SP!, {R4-R11,LR}\n"
"		SUB	SP, SP,	#0x64\n"
"		MOV	R8, #0\n"
"		LDR	R7, =0x7898\n"
"		STR	R8, [SP,#0x54]\n"
"		STR	R8, [SP,#0x4C]\n"
"		STR	R8, [R7,#0xB8]\n"
"		STR	R8, [R7,#0xBC]\n"
"		STR	R8, [R7,#0xC0]\n"
"		MOV	R4, R0\n"
"		STR	R8, [R7,#0xC4]\n"
"		LDR	R0, [R7,#0x44]\n"
"		MOV	R9, #0\n"
"		CMP	R0, #3\n"
"		MOVEQ	R0, #4\n"
"		STREQ	R0, [R7,#0x44]\n"
"		LDR	R0, [R7,#0xB4]\n"
"		MOV	R6, #0\n"
"		MOV	R5, #1\n"
"		BLX	R0\n"
"		LDR	R0, [R7,#0x44]\n"
"		CMP	R0, #6\n"
"		BEQ	loc_FF9860B4\n"
//ASM_SAFE("BL blink\n")
"		LDR	R1, [R7,#0xC]\n"
"		CMP	R1, #2\n"
"		BNE	loc_FF9860DC\n"
"		CMP	R0, #5\n"
"		BEQ	loc_FF9860EC\n"
"loc_FF9860B4:\n"
"		MOV	R6, #1\n"
"		ADD	R3, SP,	#0x34\n"
"		LDR	R2, =0xFF985F24\n"  //"		ADR	R2, sub_FF985F24\n"
"		LDR	R1, =0xFF985F84\n"
"		LDR	R0, =0xFF985FE4\n"
"		BL	sub_FF853E48\n"
"		LDR	R0, [R7,#0x44]\n"
"		CMP	R0, #4\n"
"		MOVNE	R5, #0\n"
"		B	loc_FF9860FC\n"
"loc_FF9860DC:\n"
"		CMP	R0, #4\n"
"		BEQ	loc_FF9860FC\n"
"		CMP	R1, #2\n"
"		BNE	loc_FF9860F4\n"
"loc_FF9860EC:\n"
"		MOV	R0, #0\n"
"		BL	sub_FF853E54\n"
"loc_FF9860F4:\n"
"		ADD	SP, SP,	#0x64\n"
"		LDMFD	SP!, {R4-R11,PC}\n"
"loc_FF9860FC:\n"
"		LDRH	R0, [R7,#6]\n"
"		CMP	R0, #1\n"
"		LDREQ	R1, =0x807\n"  // 100f  809
"		LDREQ	R0, =0xFF984C34\n" //aMovierecorder_c
"		BLEQ	sub_FF81EB78\n" //DebugAssert
"		LDRH	R0, [R7,#6]\n"
"		CMP	R0, #3\n"
"		BNE	loc_FF986130\n"
"		LDR	R0, [R7,#0x6C]\n"
"		LDR	R1, [R7,#0xC8]\n"
"		BL	sub_FFB89AB8\n"
"		CMP	R1, #0\n"
"		MOVNE	R5, #0\n"
"loc_FF986130:\n"
"		LDR	R0, [R7,#0x44]\n"
"		CMP	R0, #6\n"
"		CMPNE	R0, #1\n"
"		CMPNE	R0, #3\n"
"		BNE	loc_FF986174\n"
"		CMP	R6, #1\n"
"		CMPEQ	R5, #0\n"
"		BNE	loc_FF986174\n"
"		BL	sub_FF853E4C\n"
"		LDR	R0, [R7,#0x18]\n"
"		MOV	R1, #0x3E8\n"
"		BL	sub_FF83B23C\n" //TakeSemaphore
"		CMP	R0, #9\n"
"		BNE	loc_FF986584\n"
"		MOV	R0, #0x90000\n"
"		BL	sub_FF89C95C\n" //HardwareDefect
"		B	loc_FF9860F4\n"
"loc_FF986174:\n"
"		CMP	R5, #1\n"
"		MOV	R10, #1\n"
"		BNE	loc_FF98619C\n"
"		ADD	R3, SP,	#0x4C\n"
"		ADD	R2, SP,	#0x50\n"
"		ADD	R1, SP,	#0x54\n"
"		ADD	R0, SP,	#0x58\n"
"		BL	sub_FFAD9C68\n"  //__MovWriter.c__0 ;	LOCATION: MovWriter.c:0
"		MOVS	R9, R0\n"
"		BNE	loc_FF9861B8\n"
"loc_FF98619C:\n"
"		LDR	R0, [R7,#0x34]\n"
"		CMP	R0, #1\n"
"		BNE	loc_FF9862F4\n"
"		LDR	R0, [R7,#0x6C]\n"
"		LDR	R1, [R7,#0x48]\n"
"		CMP	R0, R1\n"
"		BCC	loc_FF9862F4\n"
"loc_FF9861B8:\n"
"		MOV	R0, R9\n"
"		BL	sub_FF9859AC\n"
"		LDR	R0, [R7,#0xC]\n"
"		CMP	R0, #2\n"

//TESTING GOING BACK TO FIRMWARE HERE
//"B sub_FF9861C8\n"

"		BNE	loc_FF986228\n"
"		MOV	R1, #0\n"
"		LDR	R0, =0xFF985F18\n" //"		ADR	R0, =0xFF985F18\n"
"		BL	sub_FFA8E1B0\n"
"		LDR	R2, [R7,#0x64]\n"
"		ADD	R3, SP,	#0x5C\n"
"		STRD	R2, [SP,#0x28]\n"
"		MOV	R2, #0x18\n"
"		ADD	R1, SP,	#0x34\n"
"		ADD	R0, SP,	#0x10\n"
"		BL	sub_FFB87458\n"
"		LDR	R1, [R7,#0x84]\n"
"		LDR	R2, [R7,#0x88]\n"
//"		MVN	R3, #0xFFFFFFFE\n"  //"		MOVL	R3, 0xFFFFFFFE\n"
"		MVN	R3, #01\n"  //"		MOVL	R3, 0xFFFFFFFE\n"
"		ADD	R0, SP,	#0x60\n"
"		STMEA	SP, {R0-R3}\n"
"		LDR	R0, =0xB0348\n"
"		MOV	R3, #0\n"
"		MOV	R2, #0\n"
"		MOV	R1, #0x40\n"
"		BL	sub_FFA8E108\n"
"		B	loc_FF98627C\n"
"loc_FF986220:\n"
"		MOV	R1, #1\n"
"		B	loc_FF986508\n"
"loc_FF986228:\n"
"		BL	loc_FF986C60\n"
"		LDR	R2, [R7,#0x64]\n"
"		ADD	R3, SP,	#0x5C\n"
//"		MVN	R1, #0xFFFFFFFE\n"  // "		MOVL	R1, 0xFFFFFFFE\n"
"		MVN	R1, #01\n"  //"		MOVL	R3, 0xFFFFFFFE\n"
"		MOV	R0, #0\n"
"		ADD	R5, SP,	#0x1C\n"
"		STMIA	R5, {R0-R3}\n"
"		LDR	R3, [R4,#0x1C]\n"
"		LDR	R1, [R7,#0x84]\n"
"		LDR	R2, [R7,#0x88]\n"
"		ADD	R4, SP,	#0xC\n"
"		ADD	R0, SP,	#0x60\n"
"		STMIA	R4, {R0-R3}\n"
"		MOV	R3, #0\n"
"		MOV	R1, #0x40\n"
"		MOV	R2, #0\n"
"		STMEA	SP, {R1-R3}\n"
"		LDR	R3, =0xB0348\n"
"		MOV	R1, #0\n"
"		MOV	R0, #0\n"
"		BL	sub_FFA8CBB8\n"

"loc_FF98627C:\n"
"		LDR	R0, [R7,#0x18]\n"
"		LDR	R1, [R7,#0x60]\n"
"		BL	sub_FF83B23C\n" //TakeSemaphore
"		CMP	R0, #9\n"
"		BEQ	loc_FF986220\n"
"		LDR	R0, [SP,#0x5C]\n"
"		CMP	R0, #0\n"
"		BEQ	loc_FF9862A4\n"

"loc_FF98629C:\n"
"		MOV	R1, #1\n"
"		B	loc_FF986520\n"

"loc_FF9862A4:\n"
"		LDR	R0, [R7,#0xC]\n"
"		MOV	R4, #5\n"
"		CMP	R0, #2\n"
"		MOV	R0, #1\n"
"		BNE	loc_FF9862E0\n"
"		BL	sub_FFA8E170\n"
"		BL	sub_FFA8E198\n"
"		MOV	R0, #0\n"
"		BL	sub_FF853E54\n"
"		BL	sub_FF853E64\n"
"		STR	R4, [R7,#0x44]\n"
"		BL	loc_FF986C60\n"
"		BL	sub_FF853EC0\n"
"		STR	R10, [R7,#0x44]\n"
"		B	loc_FF9862EC\n"
"loc_FF9862E0:\n"
"		BL	sub_FFA8CC6C\n"
"		BL	sub_FFA8CCCC\n"
"		STR	R4, [R7,#0x44]\n"
"loc_FF9862EC:\n"
"		STR	R8, [R7,#0x34]\n"
"		B	loc_FF9860F4\n"
"loc_FF9862F4:\n"
"		CMP	R5, #1\n"
"		BNE	loc_FF98657C\n"
"		STR	R10, [R7,#0x38]\n"
"		LDR	R0, [R7,#0x6C]\n"
"		LDR	R11, [R4,#0xC]\n"
"		CMP	R0, #0\n"
"		LDRNE	R9, [SP,#0x58]\n"
"		LDRNE	R10, [SP,#0x54]\n"
"		BNE	loc_FF986440\n"
"		LDR	R0, [R7,#0xC]\n"
"		CMP	R0, #2\n"
"		BNE	loc_FF986398\n"
"		LDR	R0, =0xFF985F18\n"
"		MOV	R1, #0\n"
"		BL	sub_FFA8E1B0\n"
"		LDR	R2, [R7,#0x64]\n"
"		ADD	R3, SP,	#0x5C\n"
"		STRD	R2, [SP,#0x28]\n"
"		MOV	R2, #0x18\n"
"		ADD	R1, SP,	#0x34\n"
"		ADD	R0, SP,	#0x10\n"
"		BL	sub_FFB87458\n"
"		LDR	R1, [R7,#0x84]\n"
"		LDR	R2, [R7,#0x88]\n"
"		MVN	R3, #0\n"  // "		MOVL	R3, 0xFFFFFFFF\n"
"		ADD	R0, SP,	#0x60\n"
"		STMEA	SP, {R0-R3}\n"
"		LDR	R0, [SP,#0x58]\n"
"		LDR	R1, [SP,#0x54]\n"
"		LDR	R2, [SP,#0x50]\n"
"		LDR	R3, [SP,#0x4C]\n"
"		BL	sub_FFA8E10C\n"
"		LDR	R0, [R7,#0x18]\n"
"		LDR	R1, [R7,#0x60]\n"
"		BL	sub_FF83B23C\n" //TakeSemaphore
"		CMP	R0, #9\n"
"		BEQ	loc_FF986220\n"
"		LDR	R0, =0xFF9858E8\n"
"		MOV	R1, #0\n"
"		BL	sub_FFA8E1B0\n"
"		B	loc_FF986400\n"
"loc_FF986398:\n"
"		LDR	R0, [R4,#0x20]\n"
"		LDR	R2, [R7,#0x64]\n"
"		ADD	R3, SP,	#0x5C\n"
"		MVN	R1, #0\n"  // "		MOVL	R1, 0xFFFFFFFF\n"
"		ADD	R9, SP,	#0x1C\n"
"		STMIA	R9, {R0-R3}\n"
"		LDR	R3, [R4,#0x1C]\n"
"		LDR	R1, [R7,#0x84]\n"
"		LDR	R2, [R7,#0x88]\n"
"		ADD	R0, SP,	#0x60\n"
"		ADD	R9, SP,	#0xC\n"
"		STMIA	R9, {R0-R3}\n"
"		LDR	R1, [SP,#0x50]\n"
"		LDR	R2, [SP,#0x54]\n"
"		LDR	R3, [SP,#0x4C]\n"
"		STMFA	SP, {R1,R3}\n"
"		STR	R2, [SP]\n"
"		LDMIB	R4, {R0,R1}\n"
"		LDR	R3, [SP,#0x58]\n"
"		MOV	R2, R11\n"
"		BL	sub_FFA8CBB8\n"
"		LDR	R0, [R7,#0x18]\n"
"		LDR	R1, [R7,#0x60]\n"
"		BL	sub_FF83B23C\n" //TakeSemaphore
"		CMP	R0, #9\n"
"		BEQ	loc_FF986220\n"
"loc_FF986400:\n"
"		LDR	R0, [SP,#0x5C]\n"
"		CMP	R0, #0\n"
"		BNE	loc_FF98629C\n"
"		LDR	R0, [R7,#0xC]\n"
"		CMP	R0, #2\n"
"		MOV	R0, #1\n"
"		BNE	loc_FF986424\n"
"		BL	sub_FFA8E170\n"
"		B	loc_FF986428\n"
"loc_FF986424:\n"
"		BL	sub_FFA8CC6C\n"
"loc_FF986428:\n"
"		STR	R8, [R7,#0xC4]\n"
"		LDR	R0, [SP,#0x60]\n"
"		LDR	R1, [SP,#0x58]\n"
"		ADD	R9, R1,	R0\n"
"		LDR	R1, [SP,#0x54]\n"
"		SUB	R10, R1, R0\n"
"loc_FF986440:\n"
"		LDR	R0, [R7,#0xC]\n"
"		LDR	R2, [R7,#0x64]\n"
"		CMP	R0, #2\n"
"		ADD	R3, SP,	#0x5C\n"
"		BNE	loc_FF986498\n"
"		STRD	R2, [SP,#0x28]\n"
"		MOV	R2, #0x18\n"
"		ADD	R1, SP,	#0x34\n"
"		ADD	R0, SP,	#0x10\n"
"		BL	sub_FFB87458\n"
"		LDR	R1, [R7,#0x84]\n"
"		LDR	R2, [R7,#0x88]\n"
"		LDR	R3, [R7,#0x68]\n"
"		ADD	R0, SP,	#0x60\n"
"		STMEA	SP, {R0-R3}\n"
"		LDR	R2, [SP,#0x50]\n"
"		LDR	R3, [SP,#0x4C]\n"
"		MOV	R1, R10\n"
"		MOV	R0, R9\n"
"		BL	sub_FFA8E108\n"
"		BL	sub_FF853E4C\n"
"		B	loc_FF9864F0\n"
"loc_FF986498:\n"
"		LDR	R1, [R7,#0x68]\n"
"		LDR	R0, [R4,#0x20]\n"
"		STR	R1, [SP,#0x20]\n"
"		STR	R0, [SP,#0x1C]\n"
"		STR	R2, [SP,#0x24]\n"
"		STR	R3, [SP,#0x28]\n"
"		LDR	R3, [R4,#0x1C]\n"
"		LDR	R1, [R7,#0x84]\n"
"		LDR	R2, [R7,#0x88]\n"
"		ADD	R0, SP,	#0x60\n"
"		STR	R2, [SP,#0x14]\n"
"		LDR	R2, [SP,#0x50]\n"
"		STR	R1, [SP,#0x10]\n"
"		STR	R3, [SP,#0x18]\n"
"		LDR	R3, [SP,#0x4C]\n"
"		STR	R0, [SP,#0xC]\n"
"		STMFA	SP, {R2,R3}\n"
"		STR	R10, [SP]\n"
"		LDMIB	R4, {R0,R1}\n"
"		MOV	R3, R9\n"
"		MOV	R2, R11\n"
"		BL	sub_FFA8CBB8\n"
"loc_FF9864F0:\n"
"		LDR	R0, [R7,#0x18]\n"
"		LDR	R1, [R7,#0x60]\n"
"		BL	sub_FF83B23C\n" //TakeSemaphore
"		CMP	R0, #9\n"
"		BNE	loc_FF986510\n"
"		MOV	R1, #0\n"
"loc_FF986508:\n"
"		MOV	R0, #0x90000\n"
"		B	loc_FF986524\n"
"loc_FF986510:\n"
"		LDR	R0, [SP,#0x5C]\n"
"		CMP	R0, #0\n"
"		BEQ	loc_FF98652C\n"
"		MOV	R1, #0\n"
"loc_FF986520:\n"
"		MOV	R0, #0xA0000\n"
"loc_FF986524:\n"
"		BL	sub_FF985930\n"
"		B	loc_FF9860F4\n"
"loc_FF98652C:\n"
"		LDR	R0, [R7,#0xC]\n"
"		CMP	R0, #2\n"
"		MOV	R0, #0\n"
"		BNE	loc_FF986544\n"
"		BL	sub_FFA8E170\n"
"		B	loc_FF986548\n"
"loc_FF986544:\n"
"		BL	sub_FFA8CC6C\n"

// I think the patch shoud be here

"loc_FF986548:\n"
"		LDR	R0, [SP,#0x58]\n"
"		LDR	R1, [SP,#0x60]\n"
"		BL	sub_FFAD9EA0\n"  //__MovWriter.c__0 ;	LOCATION: MovWriter.c:0
"		LDR	R0, [R7,#0x68]\n"
"		LDR	R3, =0x7920\n"     	// ---> -
"		ADD	R1, R0,	#1\n"		//       |
"		STR	R1, [R7,#0x68]\n"	//       |
"		STR	R3, [SP]\n"			//       |
"		LDR	R0, [R7,#0x64]\n"	//       |
"		SUB	R3, R3,	#4\n"		// ---> -
"		AND	R2, R0,	#0xFF\n"	//       |
"		LDR	R0, [SP,#0x60]\n"	//       |
"		BL	sub_FFAD7A98\n"		//       |
								//       |
 "LDR     R0, =0x7920-4\n"      // -<---     // +
 "BL      set_quality\n"                     // +

"loc_FF98657C:\n"
"		CMP	R6, #1\n"
"		BNE	loc_FF986590\n"

"loc_FF986584:\n"
"		BL	sub_FF853E50\n"
"		MOV	R0, #1\n"
"		BL	sub_FF853E54\n"

"loc_FF986590:\n"
"		CMP	R5, #1\n"
"		LDRNEH	R0, [R7,#6]\n"
"		CMPNE	R0, #3\n"
"		BNE	loc_FF9860F4\n"
"		LDR	R0, [R7,#0x6C]\n"
"		ADD	R0, R0,	#1\n"
"		STR	R0, [R7,#0x6C]\n"
"		LDRH	R1, [R7,#6]\n"
"		CMP	R1, #3\n"
"		LDRNE	R1, [R7,#0x54]\n"
"		LDREQ	R1, =0x3E9\n"
"		MUL	R0, R1,	R0\n"
"		LDREQ	R1, =0x1770\n"
"		LDRNE	R1, [R7,#0x50]\n"
"		BL	sub_FFB89AB8\n"
"		MOV	R4, R0\n"
"		BL	sub_FFADA554\n"
"		LDR	R0, [R7,#0x8C]\n"
"		CMP	R0, R4\n"
"		BNE	loc_FF9865EC\n"
"		LDR	R0, [R7,#0x3C]\n"
"		CMP	R0, #1\n"
"		BNE	loc_FF986600\n"
"loc_FF9865EC:\n"
"		LDR	R1, [R7,#0x98]\n"
"		MOV	R0, R4\n"
"		BLX	R1\n"
"		STR	R4, [R7,#0x8C]\n"
"		STR	R8, [R7,#0x3C]\n"
"loc_FF986600:\n"
"		STR	R8, [R7,#0x38]\n"
"		B	loc_FF9860F4\n"

//Other stuff??? was at the end
"loc_FF986C60:\n"
"LDR     R0, =0xB0330\n"
"LDR     R0, [R0,#8]\n"
"CMP     R0, #0\n"
"BEQ     sub_FF984F6C\n" //__MovieRecorder.c__100
"BNE     sub_FF866E24\n"



 );
}











