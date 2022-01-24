//------------------------------------------------------------------------------
//
//  Description: This file contains the functions pertaining to writing information
//  to the LCD display using a simple menu state machine.
//
//  Alex Carter
//  Mar 2019
//  Built with IAR Embedded Workbench Version: 7.12.1
//------------------------------------------------------------------------------

#include "functions.h"
#include "msp430.h"
#include "macros.h"
#include <string.h>

extern volatile unsigned int ADC_Thumb;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern char display_line[DISPLAY_ARRAY][DISPLAY_LENGTH];
char menu_state;
extern char car_state;
extern unsigned int white;
extern unsigned int black;
extern char adc_char[DEC_FOUR];
extern volatile unsigned int timer;
extern char timer_stop;
extern char baudrate;
char rxState = OFFRX;
volatile extern unsigned int oneSecTimer;

extern char serialState;
extern char dataIn;
extern char processBuffer[bufferLength];
extern signed int processLength;

extern char ip[SMALL_RING_SIZE];
extern char ssid[DEC_TEN];
extern unsigned char displayTimer;
extern unsigned char iotlocation;
char iotLocations[DEC_TEN] = {'A', 'R', 'R', 'I', 'V', 'E', 'D', ' ', ' ', ' '};

extern unsigned char command;


void Init_Menu(void){   
//
// initializes the lcd to a blank menu, as there is no menu state yet
//
  Menu_Process();
}

void Menu_Process(void){
  //
  // this function is called at the end of the while loop in main
  //
  // based on the state of the thumbwheel, the lcd displays
  //    relevent information for that state
  switch(ADC_Thumb){
  case MENU0:
    menu_state = MAIN_MENU;
    //line 0
    strcpy(display_line[DISPLAY_LINE0], "MAIN  MENU");
    update_string(display_line[DISPLAY_LINE0], DISPLAY_LINE0);
    //line 1
    strcpy(display_line[DISPLAY_LINE1], "THUMB=");
    update_string(display_line[DISPLAY_LINE1], DISPLAY_LINE1);
    //line 2
    strcpy(display_line[DISPLAY_LINE2], "L_D    R_D");
    update_string(display_line[DISPLAY_LINE2], DISPLAY_LINE2);
    
    WriteADC();
    display_changed = TRUE;
    update_display = TRUE;
    break;
  case MENU1:
    menu_state = PROJ7;
    //line 0
    strcpy(display_line[DISPLAY_LINE0], "MOVE  MENU");
    update_string(display_line[DISPLAY_LINE0], DISPLAY_LINE0);
    //line 1
    display_line[DISPLAY_LINE1][DEC_ZERO] = 'W';
    HEXtoBCD(white);
    display_line[DISPLAY_LINE1][DEC_ONE] = adc_char[DEC_ONE];
    display_line[DISPLAY_LINE1][DEC_TWO] = adc_char[DEC_TWO];
    display_line[DISPLAY_LINE1][DEC_THREE] = adc_char[DEC_THREE];
    display_line[DISPLAY_LINE1][DEC_FOUR] = ' ';
    display_line[DISPLAY_LINE1][DEC_FIVE] = ' ';
    display_line[DISPLAY_LINE1][DEC_SIX] = 'B';
    HEXtoBCD(black);
    display_line[DISPLAY_LINE1][DEC_SEVEN] = adc_char[DEC_ONE];
    display_line[DISPLAY_LINE1][DEC_EIGHT] = adc_char[DEC_TWO];
    display_line[DISPLAY_LINE1][DEC_NINE] = adc_char[DEC_THREE];
    //line 2
    strcpy(display_line[DISPLAY_LINE2], "TIME ");
    update_string(display_line[DISPLAY_LINE2], DISPLAY_LINE2);
    
    //if(car_state == INTERCEPTING)
    //  timer_stop = FALSE;
    
    //WriteTime();
    //Write();
    display_changed = TRUE;
    update_display = TRUE;
    break;
  case MENU2:
    menu_state = PROJ8;
    //line 0
    strcpy(display_line[DISPLAY_LINE0], "          ");
    update_string(display_line[DISPLAY_LINE0], DISPLAY_LINE0);
    //line 1
    strcpy(display_line[DISPLAY_LINE1], "          ");
    update_string(display_line[DISPLAY_LINE1], DISPLAY_LINE1);
    //line 2
    strcpy(display_line[DISPLAY_LINE2], "          ");
    update_string(display_line[DISPLAY_LINE2], DISPLAY_LINE2);
    //line 3
    strcpy(display_line[DISPLAY_LINE3], "          ");
    update_string(display_line[DISPLAY_LINE3], DISPLAY_LINE3);
     
    switch(serialState){
      case WAIT:
        strcpy(display_line[DISPLAY_LINE0], " WAITING  ");
        update_string(display_line[DISPLAY_LINE0], DISPLAY_LINE0);
        break;
      case RECIEVED:
        strcpy(display_line[DISPLAY_LINE0], " RECIEVED ");
        update_string(display_line[DISPLAY_LINE0], DISPLAY_LINE0);
        PrintRx();
        break;
      case SENDING:
        strcpy(display_line[DISPLAY_LINE0], " TRANSMIT ");
        update_string(display_line[DISPLAY_LINE0], DISPLAY_LINE0);  
        PrintRx();
        break;
      default:
        break;
    }
    
    switch(baudrate){
      case BAUD115K: 
        strcpy(display_line[DISPLAY_LINE2], "  115200  ");
        update_string(display_line[DISPLAY_LINE2], DISPLAY_LINE2);
      break;
      case BAUD460K: 
        strcpy(display_line[DISPLAY_LINE2], "  460800  ");
        update_string(display_line[DISPLAY_LINE2], DISPLAY_LINE2);
      break;
      default:  
        strcpy(display_line[DISPLAY_LINE2], "   9600   ");
        update_string(display_line[DISPLAY_LINE2], DISPLAY_LINE2);
      break;
    }
    
           
    display_changed = TRUE;
    update_display = TRUE;
    break;
  
  case MENU3:
    menu_state = IOT;
    //line 0
    strcpy(display_line[DISPLAY_LINE0], "          ");
    update_string(display_line[DISPLAY_LINE0], DISPLAY_LINE0);
    //line 1
    strcpy(display_line[DISPLAY_LINE1], "          ");
    update_string(display_line[DISPLAY_LINE1], DISPLAY_LINE1);
    //line 2
    strcpy(display_line[DISPLAY_LINE2], "          ");
    update_string(display_line[DISPLAY_LINE2], DISPLAY_LINE2);
    //line 3
    strcpy(display_line[DISPLAY_LINE3], "          ");
    update_string(display_line[DISPLAY_LINE3], DISPLAY_LINE3);  

    //line 0
    iotLocations[DEC_NINE] = iotlocation;
    strcpy(display_line[DISPLAY_LINE0],iotLocations);
    update_string(display_line[DISPLAY_LINE0], DISPLAY_LINE0);
    

    if(!displayTimer){  //writes the command being executed until timer stops
      switch(command){
      default:
        strcpy(display_line[DISPLAY_LINE1], "          ");
        update_string(display_line[DISPLAY_LINE1], DISPLAY_LINE1);
        break;
      case 'W':
        strcpy(display_line[DISPLAY_LINE1], " Forward  ");
        update_string(display_line[DISPLAY_LINE1], DISPLAY_LINE1);
        break;
      case 'S':
        strcpy(display_line[DISPLAY_LINE1], " Reverse  ");
        update_string(display_line[DISPLAY_LINE1], DISPLAY_LINE1);
        break;
      case 'A':
        strcpy(display_line[DISPLAY_LINE1], "Turn  Left");
        update_string(display_line[DISPLAY_LINE1], DISPLAY_LINE1);
        break;
      case 'D':
        strcpy(display_line[DISPLAY_LINE1], "Turn Right");
        update_string(display_line[DISPLAY_LINE1], DISPLAY_LINE1);
        break;
      case 'E':
        strcpy(display_line[DISPLAY_LINE1], " Exiting  ");
        update_string(display_line[DISPLAY_LINE1], DISPLAY_LINE1);
        break;
      case 'B':
        strcpy(display_line[DISPLAY_LINE1], "Blackline ");
        update_string(display_line[DISPLAY_LINE1], DISPLAY_LINE1);
        break;
      }
    }
    else{
      WriteTime();              //writes the timer value after "exit" is executed
    }
    
    //Puts the IP on lines 2 and 3
    char temp = DEC_ZERO;
    for(; (ip[temp]!=':') ; temp++){
        if(temp < DEC_TEN)
          display_line[DISPLAY_LINE2][temp] = ip[temp];
        else if(ip[temp] != '\0')
          display_line[DISPLAY_LINE3][temp-DEC_TEN] = ip[temp];
        else
          break;
    }
    
    update_string(display_line[DISPLAY_LINE2], DISPLAY_LINE2); 
    update_string(display_line[DISPLAY_LINE3], DISPLAY_LINE3);
    display_changed = TRUE;
    update_display = TRUE;
    break;
    
  default:      //blank menu for initialization
    //line 0
    strcpy(display_line[DISPLAY_LINE0], "          ");
    update_string(display_line[DISPLAY_LINE0], DISPLAY_LINE0);
    //line 1
    strcpy(display_line[DISPLAY_LINE1], "          ");
    update_string(display_line[DISPLAY_LINE1], DISPLAY_LINE1);
    //line 2
    strcpy(display_line[DISPLAY_LINE2], "          ");
    update_string(display_line[DISPLAY_LINE2], DISPLAY_LINE2);
    //line 3
    strcpy(display_line[DISPLAY_LINE3], "          ");
    update_string(display_line[DISPLAY_LINE3], DISPLAY_LINE3);    
    display_changed = TRUE;
    update_display = TRUE;
    break;
  }
}

void Write(void){
  // this function writes the car's state when following the line
  switch(car_state){
    case WAITING:
      switch(menu_state){
        case MAIN_MENU:
          WriteADC();
          break;
        case PROJ7:
          strcpy(display_line[DISPLAY_LINE3], " WAITING  ");
          update_string(display_line[DISPLAY_LINE3], DISPLAY_LINE3);
          display_changed = TRUE;
          break;
      }
      break;
    case INTERCEPTING:
      strcpy(display_line[DISPLAY_LINE3], "INTERCEPTN");
      update_string(display_line[DISPLAY_LINE3], DISPLAY_LINE3);
      display_changed = TRUE;
      break;
    case TURNING:
      strcpy(display_line[DISPLAY_LINE3], " TURNING  "); 
      update_string(display_line[DISPLAY_LINE3], DISPLAY_LINE3);
      display_changed = TRUE;
      break;
    case FOLLOWING:
      strcpy(display_line[DISPLAY_LINE3], "FOLLOWING "); 
      update_string(display_line[DISPLAY_LINE3], DISPLAY_LINE3);
      display_changed = TRUE;
      break;
    case STOPPING:
      strcpy(display_line[DISPLAY_LINE3], " STOPPING "); 
      update_string(display_line[DISPLAY_LINE3], DISPLAY_LINE3);
      display_changed = TRUE;  
      break;
    default:
      break;
  }

    update_display = TRUE;

    return;
}

void PrintRx(void){
  // function usedin proj 8
  // displays what was received 
  char temp = DEC_ZERO;
  for(; temp < DEC_TEN ; temp++){
    if(temp <= processLength)
      display_line[DISPLAY_LINE1][temp] = processBuffer[temp];
    else
      display_line[DISPLAY_LINE1][temp] = DEC_ZERO;
  }
  update_string(display_line[DISPLAY_LINE1], DISPLAY_LINE1);    
}

void WriteTime(void){
  // converts a timer into a BCD and displays it
    HEXtoBCD(timer);
    display_line[DISPLAY_LINE1][DEC_FIVE] = adc_char[DEC_ZERO];
    display_line[DISPLAY_LINE1][DEC_SIX] = adc_char[DEC_ONE];
    display_line[DISPLAY_LINE1][DEC_SEVEN] = adc_char[DEC_TWO];
    display_line[DISPLAY_LINE1][DEC_EIGHT] = '.';
    display_line[DISPLAY_LINE1][DEC_NINE] = adc_char[DEC_THREE];
    update_string(display_line[DISPLAY_LINE1], DISPLAY_LINE1);
    display_changed = TRUE;
}