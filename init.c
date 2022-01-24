//-------------------------------------------------------------------------
//  
//  Description:  Contains the code to initialize MSP ports.
//
//  Alex Carter
//  Jan 2019
//  Built with IAR Embedded Workbench Version: 7.12.1
//-------------------------------------------------------------------------

#include "functions.h"
#include "msp430.h"
#include "macros.h"
#include <string.h>

extern char display_line[4][DISPLAY_LENGTH];
extern char *display[4];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;


void Init_Conditions(void){
  
//------------------------------------------------------------------------------
  int i;

  for(i=DEC_ZERO;i<DISPLAY_LENGTH;i++){
    display_line[DISPLAY_LINE0][i] = RESET_STATE;
    display_line[DISPLAY_LINE1][i] = RESET_STATE;
    display_line[DISPLAY_LINE2][i] = RESET_STATE;
    display_line[DISPLAY_LINE3][i] = RESET_STATE;
  }
  display_line[DISPLAY_LINE0][NULL_LOC] = DEC_ZERO;
  display_line[DISPLAY_LINE1][NULL_LOC] = DEC_ZERO;
  display_line[DISPLAY_LINE2][NULL_LOC] = DEC_ZERO;
  display_line[DISPLAY_LINE3][NULL_LOC] = DEC_ZERO;

  display[DISPLAY_LINE0] = &display_line[DISPLAY_LINE0][DEC_ZERO];
  display[DISPLAY_LINE1] = &display_line[DISPLAY_LINE1][DEC_ZERO];
  display[DISPLAY_LINE2] = &display_line[DISPLAY_LINE2][DEC_ZERO];
  display[DISPLAY_LINE3] = &display_line[DISPLAY_LINE3][DEC_ZERO];
  update_display = DEC_ZERO;
  update_display_count = DEC_ZERO;
  

  
// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}


