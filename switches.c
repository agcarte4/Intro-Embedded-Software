//-------------------------------------------------------------------------
//  
//  Description:  Contains the code to control the MSP switches.
//                Functions here check to see if switches have been pressed
//                and to clear/reset the switches.
//  Alex Carter
//  Feb 2019
//  Built with IAR Embedded Workbench Version: 7.12.1
//-------------------------------------------------------------------------

#include "functions.h"
#include "msp430.h"
#include "macros.h"
#include <string.h>

extern volatile unsigned char update_display;
extern char display_line[DISPLAY_ARRAY][DISPLAY_LENGTH];
extern volatile unsigned char display_changed;


unsigned int SW1_count = DEC_ZERO;
volatile char SW1_debounce;
unsigned int SW2_count = DEC_ZERO;
volatile char SW2_debounce;



//void Init_Switches(void);
//void switch_control(void);
//void enable_switch_SW1(void);
//void enable_switch_SW2(void);
//void disable_switch_SW1(void);
//void disable_switch_SW2(void);
//void Switches_Process(void);
//void Init_Switch(void);
//void menu_act(void);
//void menu_select(void);

void Switches_Process(void){           // Calls individual switch processes
                                       // PxIN bit x will be low if pressed
  Switch1_Process();
  Switch2_Process();
  
}

void Switch1_Process(){
  if(SW1_debounce){

    }
}

void Switch2_Process(){
  if(SW2_debounce){
    }
}
