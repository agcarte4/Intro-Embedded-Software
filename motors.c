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

extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern char display_line[DISPLAY_ARRAY][DISPLAY_LENGTH];

extern volatile unsigned int Time_Sequence;        //counts to 1s
extern volatile unsigned int Time_Sequence1;        //counts to 1s
extern unsigned int time_change;
extern volatile unsigned int oneSecTimer;
extern char car_state;
char onlyonce = TRUE;

unsigned int white = DEC_ZERO;
unsigned int black = DEC_ZERO;
extern volatile unsigned int ADC_Left_Detector;
extern volatile unsigned int ADC_Right_Detector;
char lineFound = FALSE;
extern char timer_stop;
char turns = DEC_ZERO;
char lineState = DEC_ZERO;
extern volatile unsigned char commandTime;  //25ms
unsigned char turnTime = ONE_SEC;
unsigned char straightTime = DEC_THREE;


void Motors(void){
  switch(car_state){
  case WAITING:
    Motors_Off();
    //Write();
    onlyonce = TRUE;
    if(lineFound & (Time_Sequence1 == ONE_SEC)){
      car_state = TURNING; 
      lineFound = FALSE;
    }
    break;
  case INTERCEPTING:
    //Write();
    switch(lineState){
    case STRAIGHT:
        if(onlyonce){
          Run_Straight();
          oneSecTimer = DEC_ZERO;
          onlyonce = FALSE;
        }
        else if(oneSecTimer == straightTime){
          Motors_Off();
          onlyonce = TRUE;
          lineState = TURN;
          commandTime = DEC_ZERO;
          //if(turns == DEC_ONE){
            //turnTime = THREEQ_SEC;
          //}
        }
        break;
      case TURN:
        if(onlyonce){
          Turn_CW();
          onlyonce = FALSE;
          oneSecTimer = DEC_ZERO;
          turns++;
          straightTime = DEC_FOUR;
        }
        else if(commandTime == turnTime){
          Motors_Off();
          oneSecTimer = DEC_ZERO;
          onlyonce = TRUE;
          if(turns < DEC_TWO){
            lineState = STRAIGHT;
          }
          else {
            lineState = LOOKFORWHITE;
          }
        }
        break;
      case LOOKFORWHITE:
        if(onlyonce){
          Run_Straight();
          onlyonce = FALSE;
        }
        else if((ADC_Right_Detector < (white+DEC_TEN))|(ADC_Left_Detector < (white+DEC_TEN))){
          onlyonce = TRUE;
          lineState = LOOKFORBLACK;
        }
        break;
      case LOOKFORBLACK:
        if((ADC_Right_Detector > black)|(ADC_Left_Detector > black)){
           Motors_Off();
           lineFound = TRUE;
           car_state = WAITING;
        }
        break;
      default: break;
    }
    break;
  case TURNING:
    //Write();
    if(onlyonce){
      Turn_CCW();
      onlyonce = FALSE;
    }
    else if((ADC_Right_Detector > black)){
      Motors_Off();
      car_state = FOLLOWING;
      onlyonce = TRUE;
    }
    break;
  case FOLLOWING:
    //Write();
    Follow();
    //if(onlyonce){
      //oneSecTimer = DEC_ZERO;
      //onlyonce = FALSE;
     //}
    //if(oneSecTimer == 25){
      //car_state = STOPPING;
      //onlyonce = TRUE;
    //}
    break;
  /*case STOPPING:
    Write();
    if(onlyonce){
      Turn_CCW();
      onlyonce = FALSE;
      oneSecTimer = DEC_ZERO;
    } 
    if((oneSecTimer == DEC_ONE) & (!onlyonce)){
      Motors_Off();
      car_state = WAITING;
      timer_stop = TRUE;
    }
    break;*/
  default: break;
  }
  return;
}


void Run_Straight(void){
  Motors_Off();
  RIGHT_FORWARD_SPEED = STRAIGHTRIGHTSPD;
  LEFT_FORWARD_SPEED = STRAIGHTLEFTSPD;
}

void Follow(void){             
  if((ADC_Left_Detector > black) & (ADC_Right_Detector > black)){
    Run_Straight();
  }
  else{
    if((ADC_Left_Detector < black) & (ADC_Right_Detector > black)){
      Turn_CW();
    }
    else if((ADC_Left_Detector > black) & (ADC_Right_Detector < black)){
      Turn_CCW(); 
    }
  }
}



void Motors_Off(void){
  Forward_Off();
  Reverse_Off();
}

void Reverse_On(void){     //  
  Motors_Off();
  RIGHT_REVERSE_SPEED = RIGHTREVERSESPEED;
  LEFT_REVERSE_SPEED = LEFTREVERSESPEED;
}


void Turn_CW(void){
  Motors_Off();
  RIGHT_REVERSE_SPEED = TURNSPEED;
  LEFT_FORWARD_SPEED = TURNSPEED;
}
void Turn_CCW(void){         // Turns CCW
  Motors_Off();
  RIGHT_FORWARD_SPEED = TURNSPEED;
  LEFT_REVERSE_SPEED = TURNSPEED;
}

void Forward_Off(void){      // Stops going forward
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
}

void Reverse_Off(void){        // Stops reversing
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}
void init_Params(void){                 //resets the line-finding parameters so that the function can be 
  turnTime = ONE_SEC;                   //called several times without having to reset the car
  straightTime = DEC_THREE;
  lineFound = FALSE;
  turns = DEC_ZERO;
  lineState = STRAIGHT;
  car_state = WAITING;
}