//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//  Samantha Pilgreen
//  Sept 2023
//------------------------------------------------------------------------------
#include  "msp430.h"
#include  <string.h>
#include  "Headers/functions.h"
#include  "Headers/LCD.h"
#include  "Headers/macros.h"
#include  "Headers/globals.h"

// Function Prototypes
void main(void);
void Display_Process(void);

// Global Variables
volatile char slow_input_down;
extern char display_line[4][11];
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;

extern volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;


unsigned int wheel_moving;
volatile unsigned char forward_start;
// Timer Globals
unsigned int Old_Time_Sequence;
unsigned char Time_Sequence_Changed;
int cycle_time;

// Path Globals
char shape_state;

//void main(void){
void main(void){
//    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
  PM5CTL0 &= ~LOCKLPM5;
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings

  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD
  Init_REF();                          // Initialize ADC/DAC REF Voltage
  Init_DAC();                          // Initialize DAC
  Init_ADC();                          // Initialize ADC
//P2OUT &= ~RESET_LCD;
  // Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
  strcpy(display_line[0], "          ");
  strcpy(display_line[1], "IR LED ON ");
  strcpy(display_line[2], "          ");
  strcpy(display_line[3], "R        L");
  display_changed = TRUE;
//  Display_Update(0,0,0,0);


//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    Switches_Process();                // Check for switch state change
    Display_Process();                 // Update Display
    Motors_Process();

    ADC_Process();
    Path_Process();

    P3OUT ^= TEST_PROBE;               // Change State of TEST_PROBE OFF
  }
//------------------------------------------------------------------------------

}


void error_state(void) {
    // If an error occurs, reset the state, turn on Red LED, and show error message
    Init_Ports();                        // Initialize Ports
    Init_Clocks();                       // Initialize Clock System
    Init_Conditions();                   // Initialize Variables and Initial Conditions
    Init_Timers();                       // Initialize Timers
    Init_LCD();                          // Initialize LCD

    P1OUT |= RED_LED;
    // Update Display
    strcpy(display_line[0], "  ERRORS  ");
    strcpy(display_line[1], "          ");
    strcpy(display_line[2], "          ");
    strcpy(display_line[3], "          ");
    display_changed = TRUE;
}
