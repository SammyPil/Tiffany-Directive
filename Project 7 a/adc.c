//------------------------------------------------------------------------------
//  Description: This file contains the functions related to Analog to Digital
//  Conversion from the Thumbwheel Potentiometer and the IR Sensors.
//
//  Samantha Pilgreen
//  Sept 2023
//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "Headers/functions.h"
#include  "Headers/macros.h"

volatile unsigned int ADC_L_Detect;
volatile unsigned int ADC_R_Detect;
volatile unsigned int ADC_Thumb;
volatile char adc_detected;
volatile char thumb_detected;
volatile char adc_char[5];


// Path Globals
char shape_state;



void Init_ADC(void){
    //------------------------------------------------------------------------------
    // V_DETECT_L (0x04) // Pin 2 A2
    // V_DETECT_R (0x08) // Pin 3 A3
    // V_THUMB (0x20) // Pin 5 A5
    //------------------------------------------------------------------------------
    // ADCCTL0 Register
    ADCCTL0 = 0; // Reset
    ADCCTL0 |= ADCSHT_2; // 16 ADC clocks
    ADCCTL0 |= ADCMSC; // MSC
    ADCCTL0 |= ADCON; // ADC ON

    // ADCCTL1 Register
    ADCCTL1 = 0; // Reset
    ADCCTL1 |= ADCSHS_0; // 00b = ADCSC bit
    ADCCTL1 |= ADCSHP; // ADC sample-and-hold SAMPCON signal from sampling timer.
    ADCCTL1 &= ~ADCISSH; // ADC invert signal sample-and-hold.
    ADCCTL1 |= ADCDIV_0; // ADC clock divider - 000b = Divide by 1
    ADCCTL1 |= ADCSSEL_0; // ADC clock MODCLK
    ADCCTL1 |= ADCCONSEQ_0; // ADC conversion sequence 00b = Single-channel single-conversion
    // ADCCTL1 & ADCBUSY identifies a conversion is in process

    // ADCCTL2 Register
    ADCCTL2 = 0; // Reset
    ADCCTL2 |= ADCPDIV0; // ADC pre-divider 00b = Pre-divide by 1
    ADCCTL2 |= ADCRES_2; // ADC resolution 10b = 12 bit (14 clock cycle conversion time)
    ADCCTL2 &= ~ADCDF; // ADC data read-back format 0b = Binary unsigned.
    ADCCTL2 &= ~ADCSR; // ADC sampling rate 0b = ADC buffer supports up to 200 ksps
    // ADCMCTL0 Register
    ADCMCTL0 |= ADCSREF_0; // VREF - 000b = {VR+ = AVCC and VR– = AVSS }
    ADCMCTL0 |= ADCINCH_2; // V_DETECT_L Pin 1 A2

    ADCIE |= ADCIE0; // Enable ADC conv complete interrupt
    ADCCTL0 |= ADCENC; // ADC enable conversion.
    ADCCTL0 |= ADCSC; // ADC start conversion.
}

void HEXtoBCD(int hex_value){
    // Hex to BCD Conversion
    // Convert a Hex number to a BCD for display on an LCD or monitor
    int value = 0;
    unsigned int i;
    for(i=0; i < 4; i++) {
        adc_char[i] = '0';
    }
    while (hex_value > 999){
        hex_value = hex_value - 1000;
        value = value + 1;
        adc_char[0] = 0x30 + value;
    }
    value = 0;
    while (hex_value > 99){
        hex_value = hex_value - 100;
        value = value + 1;
        adc_char[1] = 0x30 + value;
    }
    value = 0;
    while (hex_value > 9){
        hex_value = hex_value - 10;
        value = value + 1;
        adc_char[2] = 0x30 + value;
    }
    adc_char[3] = 0x30 + hex_value;
}

void ADC_Process(void) {
    // Check to see if ADC values have updated, if so, update display
    // Perform certain actions based on sensor values
    if (adc_detected) {
        adc_detected = FALSE; // Reset State
        HEXtoBCD(ADC_L_Detect); // Convert result to String
        adc_line(4, 6); // Place String in Display (Line 4, Position 6)
        HEXtoBCD(ADC_R_Detect); // Convert result to String
        adc_line(4, 1); // Place String in Display (Line 4, Position 0)

        if (shape_state != NONE) {
            if (ADC_L_Detect > 400 && ADC_R_Detect > 400) {
                // Black Line Detected, indicate to Stop
                switch (shape_state) {
                case FORWARD_1:
                    shape_state = LINE_FOUND_1;
                    break;
                case CCW_TURN:
                    shape_state = LINE_FOUND_2;
                    break;
                }

            }
        }
    }

    if (thumb_detected) {
        HEXtoBCD(ADC_Thumb); // Convert result to String
//        adc_line(2, 6); // Place String in Display (Line 2, Position 6)

    }

}
