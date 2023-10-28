//------------------------------------------------------------------------------
//
//  Description: This file contains the Switch Control
//
//
//  Samantha Pilgreen
//  Sept 2023
//------------------------------------------------------------------------------
#include <string.h>
#include  "msp430.h"
#include  "Headers/functions.h"
#include  "Headers/ports.h"
#include  "Headers/globals.h"
#include  "Headers/macros.h"

// Function Prototypes
void Init_Switches(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void Switches_Process(void);
void lcd_180(void);


//------------------------------------------------------------------------------
// Switch Configurations
extern char display_line[4][11];
extern char *display[4];
char pwm_state;
extern char change;
char run_wheels;
extern volatile unsigned char display_changed;

volatile unsigned char forward_start;

volatile char sw1_pressed;
volatile char sw2_pressed;

// Path Globals
char shape_state;
char next_shape;

void Switches_Process(void){
//------------------------------------------------------------------------------
// Switches the message of the LCD based on which switch is pressed and shape state
    Switch1_Process();
    Switch2_Process();
//------------------------------------------------------------------------------
}

void Switch1_Process(void) {
    if (sw1_pressed){
        sw1_pressed = FALSE;

        // Start the sequence if in NONE
        if (shape_state == NONE) {
            shape_state = START_PAUSE;
            // Update Display
            strcpy(display_line[0], " SWITCH 1 ");
            display_changed = TRUE;
        }

    }
}
void Switch2_Process(void) {
    if (sw2_pressed){
        sw2_pressed = FALSE;

        P2OUT ^= IR_LED; // Toggle IR LED

        // Update Display
        if (P2OUT & IR_LED) {
            // LED IS ON
            strcpy(display_line[1], "IR LED ON ");
        }
        else {
            strcpy(display_line[1], "IR LED OFF");
        }

        display_changed = TRUE;

    }
}
