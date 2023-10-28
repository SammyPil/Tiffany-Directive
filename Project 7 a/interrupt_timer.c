//------------------------------------------------------------------------------
//
//  Description: This file contains code to set up Interrupts for Timer B0 & B1
//
//  Samantha Pilgreen
//  Oct 2023
//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "Headers/functions.h"
#include  "Headers/globals.h"
#include  "Headers/macros.h"
#include  "Headers/ports.h"

volatile unsigned int dc_count;
volatile unsigned int time_count;
volatile unsigned int time_count_B1CCR1;
volatile char timer_complete;
unsigned int debounce_sw1_ct;
unsigned int debounce_sw2_ct;

volatile unsigned int DAC_data;
volatile unsigned int new_DAC_data;
volatile char DAC_data_changing;

volatile unsigned char update_display;

#pragma vector = TIMERB0_CCR0_VECTOR // Timer B0 – 0 Capture compare
__interrupt void Timer0_B0_ISR(void){
    //--------------------------------------------------------------------
    // TimerB0 CCR0 Interrupt handler
    //--------------------------------------------------------------------
    // Decasecond Timer
     if(dc_count++ > time_count){
         dc_count = RESET_STATE; // Reset for next count
         timer_complete = TRUE; // Update Global variable
         TB0CCTL0 &= ~CCIFG; // CCR0 Clear interrupt flag
         TB0CCTL0 &= ~CCIE; // CCR0 disable interrupt
     }

     TB0CCR0 += TB0CCR0_INTERVAL; // Add interval Offset to TBCCR0
    //--------------------------------------------------------------------
}

#pragma vector= TIMERB0_CCR1_2_OVFL_VECTOR // // Timer B0 – 1-2, Overflow Capture compare
__interrupt void TIMER0_B1_ISR(void){
    //----------------------------------------------------------------------------
    // TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
    //----------------------------------------------------------------------------
    unsigned int temp;
    switch(__even_in_range(TB0IV,14)){
    case 0: break; // No interrupt
    case 2: // CCR1: SW1 Debounce
        if(debounce_sw1_ct++ >= DEBOUNCE_COUNT) {
            // Enough time has passed (~1sec), return the switch function
            debounce_sw1_ct = RESET_STATE;
            TB0CCTL1 &= ~CCIE; // CCR1 disable interrupt
            P4IFG &= ~SW1; // IFG SW1 cleared
            P4IE |= SW1; // SW1 interrupt Enabled
        }
        TB0CCR1 += TB0CCR1_INTERVAL; // Add Offset to TBCCR1
        break;
    case 4: // CCR2: SW2 Debounce
        if(debounce_sw2_ct++ >= DEBOUNCE_COUNT) {
            // Enough time has passed (~1sec), return the switch function
            debounce_sw2_ct = RESET_STATE;
            TB0CCTL2 &= ~CCIE; // CCR2 disable interrupt
            P2IFG &= ~SW2; // IFG SW2 cleared
            P2IE |= SW2; // SW2 interrupt Enabled
        }
        TB0CCR2 += TB0CCR2_INTERVAL; // Add Offset to TBCCR2
        break;
    case 14: // Overflow: Decrement until reaching desired DAC value
        temp = new_DAC_data;
        if (DAC_data > temp) DAC_data -= 50;
        else {
            // DAC_data is equal to or less then desired amount, set it to be precise
            DAC_data = temp;
            TB0CTL &= ~TBIE; // Disable Overflow Interrupt
            DAC_data_changing = FALSE;
        }
        SAC3DAT = DAC_data; // Set current DAC data
        break;
    default: break;
    }
}

#pragma vector = TIMERB1_CCR0_VECTOR // Timer B1 – 0 Capture compare
__interrupt void Timer1_B0_ISR(void){
    //--------------------------------------------------------------------
    // TimerB0 CCR0 Interrupt handler
    //--------------------------------------------------------------------
    // Allow Display to update
    update_display = TRUE;

    TB1CCR0 += TB1CCR0_INTERVAL; // Add interval Offset to TBCCR0
    //--------------------------------------------------------------------
}

#pragma vector= TIMERB1_CCR1_2_OVFL_VECTOR // // Timer B1 – 1-2, Overflow Capture compare
__interrupt void TIMER1_B1_ISR(void){
    //----------------------------------------------------------------------------
    // TimerB1 1-2, Overflow Interrupt Vector (TBIV) handler
    //----------------------------------------------------------------------------
    switch(__even_in_range(TB1IV,14)){
    case 0: break; // No interrupt
    case 2: // CCR1: ADC Wait Time
        if(time_count_B1CCR1++ >= ADC_COUNT) {
            // Enough time has passed (~0.05 sec), allow ADC sampling
            time_count_B1CCR1 = RESET_STATE;
            TB1CCTL1 &= ~CCIE; // CCR1 disable interrupt
            ADCCTL0 |= ADCSC; // Start next sample
        }
        TB1CCR1 += TB1CCR1_INTERVAL; // Add Offset to TBCCR1
        break;
    case 4: // CCR2
        break;
    case 14: // overflow
        break;
    default: break;
    }
}
