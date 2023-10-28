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

// ADC Globals
unsigned int ADC_Channel;
volatile unsigned int ADC_L_Detect;
volatile unsigned int ADC_R_Detect;
volatile unsigned int ADC_Thumb;
unsigned int Thumb_counter;
volatile char adc_detected;
volatile char thumb_detected;



#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
    switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
    case ADCIV_NONE:
        break;
    case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
    // before its previous conversion result was read.
        break;
    case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
        break;
    case ADCIV_ADCHIIFG: // Window comparator interrupt flags
        break;
    case ADCIV_ADCLOIFG: // Window comparator interrupt flag
        break;
    case ADCIV_ADCINIFG: // Window comparator interrupt flag
        break;
    case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
        ADCCTL0 &= ~ADCENC; // Disable ENC bit.
        switch (ADC_Channel++){
        case 0x00: // Channel A2 Interrupt, Left IR Sensor
            ADC_L_Detect = ADCMEM0; // Move result into Global Values
            ADC_L_Detect = ADC_L_Detect >> 2; // Divide the result by 4
            ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
            ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
            ADCCTL0 |= ADCSC;  // Start Next Sample
            break;
        case 0x01: // Channel A3 Interrupt, Right IR Sensor
            ADC_R_Detect = ADCMEM0; // Move result into Global Values
            ADC_R_Detect = ADC_R_Detect >> 2; // Divide the result by 4
            adc_detected = TRUE;
            ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A2
//            P1OUT ^= RED_LED;
            switch (Thumb_counter++) {
            case THUMB_COUNT:
                // Go into thumbwheel test this time
                Thumb_counter = RESET_STATE;
                ADCMCTL0 |= ADCINCH_5; // Enable Next channel A5
                ADCCTL0 |= ADCSC;  // Start Next Sample

                break;
            default:
                // No thumbwheel, just end
                ADCMCTL0 |= ADCINCH_2; // Enable Next [First] channel 2
                TB1CCTL1 |= CCIE; // TB1 CCR1 enable interrupt
                ADC_Channel = RESET_STATE;  // Reset to Original
            }



            break;
        case 0x02: // Channel A5 Interrupt, Thumbwheel
            ADC_Thumb = ADCMEM0; // Move result into Global Values
            ADC_Thumb = ADC_Thumb >> 2; // Divide the result by 4
            thumb_detected = TRUE;
            ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A5
            ADCMCTL0 |= ADCINCH_2; // Enable Next [First] channel 2
            ADC_Channel = RESET_STATE;  // Reset to Original
//            P6OUT ^= GRN_LED;  // Flip Value of LED for testing
            TB1CCTL1 |= CCIE; // TB1 CCR1 enable interrupt
            break;
        default:
            break;
        }
        ADCCTL0 |= ADCENC;  // Enable Conversions
        break;
    default:
        break;
    }

}




