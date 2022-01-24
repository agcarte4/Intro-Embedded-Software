//**************************************************************************
//  
//  Description:  Contains the macros neccessary in main and other files
//  Alex Carter
//  Jan 2019
//
//**************************************************************************

#define RED_LED_ON      (P1OUT |= RED_LED) //
#define RED_LED_OFF    (P1OUT &= ~RED_LED) //
#define GREEN_LED_ON    (P6OUT |= GRN_LED) //
#define GREEN_LED_OFF  (P6OUT &= ~GRN_LED) //
#define IR_LED_ON        (P5OUT |= IR_LED) //
#define IR_LED_OFF      (P5OUT &= ~IR_LED) // 
#define IOTRESETON   (P5OUT &= ~IOT_RESET) //
#define IOTRESETOFF   (P5OUT |= IOT_RESET) //

#define ALWAYS                         (1) //
#define RESET_STATE                    (0) //
#define TRUE                           (1) // True
#define FALSE                          (0) // False
#define RESET_BITS                  (0x00) // 0000 0000
#define BITS_HIGH                   (0xff) // 1111 1111
#define DEC_ZERO                       (0) // 0
#define DEC_ONE                        (1) // 1
#define DEC_TWO                        (2) // 2
#define DEC_THREE                      (3) // 3
#define DEC_FOUR                       (4) // 4
#define DEC_FIVE                       (5) // 5
#define DEC_SIX                        (6) // 6
#define DEC_SEVEN                      (7) // 7
#define DEC_EIGHT                      (8) // 8
#define DEC_NINE                       (9) // 9
#define DEC_TEN                       (10) // 10
#define DEC_ELV                       (11) // 11
#define DEC_TWLV                      (12) // 12
#define DEC_SXTN                      (16) // 16
#define DEC_100                      (100) // 100
#define HEX_30                      (0x30) // 0x30
#define DEBOUNCE_COUNT             (11000) // Number of function calls for SWs to reset
#define VECTOR_BOUND                  (14) // 
#define DEC_999                      (999) //
#define DEC_99                        (99) // 
#define DEC_9                          (9) //
#define BIT_3                       (1000) //
#define BIT_2                        (100) //
#define BIT_1                         (10) //
#define TXCOMPLETE                  (0x08) //
#define bufferLength                  (40) //
#define commandLength                 (16) //
#define TXWAIT                       (255) // number of counts for the tx to wait
#define HEX_ZERO                    (0x30) // used for char to int conversion

//ADC/Motors
#define THUMB                           (0) //
#define R_DET                           (1) //
#define L_DET                           (2) //
#define INTERCEPTING                  ('I') //
#define WAITING                       ('W') //
#define TURNING                       ('T') //
#define FOLLOWING                     ('F') //
#define STOPPING                      ('S') // 
#define IOTMODE                       ('M') //
#define EXITTIME                       (80) //

//Clock
#define MCLK_FREQ_MHZ                  (8) // MCLK = 8MHz
#define CLEAR_REGISTER            (0X0000) // Clear Register
#define REGISTER_HIGH             (0xffff) // Set Register to high
#define FREQ_TRIM                      (3) // 
#define HEX_256                    (0x100) //  
#define HEX_243                     (0xF3) // 
#define HEX_3K                     (0xBB8) // 
#define HEX_511                   (0x01FF) // 
#define SHIFT_4BITS                    (4) // Value used to shift 4 bits
#define BITS4_5_6                 (0x0070) // Sets bits 4, 5, and 6 to high

//Display
#define DISPLAY_LINE0                  (0) // First line in char array for display
#define DISPLAY_LINE1                  (1) // Second line for char array
#define DISPLAY_LINE2                  (2) // Third line for char array
#define DISPLAY_LINE3                  (3) // Fourth line for char array
#define NULL_LOC                      (10) // Location of NULL in char strings
#define DISPLAY_LENGTH                (11) // Max length of display string is 11
#define DISPLAY_ARRAY                  (4) // Display array size
#define MENU0                          (0) //
#define MENU1                          (1) //
#define MENU2                          (2) //
#define MENU3                          (3) // 
#define MAIN_MENU                    ('M') //
#define PROJ7                        ('7') //
#define PROJ8                        ('8') //
#define IOT                          ('I') //
#define OFFRX                        ('0') //
#define ONRX                         ('1') //

//Time
#define QUARTER_SEC                   (10) // 250ms = 10*25ms
#define HALF_SEC                      (20) // 500ms = 20*25ms
#define THREEQ_SEC                    (30) // 750ms = 30*25ms
#define ONE_SEC                       (40) // 1000s = 40*25ms
#define ONE25_SEC                     (50) // 1250ms = 50*25ms
#define TWO5_SEC                     (100) // 2500 ms

// Timers 
#define TB0CCR0_INTERVAL           (12500) // 25 ms
#define HALF_S_COUNT                  (20) // 500ms = 20*25ms
#define ONE_S_COUNT                   (40) // 1000ms = 40*25ms
#define TWOHUN_MS_COUNT                (8) // 200ms = 8*25ms
#define TB0CCR1_INTERVAL           (25000) // 50 ms
#define REG0                           (0) // Vector bit representing TB0CCR0
#define REG1                           (2) // Vector bit representing TB0CCR1
#define REG2                           (4) // Vector bit representing TB0CCR2
#define OVERFLOW                      (14) // Vector bit representing overflow of TB0


//       MOTORS
#define RIGHT_FORWARD_SPEED      (TB3CCR1) //
#define LEFT_FORWARD_SPEED       (TB3CCR2) //
#define RIGHT_REVERSE_SPEED      (TB3CCR3) // 
#define LEFT_REVERSE_SPEED       (TB3CCR4) //
#define WHEEL_PERIOD               (50000) //
#define WHEEL_OFF                      (0) //
#define STRAIGHT                       (0) //
#define TURN                           (1) //
#define LOOKFORWHITE                   (2) //
#define LOOKFORBLACK                   (3) //
#define STRAIGHTRIGHTSPD           (25000) //
#define STRAIGHTLEFTSPD            (47500) //
#define RIGHTREVERSESPEED          (22000) //
#define LEFTREVERSESPEED           (45000) //
#define TURNSPEED                 (7000) //

//      serial ports
#define BEGINNING                     (0) //
#define SMALL_RING_SIZE              (40) //
#define LARGE_RING_SIZE              (16) //
#define BAUD9600                      (0) // 
#define BAUD115K                      (1) // 115200 baudrate
#define BAUD460K                      (2) // 460800 baudrate
#define BR115K                        (4) //
#define MOD115K                  (0x5551) //
#define BR460K                        (1) //
#define MOD460K                  (0x4A11) //
#define BR9600                       (52) //
#define MOD9600                  (0x4911) //
#define CR                         (0x0D) //
#define LF                         (0x0A) //
#define WAIT                          (0) //
#define RECIEVING                     (1) //
#define RECIEVED                      (2) //
#define SENDING                       (3) //
#define USB                           (1) //
#define IoT                           (0) //
#define VERIFY                        (0) //
#define SSID                          (0) //
#define IP                            (1) //

#define iotRESET                      (0) // initial state as iot resets
#define iotSOFTRESET                  (1) // software reset for the iot
#define iotSYNC                       (2) // iot is setting the desync time
#define iotPORT                       (3) // iot is setting the port socket
#define iotRDY                        (4) // iot is ready for operation

//=============================================
//   Ports
//=============================================

//Port 1 Pins
#define RED_LED         (0x01)  //      0  RED LED 0
#define A1_SEEED        (0X02)  //      1 A1_SEEED
#define V_DETECT_L      (0X04)  //      2
#define V_DETECT_R      (0X08)  //      3
#define A4_SEEED        (0x10)  //      1 A4_SEEED
#define V_THUMB         (0x20)  //      5
#define UCA0RXD         (0x40)  //      6 Back Channel UCA0RXD
#define UCA0TXD         (0x80)  //      7 Back Channel UCA0TXD

//Port 2 Pins   
#define P2_0            (0x01)  //      0
#define P2_1            (0x02)  //      1
#define P2_2            (0x04)  //      2
#define SW2             (0x08)  //      3 SW2
#define P2_4            (0x10)  //      4
#define P2_5            (0x20)  //      5
#define LFXOUT          (0x40)  //      XOUTR
#define LFXIN           (0x80)  //      XINR

//Port 3 pins
#define TEST_PROBE      (0x01)  //      0 TEST PROBE
#define OA20            (0x02)  //      1 Photodiode Circuit
#define OA2N            (0x04)  //      2 Photodiode Circuit
#define OA2P            (0x08)  //      3 Photodiode Circuit
#define SMCLK_OUT       (0x10)  //      4 SMCLK
#define P3_5            (0x20)  //      5
#define IOT_LINK        (0x40)  //      6 IOT LINK
#define P3_7            (0x80)  //      7

//Port 4 pins

#define RESET_LCD       (0x01)  //      0 LCD Reset
#define SW1             (0x02)  //      1 SW1
#define UCA1RXD         (0x04)  //      2 Back Channel UCA1RXD
#define UCA1TXD         (0x08)  //      3 Back Channel UCA1TXD
#define UCB1_CS_LCD     (0x10)  //      4 Chip Select
#define UCB1CLK         (0x20)  //      5 SPI mode - clock output—UCB1CLK
#define UCB1SIMO        (0x40)  //      6 UCB1SIMO
#define UCB1SOMI        (0x80)  //      7 UCB1SOMI

//Port 5 pins
#define IOT_RESET       (0x01)  //      0 IoT Reset
#define P5_1            (0x02)  //      1
#define IOT_PROG_SEL    (0x04)  //      IoT program select
#define IOT_PROG_MODE   (0x08)  //      IoT program mode
#define IR_LED          (0x10)  //      IR LED

//Port 6 pins
#define R_FORWARD       (0x01)  //      Right Forward
#define L_FORWARD       (0x02)  //      Left Forward
#define R_REVERSE       (0x04)  //      Right Reverse
#define L_REVERSE       (0x08)  //      Left Reverse
#define LCD_BACKLIGHT   (0x10)  //      LCD Backlight
#define P6_5            (0x20)  //      5       
#define GRN_LED         (0x40)  //      Green LED