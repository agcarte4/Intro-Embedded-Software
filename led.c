//-------------------------------------------------------------------------
//  
//  Description:  Contains the code to control the MSP LEDs
//
//  Alex Carter
//  Jan 2019
//  Built with IAR Embedded Workbench Version: 7.12.1
//-------------------------------------------------------------------------

#include "functions.h"
#include "msp430.h"
#include "macros.h"
#include <string.h>




void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on both LEDs
  GREEN_LED_OFF;
  RED_LED_OFF;
//------------------------------------------------------------------------------
}
