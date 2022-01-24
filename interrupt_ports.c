//------------------------------------------------------------------------------
//
//  Description: This file contains the functions pertaining to the operation 
//  of timer interupts on the port pins.
//
//
//  Alex Carter
//  Feb 2019
//  Built with IAR Embedded Workbench Version: 7.12.1
//------------------------------------------------------------------------------

#include "functions.h"
#include "msp430.h"
#include "macros.h"

extern volatile unsigned char update_display;
extern volatile char SW1_debounce;
volatile unsigned int debounce1;
extern volatile char SW2_debounce;
volatile unsigned int debounce2;
extern char display_line[DISPLAY_ARRAY][DISPLAY_LENGTH];
extern volatile unsigned char display_changed;
extern char menu_state;
extern char car_state;
extern char once;

extern volatile unsigned int UCA1_index;
extern volatile unsigned int usb_rx_ring_wr;
extern volatile char usb_Char_Rx[SMALL_RING_SIZE];
extern volatile char usb_Char_Tx[LARGE_RING_SIZE];

extern volatile unsigned int UCA0_index;
extern volatile unsigned int iot_rx_ring_wr;
extern volatile char iot_Char_Rx[SMALL_RING_SIZE];
extern volatile char iot_Char_Tx[LARGE_RING_SIZE];
extern char baudrate;
extern char serialState;
extern char processBuffer[bufferLength];
extern signed int processLength;

extern char ip[SMALL_RING_SIZE];
extern char ssid[DEC_TEN];
extern char getIP;
extern char iotONCE;
extern unsigned char commandGet;

#pragma vector = PORT2_VECTOR
__interrupt void switchP2_interrupt(void){
  if(P2IFG & SW2){
    P2IE &= ~SW2;
    
    SW2_debounce = TRUE;
    debounce2 = RESET_BITS;
    
    switch(menu_state){
      case MAIN_MENU:
        CaptureBlack();
        break;
      case PROJ7:
        car_state = WAITING;
        break;
      case PROJ8:
        if(once){
          baudrate = BAUD460K;
          Init_Serial();
          once = FALSE;
        }
        else if(!once){
          baudrate = BAUD115K;
          Init_Serial();
          once = TRUE;
        }
        break;
      default: break;
      }
    
    TB0CCTL2 |= CCIE;
  }
}

#pragma vector = PORT4_VECTOR
__interrupt void switchP4_interrupt(void){
  if(P4IFG & SW1){
    P4IE &= ~SW1;
    
    SW1_debounce = TRUE;
    debounce1 = RESET_BITS;
    
    switch(menu_state){
      case MAIN_MENU:
        CaptureWhite();
        break;
      case PROJ7:
        car_state = INTERCEPTING;
        break;
      case IOT:
        break;
      default: break;
      }
    
    
    TB0CCTL1 |= CCIE;
  }
}

#pragma vector = EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
  signed int temp;
  char rx;
  switch(__even_in_range(UCA0IV,TXCOMPLETE)){
    case REG0: // Vector 0 - no interrupt
      break;
    case REG1:
        rx = UCA0RXBUF;
        if((rx == 'y') && (getIP)){
          iot_rx_ring_wr = DEC_ZERO;        
          }
        if((rx == '_') && (commandGet)){   //check for FRAM commands
          serialState = RECIEVING;
          commandGet = FALSE;
          iot_rx_ring_wr = DEC_ZERO;
        }
        temp = iot_rx_ring_wr++;
        iot_Char_Rx[temp] = rx; // RX -> iot_Char_Rx character
        if (iot_rx_ring_wr >= (sizeof(iot_Char_Rx))){
          iot_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
        }
        if((rx == ':') && (getIP)){
          char i;
          for(i = DEC_SEVEN; iot_Char_Rx[i] != ':'; i++)
            ip[i-DEC_SEVEN] = iot_Char_Rx[i];
          getIP = FALSE;
        }
        if((serialState == RECIEVING) & (rx == CR)){
          serialState = WAIT;
          processLength = temp;
          for(; temp >= DEC_ZERO; temp--)
            processBuffer[temp] = iot_Char_Rx[temp]; 
        } 

      break;
//    case REG2: // Vector 4 – TXIFG
//      /*switch(UCA0_index++){
//      case DEC_ZERO:
//      case DEC_ONE:
//      case DEC_TWO:
//      case DEC_THREE:
//      case DEC_FOUR:
//      case DEC_FIVE:
//      case DEC_SIX:
//      case DEC_SEVEN:
//      case DEC_EIGHT:
//      case DEC_NINE:
//        //UCA0TXBUF = processBuffer[UCA0_index];//test_command[UCA1_index];usb_Char_Rx[UCA1_index];
//        break;
//      case DEC_TEN:
//        UCA0TXBUF = CR;
//        break;
//      case DEC_ELV:
//        UCA0TXBUF = LF;
//        break;
//      default:
//        UCA0_index = DEC_ZERO;*/
//        //UCA0IE &= ~UCTXIE;
//        break;
//      //}
  default: break;
  }
}

#pragma vector = EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
  signed int temp;
  char rx;
  switch(__even_in_range(UCA1IV,TXCOMPLETE)){
    case REG0: // Vector 0 - no interrupt
      break;
    case REG1: // Vector 2 - RXIFG
      rx = UCA1RXBUF;
      if((rx == '_')){   //check for FRAM commands
        serialState = RECIEVING;
        usb_rx_ring_wr = DEC_ZERO;
      }
      temp = usb_rx_ring_wr++;
      usb_Char_Rx[temp] = rx; // RX -> USB_Char_Rx character
      if (usb_rx_ring_wr >= (sizeof(usb_Char_Rx))){
        usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
      }
      if((serialState == RECIEVING) & (rx == CR)){
        serialState = RECIEVED;
        processLength = temp;
        for(; temp >= DEC_ZERO; temp--)
          processBuffer[temp] = usb_Char_Rx[temp]; 
      }

          //UCA0IE |= UCTXIE;
          //UCA0TXBUF = rx; 
          
      break;
//    case REG2: // Vector 4 – TXIFG
//      
//      /*switch(UCA1_index++){
//      case DEC_ZERO:
//      case DEC_ONE:
//      case DEC_TWO:
//      case DEC_THREE:
//      case DEC_FOUR:
//      case DEC_FIVE:
//      case DEC_SIX:
//      case DEC_SEVEN:
//      case DEC_EIGHT:
//      case DEC_NINE:
//        UCA1TXBUF = processBuffer[UCA1_index];//test_command[UCA1_index];usb_Char_Rx[UCA1_index];
//        break;
//      case DEC_TEN:
//        UCA1TXBUF = CR;
//        break;
//      case DEC_ELV:
//        UCA1TXBUF = LF;
//        break;
//      default:
//        //UCA1_index = DEC_ZERO;*/
//        //UCA1IE &= ~UCTXIE;
//        break;
//    //}  
  default: break;
  }
}

