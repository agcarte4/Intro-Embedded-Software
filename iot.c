//------------------------------------------------------------------------------
//
//  Description: This file contains the functions pertaining to the operation 
//  of the IoT module.
//
//
//  Alex Carter
//  April 2019
//  Built with IAR Embedded Workbench Version: 7.12.1
//------------------------------------------------------------------------------

#include "functions.h"
#include "msp430.h"
#include "macros.h"

extern char once;


//void getNetwork(void){                  //gathers the network ssid and ip into two different arrays
//  char temp = DEC_ZERO;
//  get = TRUE;
//  once = TRUE;
//  UCA0IE |= UCTXIE;
//  transmitstring(networkState);
//  
//  //if(!get){                                                     //places null at end of ip string
//    for(temp = DEC_ZERO; temp < SMALL_RING_SIZE; temp++){
//      if(ip[temp] == ' '){
//        ip[temp] = DEC_ZERO;
//        ipLength = temp;
//      }
//    }
//  //}
//  
//  return;
//}

