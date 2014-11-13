/**
    this code completely copied from ../100k - no changes
        so i guess it does not work at all (see note below)
*/

///NOTE: this is not from ixus40! needs to be done!


#include "conf.h"

int *video_quality = &conf.video_quality;
int *video_mode    = &conf.video_mode;

long def_table1[56]={
0x10000,0xC000,0x5800, 0x2000, 0x1C6A, 0x1550,0x9C5,  0x38D,  0x3C45, 0x2D34, 0x14B8, 0x788,  0x5F60, 0x4788,
0x20C9, 0xBE1, 0x8661, 0x64C9, 0x2E31, 0x10CB,0xB21A, 0x8594, 0x3D39, 0x1642, 0xE249, 0xA9B8, 0x4DC9, 0x1C48,
0x117D2,0xD1DF,0x6030, 0x22F9, 0x153D5,0xFEE1,0x74D1, 0x2A79, 0x195F8,0x1307C,0x8B8D, 0x32AA, 0x1E01C,0x16817,
0xA509, 0x3C01,0x2328E,0x1A5ED,0xC160, 0x4637,0x28C99,0x1E975,0xE054, 0x5190, 0x2F08B,0x2346B,0x102AF,0x5E0E
};

long def_table2[12]={0xE666,0xACCD,0x4F33,0x1CCD,-0x170A,-0x1148,-0x7EB,-0x2E1,-0x2BC6,-0x20D5,-0xF0C,-0x579};

long table1[56], table2[12];

void change_video_tables(int a, int b){
 int i;
 for (i=0;i<56;i++) table1[i]=(def_table1[i]*a)/b;
 for (i=0;i<12;i++) table2[i]=(def_table2[i]*a)/b;
}

long CompressionRateTable[]={0x60, 0x5D, 0x5A, 0x57, 0x54, 0x51, 0x4D, 0x48, 0x42, 0x3B, 0x32, 0x29, 0x22, 0x1D, 0x17, 0x14, 0x10, 0xE, 0xB, 9, 7, 6, 5, 4, 3, 2, 1};


void __attribute__((naked,noinline)) movie_record_task(){
 asm volatile(
        "STMFD   SP!, {R4,LR}\n"
        "SUB     SP, SP, #4\n"
        "MOV     R4, SP\n"
        "B       loc_FF936520\n"
    "loc_FF936488:\n"
        "LDR     R3, =0x670F0\n"
        "LDR     R2, [R3]\n"
        "CMP     R2, #0\n"
        "BNE     loc_FF93650C\n"
        "LDR     R3, [R0]\n"
        "SUB     R3, R3, #1\n"
        "CMP     R3, #7\n"
        "LDRLS   PC, [PC,R3,LSL#2]\n"
        "B       loc_FF93650C\n"
        ".long loc_FF9364CC\n"
        ".long loc_FF9364D4\n"
        ".long loc_FF9364EC\n"
        ".long loc_FF9364DC\n"
        ".long loc_FF9364F4\n"
        ".long loc_FF9364E4\n"
        ".long loc_FF936504\n"
        ".long loc_FF9364FC\n"
            
    "loc_FF9364CC:\n"
        "BL      sub_FF93659C\n"
        "B       loc_FF936508\n"
    "loc_FF9364D4:\n"
        //"BL      unlock_optical_zoom\n"  //----> unset zoom NOTE: sd300 doesnt have this feature :(
         
        "BL      sub_FF9367B4\n"
        "B       loc_FF936508\n"
    "loc_FF9364DC:\n"
        "BL      sub_FF936B64_my\n"
        "B       loc_FF936508\n"
    "loc_FF9364E4:\n"
        "BL      sub_FF936F10\n"
        "B       loc_FF936508\n"
    "loc_FF9364EC:\n"
        "BL      sub_FF936DB8\n"
        "B       loc_FF936508\n"
    "loc_FF9364F4:\n"
        "BL      sub_FF936FC8\n"
        "B       loc_FF936508\n"
    "loc_FF9364FC:\n"
        "BL      sub_FF937064\n"
        "B       loc_FF936508\n"
    "loc_FF936504:\n"
        "BL      sub_FF936E08\n"
    "loc_FF936508:\n"
        "LDR     R1, [SP]\n"
    "loc_FF93650C:\n"
        "LDR     R3, =0x67074\n"
        "MOV     R2, #0\n"
        "STR     R2, [R1]\n"
        "LDR     R0, [R3]\n"
        "BL      sub_FF822738\n" //PostMessageQueue
    "loc_FF936520:\n"
        "LDR     R3, =0x67070\n"
        "MOV     R1, R4\n"
        "LDR     R0, [R3]\n"
        "MOV     R2, #0\n"
        "BL      sub_FF822320\n" //ReceiveMessageQueue
        "LDR     R0, [SP]\n"
        "CMP     R0, #0\n"
        "MOV     R1, R0\n"
        "BNE     loc_FF936488\n"
        "LDR     R3, =0x6706C\n"
        "LDR     R0, [R3]\n"
        "BL      sub_FF823144\n" //GiveSemaphore
        "BL      sub_FF823B44\n" //ExitTask
        "ADD     SP, SP, #4\n"
        "LDMFD   SP!, {R4,PC}\n"
 );
}


void __attribute__((naked,noinline)) sub_FF936B64_my(){
 asm volatile(
        "STMFD   SP!, {R4-R7,LR}\n"
        "LDR     R4, =0x67108\n"
        "SUB     SP, SP, #0x10\n"
        "LDR     R3, [R4]\n"
        "CMP     R3, #3\n"
        "MOV     R5, R0\n"
        "MOVEQ   R3, #4\n"
        "STREQ   R3, [R4]\n"
        "LDR     R3, =0x67188\n"
        "MOV     LR, PC\n"
        "LDR     PC, [R3]\n"
        "LDR     R2, [R4]\n"
        "CMP     R2, #4\n"
        "BNE     loc_FF936CC8\n"
        "ADD     R0, SP, #0xC\n"
        "BL      sub_FF9384F0\n" //--------------> redir to mine!
        "CMP     R0, #0\n"
        "BNE     loc_FF936BD4\n"
        "LDR     R3, =0x670F8\n"
        "LDR     R2, [R3]\n"
        "CMP     R2, #1\n"
        "BNE     loc_FF936BF0\n"
        "LDR     R2, =0x67130\n"
        "LDR     R1, =0x6710C\n"
        "LDR     R12, [R2]\n"
        "LDR     R3, [R1]\n"
        "CMP     R12, R3\n"
        "BCC     loc_FF936BF0\n"
"loc_FF936BD4:\n"
        "BL      sub_FF936D08\n"
        "LDR     R3, =0x67184\n"
        "LDR     R0, [R3]\n"
        "BL      sub_FFA449B4\n"
        "MOV     R3, #5\n"
        "STR     R3, [R4]\n"
        "B       loc_FF936CC8\n"
"loc_FF936BF0:\n"
        "LDR     R6, =0x67138\n"
        "LDR     R7, =0x670FC\n"
        "LDR     R0, [R5,#0x4]\n"
        "LDR     R1, [SP,#0xC]\n"
        "ADD     R12, SP, #0x4\n"
        "ADD     R3,  SP, #0x8\n"
        "LDR     R2, [R6]\n"
        "MOV     R4, #1\n"
        "STR     R12, [SP]\n"
        "STR     R4, [R7]\n"
        "BL      sub_FF8A03D8\n"
        "LDR     R3, =0x6706C\n"
        "MOV     R1, #0x3E8\n"
        "LDR     R0, [R3]\n"
        "BL      sub_FF822F5C\n" //TakeSemaphore
        "CMP     R0, #9\n"
        "BNE     loc_FF936C44\n"
        "BL      sub_FF938B2C\n"
        "LDR     R3, =0x67108\n"
        "LDR     R0, =0xFF936B4C\n" //debug string jpeg error
        "B       loc_FF936C5C\n"
"loc_FF936C44:\n"
        "LDR     R5, [SP,#4]\n"
        "CMP     R5, #0\n"
        "BEQ     loc_FF936C68\n"
        "BL      sub_FF938B2C\n"
        "LDR     R3, =0x67108\n"
        "LDR     R0, =0xFF936B58\n" //debug string jpeg error 2
"loc_FF936C5C:\n"
        "STR     R4, [R3]\n"
        "BL      sub_FF94FA2C\n" //HardwareDefect
        "B       loc_FF936CC8\n"
"loc_FF936C68:\n"
        "BL      sub_FF8A0434\n" //IsEmptyWriteCache?
        "LDR     R0, [SP,#0xC]\n"
        "LDR     R1, [SP,#0x8]\n"
        "BL      sub_FF9388B4\n"
        "LDR     R4, =0x67130\n"
        "LDR     R3, [R4]\n"
        "ADD     R3, R3, #1\n"
        "LDR     R0, [SP,#0x8]\n"
        "MOV     R1, R6\n"
        "STR     R3, [R4]\n"
        "MOV     R2, R5\n"
        "BL      sub_FF9374C0\n" //-----------> redir to mine !
        "LDR     R3, =0x67118\n"
        "LDR     R4, [R4]\n"
        "LDR     R1, [R3]\n"
        "MOV     R0, R4\n"
        "BL      sub_FFAB83DC\n" //umodsi3 ?
        "CMP     R0, #0\n"
        "BNE     loc_FF936CC4\n"
        "MOV     R0, R4\n"
        "LDR     R3, =0x67160\n"
        "MOV     LR, PC\n"
        "LDR     PC, [R3]\n"
"loc_FF936CC4:\n"
        "STR     R5, [R7]\n"
"loc_FF936CC8:\n"
        "ADD     SP, SP, #0x10\n"
        "LDMFD   SP!, {R4-R7,PC}\n"
	
 );
}

void __attribute__((naked,noinline)) sub_FF9384F0_my(){
 asm volatile(
        "STMFD   SP!, {R4-R11,LR}\n"
        "LDR     R12, =0x67434\n"
        "LDR     R3, =0x6744C\n"
        "SUB     SP, SP, #4\n"
        "LDR     R2, [R12]\n"
        "LDR     R1, [R3]\n"
        "ADD     R7, R2, #1\n"
        "LDR     R3, =0x674C4\n"
        "CMP     R7, R1\n"
        "STR     R7, [R12]\n"
        "MOV     R9, R0\n"
        "LDR     R11, [R3]\n"
        "MOVHI   R3, #0\n"
        "STRHI   R3, [R9]\n"
        "MOVHI   R0, #0x80000001\n"
        "BHI     loc_FF938828\n"
        "LDR     R3, =0x674A8\n"
        "LDR     R4, [R3]\n"
        "MOV     R0, R7\n"
        "MOV     R1, R4\n"
        "BL      sub_FFAB83DC\n" //umodsi3
        "CMP     R0, #1\n"
        "BNE     loc_FF9386EC\n"
        "LDR     R1, =0x674D4\n"
        "LDR     R3, =0x674C8\n"
        "LDR     R2, [R1]\n"
        "LDR     R1, =0x67420\n"
        "LDR     R8, [R3]\n"
        "LDR     R5, [R1]\n"
        "ADD     R2, R8, R2\n"
        "CMP     R2, R5\n"
        "BNE     loc_FF938590\n"
        "MOV     R1, R4\n"
        "MOV     R0, R7\n"
        "BL      sub_FFAB7D4C\n" //udivsi3
        "LDR     R4, =0x67428\n"
        "ADD     R0, R0, #1\n"
        "AND     R0, R0, #1\n"
        "STR     R8, [R4,R0,LSL#2]\n"
        "B       loc_FF9385AC\n"
"loc_FF938590:\n"
        "MOV     R1, R4\n"
        "MOV     R0, R7\n"
        "BL      sub_FFAB7D4C\n" //udivsi3
        "LDR     R4, =0x67428\n"
        "ADD     R0, R0, #1\n"
        "AND     R0, R0, #1\n"
        "STR     R5, [R4,R0,LSL#2]\n"
"loc_FF9385AC:\n"
        "LDR     R3, =0x67434\n"
        "LDR     R2, =0x674A8\n"
        "LDR     R0, [R3]\n"
        "LDR     R1, [R2]\n"
        "BL      sub_FFAB7D4C\n" //udivsi3
        "LDR     R3, =0x67468\n"
        "ADD     R0, R0, #1\n"
        "AND     R0, R0, #1\n"
        "LDR     R1, =0x674C8\n"
        "LDR     R12, =0x674D4\n"
        "LDR     LR, [R4,R0,LSL#2]\n"
        "LDR     R2, [R3]\n"
        "LDR     R0, [R1]\n"
        "LDR     R3, [R12]\n"
        "ADD     R1, LR, R2\n"
        "ADD     R2, R1, #8\n"
        "ADD     LR, R0, R3\n"
        "CMP     R2, LR\n"
        "BLS     loc_FF938610\n"
        "ADD     R3, R0, R1\n"
        "RSB     R3, LR, R3\n"
        "LDR     R2, =0x67420\n"
        "ADD     R3, R3, #8\n"
        "STR     R3, [R2]\n"
        "B       loc_FF938618\n"
"loc_FF938610:\n"
        "LDR     R3, =0x67420\n"
        "STR     R2, [R3]\n"
"loc_FF938618:\n"
        "LDR     R3, =0x67468\n"
        "LDR     R0, =0x67480\n"
        "LDR     R2, [R3]\n"
        "LDR     R3, [R0,#4]\n"
        "ADD     R2, R2, #0x18\n"
        "MOV     R1, R2\n"
        "MOV     R2, #0\n"
        "CMP     R2, R3\n"
        "BHI     loc_FF9387A8\n"
        "BNE     loc_FF93864C\n"
        "LDR     R3, [R0]\n"
        "CMP     R1, R3\n"
        "BHI     loc_FF9387A8\n"
"loc_FF93864C:\n"
        "LDR     R3, =0x67468\n"
        "LDR     R10, =0x67480\n"
        "LDR     R3, [R3]\n"
        "LDMIA   R10, {R1,R2}\n"
        "STR     R3, [SP]\n"
        "LDR     R0, =0x67434\n"
        "LDR     R12, =0x674A8\n"
        "SUBS    R5, R1, R3\n"
        "SBC     R6, R2, #0\n"
        "LDR     R8, [R12]\n"
        "MVN     R4, #0\n" //=0xFFFFFFFF
        "MVN     R3, #0x17\n" //=0xFFFFFFE8
        "LDR     R7, [R0]\n"
        "ADDS    R5, R5, R3\n"
        "ADC     R6, R6, R4\n"
        "SUB     R0, R7, #1\n"
        "MOV     R1, R8\n"
        "STMIA   R10, {R5,R6}\n"
        "BL      sub_FFAB7D4C\n" //udivsi3
        "CMP     R7, #1\n"
        "MLA     R0, R8, R0, R0\n"
        "BEQ     loc_FF9386EC\n"
        "SUB     R3, R0, #1\n"
        "MOV     R3, R3,LSL#4\n"
        "ADD     R4, R11, #0x10\n"
        "ADD     R5, R11, #0x14\n"
        "LDR     R1, [R5,R3]\n"
        "LDR     R2, [R4,R3]\n"
        "LDR     LR, =0x62773130\n"
        "ADD     R2, R2, R1\n"
        "MOV     R3, R0,LSL#4\n"
        "ADD     R2, R2, #8\n"
        "ADD     R12, R11, #0xC\n"
        "ADD     R1, R11, #8\n"
        "MOV     R0, #0\n"
        "STR     LR, [R1,R3]\n"
        "STR     R0, [R12,R3]\n"
        "STR     R2, [R4,R3]\n"
        "LDR     R2, [SP]\n"
        "STR     R2, [R5,R3]\n"
"loc_FF9386EC:\n"
        "LDR     R1, =0x67420\n"
        "LDR     R3, =0x6741C\n"
        "LDR     R2, [R1]\n"
        "LDR     R1, [R3]\n"
        "ADD     R2, R2, #8\n"
        "CMP     R2, R1\n"
        "STR     R2, [R9]\n"
        "BHI     loc_FF938724\n"
        "LDR     LR, =0x67478\n"
        "LDR     R3, [LR]\n"
        "ADD     R3, R2, R3\n"
        "CMP     R1, R3\n"
        "BHI     loc_FF938728\n"
        "B       loc_FF938768\n"
"loc_FF938724:\n"
        "LDR     LR, =0x67478\n"
"loc_FF938728:\n"
        "LDR     R3, =0x674C8\n"
        "LDR     R2, =0x674D4\n"
        "LDR     R12, [R3]\n"
        "LDR     R0, [R2]\n"
        "LDR     R1, [R9]\n"
        "LDR     R3, [LR]\n"
        "ADD     R2, R1, R3\n"
        "ADD     R1, R12, R0\n"
        "CMP     R2, R1\n"
        "BLS     loc_FF938778\n"
        "LDR     R3, =0x6741C\n"
        "RSB     R2, R1, R2\n"
        "LDR     R1, [R3]\n"
        "ADD     R2, R12, R2\n"
        "CMP     R1, R2\n"
        "BHI     loc_FF938778\n"
"loc_FF938768:\n"
        "MOV     R3, #0\n"
        "STR     R3, [R9]\n"
        "MOV     R0, #0x80000003\n"
        "B       loc_FF938828\n"
"loc_FF938778:\n"
        "LDR     R3, [LR]\n"
        "LDR     R12, =0x67480\n"
        "ADD     R3, R3, #0x18\n"
        "LDR     R2, [R12,#4]\n"
        "MOV     R0, R3\n"
        "MOV     R1, #0\n"
        "CMP     R1, R2\n"
        "BHI     loc_FF9387A8\n"
        "BNE     loc_FF9387B8\n"
        "LDR     R3, [R12]\n"
        "CMP     R0, R3\n"
        "BLS     loc_FF9387B8\n"
"loc_FF9387A8:\n"
        "MOV     R3, #0\n"
        "STR     R3, [R9]\n"
        "MOV     R0, #0x80000005\n"
        "B       loc_FF938828\n"
"loc_FF9387B8:\n"
        "LDR     R1, =0x67460\n"
        "LDR     R0, =0x674A8\n"
        "LDR     R3, [R1]\n"
        "LDR     R2, [R0]\n"
        "ADD     R3, R3, R2,LSL#4\n"
        "ADD     R3, R3, R3,LSL#2\n"
        "LDR     R12, =0x67480\n"
        "MOV     R3, R3,LSL#1\n"
        "ADD     R3, R3, #0xA0\n"
        "LDR     R2, [R12,#4]\n"
        "MOV     R0, R3\n"
        "MOV     R1, #0\n"
        "CMP     R1, R2\n"
        "BHI     loc_FF938800\n"
        "BNE     loc_FF938824\n"
        "LDR     R3, [R12]\n"
        "CMP     R0, R3\n"
        "BLS     loc_FF938824\n"
"loc_FF938800:\n"
        "LDR     R4, =0x67490\n"
        "LDR     R1, [R4]\n"
        "CMP     R1, #0\n"
        "BNE     loc_FF938824\n"
        
        //MOV R0 0x3148
        "MOV     R0, #0x3140\n"
        "ADD     R0, R0, #8\n" 
          
        "BL      sub_FF953AD8\n" //PostLogicalEventToUI?
        "MOV     R3, #1\n"
        "STR     R3, [R4]\n"
         
        //unclear what it does, copied from ixus50 
        //ixus40 did never store 0 on R9 (=R11 on ixus50)
        ///"MOV     R3, #0\n"          
        ///"STR     R3, [R9]\n"       
         
"loc_FF938824:\n"
        "MOV     R0, #0\n"
"loc_FF938828:\n"
        "ADD     SP, SP, #4\n"
        "LDMFD   SP!, {R4-R11,PC}\n"
 );
}

void __attribute__((naked,noinline)) sub_FF9374C0_my(){
 asm volatile(
              "NOP\n"
             );          
 ///TODO! below is from sd400
         /*
         
                "STMFD   SP!, {R4-R7,LR}\n" 
                "MOV     R7, R0\n"          
                "MOV     R6, R1\n"          
                "LDREQ   R3, =CompressionRateTable\n" 
                "LDREQ   R2, [R3,#0x18]\n"  
                "STREQ   R2, [R6]\n"        
                "LDMEQFD SP!, {R4-R7,PC}FF9374C0\n" 
                "LDR     R12, =0x6FA10\n"   
                "LDR     R0, [R12]\n"       
                "LDR     R3, =0x6FA18\n"    
                "CMP     R0, #0\n"          
                "LDR     R1, [R3]\n"        
                "BEQ     loc_FF952458\n"    
                "LDR     R2, =0x6FA1C\n"    
                "LDR     R3, [R2]\n"        
                "CMP     R3, #1\n"          
                "BNE     loc_FF95246C\n"    
                "B       loc_FF95245C\n"    
"loc_FF952458:\n"                           
                "LDR     R2, =0x6FA1C\n"    
"loc_FF95245C:\n"                           
                "MOV     R3, #0\n"          
                "STR     R3, [R2]\n"        
                "STR     R7, [R12]\n"       
                "B       loc_FF952520\n"    
"loc_FF95246C:\n"                           
                "LDR     R3, =0x6FA14\n"    
                "LDR     R2, [R3]\n"        
                "LDR     R5, =table1\n" // + 0xFF9521E0
                "MOV     LR, R2,LSL#2\n"    
                "LDR     R3, [R5,LR]\n"     
                "LDR     R4, =table2\n" // + 0xFF9522C0
                "RSB     R12, R3, R0\n"     
                "LDR     R2, [R4,LR]\n"     
                "CMP     R12, #0\n"         
                "RSB     R0, R2, R0\n"      
                "BLE     loc_FF9524CC\n"    
                "ADD     R3, R5, #0x10\n"   
                "LDR     R2, [R3,LR]\n"     
                "CMP     R2, R12\n"         
                "ADDGE   R1, R1, #1\n"      
                "BGE     loc_FF9524C0\n"    
                "ADD     R3, R5, #0x20\n"   
                "LDR     R2, [R3,LR]\n"     
                "CMP     R2, R12\n"         
                "ADDGE   R1, R1, #2\n"      
                "ADDLT   R1, R1, #3\n"      
"loc_FF9524C0:\n"                           
          //    "CMP     R1, #0xE\n"     // -
          //    "MOVGE   R1, #0xE\n"     // -
                "CMP     R1, #0x1A\n"    // +   
                "MOVGE   R1, #0x1A\n"    // +   

                "B       loc_FF952504\n"    
"loc_FF9524CC:\n"                           
                "CMP     R0, #0\n"          
                "BGE     loc_FF952504\n"    
                "ADD     R3, R4, #0x10\n"   
                "LDR     R2, [R3,LR]\n"     
                "CMP     R2, R0\n"          
                "SUBLE   R1, R1, #1\n"      
                "BLE     loc_FF9524FC\n"    
                "ADD     R3, R4, #0x20\n"   
                "LDR     R2, [R3,LR]\n"     
                "CMP     R2, R0\n"          
                "SUBLE   R1, R1, #2\n"      
                "SUBGT   R1, R1, #3\n"      
"loc_FF9524FC:\n"                           
                "CMP     R1, #0\n"          
                "MOVLT   R1, #0\n"          
"loc_FF952504:\n"                           
                                        
                "LDR     R0, =0x6FA18\n"    
                "LDR     R3, [R0]\n"        
                "CMP     R1, R3\n"          
                "LDRNE   R2, =0x6FA1C\n"    
                "MOVNE   R3, #1\n"          
                "STRNE   R1, [R0]\n"        
                "STRNE   R3, [R2]\n"        
"loc_FF952520:\n"                           
                "LDR     R3, =0x6FA18\n"    
           //   "LDR     R1, =0x56C0\n"   // -
                "LDR     R1, =video_mode\n" //+
                "LDR     R0, [R3]\n"        
                "LDR     R2, =CompressionRateTable\n"   //+ FF9521A4
                "LDR     R12, [R1]\n"
                "LDR     R12, [R12]\n" //+       
                "LDR     LR, [R2,R0,LSL#2]\n" 
                "LDR     R3, =0x6FA10\n"    
                "CMP     R12, #1\n"         
                "STR     R7, [R3]\n"        
                "STR     LR, [R6]\n"        
           //   "MOVEQ   R3, #0xB\n"   // -

                "LDREQ   R3, =video_quality\n"          // +
                "LDREQ   R3, [R3]\n"                    // +
                "LDREQ   R3, [R3]\n"                    // +

                "STREQ   R3, [R6]\n"        
                "LDMFD   SP!, {R4-R7,PC}\n" 
 );*/
}
