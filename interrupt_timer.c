//------------------------------------------------------------------------------
//
//  Description: This file contains the functions pertaining to the operation 
//  of timer interupts.
//
//
//  Alex Carter
//  Feb 2019
//  Built with IAR Embedded Workbench Version: 7.12.1
//------------------------------------------------------------------------------

#include "functions.h"
#include "msp430.h"
#include "macros.h"


volatile unsigned int Time_Sequence;
volatile unsigned int Time_Sequence1;          //Increments by 1 every 25ms
volatile unsigned int blink_count;
extern volatile unsigned char update_display;
extern volatile char one_time;
unsigned int lcd_count;
extern volatile char SW1_debounce;
extern volatile unsigned int debounce1;
extern volatile char SW2_debounce;
extern volatile unsigned int debounce2;
unsigned int time_change;
volatile unsigned int oneSecTimer = DEC_ZERO;
volatile unsigned char iotTimer = DEC_ZERO;
volatile unsigned int timer = DEC_ZERO;
char timer_stop = TRUE;
volatile unsigned char commandTime = DEC_ZERO;  //used to control iot command times

#pragma vector = TIMER0_B0_VECTOR // Timer B0 – 0 Capture compare
__interrupt void Timer0_B0_ISR(void){
//--------------------------------------------------------------------
// Timerb0 0 Interrupt handler - Interupts every 25ms
//--------------------------------------------------------------------
 
// Time Sequence
 one_time = TRUE;
 if(Time_Sequence++ > ONE25_SEC){
   Time_Sequence = DEC_ZERO;
 }
  if(Time_Sequence1++ > ONE_SEC){
   Time_Sequence1 = DEC_ZERO;
   oneSecTimer++;
   iotTimer++;
 }
 time_change = TRUE;

 // LCD Update
 if(lcd_count++ == TWOHUN_MS_COUNT){
   update_display = TRUE;
   lcd_count = DEC_ZERO;
   if(!timer_stop)
    timer = timer + DEC_TWO;
 }
 commandTime++;         //increase every 25 ms
 
 TB0CCR0 += TB0CCR0_INTERVAL; // Add interval Offset to TACCR0
//--------------------------------------------------------------------
}

#pragma vector = TIMER0_B1_VECTOR // Timer B1 – 0 Capture compare
__interrupt void Timer0_B1_ISR(void){
//--------------------------------------------------------------------
// Timerb1 0 Interrupt handler - Interupts 100ms
//--------------------------------------------------------------------
  switch(__even_in_range(TB0IV,VECTOR_BOUND)){  
    
  case REG0: break;
  case REG1:
    if(SW1_debounce){
      if(debounce1++){  //200ms switch debounce time
        P4IFG &= ~SW1;
        P4IE |= SW1;  
        SW1_debounce = FALSE;
      }
    }
      else{
        TB0CCTL1 &= ~CCIE; // CCR1 disable interrupt
        TB0CCTL1 &= ~CCIFG;
    }
    TB0CCR1 += TB0CCR1_INTERVAL; // Add interval Offset to TACCR1
    break;
  case REG2:
    if(SW2_debounce){
      if(debounce2++){ //200ms switch debounce time
        P2IFG &= ~SW2;
        P2IE |= SW2;
        SW2_debounce = FALSE;
      }
    }
      else{
        TB0CCTL2 &= ~CCIE; // CCR2 disable interrupt
        TB0CCTL2 &= ~CCIFG;
    }
    TB0CCR2 += TB0CCR1_INTERVAL; // Add interval Offset to TACCR2
    break;
  case OVERFLOW:
    break;
  } 
}