/*
 * filewrite.c - auto-generated by CHDK code_gen.
 */
#include "lolevel.h"
#include "platform.h"

typedef struct {
    unsigned int address;
    unsigned int length;
} cam_ptp_data_chunk; //camera specific structure

#define MAX_CHUNKS_FOR_JPEG 3 //model specific
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
    char name[32];
} fwt_data_struct;
#define CAM_HAS_COMPLETEFILEWRITE_REPLACEMENT 1

#include "../../../generic/filewrite.c"

/*************************************************************/
//** filewritetask @ 0xFFA914CC - 0xFFA91558, length=36
void __attribute__((naked,noinline)) filewritetask() {
asm volatile (
"    STMFD   SP!, {R4,LR} \n"
"    SUB     SP, SP, #4 \n"
"    MOV     R4, SP \n"
"    B       loc_FFA9151C \n"

"loc_FFA914DC:\n"
"    CMP     R2, #5 \n"
"    LDRLS   PC, [PC, R2, LSL#2] \n"
"    B       loc_FFA9151C \n"
"    .long   loc_FFA91500 \n"
"    .long   loc_FFA91508 \n"
"    .long   loc_FFA91510 \n"
"    .long   loc_FFA91510 \n"
"    .long   loc_FFA91510 \n"
"    .long   loc_FFA91518 \n"

"loc_FFA91500:\n"
"    BL      sub_FFA9110C \n"
"    B       loc_FFA9151C \n"

"loc_FFA91508:\n"
"    BL      sub_FFA91234_my \n"  // --> Patched. Old value = 0xFFA91234. Open Stage
"    B       loc_FFA9151C \n"

"loc_FFA91510:\n"
"    BL      sub_FFA91310 \n"
"    B       loc_FFA9151C \n"

"loc_FFA91518:\n"
"    BL      sub_FFA91408 \n"
"    BL      fwt_after_close\n" //+

"loc_FFA9151C:\n"
"    LDR     R3, =0x7B980 \n"
"    MOV     R1, R4 \n"
"    LDR     R0, [R3] \n"
"    MOV     R2, #0 \n"
"    BL      sub_FFB1360C /*_ReceiveMessageQueue*/ \n"
"    CMP     R0, #0 \n"
"    BNE     loc_FFA91558 \n"
"    LDR     R0, [SP] \n"
"    LDR     R3, [R0] \n"
"    CMP     R3, #1 \n"
"    SUB     R2, R3, #2 \n"
"    BNE     loc_FFA914DC \n"
"    LDR     R3, =0x7B978 \n"
"    LDR     R0, [R3] \n"
"    BL      _GiveSemaphore \n"

"loc_FFA91558:\n"
"    BL      _ExitTask \n"
);
}

/*************************************************************/
//** sub_FFA91234_my @ 0xFFA91234 - 0xFFA912D0, length=40
void __attribute__((naked,noinline)) sub_FFA91234_my() {
asm volatile (
"    STMFD   SP!, {R4,R5,LR} \n"
"    MOV     R5, R0 \n"
"    ADD     R4, R5, #0x2C \n"
"    MOV     R0, R4 \n"
"    BL      sub_FFA99920 \n"
"    MOV     R1, #0 \n"
"    BL      sub_FFA9C768 \n"
"    LDR     R0, [R5, #0xC] \n"
"    BL      sub_FFA9D39C \n"
"    MOV     R2, #0x1B4 \n"
"    LDR     R1, [R5, #8] \n"
"    ADD     R2, R2, #2 \n"
"    LDR     R3, [R5, #0xC] \n"
//place hook here
//the task's data block is at [R5] at this point, filename starts at [R5+0x2C]
//the block can be captured here for a (new) camera with unknown data block structure
//for ptp remote capture, pass '/null' as filename
//if writing does not need to be prevented, just continue
"    STMFD   SP!, {R1-R12,LR}\n"
"    MOV     R0, R5\n"
"    BL      filewrite_main_hook\n"
"    BL      filewrite_jpeg_complete\n"
"    CMP     R0, #0\n"
"    LDRNE   R0, =loc_mynull\n" // /null as file name (works only on VxWorks)
"    LDMFD   SP!, {R1-R12,LR}\n"
"    MOVEQ   R0, R4\n" //canon file name
//hook end
//"  MOV     R0, R4 \n"  // - file name
"    BL      sub_FFA911A0 \n"
"    LDR     R3, =0x7B970 \n"
"    MOV     R12, R0 \n"
"    CMN     R12, #1 \n"
"    MOV     R1, R4 \n"
"    MOV     R2, #0x20 \n"
"    MOV     R0, R4 \n"
"    STR     R12, [R3] \n"
"    BNE     loc_FFA912BC \n"
"    BL      sub_FFA99920 \n"
"    BL      sub_FFA9C7D0 \n"
"    LDR     R3, =0x7BA90 \n"
"    LDR     R3, [R3] \n"
"    MOV     R0, #0x8000001 \n"
"    CMP     R3, #0 \n"
"    ADD     R0, R0, #0x1200000 \n"
"    LDMEQFD SP!, {R4,R5,PC} \n"
"    MOV     LR, PC \n"
"    MOV     PC, R3 \n"
"    LDMFD   SP!, {R4,R5,PC} \n"

"loc_FFA912BC:\n"
"    LDR     R0, =0x7BA70 \n"
"    BL      _memcpy \n"
"    MOV     R0, #4 \n"
"    MOV     R1, R5 \n"
"    LDMFD   SP!, {R4,R5,LR} \n"
"    B       sub_FFA9101C \n"
//mod start
"loc_mynull:\n"
".asciz     \"/null\" \n"
//mod end
);
}
