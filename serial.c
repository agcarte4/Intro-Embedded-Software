//------------------------------------------------------------------------------
//
//  Description: This file contains the functions pertaining to the operation 
//  of serial ports.
//
//
//  Alex Carter
//  March 2019
//  Built with IAR Embedded Workbench Version: 7.12.1
//------------------------------------------------------------------------------

#include "functions.h"
#include "msp430.h"
#include "macros.h"

volatile unsigned int iot_rx_ring_wr;
volatile unsigned int iot_rx_ring_rd;
volatile unsigned int iot_tx_ring_wr;
volatile unsigned int iot_tx_ring_rd;
volatile char iot_Char_Rx[SMALL_RING_SIZE];
volatile char iot_Char_Tx[LARGE_RING_SIZE];
volatile unsigned int usb_rx_ring_wr;
volatile unsigned int usb_rx_ring_rd;
volatile unsigned int usb_tx_ring_wr;
volatile unsigned int usb_tx_ring_rd;
volatile char usb_Char_Rx[SMALL_RING_SIZE];
volatile char usb_Char_Tx[LARGE_RING_SIZE];
char baudrate = DEC_ONE; //defaults to 115k

char processBuffer[bufferLength] = { DEC_ZERO };
signed int processLength = DEC_ZERO;
char serialState = WAIT;
extern volatile unsigned int oneSecTimer;

extern volatile unsigned int UCA1_index;
extern volatile unsigned int UCA0_index;
extern char serialState;
char commands[commandLength] = {DEC_ZERO};
char commandsTime[commandLength] = {DEC_ZERO};
char serialSelect = IoT;
unsigned char command_wr = DEC_ZERO;
unsigned char command_rd = DEC_ZERO;

char iotONCE = FALSE;
char ip[SMALL_RING_SIZE] = {DEC_ZERO};
char ssid[DEC_TEN] = {' ', ' ', ' ', 'N', 'C', 'S', 'U', ' ', ' ', ' '};

extern volatile unsigned char commandTime;  //25ms
unsigned char commandStart = TRUE;
unsigned char commandGet = TRUE;

extern char car_state;
extern char timer_stop;
unsigned char timerStart = TRUE;
unsigned char displayTimer = FALSE;
unsigned char iotlocation = '0';
unsigned char command;


void Init_Serial(void){
  Init_Serial_UCA0();
  Init_Serial_UCA1();
  UCA0_index = DEC_ZERO;
  UCA1_index = DEC_ZERO;
}

void Init_Serial_UCA0(void){
  //UCA0TXBUF = test_command[0];

  int i;
  for(i=DEC_ZERO; i<SMALL_RING_SIZE; i++){
    iot_Char_Rx[i] = DEC_ZERO; // USB Rx Buffer
  }
  
  iot_rx_ring_wr = BEGINNING;
  iot_rx_ring_rd = BEGINNING;
  
  for(i=DEC_ZERO; i<LARGE_RING_SIZE; i++){ // May not use this
    iot_Char_Tx[i] = DEC_ZERO; // USB Tx Buffer
  }

  iot_tx_ring_wr = BEGINNING;
  iot_tx_ring_rd = BEGINNING;

  // Configure UART 0
  UCA0CTLW0 = DEC_ZERO; // Use word register
  UCA0CTLW0 |= UCSWRST; // Set Software reset enable
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  
  //Software Example
  // ***** Continuation from previous slide
  // 9,600 Baud Rate
  // 1. Calculate N = fBRCLK / Baudrate
  // N = SMCLK / 9,600 => 8,000,000 / 9,600 = 833.3333333
  // if N > 16 continue with step 3, otherwise with step 2
  // 2. OS16 = 0, UCBRx = INT(N)
  // continue with step 4
  // 3. OS16 = 1,
  // UCx = INT(N/16),
  // = INT(N/16) = 833.333/16 => 52
  // UCFx = INT([(N/16) – INT(N/16)] × 16)
  // = ([833.333/16-INT(833.333/16)]*16)
  // = (52.08333333-52)*16
  // = 0.083*16 = 1
  // 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
  // Decimal of SMCLK / 8,000,000 / 9,600 = 833.3333333 => 0.333 yields 0x49 [Table]
  // 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
  // TX error (%) RX error (%)
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
  //UCA0BRW = 52; // 9,600 Baud
  // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
  // UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
  //UCA0BRW = ((CLK_FREQ/baudrate)/DEC_SXTN);
   
  switch(baudrate){
   case BAUD115K: //   8MHz/115200 = 69.4444/16 = 4.3403,   BRW = 4, UCFx = 5 (5.4448), UCSx = 0x55 (.4444)
     UCA0BRW = BR115K;
     UCA0MCTLW = MOD115K;
     break;
   case BAUD460K: //   8MHz/460800 = 17.3611/16 = 1.0851,   BRW = 1, UCFx = 1 (1.3611), UCSx = 0x4A (.3611)
     UCA0BRW = BR460K;
     UCA0MCTLW = MOD460K;
     break;
   default:  //defaults to 9600 baud
     UCA0BRW = BR9600;
     UCA0MCTLW = MOD9600;
     break;
   }

  UCA0CTLW0 &= ~UCSWRST; // Set Software reset enable
  UCA0IE |= UCRXIE; // Enable RX interrupt
}


void Init_Serial_UCA1(void){
  //UCA1TXBUF = test_command[0];

  int i;
  for(i=DEC_ZERO; i<SMALL_RING_SIZE; i++){
  usb_Char_Rx[i] = DEC_ZERO; // USB Rx Buffer
  }
  
  usb_rx_ring_wr = BEGINNING;
  usb_rx_ring_rd = BEGINNING;
  
  
  for(i=DEC_ZERO; i<LARGE_RING_SIZE; i++){ // May not use this
    usb_Char_Tx[i] = DEC_ZERO; // USB Tx Buffer
  }

  usb_tx_ring_wr = BEGINNING;
  usb_tx_ring_rd = BEGINNING;

  // Configure UART 1
  UCA1CTLW0 = DEC_ZERO; // Use word register
  UCA1CTLW0 |= UCSWRST; // Set Software reset enable
  UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  
  switch(baudrate){
   case BAUD115K: //   8MHz/115200 = 69.4444/16 = 4.3403,   BRW = 4, UCFx = 5 (5.4448), UCSx = 0x55 (.4444)
     UCA1BRW = BR115K;
     UCA1MCTLW = MOD115K;
     break;
   case BAUD460K: //   8MHz/460800 = 17.3611/16 = 1.0851,   BRW = 1, UCFx = 1 (1.3611), UCSx = 0x4A (.3611)
     UCA1BRW = BR460K;
     UCA1MCTLW = MOD460K;
     break;
   default:  //defaults to 9600 baud
     UCA1BRW = BR9600;
     UCA1MCTLW = MOD9600;
     break;
   }

  UCA1CTLW0 &= ~UCSWRST; // Set Software reset enable
  UCA1IE |= UCRXIE; // Enable RX interrupt
}

void SerialProcess(void){
  // Alex Carter
  //
  //Function called in main
  //check the processBuffer for a new command
  //
  //
   switch(processBuffer[DEC_ZERO]){
    case '_':                           //FRAM command
      switch(processBuffer[DEC_ONE]){
      case '0':
        switch(processBuffer[DEC_TWO]){
          case '5':
            switch(processBuffer[DEC_THREE]){
            case '1':
              switch(processBuffer[DEC_FOUR]){
                case '4':
                  saveCommand();
                  break;
              default: break;
              }
            break;
            default: break;
          }
          break;
          default: break;
        }
        clearProcessBuffer();
        break;
      default: break;
      }
      break;
    default:
       clearProcessBuffer();
      break;
    }
}

void saveCommand(void){
  // Alex Carter
  //
  //This function checks the porcess buffer for a command, then saves it to 
  //command and time array.  
  //
  //ProcessBuffer elements 6-8 should be BCD, needs to be converted to time (ms)
  //temp should hold the decimal equivalent of what was recieved
  
  char count = DEC_ZERO;
  char temp = DEC_ZERO;
  for(;count < processLength; count++){
    if(processBuffer[count] == '_'){
      commands[command_wr] = processBuffer[count+DEC_FIVE]; //offset to read time received
        temp = (processBuffer[count+DEC_SIX] - HEX_ZERO)*DEC_100;
        temp = temp + (processBuffer[count+DEC_SEVEN] - HEX_ZERO)*DEC_TEN;
        temp = temp + (processBuffer[count+DEC_EIGHT] - HEX_ZERO);          
                                                                
        commandsTime[command_wr] = temp;        //the number recieved is how many 25ms intervals to do
        command_wr++;
        if(command_wr >= sizeof(commands))      //circle back to beginning of the array
          command_wr = DEC_ZERO;
    }
  }
  commandGet = TRUE;            //tells other functions it is ready to save commands
}

void runCommands(void){
  // Alex Carter
  //
  //This function executes the commands stored in the commands array
  //Each command has a corresponding duration in commandsTime
  //
  switch(commands[command_rd]){
  case '1':             //increments location index for iot course
    if(commandStart){
      commandStart = FALSE;     
      commandTime = DEC_ZERO;
      iotlocation++;
    }
    else if(commandTime == commandsTime[command_rd]){
      commandStart = TRUE;
      commands[command_rd] = DEC_ZERO;
      commandsTime[command_rd] = DEC_ZERO;
      command_rd++;
    }
    break;
  case 'W':             //drives straight
    if(commandStart){
      Run_Straight();                   //turn on the motors
      commandTime = DEC_ZERO;           //clear the timer value;
      commandStart = FALSE;
      command = 'W';
    }
    else if(commandTime == commandsTime[command_rd]){
      Motors_Off();
      commandStart = TRUE;
      commands[command_rd] = DEC_ZERO;
      commandsTime[command_rd] = DEC_ZERO;
      command_rd++;
    }
    if(timerStart){
      timerStart = FALSE;
      timer_stop = FALSE;
    }
    break;
  case 'S':             //reverse
    if(commandStart){
      Reverse_On();                   //turn on the motors
      commandTime = DEC_ZERO;           //clear the timer value;
      commandStart = FALSE;
      command = 'S';
    }
    else if(commandTime == commandsTime[command_rd]){
      Motors_Off();
      commandStart = TRUE;
      commands[command_rd] = DEC_ZERO;
      commandsTime[command_rd] = DEC_ZERO;
      command_rd++;
    }
    break;
  case 'A':             //turn left
    if(commandStart){
      Turn_CCW();                   //turn on the motors
      commandTime = DEC_ZERO;           //clear the timer value;
      commandStart = FALSE;
      command = 'A';
    }
    else if(commandTime == commandsTime[command_rd]){
      Motors_Off();
      commandStart = TRUE;
      commands[command_rd] = DEC_ZERO;
      commandsTime[command_rd] = DEC_ZERO;
      command_rd++;
    }
    break;
  case 'D':             //turn right
    if(commandStart){
      Turn_CW();                   //turn on the motors
      commandTime = DEC_ZERO;           //clear the timer value;
      commandStart = FALSE;
      command = 'D';
    }
    else if(commandTime == commandsTime[command_rd]){
      Motors_Off();
      commandStart = TRUE;
      commands[command_rd] = DEC_ZERO;
      commandsTime[command_rd] = DEC_ZERO;
      command_rd++;
    }
    break;
  case 'B':             //initiate blackline
    if(commandStart){
      car_state = INTERCEPTING;         //sets car state to intercept line
      commandStart = FALSE;             //doesnt have a duration
      commands[command_rd] = DEC_ZERO;
      commandsTime[command_rd] = DEC_ZERO;
      command_rd++;
      command = 'B';
    }
    break;
  case 'E':             //exit blackline
    if(!commandStart){
      car_state = IOTMODE;
      Run_Straight();
      commandStart = TRUE;
      commandTime = DEC_ZERO;
      command = 'E';
    }
    else if(commandTime == commandsTime[command_rd]){
      Motors_Off();
      commands[command_rd] = DEC_ZERO;
      commandsTime[command_rd] = DEC_ZERO;
      command_rd++;
      timer_stop = TRUE;
      displayTimer = TRUE;
      init_Params();

    }
    break;
  default: break;
  }

  if(command_rd >= sizeof(commands)){  //circle back to the beginning of the array
    command_rd = DEC_ZERO;
  }
}

void clearProcessBuffer(void){
  char i = DEC_ZERO;
  for(; (processBuffer[i]!='\0'); i++)
    processBuffer[i] = DEC_ZERO;
}

void transmitString(char * input) {
  
  char temp;
  for(temp = DEC_ZERO; *(input+temp)!= '\0'; temp++) {
    out_character(input[temp]);
  }
  
}

void out_character(char character){
  for(char i = DEC_ZERO; i < TXWAIT; i++);
  UCA0TXBUF = character;
}