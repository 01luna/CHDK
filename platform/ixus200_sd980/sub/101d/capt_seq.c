#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"

static long *nrflag = (long*)0x6cb4;

#include "../../../generic/capt_seq.c"

//** capt_seq_task  @ 0xFF876EC0 

void __attribute__((naked,noinline)) capt_seq_task(  ) { 
asm volatile (
"	STMFD	SP!, {R3-R9,LR} \n"                
"	LDR	R6, =0x2B04 \n"                      
"	LDR	R4, =0x4A5C8 \n"                     
"	MOV	R9, #1 \n"                           
"	MOV	R7, #0 \n"                           
"loc_FF876ED4:\n"
"	LDR	R0, [R6, #4] \n"                     
"	MOV	R2, #0 \n"                           
"	MOV	R1, SP \n"                           
"	BL	sub_FF837F08 \n"                      
"	TST	R0, #1 \n"                           
"	BEQ	loc_FF876F00 \n"                     
"	LDR	R1, =0x5B3 \n"                       
"	LDR	R0, =0xFF876A00 \n"                  
"	BL	sub_FF81E88C \n"                      
"	BL	sub_FF81E844 \n"                      
"	LDMFD	SP!, {R3-R9,PC} \n"                
"loc_FF876F00:\n"
"	LDR	R0, [SP] \n"                         
"	LDR	R1, [R0] \n"                         
"	CMP	R1, #0x1F \n"                        
"	ADDLS	PC, PC, R1, LSL #2 \n"             
"	B	loc_FF8771A4 \n"                       
"	B	loc_FF876F94 \n"                       
"	B	loc_FF876FF8 \n"                       
"	B	loc_FF877034 \n"                       
"	B	loc_FF877048 \n"                       
"	B	loc_FF877040 \n"                       
"	B	loc_FF877050 \n"                       
"	B	loc_FF877058 \n"                       
"	B	loc_FF877060 \n"                       
"	B	loc_FF8770B8 \n"                       
"	B	loc_FF8770E0 \n"                       
"	B	loc_FF8770C4 \n"                       
"	B	loc_FF8770D0 \n"                       
"	B	loc_FF8770D8 \n"                       
"	B	loc_FF8770E8 \n"                       
"	B	loc_FF8770F0 \n"                       
"	B	loc_FF8770F8 \n"                       
"	B	loc_FF877100 \n"                       
"	B	loc_FF877108 \n"                       
"	B	loc_FF877114 \n"                       
"	B	loc_FF87711C \n"                       
"	B	loc_FF877124 \n"                       
"	B	loc_FF87712C \n"                       
"	B	loc_FF877134 \n"                       
"	B	loc_FF877140 \n"                       
"	B	loc_FF877148 \n"                       
"	B	loc_FF877150 \n"                       
"	B	loc_FF877158 \n"                       
"	B	loc_FF877160 \n"                       
"	B	loc_FF877168 \n" 
"	B	loc_FF877170 \n"                       
"	B	loc_FF87717C \n"                       
"	B	loc_FF8771B0 \n"                       
"loc_FF876F94:\n"
"	BL	sub_FF877844 \n"
 "	BL      shooting_expo_param_override\n"                      
"	BL	sub_FF874CBC \n"

//  this code added to avoid some incorrect behavior if overrides are used.
 //  but it can cause some unexpected side effects. In this case, remove this code!
                 "MOV     R0, #0\n"
                 "STR     R0, [R4,#0x24]\n"  // fixes overrides  behavior at short shutter press
//end of modified code
                      
"	LDR	R0, [R4, #0x24] \n"                  
"	CMP	R0, #0 \n"                           
"	BEQ	loc_FF8771B0 \n"                     
"	BL	sub_FF8766DC \n"                      
"	MOV	R5, R0 \n"                           
"	LDR	R0, [R4, #0x24] \n"                  
"	CMP	R0, #0 \n"                           
"	BEQ	loc_FF876FDC \n"                     
"	MOV	R0, #0xC \n"                         
"	BL	sub_FF87BB64 \n"                      
"	TST	R0, #1 \n"                           
"	STRNE	R9, [R6, #0x10] \n"                
"	LDRNE	R0, [R5, #8] \n"                   
"	ORRNE	R0, R0, #0x40000000 \n"            
"	STRNE	R0, [R5, #8] \n"                   
"	BNE	loc_FF8771B0 \n"                     
"loc_FF876FDC:\n"
"	MOV	R0, R5 \n"                           
"	BL	sub_FF876980 \n"                      
"	MOV	R0, R5 \n"                           
"	BL	sub_FF950030_my \n"   //----------------->
"	BL      capt_seq_hook_raw_here\n"                
"	TST	R0, #1 \n"                           
"	STRNE	R9, [R6, #0x10] \n"                
"	B	loc_FF8771B0 \n"                       
"loc_FF876FF8:\n"
"	LDR	R0, [R4, #0x24] \n"                  
"	CMP	R0, #0 \n"                           
"	BNE	loc_FF877024 \n"                     
"	MOV	R0, #0xC \n"                         
"	BL	sub_FF87BB64 \n"                      
"	TST	R0, #1 \n"                           
"	LDRNE	R0, [SP] \n"                       
"	MOVNE	R1, #1 \n"                         
"	LDRNE	R2, [R0, #0xC] \n"                 
"	MOVNE	R0, #1 \n"                         
"	BNE	loc_FF8770B0 \n"                     
"loc_FF877024:\n"
"	LDR	R0, [SP] \n"                         
"	BL	sub_FF8772C8_my \n"  //----------------->                   
"loc_FF87702C:\n"
"	STR	R7, [R4, #0x24] \n"                  
"	B	loc_FF8771B0 \n"                       
"loc_FF877034:\n"
"	MOV	R0, #1 \n"                           
"	BL	sub_FF877AA0 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF877040:\n"
"	BL	sub_FF877480 \n"                      
"	B	loc_FF87702C \n"                       
"loc_FF877048:\n"
"	BL	sub_FF877824 \n"                      
"	B	loc_FF87702C \n"                       
"loc_FF877050:\n"
"	BL	sub_FF87782C \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF877058:\n"
"	BL	sub_FF8779C0 \n"                      
"	B	loc_FF8770BC \n"                       
"loc_FF877060:\n"
"	LDR	R5, [R0, #0xC] \n"                   
"	BL	sub_FF877834 \n"                      
"	MOV	R0, R5 \n"                           
"	BL	sub_FF94ECEC \n"                      
"	TST	R0, #1 \n"                           
"	MOV	R8, R0 \n"                           
"	BNE	loc_FF8770A0 \n"                     
"	BL	sub_FF888D28 \n"                      
"	STR	R0, [R5, #0x18] \n"                  
"	MOV	R0, R5 \n"                           
"	BL	sub_FF94FF48 \n"                      
"	MOV	R0, R5 \n"                           
"	BL	sub_FF950348 \n"                      
"	MOV	R8, R0 \n"                           
"	LDR	R0, [R5, #0x18] \n"                  
"	BL	sub_FF888F3C \n"                      
"loc_FF8770A0:\n"
"	BL	sub_FF877824 \n"                      
"	MOV	R2, R5 \n"                           
"	MOV	R1, #9 \n"                           
"	MOV	R0, R8 \n"                           
"loc_FF8770B0:\n"
"	BL	sub_FF8751A8 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF8770B8:\n"
"	BL	sub_FF877A20 \n"                      
"loc_FF8770BC:\n"
"	BL	sub_FF874CBC \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF8770C4:\n"
"	LDR	R0, [R4, #0x54] \n"                  
"	BL	sub_FF877E30 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF8770D0:\n"
"	BL	sub_FF8780E4 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF8770D8:\n"
"	BL	sub_FF878178 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF8770E0:\n"
"	BL	sub_FF877824 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF8770E8:\n"
"	BL	sub_FF94EF04 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF8770F0:\n"
"	BL	sub_FF94F118 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF8770F8:\n"
"	BL	sub_FF94F1B0 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF877100:\n"
"	BL	sub_FF94F280 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF877108:\n"
"	MOV	R0, #0 \n"                           
"	BL	sub_FF94F4D0 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF877114:\n"
"	BL	sub_FF94F62C \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF87711C:\n"
"	BL	sub_FF94F6BC \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF877124:\n"
"	BL	sub_FF94F77C \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF87712C:\n"
"	BL	sub_FF877C1C \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF877134:\n"
"	BL	sub_FF877CBC \n"                      
"	BL	sub_FF835F60 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF877140:\n"
"	BL	sub_FF94F34C \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF877148:\n"
"	BL	sub_FF94F3B8 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF877150:\n"
"	BL	sub_FF87A238 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF877158:\n"
"	BL	sub_FF87A2A4 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF877160:\n"
"	BL	sub_FF94F8FC \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF877168:\n"
"	BL	sub_FF94F968 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF877170:\n"
"	BL	sub_FF87A300 \n"                      
"	BL	sub_FF87A2C0 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF87717C:\n"
"	MOV	R0, #1 \n"                           
"	BL	sub_FF950BC0 \n"                      
"	MOV	R0, #1 \n"                           
"	BL	sub_FF950CD0 \n"                      
"	LDRH	R0, [R4, #0x98] \n"                 
"	CMP	R0, #4 \n"                           
"	BNE	loc_FF8771B0 \n"                     
"	BL	sub_FF87A2A4 \n"                      
"	BL	sub_FF87A778 \n"                      
"	B	loc_FF8771B0 \n"                       
"loc_FF8771A4:\n"
"	LDR	R1, =0x708 \n"                       
"	LDR	R0, =0xFF876A00 \n"                  
"	BL	sub_FF81E88C \n"                      
"loc_FF8771B0:\n"
"	LDR	R0, [SP] \n"                         
"	LDR	R1, [R0, #4] \n"                     
"	LDR	R0, [R6] \n"                         
"	BL	sub_FF880A14 \n"                      
"	LDR	R5, [SP] \n"                         
"	LDR	R0, [R5, #8] \n"                     
"	CMP	R0, #0 \n"                           
"	LDREQ	R1, =0x131 \n"                     
"	LDREQ	R0, =0xFF876A00 \n"                
"	BLEQ	sub_FF81E88C \n"                    
"	STR	R7, [R5, #8] \n"                     
"	B	loc_FF876ED4 \n"                       
"	STMFD	SP!, {R3-R5,LR} \n"                
"	LDR	R2, =0x4A514 \n"                     
"	MOV	R0, #0 \n"                           
"	MOV	R1, #0 \n"                           
"loc_FF8771F0:\n"
"	ADD	R3, R2, R0, LSL #4 \n"               
"	ADD	R0, R0, #1 \n"                       
"	CMP	R0, #5 \n"                           
"	STR	R1, [R3, #8] \n"                     
"	BCC	loc_FF8771F0 \n"                     
"	BL	sub_FF877D6C \n"                      
"	BL	sub_FF950E6C \n"                      
"	MOV	R1, #5 \n"                           
"	MOV	R0, #0 \n"                           
"	BL	sub_FF838750 \n"                      
"	LDR	R4, =0x2B04 \n"                      
"	LDR	R1, =0x101DFF \n"                    
"	STR	R0, [R4, #4] \n"                     
"	MOV	R0, #0 \n"                           
"	BL	sub_FF838774 \n"                      
"	STR	R0, [R4] \n"                         
	);
}

//** sub_FF94FE74_my  @ 0xFF950030 

void __attribute__((naked,noinline)) sub_FF950030_my(  ) { 
asm volatile (
"	STMFD	SP!, {R0-R8,LR} \n"                
"	MOV	R4, R0 \n"                           
"	BL	sub_FF950EBC \n"                      
"	MVN	R1, #0 \n"                           
"	BL	sub_FF880A48 \n"                      
"	LDR	R5, =0x6CB0 \n"                      
"	LDR	R0, [R5, #0xC] \n"                   
"	CMP	R0, #0 \n"                           
"	BNE	loc_FF950080 \n"                     
"	MOV	R1, #1 \n"                           
"	MOV	R0, #0 \n"                           
"	BL	sub_FF838750 \n"                      
"	STR	R0, [R5, #0xC] \n"                   
"	MOV	R3, #0 \n"                           
"	STR	R3, [SP] \n"                         
"	LDR	R3, =0xFF94F9BC \n"                  
"	LDR	R0, =0xFF9502B0 \n"                  
"	MOV	R2, #0x400 \n"                       
"	MOV	R1, #0x17 \n"                        
"	BL	sub_FF83871C \n"                      
"loc_FF950080:\n"
"	MOV	R2, #4 \n"                           
"	ADD	R1, SP, #8 \n"                       
"	MOV	R0, #0x8A \n"                        
"	BL	sub_FF888B98 \n"                      
"	TST	R0, #1 \n"                           
"	LDRNE	R1, =0x3C5 \n"                     
"	LDRNE	R0, =0xFF94FC54 \n"                
"	BLNE	sub_FF81E88C \n"                    
"	LDR	R6, =0x4A690 \n"                     
"	LDR	R8, =0x4A5C8 \n"                     
"	LDR	R3, [R6] \n"                         
"	LDRSH	R2, [R6, #0xC] \n"                 
"	LDRSH	R1, [R6, #0xE] \n"                 
"	LDR	R0, [R8, #0x8C] \n"                  
"	BL	sub_FF916370 \n"                      
"	BL	sub_FF85E238 \n"                      
"	LDR	R3, =0x6CB8 \n"                      
"	STRH	R0, [R4, #0xA4] \n"                 
"	SUB	R2, R3, #4 \n"                       
"	STRD	R2, [SP] \n"                        
"	MOV	R1, R0 \n"                           
"	LDRH	R0, [R8, #0x5C] \n"                 
"	LDRSH	R2, [R6, #0xC] \n"                 
"	SUB	R3, R3, #8 \n"                       
"	BL	sub_FF952578 \n"                      
"	BL  wait_until_remote_button_is_released\n"
"	BL  capt_seq_hook_set_nr\n"
"	B	sub_FF9500E4\n"//go to the ROM
         
	);
}

//** sub_FF877278_my  @ 0xFF8772C8 

void __attribute__((naked,noinline)) sub_FF8772C8_my(  ) { 
asm volatile (
"	STMFD	SP!, {R4-R6,LR} \n"                
"	LDR	R4, [R0, #0xC] \n"                   
"	LDR	R6, =0x4A5C8 \n"                     
"	LDR	R0, [R4, #8] \n"                     
"	MOV	R5, #0 \n"                           
"	ORR	R0, R0, #1 \n"                       
"	STR	R0, [R4, #8] \n"                     
"	LDR	R0, [R6, #0x24] \n"                  
"	CMP	R0, #0 \n"                           
"	MOVEQ	R0, #2 \n"                         
"	BLEQ	sub_FF8733C0 \n"                    
"	BL	sub_FF877834 \n"                      
"	LDR	R0, [R6, #0x24] \n"                  
"	CMP	R0, #0 \n"                           
"	BNE	loc_FF8773A4 \n"                     
"	MOV	R0, #0 \n"                           
"	BL	sub_FF950BC0 \n"                      
"	MOV	R0, #0 \n"                           
"	BL	sub_FF950CD0 \n"                      
"	MOV	R0, R4 \n"                           
"	BL	sub_FF877BC4 \n"                      
"	MOV	R0, R4 \n"                           
"	BL	sub_FF94E93C \n"                      
"	CMP	R0, #0 \n"                           
"	BEQ	loc_FF877358 \n"                     
"	BL	sub_FF950C00 \n"                      
"	BL	sub_FF950D14 \n"                      
"	BL	sub_FF950D64 \n"                      
"	MOV	R0, R4 \n"                           
"	BL	sub_FF94EA20 \n"                      
"	TST	R0, #1 \n"                           
"	MOVNE	R2, R4 \n"                         
"	LDMNEFD	SP!, {R4-R6,LR} \n"              
"	MOVNE	R1, #1 \n"                         
"	BNE	sub_FF8751A8 \n"                     
"	B	loc_FF87736C \n"                       
"loc_FF877358:\n"
"	MOV	R0, R4 \n"                           
"	BL	sub_FF94E9BC \n"                      
"	BL	sub_FF950C00 \n"                      
"	BL	sub_FF950D14 \n"                      
"	BL	sub_FF950D64 \n"                      
"loc_FF87736C:\n"
"	MOV	R0, R4 \n"                           
"	BL	sub_FF876980 \n"                      
"	LDRH	R0, [R6] \n"                        
"	SUB	R12, R0, #0x8200 \n"                 
"	SUBS	R12, R12, #0xF \n"                  
"	LDREQ	R0, [R4, #0x18] \n"                
"	BLEQ	sub_FF872E88 \n"                    
"	MOV	R0, R4 \n"                           
"	BL	sub_FF94FF48 \n"                      
"	BL	sub_FF9509C8 \n"                      
"	MOV	R0, R4 \n"                           
"	BL	sub_FF950030_my \n"  //----------------->                      
"	MOV	R5, R0 \n"                           
"	BL     capt_seq_hook_raw_here\n"   //-----------------> 
"	B	loc_FF8773B4 \n"                       
"loc_FF8773A4:\n"
"	LDR	R0, =0x2B04 \n"                      
"	LDR	R0, [R0, #0x10] \n"                  
"	CMP	R0, #0 \n"                           
"	MOVNE	R5, #0x1D \n"                      
"loc_FF8773B4:\n"
"	BL	sub_FF87A2A4 \n"                      
"	BL	sub_FF87A2EC \n"                      
"	BL	sub_FF87A32C \n"                      
"	MOV	R2, R4 \n"                           
"	MOV	R1, #1 \n"                           
"	MOV	R0, R5 \n"                           
"	BL	sub_FF8751A8 \n"                      
"	BL	sub_FF9502EC \n"                      
"	CMP	R0, #0 \n"                           
"	LDRNE	R0, [R4, #8] \n"                   
"	ORRNE	R0, R0, #0x2000 \n"                
"	STRNE	R0, [R4, #8] \n"                   
"	LDMFD	SP!, {R4-R6,PC} \n"                
	);
}


//** exp_drv_task  @ 0xFF8BA324 

void __attribute__((naked,noinline)) exp_drv_task(  ) { 
asm volatile (
"	STMFD	SP!, {R4-R8,LR} \n"                
"	SUB	SP, SP, #0x20 \n"                    
"	LDR	R8, =0xBB8 \n"                       
"	LDR	R7, =0x4130 \n"                      
"	LDR	R5, =0x4F45C \n"                     
"	MOV	R0, #0 \n"                           
"	ADD	R6, SP, #0x10 \n"                    
"	STR	R0, [SP, #0xC] \n"                   
"loc_FF8BA344:\n"
"	LDR	R0, [R7, #0x20] \n"                  
"	MOV	R2, #0 \n"                           
"	ADD	R1, SP, #0x1C \n"                    
"	BL	sub_FF837F08 \n"                      
"	LDR	R0, [SP, #0xC] \n"                   
"	CMP	R0, #1 \n"                           
"	BNE	loc_FF8BA390 \n"                     
"	LDR	R0, [SP, #0x1C] \n"                  
"	LDR	R0, [R0] \n"                         
"	CMP	R0, #0x13 \n"                        
"	CMPNE	R0, #0x14 \n"                      
"	CMPNE	R0, #0x15 \n"                      
"	CMPNE	R0, #0x16 \n"                      
"	BEQ	loc_FF8BA4AC \n"                     
"	CMP	R0, #0x28 \n"                        
"	BEQ	loc_FF8BA484 \n"                     
"	ADD	R1, SP, #0xC \n"                     
"	MOV	R0, #0 \n"                           
"	BL	sub_FF8BA2D4 \n"                      
"loc_FF8BA390:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	LDR	R1, [R0] \n"                         
"	CMP	R1, #0x2D \n"                        
"	BNE	loc_FF8BA3C0 \n"                     
"	LDR	R0, [SP, #0x1C] \n"                  
"	BL	sub_FF8BB594 \n"                      
"	LDR	R0, [R7, #0x1C] \n"                  
"	MOV	R1, #1 \n"                           
"	BL	sub_FF880A14 \n"                      
"	BL	sub_FF81E844 \n"                      
"	ADD	SP, SP, #0x20 \n"                    
"	LDMFD	SP!, {R4-R8,PC} \n"                
"loc_FF8BA3C0:\n"
"	CMP	R1, #0x2C \n"                        
"	BNE	loc_FF8BA3DC \n"                     
"	LDR	R2, [R0, #0x8C]! \n"                 
"	LDR	R1, [R0, #4] \n"                     
"	MOV	R0, R1 \n"                           
"	BLX	R2 \n"                               
"	B	loc_FF8BA8D4 \n"                       
"loc_FF8BA3DC:\n"
"	CMP	R1, #0x26 \n"                        
"	BNE	loc_FF8BA42C \n"                     
"	LDR	R0, [R7, #0x1C] \n"                  
"	MOV	R1, #0x80 \n"                        
"	BL	sub_FF880A48 \n"                      
"	LDR	R0, =0xFF8B6A14 \n"                  
"	MOV	R1, #0x80 \n"                        
"	BL	sub_FF943A58 \n"                      
"	LDR	R0, [R7, #0x1C] \n"                  
"	MOV	R2, R8 \n"                           
"	MOV	R1, #0x80 \n"                        
"	BL	sub_FF880954 \n"                      
"	TST	R0, #1 \n"                           
"	LDRNE	R1, =0xE57 \n"                     
"	BNE	loc_FF8BA470 \n"                     
"loc_FF8BA418:\n"
"	LDR	R1, [SP, #0x1C] \n"                  
"	LDR	R0, [R1, #0x90] \n"                  
"	LDR	R1, [R1, #0x8C] \n"                  
"	BLX	R1 \n"                               
"	B	loc_FF8BA8D4 \n"                       
"loc_FF8BA42C:\n"
"	CMP	R1, #0x27 \n"                        
"	BNE	loc_FF8BA47C \n"                     
"	ADD	R1, SP, #0xC \n"                     
"	BL	sub_FF8BA2D4 \n"                      
"	LDR	R0, [R7, #0x1C] \n"                  
"	MOV	R1, #0x100 \n"                       
"	BL	sub_FF880A48 \n"                      
"	LDR	R0, =0xFF8B6A24 \n"                  
"	MOV	R1, #0x100 \n"                       
"	BL	sub_FF9443E8 \n"                      
"	LDR	R0, [R7, #0x1C] \n"                  
"	MOV	R2, R8 \n"                           
"	MOV	R1, #0x100 \n"                       
"	BL	sub_FF880954 \n"                      
"	TST	R0, #1 \n"                           
"	BEQ	loc_FF8BA418 \n"                     
"	LDR	R1, =0xE61 \n"                       
"loc_FF8BA470:\n"
"	LDR	R0, =0xFF8B7084 \n"                  
"	BL	sub_FF81E88C \n"                      
"	B	loc_FF8BA418 \n"                       
"loc_FF8BA47C:\n"
"	CMP	R1, #0x28 \n"                        
"	BNE	loc_FF8BA494 \n"                     
"loc_FF8BA484:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	ADD	R1, SP, #0xC \n"                     
"	BL	sub_FF8BA2D4 \n"                      
"	B	loc_FF8BA418 \n"                       
"loc_FF8BA494:\n"
"	CMP	R1, #0x2B \n"                        
"	BNE	loc_FF8BA4AC \n"                     
"	BL	sub_FF8AA4D0 \n"                      
"	BL	sub_FF8AB0F4 \n"                      
"	BL	sub_FF8AAC48 \n"                      
"	B	loc_FF8BA418 \n"                       
"loc_FF8BA4AC:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	MOV	R4, #1 \n"                           
"	LDR	R1, [R0] \n"                         
"	CMP	R1, #0x11 \n"                        
"	CMPNE	R1, #0x12 \n"                      
"	BNE	loc_FF8BA51C \n"                     
"	LDR	R1, [R0, #0x7C] \n"                  
"	ADD	R1, R1, R1, LSL #1 \n"               
"	ADD	R1, R0, R1, LSL #2 \n"               
"	SUB	R1, R1, #8 \n"                       
"	LDMIA	R1, {R2-R4} \n"                    
"	STMIA	R6, {R2-R4} \n"                    
"	BL	sub_FF8B8BF0 \n"                      
"	LDR	R0, [SP, #0x1C] \n"                  
"	LDR	R1, [R0, #0x7C] \n"                  
"	LDR	R3, [R0, #0x8C] \n"                  
"	LDR	R2, [R0, #0x90] \n"                  
"	ADD	R0, R0, #4 \n"                       
"	BLX	R3 \n"                               
"	LDR	R0, [SP, #0x1C] \n"                  
"	BL	sub_FF8BB950 \n"                      
"	LDR	R0, [SP, #0x1C] \n"                  
"	LDR	R1, [R0, #0x7C] \n"                  
"	LDR	R3, [R0, #0x94] \n"                  
"	LDR	R2, [R0, #0x98] \n"                  
"	ADD	R0, R0, #4 \n"                       
"	BLX	R3 \n"                               
"	B	loc_FF8BA814 \n"                       
"loc_FF8BA51C:\n"
"	CMP	R1, #0x13 \n"                        
"	CMPNE	R1, #0x14 \n"                      
"	CMPNE	R1, #0x15 \n"                      
"	CMPNE	R1, #0x16 \n"                      
"	BNE	loc_FF8BA5D4 \n"                     
"	ADD	R3, SP, #0xC \n"                     
"	MOV	R2, SP \n"                           
"	ADD	R1, SP, #0x10 \n"                    
"	BL	sub_FF8B8ECC \n"                      
"	CMP	R0, #1 \n"                           
"	MOV	R4, R0 \n"                           
"	CMPNE	R4, #5 \n"                         
"	BNE	loc_FF8BA570 \n"                     
"	LDR	R0, [SP, #0x1C] \n"                  
"	MOV	R2, R4 \n"                           
"	LDR	R1, [R0, #0x7C]! \n"                 
"	LDR	R12, [R0, #0x10]! \n"                
"	LDR	R3, [R0, #4] \n"                     
"	MOV	R0, SP \n"                           
"	BLX	R12 \n"                              
"	B	loc_FF8BA5A8 \n"                       
"loc_FF8BA570:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	CMP	R4, #2 \n"                           
"	LDR	R3, [R0, #0x90] \n"                  
"	CMPNE	R4, #6 \n"                         
"	BNE	loc_FF8BA5BC \n"                     
"	LDR	R12, [R0, #0x8C] \n"                 
"	MOV	R0, SP \n"                           
"	MOV	R2, R4 \n"                           
"	MOV	R1, #1 \n"                           
"	BLX	R12 \n"                              
"	LDR	R0, [SP, #0x1C] \n"                  
"	MOV	R2, SP \n"                           
"	ADD	R1, SP, #0x10 \n"                    
"	BL	sub_FF8B9FE8 \n"                      
"loc_FF8BA5A8:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	LDR	R2, [SP, #0xC] \n"                   
"	MOV	R1, R4 \n"                           
"	BL	sub_FF8BA274 \n"                      
"	B	loc_FF8BA814 \n"                       
"loc_FF8BA5BC:\n"
"	LDR	R1, [R0, #0x7C] \n"                  
"	LDR	R12, [R0, #0x8C] \n"                 
"	ADD	R0, R0, #4 \n"                       
"	MOV	R2, R4 \n"                           
"	BLX	R12 \n"                              
"	B	loc_FF8BA814 \n"                       
"loc_FF8BA5D4:\n"
"	CMP	R1, #0x22 \n"                        
"	CMPNE	R1, #0x23 \n"                      
"	BNE	loc_FF8BA620 \n"                     
"	LDR	R1, [R0, #0x7C] \n"                  
"	ADD	R1, R1, R1, LSL #1 \n"               
"	ADD	R1, R0, R1, LSL #2 \n"               
"	SUB	R1, R1, #8 \n"                       
"	LDMIA	R1, {R2-R4} \n"                    
"	STMIA	R6, {R2-R4} \n"                    
"	BL	sub_FF8B8134 \n"                      
"	LDR	R0, [SP, #0x1C] \n"                  
"	LDR	R1, [R0, #0x7C] \n"                  
"	LDR	R3, [R0, #0x8C] \n"                  
"	LDR	R2, [R0, #0x90] \n"                  
"	ADD	R0, R0, #4 \n"                       
"	BLX	R3 \n"                               
"	LDR	R0, [SP, #0x1C] \n"                  
"	BL	sub_FF8B8434 \n"                      
"	B	loc_FF8BA814 \n"                       
"loc_FF8BA620:\n"
"	ADD	R1, R0, #4 \n"                       
"	LDMIA	R1, {R2,R3,R12} \n"                
"	STMIA	R6, {R2,R3,R12} \n"                
"	LDR	R1, [R0] \n"                         
"	CMP	R1, #0x25 \n"                        
"	ADDLS	PC, PC, R1, LSL #2 \n"             
"	B	loc_FF8BA7F4 \n"                       
"	B	loc_FF8BA6D4 \n"                       
"	B	loc_FF8BA6D4 \n"                       
"	B	loc_FF8BA6DC \n"                       
"	B	loc_FF8BA6E4 \n"                       
"	B	loc_FF8BA6E4 \n"                       
"	B	loc_FF8BA6E4 \n"                       
"	B	loc_FF8BA6D4 \n"                       
"	B	loc_FF8BA6DC \n"                       
"	B	loc_FF8BA6E4 \n"                       
"	B	loc_FF8BA6E4 \n"                       
"	B	loc_FF8BA6FC \n"                       
"	B	loc_FF8BA6FC \n"                       
"	B	loc_FF8BA7E8 \n"                       
"	B	loc_FF8BA7F0 \n"                       
"	B	loc_FF8BA7F0 \n"                       
"	B	loc_FF8BA7F0 \n"                       
"	B	loc_FF8BA7F0 \n"                       
"	B	loc_FF8BA7F4 \n"                       
"	B	loc_FF8BA7F4 \n"                       
"	B	loc_FF8BA7F4 \n"                       
"	B	loc_FF8BA7F4 \n"                       
"	B	loc_FF8BA7F4 \n"                       
"	B	loc_FF8BA7F4 \n"                       
"	B	loc_FF8BA6EC \n"                       
"	B	loc_FF8BA6F4 \n"                       
"	B	loc_FF8BA6F4 \n"                       
"	B	loc_FF8BA708 \n"                       
"	B	loc_FF8BA708 \n"                       
"	B	loc_FF8BA710 \n"                       
"	B	loc_FF8BA740 \n"                       
"	B	loc_FF8BA770 \n"                       
"	B	loc_FF8BA7A0 \n"                       
"	B	loc_FF8BA7D0 \n"                       
"	B	loc_FF8BA7D0 \n"                       
"	B	loc_FF8BA7F4 \n"                       
"	B	loc_FF8BA7F4 \n"                       
"	B	loc_FF8BA7D8 \n"                       
"	B	loc_FF8BA7E0 \n"                       
"loc_FF8BA6D4:\n"
"	BL	sub_FF8B6F2C \n"                      
"	B	loc_FF8BA7F4 \n"                       
"loc_FF8BA6DC:\n"
"	BL	sub_FF8B71B0 \n"                      
"	B	loc_FF8BA7F4 \n"                       
"loc_FF8BA6E4:\n"
"	BL	sub_FF8B73B8 \n"                      
"	B	loc_FF8BA7F4 \n"                       
"loc_FF8BA6EC:\n"
"	BL	sub_FF8B7630 \n"                      
"	B	loc_FF8BA7F4 \n"                       
"loc_FF8BA6F4:\n"
"	BL	sub_FF8B7828 \n"                      
"	B	loc_FF8BA7F4 \n"                       
"loc_FF8BA6FC:\n"
"	BL	sub_FF8B7AE4_my \n"    //----------------->                      
"	MOV	R4, #0 \n"                           
"	B	loc_FF8BA7F4 \n"                       
"loc_FF8BA708:\n"
"	BL	sub_FF8B7C24 \n"                      
"	B	loc_FF8BA7F4 \n"                       
"loc_FF8BA710:\n"
"	LDRH	R1, [R0, #4] \n"                    
"	STRH	R1, [SP, #0x10] \n"                 
"	LDRH	R1, [R5, #2] \n"                    
"	STRH	R1, [SP, #0x12] \n"                 
"	LDRH	R1, [R5, #4] \n"                    
"	STRH	R1, [SP, #0x14] \n"                 
"	LDRH	R1, [R5, #6] \n"                    
"	STRH	R1, [SP, #0x16] \n"                 
"	LDRH	R1, [R0, #0xC] \n"                  
"	STRH	R1, [SP, #0x18] \n"                 
"	BL	sub_FF8BB608 \n"                      
"	B	loc_FF8BA7F4 \n"                       
"loc_FF8BA740:\n"
"	LDRH	R1, [R0, #4] \n"                    
"	STRH	R1, [SP, #0x10] \n"                 
"	LDRH	R1, [R5, #2] \n"                    
"	STRH	R1, [SP, #0x12] \n"                 
"	LDRH	R1, [R5, #4] \n"                    
"	STRH	R1, [SP, #0x14] \n"                 
"	LDRH	R1, [R5, #6] \n"                    
"	STRH	R1, [SP, #0x16] \n"                 
"	LDRH	R1, [R5, #8] \n"                    
"	STRH	R1, [SP, #0x18] \n"                 
"	BL	sub_FF8BB768 \n"                      
"	B	loc_FF8BA7F4 \n"                       
"loc_FF8BA770:\n"
"	LDRH	R1, [R5] \n"                        
"	STRH	R1, [SP, #0x10] \n"                 
"	LDRH	R1, [R0, #6] \n"                    
"	STRH	R1, [SP, #0x12] \n"                 
"	LDRH	R1, [R5, #4] \n"                    
"	STRH	R1, [SP, #0x14] \n"                 
"	LDRH	R1, [R5, #6] \n"                    
"	STRH	R1, [SP, #0x16] \n"                 
"	LDRH	R1, [R5, #8] \n"                    
"	STRH	R1, [SP, #0x18] \n"                 
"	BL	sub_FF8BB814 \n"                      
"	B	loc_FF8BA7F4 \n"                       
"loc_FF8BA7A0:\n"
"	LDRH	R1, [R5] \n"                        
"	STRH	R1, [SP, #0x10] \n"                 
"	LDRH	R1, [R5, #2] \n"                    
"	STRH	R1, [SP, #0x12] \n"                 
"	LDRH	R1, [R5, #4] \n"                    
"	STRH	R1, [SP, #0x14] \n"                 
"	LDRH	R1, [R5, #6] \n"                    
"	STRH	R1, [SP, #0x16] \n"                 
"	LDRH	R1, [R0, #0xC] \n"                  
"	STRH	R1, [SP, #0x18] \n"                 
"	BL	sub_FF8BB8B4 \n"                      
"	B	loc_FF8BA7F4 \n"                       
"loc_FF8BA7D0:\n"
"	BL	sub_FF8B7F70 \n"                      
"	B	loc_FF8BA7F4 \n"                       
"loc_FF8BA7D8:\n"
"	BL	sub_FF8B8538 \n"                      
"	B	loc_FF8BA7F4 \n"                       
"loc_FF8BA7E0:\n"
"	BL	sub_FF8B8774 \n"                      
"	B	loc_FF8BA7F4 \n"                       
"loc_FF8BA7E8:\n"
"	BL	sub_FF8B88F0 \n"                      
"	B	loc_FF8BA7F4 \n"                       
"loc_FF8BA7F0:\n"
"	BL	sub_FF8B8A8C \n"                      
"loc_FF8BA7F4:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	LDR	R1, [R0, #0x7C] \n"                  
"	LDR	R3, [R0, #0x8C] \n"                  
"	LDR	R2, [R0, #0x90] \n"                  
"	ADD	R0, R0, #4 \n"                       
"	BLX	R3 \n"                               
"	CMP	R4, #1 \n"                           
"	BNE	loc_FF8BA85C \n"                     
"loc_FF8BA814:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	MOV	R2, #0xC \n"                         
"	LDR	R1, [R0, #0x7C] \n"                  
"	ADD	R1, R1, R1, LSL #1 \n"               
"	ADD	R0, R0, R1, LSL #2 \n"               
"	SUB	R4, R0, #8 \n"                       
"	LDR	R0, =0x4F45C \n"                     
"	ADD	R1, SP, #0x10 \n"                    
"	BL	sub_FFB3A548 \n"                      
"	LDR	R0, =0x4F468 \n"                     
"	MOV	R2, #0xC \n"                         
"	ADD	R1, SP, #0x10 \n"                    
"	BL	sub_FFB3A548 \n"                      
"	LDR	R0, =0x4F474 \n"                     
"	MOV	R2, #0xC \n"                         
"	MOV	R1, R4 \n"                           
"	BL	sub_FFB3A548 \n"                      
"	B	loc_FF8BA8D4 \n"                       
"loc_FF8BA85C:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	LDR	R0, [R0] \n"                         
"	CMP	R0, #0xB \n"                         
"	BNE	loc_FF8BA8A4 \n"                     
"	MOV	R3, #0 \n"                           
"	STR	R3, [SP] \n"                         
"	MOV	R3, #1 \n"                           
"	MOV	R2, #1 \n"                           
"	MOV	R1, #1 \n"                           
"	MOV	R0, #0 \n"                           
"	BL	sub_FF8B6D34 \n"                      
"	MOV	R3, #0 \n"                           
"	STR	R3, [SP] \n"                         
"	MOV	R3, #1 \n"                           
"	MOV	R2, #1 \n"                           
"	MOV	R1, #1 \n"                           
"	MOV	R0, #0 \n"                           
"	B	loc_FF8BA8D0 \n"                       
"loc_FF8BA8A4:\n"
"	MOV	R3, #1 \n"                           
"	MOV	R2, #1 \n"                           
"	MOV	R1, #1 \n"                           
"	MOV	R0, #1 \n"                           
"	STR	R3, [SP] \n"                         
"	BL	sub_FF8B6D34 \n"                      
"	MOV	R3, #1 \n"                           
"	MOV	R2, #1 \n"                           
"	MOV	R1, #1 \n"                           
"	MOV	R0, #1 \n"                           
"	STR	R3, [SP] \n"                         
"loc_FF8BA8D0:\n"
"	BL	sub_FF8B6E74 \n"                      
"loc_FF8BA8D4:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	BL	sub_FF8BB594 \n"                      
"	B	loc_FF8BA344 \n"                       
	);
}


//** sub_FF8B7A94_my  @ 0xFF8B7AE4 

void __attribute__((naked,noinline)) sub_FF8B7AE4_my(  ) { 
asm volatile (
"	STMFD	SP!, {R4-R8,LR} \n"                
"	LDR	R7, =0x4130 \n"                      
"	MOV	R4, R0 \n"                           
"	LDR	R0, [R7, #0x1C] \n"                  
"	MOV	R1, #0x3E \n"                        
"	BL	sub_FF880A48 \n"                      
"	LDRSH	R0, [R4, #4] \n"                   
"	MOV	R2, #0 \n"                           
"	MOV	R1, #0 \n"                           
"	BL	sub_FF8B6A98 \n"                      
"	MOV	R6, R0 \n"                           
"	LDRSH	R0, [R4, #6] \n"                   
"	BL	sub_FF8B6BA8 \n"                      
"	LDRSH	R0, [R4, #8] \n"                   
"	BL	sub_FF8B6C00 \n"                      
"	LDRSH	R0, [R4, #0xA] \n"                 
"	BL	sub_FF8B6C58 \n"                      
"	LDRSH	R0, [R4, #0xC] \n"                 
"	MOV	R1, #0 \n"                           
"	BL	sub_FF8B6CB0 \n"                      
"	MOV	R5, R0 \n"                           
"	LDR	R0, [R4] \n"                         
"	LDR	R8, =0x4F474 \n"                     
"	CMP	R0, #0xB \n"                         
"	MOVEQ	R6, #0 \n"                         
"	MOVEQ	R5, #0 \n"                         
"	BEQ	loc_FF8B7B78 \n"                     
"	CMP	R6, #1 \n"                           
"	BNE	loc_FF8B7B78 \n"                     
"	LDRSH	R0, [R4, #4] \n"                   
"	LDR	R1, =0xFF8B6A04 \n"                  
"	MOV	R2, #2 \n"                           
"	BL	sub_FF943DA4 \n"                      
"	STRH	R0, [R4, #4] \n"                    
"	MOV	R0, #0 \n"                           
"	STR	R0, [R7, #0x28] \n"                  
"	B	loc_FF8B7B80 \n"                       
"loc_FF8B7B78:\n"
"	LDRH	R0, [R8] \n"                        
"	STRH	R0, [R4, #4] \n"                    
"loc_FF8B7B80:\n"
"	CMP	R5, #1 \n"                           
"	LDRNEH	R0, [R8, #8] \n"                  
"	BNE	loc_FF8B7B9C \n"                     
"	LDRSH	R0, [R4, #0xC] \n"                 
"	LDR	R1, =0xFF8B6A88 \n"                  
"	MOV	R2, #0x20 \n"                        
"	BL	sub_FF8BB5C4 \n"                      
"loc_FF8B7B9C:\n"
"	STRH	R0, [R4, #0xC] \n"                  
"	LDRSH	R0, [R4, #6] \n"                   
"	BL	sub_FF8AA240_my \n"    //----------------->                     
"	LDRSH	R0, [R4, #8] \n"                   
"	MOV	R1, #1 \n"                           
"	BL	sub_FF8AA990 \n"                      
"	MOV	R1, #0 \n"                           
"	ADD	R0, R4, #8 \n"                       
"	BL	sub_FF8AAA18 \n"                      
"	LDRSH	R0, [R4, #0xE] \n"                 
"	BL	sub_FF8B2500 \n"                      
"	LDR	R4, =0xBB8 \n"                       
"	CMP	R6, #1 \n"                           
"	BNE	loc_FF8B7BF4 \n"                     
"	LDR	R0, [R7, #0x1C] \n"                  
"	MOV	R2, R4 \n"                           
"	MOV	R1, #2 \n"                           
"	BL	sub_FF880954 \n"                      
"	TST	R0, #1 \n"                           
"	LDRNE	R1, =0x59B \n"                     
"	LDRNE	R0, =0xFF8B7084 \n"                
"	BLNE	sub_FF81E88C \n"                    
"loc_FF8B7BF4:\n"
"	CMP	R5, #1 \n"                           
"	LDMNEFD	SP!, {R4-R8,PC} \n"              
"	LDR	R0, [R7, #0x1C] \n"                  
"	MOV	R2, R4 \n"                           
"	MOV	R1, #0x20 \n"                        
"	BL	sub_FF880954 \n"                      
"	TST	R0, #1 \n"                           
"	LDRNE	R0, =0xFF8B7084 \n"                
"	LDMNEFD	SP!, {R4-R8,LR} \n"              
"	MOVNE	R1, #0x5A0 \n"                     
"	BNE	sub_FF81E88C \n"                     
"	LDMFD	SP!, {R4-R8,PC} \n"                
	);
}


//** sub_FF8AA1F0_my  @ 0xFF8AA240 

void __attribute__((naked,noinline)) sub_FF8AA240_my(  ) { 
asm volatile (
"	STMFD	SP!, {R4-R6,LR} \n"                
"	LDR	R5, =0x3E48 \n"                      
"	MOV	R4, R0 \n"                           
"	LDR	R0, [R5, #4] \n"                     
"	CMP	R0, #1 \n"                           
"	LDRNE	R1, =0x146 \n"                     
"	LDRNE	R0, =0xFF8AA044 \n"                
"	BLNE	sub_FF81E88C \n"                    
"	CMN	R4, #0xC00 \n"                       
"	LDREQSH	R4, [R5, #2] \n"                 
"	CMN	R4, #0xC00 \n"                       
"	MOVEQ	R1, #0x14C \n"                     
"	LDREQ	R0, =0xFF8AA044 \n"                
"	STRH	R4, [R5, #2] \n"                    
"	BLEQ	sub_FF81E88C \n"                    
"	MOV	R0, R4 \n"                           
"	BL	sub_FF9FD5E8 \n"                      
"	MOV	R4, R0 \n"                           
"	BL	sub_FF8DF618 \n"                      
"	MOV	R0, R4 \n"                           
"	BL	sub_FF8E3310 \n"                      
"	TST	R0, #1 \n"                           
"	LDRNE	R1, =0x151 \n"                     
"	LDMNEFD	SP!, {R4-R6,LR} \n"              
"	LDRNE	R0, =0xFF8AA044 \n"                
"	BNE	sub_FF81E88C \n"                     
"	LDMFD	SP!, {R4-R6,PC} \n"                
	);
}
