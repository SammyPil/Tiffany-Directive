//------------------------------------------------------------------------------
//
//  Description: This file contains the functions related to
//  operating the motors that drive the car
//  Samantha Pilgreen
//  Sept 2023
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "Headers/functions.h"
#include  "Headers/ports.h"
#include  "Headers/macros.h"


void Motors_Process(void) {
    Motors_check();
}

void Motors_forward(void) {
    // Turn the motors on forward
    RIGHT_FORWARD_SPEED = FAST;
    LEFT_FORWARD_SPEED = FAST;
}

void Motors_reverse(void) {
    // Turn the motors on reverse
    RIGHT_REVERSE_SPEED = FAST;
    LEFT_REVERSE_SPEED = FAST;
}

void Motors_cw(void) {
    RIGHT_FORWARD_SPEED = FAST;
    LEFT_REVERSE_SPEED = FAST;
}

void Motors_ccw(void) {
    RIGHT_REVERSE_SPEED = FAST;
    LEFT_FORWARD_SPEED = FAST;
}

void Motors_stop(void) {
    // Stop motors, forward or reverse
    RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Right Forward PWM OFF
    RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM OFF
    LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.3 Left Forward PWM OFF
    LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.4 Left Reverse PWM OFF
}

void Motors_check(void) {
    // Check to see if a wheel is moving forward and reverse at the same time
    char is_error = FALSE;
    if (RIGHT_FORWARD_SPEED && RIGHT_REVERSE_SPEED) is_error = TRUE;
    if (LEFT_FORWARD_SPEED && LEFT_REVERSE_SPEED) is_error = TRUE;

    if (is_error) {
        error_state(); // Call for an error
    }
}
