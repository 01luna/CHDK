void __attribute__((naked,noinline)) init_file_modules_task(){
 asm volatile(
                "STMFD   SP!, {R4,LR}\n"
                "BL      _Unmount_FileSystem\n" // + 
                "BL      sub_FFB7F33C\n"
                "SUBS    R4, R0, #0\n"
                "MOV     R0, #0x5000\n"
                "MOV     R1, #0\n"
                "ADD     R0, R0, #6\n"
                "BEQ     loc_FF9E505C\n"
                "BL      sub_FF9B1A04\n"  // PostLogicalEventToUI
"loc_FF9E505C:\n"
                "BL      sub_FFB7F368_my\n"      //-------------->
                "MOV     R0, #0x5000\n"
                "CMP     R4, #0\n"
                "MOV     R1, R4\n"
                "ADD     R0, R0, #6\n"
                "LDMNEFD SP!, {R4,PC}\n"
                "LDMFD   SP!, {R4,LR}\n"
                "B       sub_FF9B1A04\n"  // PostLogicalEventToUI

 );
}

void __attribute__((naked,noinline)) sub_FFB7F368_my(){
 asm volatile(
                "STR     LR, [SP,#-4]!\n"
                "BL      Mount_FileSystem_my\n" // --------------->
                "LDR     R3, =0xC7E8\n"
                "LDR     R2, [R3]\n"
                "CMP     R2, #0\n"
                "BNE     loc_FFB7F3A4\n"
                "BL      sub_FFA12C00\n"
                "AND     R0, R0, #0xFF\n"
                "BL      sub_FF8363D4\n"
                "BL      sub_FFA12C00\n"
                "AND     R0, R0, #0xFF\n"
                "BL      sub_FF870664\n"
                "BL      sub_FFA12C10\n"
                "AND     R0, R0, #0xFF\n"
                "BL      sub_FF8364B0\n"
"loc_FFB7F3A4:\n"
                "LDR     R2, =0xC7E4\n"
                "MOV     R3, #1\n"
                "STR     R3, [R2]\n"
                "LDR     PC, [SP],#4\n"
 );
}

void __attribute__((naked,noinline)) Mount_FileSystem_my(){
 asm volatile(
                "STMFD   SP!, {R4-R6,LR}\n"
                "MOV     R5, #0\n"
                "LDR     R6, =0x2E3C0\n"
                "MOV     R0, R5\n"
                "BL      sub_FF87B85C\n"
                "LDR     R0, [R6,#0x38]\n"
                "BL      sub_FF87AF1C\n"
                "SUBS    R1, R0, #0\n"
                "MOV     R0, R5\n"
                "BNE     loc_FF87BEB4\n"
                "LDR     R3, =0x29A0\n"
                "LDR     R2, =0x2998\n"
                "STR     R1, [R3]\n"
                "LDR     R3, =0x299C\n"
                "STR     R1, [R2]\n"
                "STR     R1, [R3]\n"
"loc_FF87BEB4:\n"
                "BL      sub_FF87B8AC\n"
                "MOV     R0, R5\n"
                "BL      sub_FF87BBD4_my\n"    //--------------->
                "MOV     R4, R0\n"
                "MOV     R0, R5\n"
                "BL      sub_FF87BC5C\n"
                "AND     R4, R4, R0\n"
                "MOV     R2, R4\n"
                "MOV     R0, R6\n"
                "LDR     R1, [R6,#0x3C]\n"
                "BL      sub_FF87BE24\n"
                "STR     R0, [R6,#0x40]\n"
                "LDMFD   SP!, {R4-R6,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FF87BBD4_my(){
 asm volatile(
                "STMFD   SP!, {R4-R7,LR}\n"
                "LDR     R7, =0x299C\n"
                "LDR     R3, [R7]\n"
                "MOV     R4, R0\n"
                "CMP     R3, #0\n"
                "ADD     R3, R4, R4,LSL#1\n"
                "RSB     R3, R4, R3,LSL#3\n"
                "LDR     R6, =0x2E3F8\n"
                "MOV     R5, R3,LSL#2\n"
                "MOV     R1, R4\n"
                "BNE     loc_FF87BC48\n"
                "LDR     R0, [R6,R5]\n"
                "BL      sub_FF87B968_my\n"  //------------->
                "SUBS    R3, R0, #0\n"
                "MOV     R1, R4\n"
                "BEQ     loc_FF87BC20\n"
                "LDR     R0, [R6,R5]\n"
                "BL      sub_FF87BAB4\n"
                "MOV     R3, R0\n"
"loc_FF87BC20:\n"
                "CMP     R3, #0\n"
                "MOV     R0, R4\n"
                "BEQ     loc_FF87BC34\n"
                "BL      sub_FF87AFF4\n"
                "MOV     R3, R0\n"
"loc_FF87BC34:\n"
                "CMP     R3, #0\n"
                "MOV     R0, R3\n"
                "MOVNE   R3, #1\n"
                "STRNE   R3, [R7]\n"
                "LDMFD   SP!, {R4-R7,PC}\n"
"loc_FF87BC48:\n"
                "MOV     R0, #1\n"
                "LDMFD   SP!, {R4-R7,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FF87B968_my(){
 asm volatile(
                "STMFD   SP!, {R4-R8,LR}\n"
                "MOV     R5, R1\n"
                "MOV     R8, R5,LSL#1\n"
                "ADD     R3, R8, R5\n"
                "LDR     R2, =0x2E3FC\n"
                "SUB     SP, SP, #8\n"
                "RSB     R3, R5, R3,LSL#3\n"
                "LDR     R1, [R2,R3,LSL#2]\n"
                "MOV     R6, #0\n"
                "STR     R6, [SP]\n"
                "MOV     R7, R0\n"
                "STR     R6, [SP,#4]\n"
                "CMP     R1, #5\n"
                "LDRLS   PC, [PC,R1,LSL#2]\n"
                "B       loc_FF87BA64\n"
                ".long loc_FF87BA08\n"
                ".long loc_FF87B9BC\n"
                ".long loc_FF87B9BC\n"
                ".long loc_FF87B9BC\n"
                ".long loc_FF87B9BC\n"
                ".long loc_FF87BA54\n"
"loc_FF87B9BC:\n"
                "MOV     R0, #3\n"
                "MOV     R1, #0x200\n"
                "MOV     R2, #0\n"
                "BL      sub_FF812834\n"
                "SUBS    R6, R0, #0\n"
                "BEQ     loc_FF87BA98\n"
                "ADD     R12, R8, R5\n"
                "RSB     R12, R5, R12,LSL#3\n"
                "LDR     R4, =0x2E40C\n"
                "MOV     R0, R7\n"
                "MOV     R1, #0\n"
                "MOV     R2, #1\n"
                "MOV     R3, R6\n"
                "MOV     LR, PC\n"
                "LDR     PC, [R4,R12,LSL#2]\n"
                "CMP     R0, #1\n"
                "BNE     loc_FF87BA10\n"
                "MOV     R0, #3\n"
                "BL      sub_FF812904\n"
"loc_FF87BA08:\n"
                "MOV     R0, #0\n"
                "B       loc_FF87BA98\n"
"loc_FF87BA10:\n"
                "MOV     R0, R7\n"
                "BL      sub_FF88C3B0\n"
                "MOV     R1, R0\n"
                "ADD     R2, SP, #4\n"
                "MOV     R3, SP\n"
                "MOV     R0, R6\n"

                "STMFD   SP!, {R4-R11,LR}\n" // +
                "BL      mbr_read\n"    //-----------> 
                "LDMFD   SP!, {R4-R11,LR}\n" // +

          //    "BL      sub_FF87B0F8\n"  // original

                "MOV     R4, R0\n"
                "MOV     R0, #3\n"
                "BL      sub_FF812904\n"
                "CMP     R4, #0\n"
                "BNE     loc_FF87BA70\n"
                "MOV     R0, R7\n"
                "STR     R4, [SP,#4]\n"
                "BL      sub_FF88C3B0\n"
                "STR     R0, [SP]\n"
                "B       loc_FF87BA70\n"
"loc_FF87BA54:\n"
                "MOV     R3, #0\n"
                "MOV     R2, #0x40\n"
                "STMEA   SP, {R2,R3}\n"
                "B       loc_FF87BA70\n"
"loc_FF87BA64:\n"
                "LDR     R0, =0xFF87B750\n"  // aMounter_c
                "MOV     R1, #0x2B4\n"
                "BL      sub_FF813D70\n" // DebugAssert
"loc_FF87BA70:\n"
                "LDR     R2, =0x2E3C0\n"
                "ADD     R3, R8, R5\n"
                "LDMFD   SP, {R0,R12}\n"
                "RSB     R3, R5, R3,LSL#3\n"
                "MOV     R3, R3,LSL#2\n"
                "ADD     R1, R2, #0x48\n"
                "ADD     R2, R2, #0x44\n"
                "STR     R0, [R1,R3]\n"
                "STR     R12, [R2,R3]\n"
                "MOV     R0, #1\n"
"loc_FF87BA98:\n"
                "ADD     SP, SP, #8\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
 );
}

