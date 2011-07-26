// IXUS120-SD940 fw 1.01A
#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"

static long *nrflag = (long*)0x6718;			//

#include "../../../generic/capt_seq.c"

/*----------------------------------------------------------------------
	capt_seq_task()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) capt_seq_task() {
asm volatile (
"	STMFD	SP!, {R3-R9,LR} \n"                
"	LDR	R6, =0x2988 \n"                  
"	LDR	R4, =0x37B08 \n"                  
"	MOV	R9, #1 \n"                           
"	MOV	R7, #0 \n"                           
"loc_FF872F98:\n"
"	LDR	R0, [R6, #4] \n"                     
"	MOV	R2, #0 \n"                           
"	MOV	R1, SP \n"                           
"	BL	sub_FF837DC8 \n"                      
"	TST	R0, #1 \n"                           
"	BEQ	loc_FF872FC4 \n"                     
"	LDR	R1, =0x5B4 \n"                  
"	LDR	R0, =0xFF872B14 \n"                  
"	BL	sub_FF81E88C \n"                      
"	BL	sub_FF81E844 \n"                      
"	LDMFD	SP!, {R3-R9,PC} \n"                
"loc_FF872FC4:\n"
"	LDR	R0, [SP] \n"                     
"	LDR	R1, [R0] \n"                     
"	CMP	R1, #0x1D \n"                        
"	ADDLS	PC, PC, R1, LSL #2 \n" 
"	B	loc_FF873250 \n" 
            
"	B	loc_FF873050 \n"                       
"	B	loc_FF8730B4 \n"                       
"	B	loc_FF8730F0 \n"                       
"	B	loc_FF873104 \n"                       
"	B	loc_FF8730FC \n"                       
"	B	loc_FF87310C \n"                       
"	B	loc_FF873114 \n"                       
"	B	loc_FF87311C \n"                       
"	B	loc_FF873174 \n"                       
"	B	loc_FF87319C \n"                       
"	B	loc_FF873180 \n"                       
"	B	loc_FF87318C \n"                       
"	B	loc_FF873194 \n"                       
"	B	loc_FF8731A4 \n"                       
"	B	loc_FF8731AC \n"                       
"	B	loc_FF8731B4 \n"                       
"	B	loc_FF8731BC \n"                       
"	B	loc_FF8731C4 \n"                       
"	B	loc_FF8731D0 \n"                       
"	B	loc_FF8731D8 \n"                       
"	B	loc_FF8731E0 \n"                       
"	B	loc_FF8731E8 \n"                       
"	B	loc_FF8731F0 \n"                       
"	B	loc_FF8731FC \n"                       
"	B	loc_FF873204 \n"                       
"	B	loc_FF87320C \n"                       
"	B	loc_FF873214 \n"                       
"	B	loc_FF87321C \n"                       
"	B	loc_FF873228 \n"                       
"	B	loc_FF87325C \n"  
                     
"loc_FF873050:\n"
"	BL	sub_FF8738DC \n"  
"	BL	shooting_expo_param_override\n"			// added            
"	BL	sub_FF870DCC \n"                      

//  this code added to avoid some incorrect behavior if overrides are used.
 //  but it can cause some unexpected side effects. In this case, remove this code!
"		MOV R0,	#0\n"
"		STR R0,	[R4,#0x24]\n"  // fixes overrides  behavior at short shutter press

"	LDR	R0, [R4, #0x24] \n"                  
"	CMP	R0, #0 \n"                           
"	BEQ	loc_FF87325C \n"                     
"	BL	sub_FF8727F4 \n"                      
"	MOV	R5, R0 \n"                           
"	LDR	R0, [R4, #0x24] \n"                  
"	CMP	R0, #0 \n"                           
"	BEQ	loc_FF873098 \n"                     
"	MOV	R0, #0xC \n"                        
"	BL	sub_FF877A20 \n"                      
"	TST	R0, #1 \n"                           
"	STRNE	R9, [R6, #0x10] \n"                
"	LDRNE	R0, [R5, #8] \n"                   
"	ORRNE	R0, R0, #0x40000000 \n"               
"	STRNE	R0, [R5, #8] \n"                   
"	BNE	loc_FF87325C \n"  
                   
"loc_FF873098:\n"
"	MOV	R0, R5 \n"                           
"	BL	sub_FF872A98 \n"                      
"	MOV	R0, R5 \n"  
                         
//"	BL	sub_FF94242C \n"                      
"		BL		sub_FF94242C_my\n"				// patched

"	TST	R0, #1 \n"                           
"	STRNE	R9, [R6, #0x10] \n"                
"	B	loc_FF87325C \n"  
                     
"loc_FF8730B4:\n"
"	LDR	R0, [R4, #0x24] \n"                  
"	CMP	R0, #0 \n"                           
"	BNE	loc_FF8730E0 \n"                     
"	MOV	R0, #0xC \n"                        
"	BL	sub_FF877A20 \n"                      
"	TST	R0, #1 \n"                           
"	LDRNE	R0, [SP] \n"                   
"	MOVNE	R1, #1 \n"                         
"	LDRNE	R2, [R0, #0xC] \n"                
"	MOVNE	R0, #1 \n"                         
"	BNE	loc_FF87316C \n"  
                   
"loc_FF8730E0:\n"
"	LDR	R0, [SP] \n"                     
//"	BL	sub_FF873374 \n" 
"	BL	sub_FF873374_my \n"				// patched 

   
"loc_FF8730E8:\n"
"	STR	R7, [R4, #0x24] \n"                  
"	B	loc_FF87325C \n" 
                      
"loc_FF8730F0:\n"
"	MOV	R0, #1 \n"                           
"	BL	sub_FF873B30 \n"                      
"	B	loc_FF87325C \n" 
                      
"loc_FF8730FC:\n"
"	BL	sub_FF87351C \n"                      
"	B	loc_FF8730E8 \n"  
                     
"loc_FF873104:\n"
"	BL	sub_FF8738BC \n"                      
"	B	loc_FF8730E8 \n" 
                      
"loc_FF87310C:\n"
"	BL	sub_FF8738C4 \n"                      
"	B	loc_FF87325C \n"
                       
"loc_FF873114:\n"
"	BL	sub_FF873A50 \n"                      
"	B	loc_FF873178 \n" 
                      
"loc_FF87311C:\n"
"	LDR	R5, [R0, #0xC] \n"                  
"	BL	sub_FF8738CC \n"                      
"	MOV	R0, R5 \n"                           
"	BL	sub_FF941244 \n"                      
"	TST	R0, #1 \n"                           
"	MOV	R8, R0 \n"                           
"	BNE	loc_FF87315C \n"                     
"	BL	sub_FF884AD8 \n"                      
"	STR	R0, [R5, #0x18] \n"                  
"	MOV	R0, R5 \n"                           
"	BL	sub_FF942344 \n"                      
"	MOV	R0, R5 \n"                           
"	BL	sub_FF942740 \n"                      
"	MOV	R8, R0 \n"                           
"	LDR	R0, [R5, #0x18] \n"                  
"	BL	sub_FF884CDC \n"                      
"loc_FF87315C:\n"
"	BL	sub_FF8738BC \n"                      
"	MOV	R2, R5 \n"                           
"	MOV	R1, #9 \n"                           
"	MOV	R0, R8 \n"                           
"loc_FF87316C:\n"
"	BL	sub_FF8712B8 \n"                      
"	B	loc_FF87325C \n"
  
  
"loc_FF873174:\n"
"	BL	sub_FF873AB0 \n"                      
"loc_FF873178:\n"
"	BL	sub_FF870DCC \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF873180:\n"
"	LDR	R0, [R4, #0x54] \n"                  
"	BL	sub_FF873EBC \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF87318C:\n"
"	BL	sub_FF874170 \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF873194:\n"
"	BL	sub_FF874204 \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF87319C:\n"
"	BL	sub_FF8738BC \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF8731A4:\n"
"	BL	sub_FF94145C \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF8731AC:\n"
"	BL	sub_FF941670 \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF8731B4:\n"
"	BL	sub_FF941708 \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF8731BC:\n"
"	BL	sub_FF9417D8 \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF8731C4:\n"
"	MOV	R0, #0 \n"                           
"	BL	sub_FF941A28 \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF8731D0:\n"
"	BL	sub_FF941B78 \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF8731D8:\n"
"	BL	sub_FF941C08 \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF8731E0:\n"
"	BL	sub_FF941CC8 \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF8731E8:\n"
"	BL	sub_FF873CA8 \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF8731F0:\n"
"	BL	sub_FF873D48 \n"                      
"	BL	sub_FF835F18 \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF8731FC:\n"
"	BL	sub_FF9418A4 \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF873204:\n"
"	BL	sub_FF941910 \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF87320C:\n"
"	BL	sub_FF8761D0 \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF873214:\n"
"	BL	sub_FF876238 \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF87321C:\n"
"	BL	sub_FF876294 \n"                      
"	BL	sub_FF876254 \n"                      
"	B	loc_FF87325C \n"                       
"loc_FF873228:\n"
"	MOV	R0, #1 \n"                           
"	BL	sub_FF942F84 \n"                      
"	MOV	R0, #1 \n"                           
"	BL	sub_FF943094 \n"                      
"	LDRH	R0, [R4, #0x98] \n"                 
"	CMP	R0, #4 \n"                           
"	BNE	loc_FF87325C \n"                     
"	BL	sub_FF876238 \n"                      
"	BL	sub_FF876674 \n"                      
"	B	loc_FF87325C \n" 
                      
"loc_FF873250:\n"
"	LDR	R1, =0x709 \n"                  
"	LDR	R0, =0xFF872B14 \n"                  
"	BL	sub_FF81E88C \n"  
                    
"loc_FF87325C:\n"
"	LDR	R0, [SP] \n"                     
"	LDR	R1, [R0, #4] \n"                     
"	LDR	R0, [R6] \n"                     
"	BL	sub_FF87C7DC \n"                      
"	LDR	R5, [SP] \n"                     
"	LDR	R0, [R5, #8] \n"                     
"	CMP	R0, #0 \n"                           
"	LDREQ	R1, =0x132 \n"                
"	LDREQ	R0, =0xFF872B14 \n"                
"	BLEQ	sub_FF81E88C \n"                    
"	STR	R7, [R5, #8] \n"                     
"	B	loc_FF872F98 \n"               
	);
}


/*----------------------------------------------------------------------
	sub_FF94242C_my()  - capt_seq_task()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF94242C_my() {
asm volatile (
"	STMFD	SP!, {R0-R8,LR} \n"                
"	MOV	R4, R0 \n"                           
"	BL	sub_FF943280 \n"                      
"	MVN	R1, #0 \n"                           
"	BL	sub_FF87C810 \n"                      
"	LDR	R5, =0x6718 \n"                  
"	LDR	R0, [R5, #0xC] \n"                  
"	CMP	R0, #0 \n"                           
"	BNE	loc_FF94247C \n"                     
"	MOV	R1, #1 \n"                           
"	MOV	R0, #0 \n"                           
"	BL	sub_FF838610 \n"                      
"	STR	R0, [R5, #0xC] \n"                  
"	MOV	R3, #0 \n"                           
"	STR	R3, [SP] \n"                     
"	LDR	R3, =0xFF941DB8 \n"                  
"	LDR	R0, =0xFF9426A8 \n"                  
"	MOV	R2, #0x400\n"                     
"	MOV	R1, #0x17 \n"                        
"	BL	sub_FF8385DC \n"                      
"loc_FF94247C:\n"
"	MOV	R2, #4 \n"                           
"	ADD	R1, SP, #0x08 \n"                       
"	MOV	R0, #0x8A \n"                        
"	BL	sub_FF884948 \n"                      
"	TST	R0, #1 \n"                           
"	LDRNE	R1, =0x3C5 \n"                
"	LDRNE	R0, =0xFF942050 \n"                
"	BLNE	sub_FF81E88C \n"                    
"	LDR	R6, =0x37BCC \n"                  
"	LDR	R8, =0x37B08 \n"                  
"	LDRSH	R2, [R6, #0xC] \n"                
"	LDRSH	R1, [R6, #0xE] \n"                
"	LDR	R0, [R8, #0x8C] \n"                  
"	BL	sub_FF90B564 \n"                      
"	BL	sub_FF85BC98 \n"                      
"	LDR	R3, =0x6720 \n"                  
"	STRH	R0, [R4, #0xA4] \n"                 
"	SUB	R2, R3, #4 \n"                       
"	STRD	R2, [SP]\n"               
"	MOV	R1, R0 \n"                           
"	LDRH	R0, [R8, #0x5C] \n"                 
"	LDRSH	R2, [R6, #0xC] \n"                
"	SUB	R3, R3, #8 \n"                       
"	BL	sub_FF9448C4 \n"  

"	BL      wait_until_remote_button_is_released\n"
"	BL      capt_seq_hook_set_nr\n"

                    
"	LDR	R0, [R4, #0x1C] \n"                  
"	CMP	R0, #0 \n"                           
"	MOVNE	R0, #1 \n"                         
"	STRNE	R0, [R5] \n"                   
"	LDR	R0, [R5, #4] \n"                     
"	BL	sub_FF90B814 \n"                      
"	LDR	R0, [R5, #8] \n"                     
"	BL	sub_FF8B9E64 \n"                      
"	MOV	R0, #1 \n"                           
"	BL	sub_FF8B9E70 \n"                      
"	LDR	R0, =0xFF941E28 \n"                  
"	MOV	R1, R4 \n"                           
"	BL	sub_FF8B9E40 \n"                      
"	LDR	R0, [R5] \n"                     
"	CMP	R0, #5 \n"                           
"	ADDLS	PC, PC, R0, LSL #2 \n"             

"	B	sub_FF9425E8 \n"   // go to the ROM                   
	);
}


	
/*----------------------------------------------------------------------
	sub_FF873374_my() - capt_seq_task()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF873374_my() {
asm volatile (
"	STMFD	SP!, {R4-R6,LR} \n"                
"	LDR	R4, [R0, #0xC] \n"                  
"	LDR	R6, =0x37B08 \n"                  
"	LDR	R0, [R4, #8] \n"                     
"	MOV	R5, #0 \n"                           
"	ORR	R0, R0, #1 \n"                       
"	STR	R0, [R4, #8] \n"                     
"	LDR	R0, [R6, #0x24] \n"                  
"	CMP	R0, #0 \n"                           
"	MOVEQ	R0, #2 \n"                         
"	BLEQ	sub_FF86F4AC \n"                    
"	BL		sub_FF8738CC \n"                      
"	LDR	R0, [R6, #0x24] \n"                  
"	CMP	R0, #0 \n"                           
"	BNE	loc_FF87343C \n"                     
"	MOV	R0, #0 \n"                           
"	BL	sub_FF942F84 \n"                      
"	MOV	R0, #0 \n"                           
"	BL	sub_FF943094 \n"                      
"	MOV	R0, R4 \n"                           
"	BL	sub_FF873C50 \n"                      
"	MOV	R0, R4 \n"                           
"	BL	sub_FF940E94 \n"                      
"	CMP	R0, #0 \n"                           
"	BEQ	loc_FF873404 \n"                     
"	BL	sub_FF942FC4 \n"                      
"	BL	sub_FF9430D8 \n"                      
"	BL	sub_FF943128 \n"                      
"	MOV	R0, R4 \n"                           
"	BL	sub_FF940F78 \n"                      
"	TST	R0, #1 \n"                           
"	MOVNE	R2, R4 \n"                         
"	LDMNEFD	SP!, {R4-R6,LR} \n"              
"	MOVNE	R1, #1 \n"                         
"	BNE	sub_FF8712B8 \n"                     
"	B	loc_FF873418 \n"                       
"loc_FF873404:\n"
"	MOV	R0, R4 \n"                           
"	BL	sub_FF940F14 \n"                      
"	BL	sub_FF942FC4 \n"                      
"	BL	sub_FF9430D8 \n"                      
"	BL	sub_FF943128 \n"                      
"loc_FF873418:\n"
"	MOV	R0, R4 \n"                           
"	BL	sub_FF872A98 \n"                      
"	MOV	R0, R4 \n"                           
"	BL	sub_FF942344 \n"                      
"	BL	sub_FF942DBC \n"                      
"	MOV	R0, R4 \n"  

// this patch causes a crash when shooting
// it is unknown what the effect is of not calling this	(called elsewhere)	                 
"	BL	sub_FF94242C \n"  
//"	BL	sub_FF94242C_my \n"                    
"	MOV	R5, R0 \n"  
"	BL		capt_seq_hook_raw_here\n"  //----------->>                         
"	B	loc_FF87344C \n" 
// ---------------------------------------------------------------------------


"loc_FF87343C:\n"
"	LDR	R0, =0x2988 \n"                  
"	LDR	R0, [R0, #0x10] \n"                  
"	CMP	R0, #0 \n"                           
"	MOVNE	R5, #0x1D \n"   
                   
"loc_FF87344C:\n"
"	BL	sub_FF876238 \n"                      
"	BL	sub_FF876280 \n"                      
"	BL	sub_FF8762C0 \n"                      
"	MOV	R2, R4 \n"                           
"	MOV	R1, #1 \n"                           
"	MOV	R0, R5 \n"                           
"	BL	sub_FF8712B8 \n"                      
"	BL	sub_FF9426E4 \n"                      
"	CMP	R0, #0 \n"                           
"	LDRNE	R0, [R4, #8] \n"                   
"	ORRNE	R0, R0, #0x2000 \n"               
"	STRNE	R0, [R4, #8] \n"                   
"	LDMFD	SP!, {R4-R6,PC} \n"                 
	);
}


/*----------------------------------------------------------------------
	exp_drv_task()  FF8B2F74
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) exp_drv_task() {
asm volatile (
"	STMFD	SP!, {R4-R8,LR} \n"                
"	SUB	SP, SP, #0x20 \n"                    
"	LDR	R8, =0xBB8 \n"                  
"	LDR	R7, =0x3C80 \n"                  
"	LDR	R5, =0x3C760 \n"                  
"	MOV	R0, #0 \n"                           
"	ADD	R6, SP, #0x10 \n"                    
"	STR	R0, [SP, #0x0C] \n"                  
"loc_FF8B2F94:\n"
"	LDR	R0, [R7, #0x20] \n"                  
"	MOV	R2, #0 \n"                           
"	ADD	R1, SP, #0x1C \n"                    
"	BL	sub_FF837DC8 \n"                      
"	LDR	R0, [SP, #0x0C] \n"                  
"	CMP	R0, #1 \n"                           
"	BNE	loc_FF8B2FE0 \n"                     
"	LDR	R0, [SP, #0x1C] \n"                  
"	LDR	R0, [R0] \n"                     
"	CMP	R0, #0x13 \n"                        
"	CMPNE	R0, #0x14 \n"                      
"	CMPNE	R0, #0x15 \n"                      
"	CMPNE	R0, #0x16 \n"                      
"	BEQ		loc_FF8B30FC \n"                     
"	CMP	R0, #0x28 \n"                        
"	BEQ		loc_FF8B30D4 \n"                     
"	ADD	R1, SP, #0x0C \n"                    
"	MOV	R0, #0 \n"                           
"	BL	sub_FF8B2F24 \n"                      
"loc_FF8B2FE0:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	LDR	R1, [R0] \n"                     
"	CMP	R1, #0x2D \n"                        
"	BNE		loc_FF8B3010 \n"                     
"	LDR	R0, [SP, #0x1C] \n"                  
"	BL	sub_FF8B41E4 \n"                      
"	LDR	R0, [R7, #0x1C] \n"                  
"	MOV	R1, #1 \n"                           
"	BL	sub_FF87C7DC \n"                      
"	BL	sub_FF81E844 \n"                      
"	ADD	SP, SP, #0x20 \n"                    
"	LDMFD	SP!, {R4-R8,PC} \n"                
"loc_FF8B3010:\n"
"	CMP	R1, #0x2C \n"                        
"	BNE	loc_FF8B302C \n"                     
"	LDR	R2, [R0, #0x8C]! \n"                 
"	LDR	R1, [R0, #4] \n"                     
"	MOV	R0, R1 \n"                           
"	BLX	R2 \n"                               
"	B	loc_FF8B3524 \n"                       
"loc_FF8B302C:\n"
"	CMP	R1, #0x26 \n"                        
"	BNE	loc_FF8B307C \n"                     
"	LDR	R0, [R7, #0x1C] \n"                  
"	MOV	R1, #0x80 \n"                        
"	BL	sub_FF87C810 \n"                      
"	LDR	R0, =0xFF8AF684 \n"                  
"	MOV	R1, #0x80 \n"                        
"	BL	sub_FF936254 \n"                      
"	LDR	R0, [R7, #0x1C] \n"                  
"	MOV	R2, R8 \n"                           
"	MOV	R1, #0x80 \n"                        
"	BL	sub_FF87C71C \n"                      
"	TST	R0, #1 \n"                           
"	LDRNE	R1, =0xE54 \n"                
"	BNE		loc_FF8B30C0 \n"                     
"loc_FF8B3068:\n"
"	LDR	R1, [SP, #0x1C] \n"                  
"	LDR	R0, [R1, #0x90] \n"                  
"	LDR	R1, [R1, #0x8C] \n"                  
"	BLX	R1 \n"                               
"	B	loc_FF8B3524 \n"                       
"loc_FF8B307C:\n"
"	CMP	R1, #0x27 \n"                        
"	BNE	loc_FF8B30CC \n"                     
"	ADD	R1, SP, #0xC \n"                    
"	BL	sub_FF8B2F24 \n"                      
"	LDR	R0, [R7, #0x1C] \n"                  
"	MOV	R1, #0x100 \n"                       
"	BL	sub_FF87C810 \n"                      
"	LDR	R0, =0xFF8AF694 \n"                  
"	MOV	R1, #0x100 \n"                       
"	BL	sub_FF9364DC \n"                      
"	LDR	R0, [R7, #0x1C] \n"                  
"	MOV	R2, R8 \n"                           
"	MOV	R1, #0x100 \n"                       
"	BL	sub_FF87C71C \n"                      
"	TST	R0, #1 \n"                           
"	BEQ	loc_FF8B3068 \n"                     
"	LDR	R1, =0xE5E \n"                  
"loc_FF8B30C0:\n"
"	LDR	R0, =0xFF8AFCF8 \n"                  
"	BL	sub_FF81E88C \n"                      
"	B	loc_FF8B3068 \n"                       
"loc_FF8B30CC:\n"
"	CMP	R1, #0x28 \n"                        
"	BNE	loc_FF8B30E4 \n"                     
"loc_FF8B30D4:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	ADD	R1, SP, #0x0C \n"                    
"	BL	sub_FF8B2F24 \n"                      
"	B	loc_FF8B3068 \n"                       
"loc_FF8B30E4:\n"
"	CMP	R1, #0x2B \n"                        
"	BNE	loc_FF8B30FC \n"                     
"	BL	sub_FF8A3194 \n"                      
"	BL	sub_FF8A3DB8 \n"                      
"	BL	sub_FF8A390C \n"                      
"	B	loc_FF8B3068 \n"                       
"loc_FF8B30FC:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	MOV	R4, #1 \n"                           
"	LDR	R1, [R0] \n"                     
"	CMP	R1, #0x11 \n"                        
"	CMPNE	R1, #0x12 \n"                      
"	BNE	loc_FF8B316C \n"                     
"	LDR	R1, [R0, #0x7C] \n"                  
"	ADD	R1, R1, R1, LSL #1 \n"               
"	ADD	R1, R0, R1, LSL #2 \n"               
"	SUB	R1, R1, #8 \n"                       
"	LDMIA	R1, {R2-R4} \n"                    
"	STMIA	R6, {R2-R4} \n"                    
"	BL	sub_FF8B1838 \n"                      
"	LDR	R0, [SP, #0x1C] \n"                  
"	LDR	R1, [R0, #0x7C] \n"                  
"	LDR	R3, [R0, #0x8C] \n"                  
"	LDR	R2, [R0, #0x90] \n"                  
"	ADD	R0, R0, #4 \n"                       
"	BLX	R3 \n"                               
"	LDR	R0, [SP, #0x1C] \n"                  
"	BL	sub_FF8B45A4 \n"                      
"	LDR	R0, [SP, #0x1C] \n"                  
"	LDR	R1, [R0, #0x7C] \n"                  
"	LDR	R3, [R0, #0x94] \n"                  
"	LDR	R2, [R0, #0x98] \n"                  
"	ADD	R0, R0, #4 \n"                       
"	BLX	R3 \n"                               
"	B	loc_FF8B3464 \n"                       
"loc_FF8B316C:\n"
"	CMP	R1, #0x13 \n"                        
"	CMPNE	R1, #0x14 \n"                      
"	CMPNE	R1, #0x15 \n"                      
"	CMPNE	R1, #0x16 \n"                      
"	BNE	loc_FF8B3224 \n"                     
"	ADD	R3, SP, #0x0C \n"                    
"	MOV	R2, SP \n"                           
"	ADD	R1, SP, #0x10 \n"                    
"	BL	sub_FF8B1B20 \n"                      
"	CMP	R0, #1 \n"                           
"	MOV	R4, R0 \n"                           
"	CMPNE	R4, #5 \n"                         
"	BNE	loc_FF8B31C0 \n"                     
"	LDR	R0, [SP, #0x1C] \n"                  
"	MOV	R2, R4 \n"                           
"	LDR	R1, [R0, #0x7C]! \n"                 
"	LDR	R12, [R0, #0x10]! \n"                
"	LDR	R3, [R0, #4] \n"                     
"	MOV	R0, SP \n"                           
"	BLX	R12 \n"                              
"	B	loc_FF8B31F8 \n"                       
"loc_FF8B31C0:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	CMP	R4, #2 \n"                           
"	LDR	R3, [R0, #0x90] \n"                  
"	CMPNE	R4, #6 \n"                         
"	BNE	loc_FF8B320C \n"                     
"	LDR	R12, [R0, #0x8C] \n"                 
"	MOV	R0, SP \n"                           
"	MOV	R2, R4 \n"                           
"	MOV	R1, #1 \n"                           
"	BLX	R12 \n"                              
"	LDR	R0, [SP, #0x1C] \n"                  
"	MOV	R2, SP \n"                           
"	ADD	R1, SP, #0x10 \n"                    
"	BL	sub_FF8B2C38 \n"                      
"loc_FF8B31F8:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	LDR	R2, [SP, #0x0C] \n"                  
"	MOV	R1, R4 \n"                           
"	BL	sub_FF8B2EC4 \n"                      
"	B	loc_FF8B3464 \n"                       
"loc_FF8B320C:\n"
"	LDR	R1, [R0, #0x7C] \n"                  
"	LDR	R12, [R0, #0x8C] \n"                 
"	ADD	R0, R0, #4 \n"                       
"	MOV	R2, R4 \n"                           
"	BLX	R12 \n"                              
"	B	loc_FF8B3464 \n"                       
"loc_FF8B3224:\n"
"	CMP	R1, #0x22 \n"                        
"	CMPNE	R1, #0x23 \n"                      
"	BNE	loc_FF8B3270 \n"                     
"	LDR	R1, [R0, #0x7C] \n"                  
"	ADD	R1, R1, R1, LSL #1 \n"               
"	ADD	R1, R0, R1, LSL #2 \n"               
"	SUB	R1, R1, #8 \n"                       
"	LDMIA	R1, {R2-R4} \n"                    
"	STMIA	R6, {R2-R4} \n"                    
"	BL	sub_FF8B0D88 \n"                      
"	LDR	R0, [SP, #0x1C] \n"                  
"	LDR	R1, [R0, #0x7C] \n"                  
"	LDR	R3, [R0, #0x8C] \n"                  
"	LDR	R2, [R0, #0x90] \n"                  
"	ADD	R0, R0, #4 \n"                       
"	BLX	R3 \n"                               
"	LDR	R0, [SP, #0x1C] \n"                  
"	BL	sub_FF8B107C \n"                      
"	B	loc_FF8B3464 \n"                       
"loc_FF8B3270:\n"
"	ADD	R1, R0, #4 \n"                       
"	LDMIA	R1, {R2,R3,R12} \n"                
"	STMIA	R6, {R2,R3,R12} \n"                
"	LDR	R1, [R0] \n"                     
"	CMP	R1, #0x25 \n"                        
"	ADDLS	PC, PC, R1, LSL #2 \n"             
"	B	loc_FF8B3444 \n"  
                     
"	B	loc_FF8B3324 \n"                       
"	B	loc_FF8B3324 \n"                       
"	B	loc_FF8B332C \n"                       
"	B	loc_FF8B3334 \n"                       
"	B	loc_FF8B3334 \n"                       
"	B	loc_FF8B3334 \n"                       
"	B	loc_FF8B3324 \n"                       
"	B	loc_FF8B332C \n"                       
"	B	loc_FF8B3334 \n"                       
"	B	loc_FF8B3334 \n"                       
"	B	loc_FF8B334C \n"                       
"	B	loc_FF8B334C \n"                       
"	B	loc_FF8B3438 \n"                       
"	B	loc_FF8B3440 \n"                       
"	B	loc_FF8B3440 \n"                       
"	B	loc_FF8B3440 \n"                       
"	B	loc_FF8B3440 \n"                       
"	B	loc_FF8B3444 \n"                       
"	B	loc_FF8B3444 \n"                       
"	B	loc_FF8B3444 \n"                       
"	B	loc_FF8B3444 \n"                       
"	B	loc_FF8B3444 \n"                       
"	B	loc_FF8B3444 \n"                       
"	B	loc_FF8B333C \n"                       
"	B	loc_FF8B3344 \n"                       
"	B	loc_FF8B3344 \n"                       
"	B	loc_FF8B3358 \n"                       
"	B	loc_FF8B3358 \n"                       
"	B	loc_FF8B3360 \n"                       
"	B	loc_FF8B3390 \n"                       
"	B	loc_FF8B33C0 \n"                       
"	B	loc_FF8B33F0 \n"                       
"	B	loc_FF8B3420 \n"                       
"	B	loc_FF8B3420 \n"                       
"	B	loc_FF8B3444 \n"                       
"	B	loc_FF8B3444 \n"                       
"	B	loc_FF8B3428 \n"                       
"	B	loc_FF8B3430 \n"


"loc_FF8B3324:\n"
"	BL	sub_FF8AFB9C \n"                      
"	B	loc_FF8B3444 \n"  
                     
"loc_FF8B332C:\n"
"	BL	sub_FF8AFE24 \n"                      
"	B	loc_FF8B3444 \n"   
                    
"loc_FF8B3334:\n"
"	BL	sub_FF8B002C \n"                      
"	B	loc_FF8B3444 \n" 
        
		
"loc_FF8B333C:\n"
"	BL	sub_FF8B02A4 \n"                      
"	B	loc_FF8B3444 \n"
                       
"loc_FF8B3344:\n"
"	BL	sub_FF8B049C \n"                      
"	B	loc_FF8B3444 \n" 
                      
"loc_FF8B334C:\n"
//"	BL	sub_FF8B0758 \n"    
"	BL	sub_FF8B0758_my \n"    //----->>>

                  
"	MOV	R4, #0 \n"                           
"	B	loc_FF8B3444 \n"  
                     
"loc_FF8B3358:\n"
"	BL	sub_FF8B0898 \n"                      
"	B	loc_FF8B3444 \n"  
                     
"loc_FF8B3360:\n"
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
"	BL	sub_FF8B4258 \n"                      
"	B	loc_FF8B3444 \n"   
                    
"loc_FF8B3390:\n"
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
"	BL	sub_FF8B43BC \n"                      
"	B	loc_FF8B3444 \n"      
                 
"loc_FF8B33C0:\n"
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
"	BL	sub_FF8B4468 \n"                      
"	B	loc_FF8B3444 \n"  
                     
"loc_FF8B33F0:\n"
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
"	BL	sub_FF8B4508 \n"                      
"	B	loc_FF8B3444 \n" 
                     
"loc_FF8B3420:\n"
"	BL	sub_FF8B0BE0 \n"                      
"	B	loc_FF8B3444 \n"  
                     
"loc_FF8B3428:\n"
"	BL	sub_FF8B1180 \n"                      
"	B	loc_FF8B3444 \n"  
                     
"loc_FF8B3430:\n"
"	BL	sub_FF8B13BC \n"                      
"	B	loc_FF8B3444 \n" 
                      
"loc_FF8B3438:\n"
"	BL	sub_FF8B1538 \n"                      
"	B	loc_FF8B3444 \n" 
                      
"loc_FF8B3440:\n"
"	BL	sub_FF8B16D4 \n" 
                     
"loc_FF8B3444:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	LDR	R1, [R0, #0x7C] \n"                  
"	LDR	R3, [R0, #0x8C] \n"                  
"	LDR	R2, [R0, #0x90] \n"                  
"	ADD	R0, R0, #4 \n"                       
"	BLX	R3 \n"                               
"	CMP	R4, #1 \n"                           
"	BNE	loc_FF8B34AC \n" 
                    
"loc_FF8B3464:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	MOV	R2, #0xC \n"                        
"	LDR	R1, [R0, #0x7C] \n"                  
"	ADD	R1, R1, R1, LSL #1 \n"               
"	ADD	R0, R0, R1, LSL #2 \n"               
"	SUB	R4, R0, #8 \n"                       
"	LDR	R0, =0x3C760 \n"                  
"	ADD	R1, SP, #0x10 \n"                    
"	BL	sub_FFB077B8 \n"                      
"	LDR	R0, =0x3C76C \n"                  
"	MOV	R2, #0xC \n"                        
"	ADD	R1, SP, #0x10 \n"                    
"	BL	sub_FFB077B8 \n"                      
"	LDR	R0, =0x3C778 \n"                  
"	MOV	R2, #0xC \n"                        
"	MOV	R1, R4 \n"                           
"	BL	sub_FFB077B8 \n"                      
"	B	loc_FF8B3524 \n"                       
"loc_FF8B34AC:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	LDR	R0, [R0] \n"                     
"	CMP	R0, #0xB \n"                        
"	BNE	loc_FF8B34F4 \n"                     
"	MOV	R3, #0 \n"                           
"	STR	R3, [SP] \n"                     
"	MOV	R3, #1 \n"                           
"	MOV	R2, #1 \n"                           
"	MOV	R1, #1 \n"                           
"	MOV	R0, #0 \n"                           
"	BL	sub_FF8AF9A4 \n"                      
"	MOV	R3, #0 \n"                           
"	STR	R3, [SP] \n"                     
"	MOV	R3, #1 \n"                           
"	MOV	R2, #1 \n"                           
"	MOV	R1, #1 \n"                           
"	MOV	R0, #0 \n"                           
"	B	loc_FF8B3520 \n"                       
"loc_FF8B34F4:\n"
"	MOV	R3, #1 \n"                           
"	MOV	R2, #1 \n"                           
"	MOV	R1, #1 \n"                           
"	MOV	R0, #1 \n"                           
"	STR	R3, [SP] \n"                     
"	BL	sub_FF8AF9A4 \n"                      
"	MOV	R3, #1 \n"                           
"	MOV	R2, #1 \n"                           
"	MOV	R1, #1 \n"                           
"	MOV	R0, #1 \n"                           
"	STR	R3, [SP] \n" 
                    
"loc_FF8B3520:\n"
"	BL	sub_FF8AFAE4 \n"  
                    
"loc_FF8B3524:\n"
"	LDR	R0, [SP, #0x1C] \n"                  
"	BL	sub_FF8B41E4 \n"                      
"	B	loc_FF8B2F94 \n"               
	);
}

/*----------------------------------------------------------------------
	sub_FF8B0758_my() - exp_drv_task()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF8B0758_my() {
asm volatile (
"	STMFD	SP!, {R4-R8,LR} \n"                
"	LDR	R7, =0x3C80 \n"                  
"	MOV	R4, R0 \n"                           
"	LDR	R0, [R7, #0x1C] \n"                  
"	MOV	R1, #0x3E \n"                        
"	BL	sub_FF87C810 \n"                      
"	LDRSH	R0, [R4, #4] \n"                   
"	MOV	R2, #0 \n"                           
"	MOV	R1, #0 \n"                           
"	BL	sub_FF8AF708 \n"                      
"	MOV	R6, R0 \n"                           
"	LDRSH	R0, [R4, #6] \n"                   
"	BL	sub_FF8AF818 \n"                      
"	LDRSH	R0, [R4, #8] \n"                   
"	BL	sub_FF8AF870 \n"                      
"	LDRSH	R0, [R4, #0xA] \n"                
"	BL	sub_FF8AF8C8 \n"                      
"	LDRSH	R0, [R4, #0xC] \n"                
"	MOV	R1, #0 \n"                           
"	BL	sub_FF8AF920 \n"                      
"	MOV	R5, R0 \n"                           
"	LDR	R0, [R4] \n"                     
"	LDR	R8, =0x3C778 \n"                  
"	CMP	R0, #0xB \n"                        
"	MOVEQ	R6, #0 \n"                         
"	MOVEQ	R5, #0 \n"                         
"	BEQ		loc_FF8B07EC \n"                     
"	CMP	R6, #1 \n"                           
"	BNE		loc_FF8B07EC \n"                     
"	LDRSH	R0, [R4, #4] \n"                   
"	LDR	R1, =0xFF8AF674 \n"                  
"	MOV	R2, #2 \n"                           
"	BL	sub_FF9363A8 \n"                      
"	STRH	R0, [R4, #4] \n"                    
"	MOV	R0, #0 \n"                           
"	STR	R0, [R7, #0x28] \n"                  
"	B		loc_FF8B07F4 \n"                       
"loc_FF8B07EC:\n"
"	LDRH	R0, [R8, #0] \n"                    
"	STRH	R0, [R4, #4] \n"                    
"loc_FF8B07F4:\n"
"	CMP	R5, #1 \n"                           
"	LDRNEH	R0, [R8, #8] \n"                  
"	BNE		loc_FF8B0810 \n"                     
"	LDRSH	R0, [R4, #0xC] \n"                
"	LDR	R1, =0xFF8AF6F8 \n"                  
"	MOV	R2, #0x20 \n"                        
"	BL	sub_FF8B4214 \n"                      
"loc_FF8B0810:\n"
"	STRH	R0, [R4, #0xC] \n"                 
"	LDRSH	R0, [R4, #6] \n" 
                  
//"	BL	sub_FF8A2F04 \n" 
"	BL	sub_FF8A2F04_my \n"   //------------->>>
   
"	LDRSH	R0, [R4, #8] \n"                   
"	MOV	R1, #1 \n"                           
"	BL	sub_FF8A3654 \n"                      
"	MOV	R1, #0 \n"                           
"	ADD	R0, R4, #8 \n"                       
"	BL	sub_FF8A36DC \n"                      
"	LDRSH	R0, [R4, #0xE] \n"                
"	BL	sub_FF8AB1C8 \n"                      
"	LDR	R4, =0xBB8 \n"                  
"	CMP	R6, #1 \n"                           
"	BNE		loc_FF8B0868 \n"                     
"	LDR	R0, [R7, #0x1C] \n"                  
"	MOV	R2, R4 \n"                           
"	MOV	R1, #2 \n"                           
"	BL	sub_FF87C71C \n"                      
"	TST	R0, #1 \n"                           
"	SUBNE	R1, R4, #0x620 \n"                 
"	LDRNE	R0, =0xFF8AFCF8 \n"                
"	BLNE	sub_FF81E88C \n"                    
"loc_FF8B0868:\n"
"	CMP	R5, #1 \n"                           
"	LDMNEFD	SP!, {R4-R8,PC} \n"              
"	LDR	R0, [R7, #0x1C] \n"                  
"	MOV	R2, R4 \n"                           
"	MOV	R1, #0x20 \n"                        
"	BL	sub_FF87C71C \n"                      
"	TST	R0, #1 \n"                           
"	LDRNE	R1, =0x59D \n"                
"	LDRNE	R0, =0xFF8AFCF8 \n"                
"	LDMNEFD	SP!, {R4-R8,LR} \n"              
"	BNE	sub_FF81E88C \n"                     
"	LDMFD	SP!, {R4-R8,PC} \n"              
	);
}


/*----------------------------------------------------------------------
	sub_FF8A2F04_my() - exp_drv_task()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF8A2F04_my() {
asm volatile (
"	STMFD	SP!, {R4-R6,LR} \n"                
"	LDR	R5, =0x3998 \n"                  
"	MOV	R4, R0 \n"                           
"	LDR	R0, [R5, #4] \n"                     
"	CMP	R0, #1 \n"                           
"	LDRNE	R1, =0x146 \n"                
"	LDRNE	R0, =0xFF8A2D08 \n"                
"	BLNE	sub_FF81E88C \n"                    
"	CMN	R4, #0xC00 \n"                       
"	LDREQSH	R4, [R5, #2] \n"                 
"	CMN	R4, #0xC00 \n"                       
"	MOVEQ	R1, #0x14C \n"                     
"	LDREQ	R0, =0xFF8A2D08 \n"                
"	STRH	R4, [R5, #2] \n"                    
"	BLEQ	sub_FF81E88C \n"                    
"	MOV	R0, R4 \n"  
                         
//"	BL	sub_FF9D5394 \n"   	// old??? apex2us                   
"	BL	apex2us\n"		//--------------->>

"	MOV	R4, R0 \n"                           
//"	BL	sub_FF8D7B04 \n"                      
"	MOV	R0, R4 \n"                           
"	BL	sub_FF8DB778 \n"                      
"	TST	R0, #1 \n"                           
"	LDRNE	R1, =0x0151 \n"                
"	LDMNEFD	SP!, {R4-R6,LR} \n"              
"	LDRNE	R0, =0xFF8A2D08 \n"                
"	BNE	sub_FF81E88C \n"                     
"	LDMFD	SP!, {R4-R6,PC} \n"                
	);
}

