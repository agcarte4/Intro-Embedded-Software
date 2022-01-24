//------------------------------------------------------------------------------
//
//  Description: This file contains the functions pertaining to the operation 
//  of timerB0.
//
//
//  Alex Carter
//  Feb 2019
//  Built with IAR Embedded Workbench Version: 7.12.1
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include "functions.h"
#include "msp430.h"
#include "macros.h"

void Init_Timers(void){
  Init_Timer_B0();
  Init_Timer_B1();
  Init_Timer_B3();
}

void Init_Timer_B0(void) {
//--------------------------------------------------------------------
// Timer B0 initialization sets up both b0_0, B0_1-B0_2 and overflow
  TB0CTL = RESET_BITS; // Clear TA0 Control Register
  TB0EX0 = RESET_BITS; // Clear TAIDEX Register
  
  TB0CTL |= TBSSEL__SMCLK; // SMCLK source
  TB0CTL |= MC__CONTINOUS; // Continuous up to 0xFFFF and overflow
  TB0CTL |= ID__2; // Divide clock by 2
  TB0EX0 |= TBIDEX__8; // Divide clock by an additional 8
  TB0CTL |= TBCLR; // Resets TB0R
  
  // Capture Compare 0
  // #pragma vector = TIMER0_B0_VECTOR
  // Capture Compare 0
  TB0CCR0 = TB0CCR0_INTERVAL; // CCR0
  TB0CCTL0 |= CCIE; // CCR0 enable interrupt
  
  
  // Capture Compare 1,2, Overflow
  // #pragma vector = TIMER0_B1_VECTOR
  
  // Capture compare 1
  TB0CCR1 = TB0CCR1_INTERVAL;// CCR1
  //TB0CCTL1 |= CCIE; // CCR1 enable interrupt
  
  // Capture compare 2
  TB0CCR2 = TB0CCR1_INTERVAL;// CCR2
  //TB0CCTL2 |= CCIE; // CCR2 enable interrupt
    
  // Catpure compare 3
  //TB0CCR3 = TB0CCR3_INTERVAL; //CCR3
  
  // Overflow
  TB0CTL &= ~TBIE; // Disable Overflow Interrupt
  TB0CTL &= ~TBIFG; // Clear Overflow Interrupt flag
//--------------------------------------------------------------------
}
void Init_Timer_B1(void) {
//--------------------------------------------------------------------
// Timer B0 initialization sets up both b0_0, B0_1-B0_2 and overflow
  TB1CTL = RESET_BITS; // Clear TA0 Control Register
  TB1EX0 = RESET_BITS; // Clear TAIDEX Register
  TB1CTL |= TBSSEL__SMCLK; // SMCLK source
  TB1CTL |= MC__CONTINOUS; // Continuous up to 0xFFFF and overflow
  
  TB1CTL |= ID__2; // Divide clock by 2
  TB1EX0 |= TBIDEX__8; // Divide clock by an additional 8
  TB1CTL |= TBCLR; // Resets TB0R
  
  // Capture Compare 0
  // #pragma vector = TIMER0_B0_VECTOR
  // Capture Compare 0
  //TB1CCR0 = TB1CCR0_INTERVAL; // CCR0
  //TB1CCTL0 |= CCIE; // CCR0 enable interrupt
  
  // Capture Compare 1,2, Overflow
  // #pragma vector = TIMER0_B1_VECTOR
  
  // Capture compare 1
  //TB1CCR1 = TB0CCR1_INTERVAL;// CCR1
  // TB1CCTL1 |= CCIE; // CCR1 enable interrupt
  
  // Capture compare 2
  //TB0CCR2 = TB0CCR2_INTERVAL;// CCR2
  // TB0CCTL2 |= CCIE; // CCR2 enable interrupt
  
  
  // Overflow
  TB1CTL &= ~TBIE; // Disable Overflow Interrupt
  TB1CTL &= ~TBIFG; // Clear Overflow Interrupt flag
//--------------------------------------------------------------------
}
void Init_Timer_B3(void) {
//------------------------------------------------------------------------------
// SMCLK source, up count mode, PWM Right Side
// TB3.1 P6.0 R_FORWARD
// TB3.2 P6.1 L_FORWARD
// TB3.3 P6.2 R_REVERSE
// TB3.4 P6.3 L_REVERSE
//------------------------------------------------------------------------------
 TB3CTL = TBSSEL__SMCLK;             // SMCLK
 TB3CTL |= MC__UP;                   // Up Mode
 TB3CTL |= TBCLR;                    // Clear TAR
 TB3CCR0 = WHEEL_PERIOD;             // PWM Period
 TB3CCTL1 = OUTMOD_7;                // CCR1 reset/set
 RIGHT_FORWARD_SPEED = WHEEL_OFF;    // P6.0 Right Forward PWM duty cycle
 TB3CCTL2 = OUTMOD_7;                // CCR2 reset/set
 LEFT_FORWARD_SPEED = WHEEL_OFF;     // P6.1 Left Forward PWM duty cycle
 TB3CCTL3 = OUTMOD_7;                // CCR3 reset/set
 RIGHT_REVERSE_SPEED = WHEEL_OFF;    // P6.2 Right Reverse PWM duty cycle
 TB3CCTL4 = OUTMOD_7;                // CCR4 reset/set
 LEFT_REVERSE_SPEED = WHEEL_OFF;     // P6.3 Left Reverse PWM duty cycle
//------------------------------------------------------------------------------
}

