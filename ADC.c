//------------------------------------------------------------------------------
//
//  Description: This file contains the functions pertaining to the operation 
//  of the ADC.
//
//
//  Alex Carter
//  Mar 2019
//  Built with IAR Embedded Workbench Version: 7.12.1
//------------------------------------------------------------------------------

#include "functions.h"
#include "msp430.h"
#include "macros.h"
#include <string.h>

char adc_char[DEC_FOUR];
extern volatile unsigned int ADC_Thumb;
extern volatile unsigned int ADC_Left_Detector;
extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern char display_line[DISPLAY_ARRAY][DISPLAY_LENGTH];
extern unsigned int white;
extern unsigned int black;

void Init_ADC(void){
//------------------------------------------------------------------------------
// V_DETECT_L (0x04) // Pin 2 A2
// V_DETECT_R (0x08) // Pin 3 A3
// V_THUMB (0x20) // Pin 5 A5
//------------------------------------------------------------------------------
// ADCCTL0 Register
ADCCTL0 = RESET_STATE; // Reset
ADCCTL0 |= ADCSHT_2; // 16 ADC clocks
ADCCTL0 |= ADCMSC; // MSC
ADCCTL0 |= ADCON; // ADC ON
// ADCCTL1 Register
ADCCTL2 = RESET_STATE; // Reset
ADCCTL1 |= ADCSHS_0; // 00b = ADCSC bit
ADCCTL1 |= ADCSHP; // ADC sample-and-hold SAMPCON signal from sampling timer.
ADCCTL1 &= ~ADCISSH; // ADC invert signal sample-and-hold.
ADCCTL1 |= ADCDIV_0; // ADC clock divider - 000b = Divide by 1
ADCCTL1 |= ADCSSEL_0; // ADC clock MODCLK
ADCCTL1 |= ADCCONSEQ_0; // ADC conversion sequence 00b = Single-channel single-conversion
// ADCCTL1 & ADCBUSY identifies a conversion is in process
// ADCCTL2 Register
ADCCTL2 = RESET_STATE; // Reset
ADCCTL2 |= ADCPDIV0; // ADC pre-divider 00b = Pre-divide by 1
ADCCTL2 |= ADCRES_2; // ADC resolution 10b = 12 bit (14 clock cycle conversion time)
ADCCTL2 &= ~ADCDF; // ADC data read-back format 0b = Binary unsigned.
ADCCTL2 &= ~ADCSR; // ADC sampling rate 0b = ADC buffer supports up to 200 ksps
// ADCMCTL0 Register
ADCMCTL0 |= ADCSREF_0; // VREF - 000b = {VR+ = AVCC and VR– = AVSS }
ADCMCTL0 |= ADCINCH_5; // V_THUMB (0x20) Pin 5 A5
ADCIE |= ADCIE0; // Enable ADC conv complete interrupt
ADCCTL0 |= ADCENC; // ADC enable conversion.
ADCCTL0 |= ADCSC; // ADC start conversion.
}

//******************************************************************************
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//------------------------------------------------------------------------------
void HEXtoBCD(int hex_value){
  int value = DEC_ZERO;
  adc_char[DEC_ZERO] = '0';
  adc_char[DEC_ONE] = '0';
  adc_char[DEC_TWO] = '0';
  adc_char[DEC_THREE] = '0';
  while (hex_value > DEC_999){
    hex_value = hex_value - BIT_3;
    value = value + DEC_ONE;
    adc_char[DEC_ZERO] = HEX_30 + value;
  }
  value = DEC_ZERO;
  while (hex_value > DEC_99){
    hex_value = hex_value - BIT_2;
    value = value + DEC_ONE;
    adc_char[DEC_ONE] = HEX_30 + value;
  }
  value = DEC_ZERO;
  while (hex_value > DEC_9){
    hex_value = hex_value - BIT_1;
    value = value + DEC_ONE;
    adc_char[DEC_TWO] = HEX_30 + value;
  }
  adc_char[DEC_THREE] = HEX_30 + hex_value;
}
//******************************************************************************
//------------------------------------------------------------------------------

void WriteADC(void){
  HEXtoBCD(ADC_Thumb);
  display_line[DISPLAY_LINE1][DEC_SIX] = adc_char[DEC_ZERO];
  display_line[DISPLAY_LINE1][DEC_SEVEN] = adc_char[DEC_ONE];
  display_line[DISPLAY_LINE1][DEC_EIGHT] = adc_char[DEC_TWO];
  display_line[DISPLAY_LINE1][DEC_NINE] = adc_char[DEC_THREE];
  update_string(display_line[DISPLAY_LINE1], DISPLAY_LINE1);

  HEXtoBCD(ADC_Left_Detector);
  display_line[DISPLAY_LINE3][DEC_ZERO] = adc_char[DEC_ZERO];
  display_line[DISPLAY_LINE3][DEC_ONE] = adc_char[DEC_ONE];
  display_line[DISPLAY_LINE3][DEC_TWO] = adc_char[DEC_TWO];
  display_line[DISPLAY_LINE3][DEC_THREE] = adc_char[DEC_THREE];
  display_line[DISPLAY_LINE3][DEC_FOUR] = ' ';
  display_line[DISPLAY_LINE3][DEC_FIVE] = ' ';
  
  
  HEXtoBCD(ADC_Right_Detector);
  display_line[DISPLAY_LINE3][DEC_SIX] = adc_char[DEC_ZERO];
  display_line[DISPLAY_LINE3][DEC_SEVEN] = adc_char[DEC_ONE];
  display_line[DISPLAY_LINE3][DEC_EIGHT] = adc_char[DEC_TWO];
  display_line[DISPLAY_LINE3][DEC_NINE] = adc_char[DEC_THREE];
  update_string(display_line[DISPLAY_LINE3], DISPLAY_LINE3);
  
  
  display_changed = TRUE;
  update_display = TRUE;

  return;
}

void CaptureWhite(void){
  white = ((ADC_Right_Detector + ADC_Left_Detector) / DEC_TWO);
  return;
}

void CaptureBlack(void){
  black = ((ADC_Right_Detector + ADC_Left_Detector) / DEC_TWO) - 150;
  return;
}

