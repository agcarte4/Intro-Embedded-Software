//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Alex Carter
//  Jan 2019
//  Built with IAR Embedded Workbench Version: 7.12.1
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include "functions.h"
#include "msp430.h"
#include "macros.h"
#include <string.h>

// Function Prototypes
void main(void);

// Global Variables
volatile char slow_input_down;
extern char display_line[DISPLAY_ARRAY][DISPLAY_LENGTH];
extern char *display[DISPLAY_ARRAY];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;             //Increments by 1 every 25ms, counts to 1.25s
volatile char one_time;                                 //a control variable
extern volatile unsigned int Time_Sequence1;            //like previous time_sequence, counts to 1s
char once = TRUE;
extern char menu_state;
extern volatile unsigned int oneSecTimer;

volatile unsigned int UCA0_index;
volatile unsigned int UCA1_index;
extern char baudrate;

extern volatile unsigned char iotTimer;
char iotState = iotRESET;
char getIP = FALSE;

char car_state = IOTMODE;



void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD
  Init_ADC();                          // Initialize ADCs
  Init_Menu();                         // Initialize menu
  Init_Serial();                       // Initialize serial ports
  
   UCA0_index = DEC_ZERO;
   UCA1_index = DEC_ZERO;
   char * TCPport = "AT+NSTCP=2514,1\r";
   char * syncTime = "AT+WSYNCINTRL=65535\r";
   char * iotReset = "AT+RESET=1\r";
   char iotONCE = TRUE;
   
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    
    switch(Time_Sequence){
      case ONE25_SEC:                        //
        if(one_time){
          Init_LEDs();
          display_changed = TRUE;
          one_time = RESET_STATE;
        }
        break;
      case ONE_SEC:                        //
        if(one_time){
          GREEN_LED_ON;            // Change State of LED 5
          one_time = RESET_STATE;
        }
        break;
      case THREEQ_SEC:                         //
        if(one_time){
          RED_LED_ON;            // Change State of LED 4
          GREEN_LED_OFF;           // Change State of LED 5
          one_time = RESET_STATE;
        }
        break;
      case HALF_SEC:                         //
        if(one_time){
          lcd_4line();
          GREEN_LED_ON;            // Change State of LED 5
          display_changed = TRUE;
          one_time = RESET_STATE;
        }
        break;
      case  QUARTER_SEC:                        //
        if(one_time){
          RED_LED_OFF;           // Change State of LED 4
          GREEN_LED_OFF;           // Change State of LED 5
          one_time = RESET_STATE;
        }
        break;                         //
      default: break;
    }
  
    //state machine controlling the initial operation of the iot module
    switch(iotState){
    case iotRESET:
      if(iotTimer == DEC_ONE){          //1 secs for hard iot to reset
        IOTRESETOFF;
        iotState = iotSOFTRESET;
        iotTimer = DEC_ZERO;
      }
      break;
    case iotSOFTRESET:
      if(iotONCE){                      //4 secs for soft iot reset
        transmitString(iotReset);
        iotTimer = DEC_ZERO;
        iotONCE = FALSE;
        getIP = TRUE;
      }
      if(!iotONCE && (iotTimer == DEC_FOUR)){
        iotState = iotSYNC;
        iotONCE = TRUE;
        iotTimer = DEC_ZERO;
      }
      break;
    case iotSYNC:
      if(iotONCE){
        transmitString(syncTime);
        iotONCE = FALSE;
      }
      if(iotTimer == DEC_ONE){          //1 sec to set sync time
        iotState = iotPORT;
        iotTimer = DEC_ZERO;
        iotONCE = TRUE;
      }
      break;
    case iotPORT:
      if(iotONCE){
        transmitString(TCPport);
        iotONCE = FALSE;
      }
      if(iotTimer == DEC_ONE){         //1 sec to set up the socket
        iotState = iotRDY;
        iotTimer = DEC_ZERO;
        iotONCE = TRUE;
      }
      break;      
    default: break;
    }
    
    Menu_Process();                    // Update the menu
    Motors();                          // Check the operations of the motors
    Switches_Process();                // Check for switch state change
    Display_Process();                 // Updates the LCD
    SerialProcess();                   // Save commands if needed
    runCommands();                     // Execute the commands list

   
    
  }
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
