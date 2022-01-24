//-------------------------------------------------------------------------
//  
//  Description:  Contains the code to control the MSP ports.
//                All port pins are defaulted to GPIOs as outputs
//                to conserve power.
//  Alex Carter
//  Jan 2019
//  Built with IAR Embedded Workbench Version: 7.12.1
//-------------------------------------------------------------------------

#include "functions.h"
#include "msp430.h"
#include "macros.h"
#include <string.h>

//  &= ~ sets pin low for PxSELx
//  |=   sets pin high
//  0 = in for PxDIR
//  1 = out

void Init_Ports(){
  
  Init_Port1();
  Init_Port2();
  Init_Port3();
  Init_Port4();
  Init_Port5();
  Init_Port6();

}

void Init_Port1(void){
  //-----------------------------------------------------------------------------
  // Configure Port 1
  P1DIR = BITS_HIGH;       // Set P1 direction to output
  P1OUT = RESET_BITS;      // P1 set Low
  
  //Pin 0
  P1SEL0 &= ~RED_LED;      // GPIO operation
  P1SEL1 &= ~RED_LED;      // GPIO operation
  //P1DIR |= RED_LED;        // P1_0 is an output

  //Pin 1  
  P1SEL0 &= ~A1_SEEED;     // GPIO operation (A1 SEEED unused currently)
  P1SEL1 &= ~A1_SEEED;     // GPIO operation
  P1DIR &= ~A1_SEEED;      // A1_SEEED is set as input
    
  //Pin 2
  P1SEL0 |= V_DETECT_L;    // V_DETECT_L selected
  P1SEL1 |= V_DETECT_L;    // V_DETECT_L selected
  
  //Pin 3
  P1SEL0 |= V_DETECT_R;    // V_DETECT_R selected
  P1SEL1 |= V_DETECT_R;    // V_DETECT_R selected
  
  //Pin 4
  P1SEL0 &= ~A4_SEEED;     // GPIO operation (A4_SEED is unused currently)
  P1SEL1 &= ~A4_SEEED;     // GPIO operation (A4_SEED is unused currently)
  P1DIR &= ~A4_SEEED;      // A4_SEED is set as input
  
  //Pin 5
  P1SEL0 |= V_THUMB;       // V_THUMB selected 
  P1SEL1 |= V_THUMB;       // 
  
  //Pin 6
  P1SEL0 |= UCA0RXD;      // UCA0RXD selected
  P1SEL1 &= ~UCA0RXD;     //
  
  //Pin 7
  P1SEL0 |= UCA0TXD;      // UCA0TXD selected
  P1SEL1 &= ~UCA0TXD;     //
  
  //-----------------------------------------------------------------------------
}

void Init_Port2(void){
 //------------------------------------------------------------------------------
 // Configure PORT 2
 P2DIR = BITS_HIGH;     // Set P2 direction to output
 P2OUT = RESET_BITS;    // P2 set Low
 
 //Pin 0
 P2SEL0 &= ~P2_0;       // P2_0 GPIO operation
 P2SEL1 &= ~P2_0;       // P2_0 GPIO operation
 P2DIR &= ~P2_0;        // Direction = input
 
 //Pin 1
 P2SEL0 &= ~P2_1;       // P2_1 GPIO operation
 P2SEL1 &= ~P2_1;       // P2_1 GPIO operation
 P2DIR &= ~P2_1;        // Direction = input
 
 //Pin 2
 P2SEL0 &= ~P2_2;       // P2_2 GPIO operation
 P2SEL1 &= ~P2_2;       // P2_2 GPIO operation
 P2DIR &= ~P2_2;        // Direction = input
 
 //Pin 3
 P2SEL0 &= ~SW2;        // SW2 Operation
 P2SEL1 &= ~SW2;        // SW2 Operation
 P2DIR &= ~SW2;         // Direction = input
 P2OUT |= SW2;          // Configure pullup resistor
 P2REN |= SW2;          // Enable pullup resistor
 P2IES |= SW2;       // P2.0 Hi/Lo edge interrupt
 P2IFG &= ~SW2;      // Clear all P2.6 interrupt flags
 P2IE |= SW2;        // P2.6 interrupt enabled
 
 //Pin 4
 P2SEL0 &= ~P2_4;       // P2_4 GPIO operation
 P2SEL1 &= ~P2_4;       // P2_4 GPIO operation
 P2DIR &= ~P2_4;        // Direction = input
 
 //Pin 5
 P2SEL0 &= ~P2_5;       // P2_5 GPIO operation
 P2SEL1 &= ~P2_5;       // P2_5 GPIO operation
 P2DIR &= ~P2_5;        // Direction = input
 
 //Pin 6
 P2SEL0 &= ~LFXOUT;     // LFXOUT Clock operation
 P2SEL1 |= LFXOUT;      // LFXOUT Clock operation
 
 //Pin 7
 P2SEL0 &= ~LFXIN;      // LFXIN Clock operation
 P2SEL1 |= LFXIN;       // LFXIN Clock operation
 //------------------------------------------------------------------------------
}
 
void Init_Port3(void){
  //-----------------------------------------------------------------------------
  // Configure Port 3
  P3DIR = BITS_HIGH;         // Set P3 direction to output
  P3OUT = RESET_BITS;        // P3 set Low
  
  //Pin 0
  P3SEL0 &= ~TEST_PROBE;     // Testprobe is GPIO
  P3SEL1 &= ~TEST_PROBE;
  
  //Pin 1
  P3SEL0 &= ~OA20;           // Photodiode is unused
  P3SEL1 &= ~OA20;           // Output
  
  //Pin 2
  P3SEL0 &= ~OA2N;           // Negative from photodiode
  P3SEL1 &= ~OA2N;           // UNUSED
  //P3DIR |= OA2N;           // Input
  
  //Pin 3
  P3SEL0 &= ~OA2P;           // Positive from photodiode
  P3SEL1 &= ~OA2P;           // UNUSED
  //P3DIR |= OA2P;           // Input
  
  //Pin 4
  P3SEL0 |= SMCLK_OUT;       // 
  P3SEL1 &= ~SMCLK_OUT;      //
  P3DIR |= SMCLK_OUT;        //
  
  //Pin 5
  P3SEL0 &= ~P3_5;           // GPIO 
  P3SEL1 &= ~P3_5;           //
  
  //Pin 6
  P3SEL0 &= ~IOT_LINK;       //Unused, set to GPIO
  P3SEL1 &= ~IOT_LINK;       //
  
  //Pin 7
  P3SEL0 &= ~P3_7;           //GPIO
  P3SEL1 &= ~P3_7;           //
  //-----------------------------------------------------------------------------
}

void Init_Port4(void){
//------------------------------------------------------------------------------
// Configure PORT 4
 P4DIR = BITS_HIGH;     // Set P4 direction to output
 P4OUT = RESET_BITS;    // P4 set Low
 
 //Pin 0
 P4SEL0 &= ~RESET_LCD;  // RESET_LCD GPIO operation
 P4SEL1 &= ~RESET_LCD;  // RESET_LCD GPIO operation
 P4DIR |= RESET_LCD;    // Set RESET_LCD direction to output
 P4OUT |= RESET_LCD;    // Set RESET_LCD Off [High]
 
 //Pin 1
 P4SEL0 &= ~SW1;        // SW1 GPIO operation
 P4SEL1 &= ~SW1;        // SW1 GPIO operation
 P4DIR &= ~SW1;         // Direction = input
 P4OUT |= SW1;          // Configure pullup resistor
 P4REN |= SW1;          // Enable pullup resistor
 P4IES |= SW1;       // P2.0 Hi/Lo edge interrupt
 P4IFG &= ~SW1;      // Clear all P2.6 interrupt flags
 P4IE |= SW1;        // P2.6 interrupt enabled
 
 //Pin 2
 P4SEL0 |= UCA1TXD;     // USCI_A1 UART operation
 P4SEL1 &= ~UCA1TXD;    // USCI_A1 UART operation
 
 //Pin 3
 P4SEL0 |= UCA1RXD;     // USCI_A1 UART operation
 P4SEL1 &= ~UCA1RXD;    // USCI_A1 UART operation
 
 //Pin 4
 P4SEL0 &= ~UCB1_CS_LCD;// UCB1_CS_LCD GPIO operation
 P4SEL1 &= ~UCB1_CS_LCD;// UCB1_CS_LCD GPIO operation
 P4DIR |= UCB1_CS_LCD;  // Set SPI_CS_LCD direction to output
 P4OUT |= UCB1_CS_LCD;  // Set SPI_CS_LCD Off [High]
 
 //Pin 5
 P4SEL0 |= UCB1CLK;     // UCB1CLK SPI BUS operation
 P4SEL1 &= ~UCB1CLK;    // UCB1CLK SPI BUS operation
 
 //Pin 6
 P4SEL0 |= UCB1SIMO;    // UCB1SIMO SPI BUS operation
 P4SEL1 &= ~UCB1SIMO;   // UCB1SIMO SPI BUS operation
 
 //Pin 7
 P4SEL0 |= UCB1SOMI;    // UCB1SOMI SPI BUS operation
 P4SEL1 &= ~UCB1SOMI;   // UCB1SOMI SPI BUS operation
 //------------------------------------------------------------------------------
}

void Init_Port5(void){
  //-----------------------------------------------------------------------------
  // Configure Port 5
  P5DIR = BITS_HIGH;        // Set P5 direction to output
  P5OUT = RESET_BITS;       // P5 set Low
  
  //Pin 0
  P5SEL0 &= ~IOT_RESET;     // UNUSED, Set as GPIO
  P5SEL1 &= ~IOT_RESET;     // 
  P5DIR |= IOT_RESET;       // set as an output
  P5REN |= IOT_RESET;       // set as pullup resistor
  
  //Pin 1
  P5SEL0 &= ~P5_1;          // GPIO
  P5SEL1 &= ~P5_1;          // 
  
  //Pin 2
  P5SEL0 &= ~IOT_PROG_SEL;  // GPIO
  P5SEL1 &= ~IOT_PROG_SEL;  // 
  
  //Pin 3
  P5SEL0 &= ~IOT_PROG_MODE; // GPIO
  P5SEL1 &= ~IOT_PROG_MODE; // 
    
  //Pin 4
  P5SEL0 &= ~IR_LED;       // GPIO
  P5SEL1 &= ~IR_LED;       // 
  //P5OUT |= IR_LED;
  //-----------------------------------------------------------------------------
}

void Init_Port6(void){  
  //-----------------------------------------------------------------------------
  // Configure Port 6
  P6DIR = BITS_HIGH;        // Set P6 direction to output
  P6OUT = RESET_BITS;       // P6 set Low
  
  //Pin 0
  P6SEL0 |= R_FORWARD;       // R_Forward is a function
  P6SEL1 &= ~R_FORWARD;      // 

  //Pin 1
  P6SEL0 |= L_FORWARD;       // L_Forward is a function
  P6SEL1 &= ~L_FORWARD;      // 
  
  //Pin 2
  P6SEL0 |= R_REVERSE;       // R_Reverse is a function
  P6SEL1 &= ~R_REVERSE;      // 
  
  //Pin 3
  P6SEL0 |= L_REVERSE;       // L_Reverse is a function
  P6SEL1 &= ~L_REVERSE;      //
  
  //Pin 4
  P6SEL0 &= ~LCD_BACKLIGHT;  // GPIO
  P6SEL1 &= ~LCD_BACKLIGHT;  // 
  P6OUT &= ~LCD_BACKLIGHT;    //Backlight is DISABLED to conserve power
  
  //Pin 5
  P6SEL0 &= ~P6_5;           // GPIO, Unused
  P6SEL1 &= ~P6_5;           // 
  
  //Pin 6
  P6SEL0 &= ~GRN_LED;        // Green LED is GPIO
  P6SEL1 &= ~GRN_LED;        // 

  //-----------------------------------------------------------------------------
}
