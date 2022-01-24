//------------------------------------------------------------------------------
//
//  Description: This file contains the functions pertaining to the operation 
//  of interupts on the ADC.
//
//
//  Alex Carter
//  Mar 2019
//  Built with IAR Embedded Workbench Version: 7.12.1
//------------------------------------------------------------------------------

#include "functions.h"
#include "msp430.h"
#include "macros.h"

volatile unsigned int ADC_Thumb;
volatile unsigned int ADC_Left_Detector;
volatile unsigned int ADC_Right_Detector;

char channel = THUMB;

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
    case ADCIV_NONE:
      break;
    case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
                         // before its previous conversion result was read.
      break;
    case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
      break;
    case ADCIV_ADCHIIFG: // Window comparator interrupt flags
      break;
    case ADCIV_ADCLOIFG: // Window comparator interrupt flag
      break;
    case ADCIV_ADCINIFG: // Window comparator interrupt flag
      break;
    case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
      ADCCTL0 &= ~ADCENC;
      switch(channel){
        case THUMB:
          ADC_Thumb = ADCMEM0;
          ADC_Thumb = ADC_Thumb >> DEC_TEN; // divides ADC value by 1024
          ADCMCTL0 &= ~ADCINCH_5;
          ADCMCTL0 |= ADCINCH_2;
          channel = L_DET;
          break;
        case L_DET:
          ADC_Left_Detector = ADCMEM0;
          ADC_Left_Detector = ADC_Left_Detector >> DEC_TWO;  // divides ADC value by 4
          ADCMCTL0 &= ~ADCINCH_2;
          ADCMCTL0 |= ADCINCH_3;
          channel = R_DET;
          break;
        case R_DET:
          ADC_Right_Detector = ADCMEM0;
          ADC_Right_Detector = ADC_Right_Detector >> DEC_TWO; // divides ADC value by 4
          ADCMCTL0 &= ~ADCINCH_3;
          ADCMCTL0 |= ADCINCH_5;
          channel = THUMB;
          break;
        default:
          break;
      }
      ADCCTL0 |= ADCENC;
      ADCCTL0 |= ADCSC;
      break;
    default:
      break;
  }
}