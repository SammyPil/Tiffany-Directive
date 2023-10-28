//------------------------------------------------------------------------------
//
//  Description: This file contains the functions related to
//  the paths that the car drives
//  Samantha Pilgreen
//  Sept 2023
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include <string.h>
#include  "msp430.h"
#include  "Headers/functions.h"
#include  "Headers/ports.h"
#include  "Headers/macros.h"
#include  "Headers/globals.h"

extern char display_line[4][11];
extern volatile unsigned char display_changed;

// Timer Globals
unsigned char Time_Sequence_Changed;
int cycle_time;
int delay_start;
volatile unsigned int time_count;
volatile char timer_complete;
volatile unsigned int dc_count;


// Path Globals
char shape_state;
char run_state;
int right_motor_count;
int left_motor_count;
//int segment_time;
//int action_stage;
//int action_cycles;


// Function Prototypes
void Run(void);

void start_case(void);
void run_case(void);
void end_case(void);
void run_case_circle(void);
void run_case_figure_8(void);
void run_case_triangle(void);

void run_case_general(int right_count_time, int left_count_time, int wheel_count_time, int travel_dist);

void Path_Process(void) {
    // Call the appropriate functions based on the current state
    switch (shape_state) {
    case NONE: break;  // Nothing to do if None
    case LINE_FOUND_1:   // Line Found, Cancel action and reset values
        Motors_stop();  // Turn all motors off
        run_state = START;
        timer_complete = RESET_STATE;
        shape_state = BIG_PAUSE;
        display_update_line1("LINE FOUND");
        // Cancel any existing interrupt
        TB0CCTL0 &= ~CCIE; // CCR0 disable interrupt
        TB0CCTL0 &= ~CCIFG; // CCR0 Clear interrupt flag
        dc_count = RESET_STATE; // Reset for next count
        break;
    case LINE_FOUND_2:
        Motors_stop();  // Turn all motors off
        run_state = START;
        timer_complete = RESET_STATE;
        shape_state = NONE;
        display_update_line1("LINE FOUND");
        // Cancel any existing interrupt
        TB0CCTL0 &= ~CCIE; // CCR0 disable interrupt
        TB0CCTL0 &= ~CCIFG; // CCR0 Clear interrupt flag
        dc_count = RESET_STATE; // Reset for next count
        break;

    default:
        // For all other states, perform standard run command
        Run();
        break;
    }

}

void Run(void) {
    switch (run_state) {
    case START: // Begin
        start_case();
        break; //
    case RUN: // Run
        run_case();
        break; //
    case END: // End
        end_case();
        break; //
    default: break;
    }
}



void start_case(void) {
    // Set Wheel Speed, Turn on State Timer
    // Motors are off
    TB0CCTL0 &= ~CCIFG; // TB0CCR0 Clear interrupt flag
    TB0CCTL0 |= CCIE; // TB0CCR0 enable interrupt

    switch (shape_state) {
    case START_PAUSE:
        time_count = WAIT_1_SEC;
        display_update_line1("  WAITING ");
        break;
    case FORWARD_1:
        time_count = WAIT_1_SEC;
        display_update_line1("  FORWARD ");
        Motors_forward();
        break;
    case BIG_PAUSE:
        time_count = WAIT_5_SEC;
        break;
    case CCW_TURN:
        time_count = WAIT_5_SEC;
        display_update_line1("  TURNING ");
        Motors_ccw();
        break;

    }
     run_state = RUN;
}

void run_case(void) {
    if (timer_complete) run_state = END;
}

void end_case(void) {
    // Reset Conditionals
    Motors_stop();  // Turn all motors off
    run_state = START;
    timer_complete = RESET_STATE;

    switch (shape_state) {
    case FORWARD_1:
        // Line not found, break free from the loop
        shape_state = NONE;
        display_update_line1("NOT FOUND ");
        break;
    case CCW_TURN:
        // Line not found, report error
        shape_state = NONE;
        display_update_line1("NOT FOUND ");
    default:
        shape_state++;
        break;
    }
}
