//------------------------------------------------------------------------------
//
//  Description: This file contains code to setup Interrupts for Ports
//
//  Samantha Pilgreen
//  Oct 2023
//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "Headers/functions.h"
#include  "Headers/globals.h"
#include  "Headers/macros.h"
#include  "Headers/ports.h"

volatile char sw1_pressed;
volatile char sw2_pressed;

unsigned int debounce_sw1_ct;
unsigned int debounce_sw2_ct;

#pragma vector= PORT4_VECTOR
__interrupt void switchP4_interrupt(void){
    // Interrupt for Switch 1
    if (P4IFG & SW1) {
        sw1_pressed = TRUE;  // Allow Switch Process to perform action
        P4IE &= ~SW1; // SW1 interrupt Disabled
        TB0CCTL1 &= ~CCIFG; // CCR1 Clear interrupt flag
        TB0CCTL1 |= CCIE; // CCR1 enable interrupt
        debounce_sw1_ct = RESET_STATE;  // Reset debounce count
        P4IFG &= ~SW1; // IFG SW1 cleared
    }
}


#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void){
    // Interrupt for Switch 2
    if (P2IFG & SW2) {
        sw2_pressed = TRUE;  // Allow Switch Process to perform action
        P2IE &= ~SW2; // SW2 interrupt Disabled
        TB0CCTL2 &= ~CCIFG; // CCR2 Clear interrupt flag
        TB0CCTL2 |= CCIE; // CCR2 enable interrupt
        debounce_sw1_ct = RESET_STATE;  // Reset debounce count
        P2IFG &= ~SW2; // IFG SW2 cleared
    }
}


