//------------------------------------------------------------------------------
//  Description: This file contains the functions related to Digital to Analog
//  Conversion to the wheel power system
//
//  Samantha Pilgreen
//  Sept 2023
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "Headers/functions.h"
#include  "Headers/macros.h"
#include  "Headers/globals.h"

volatile unsigned int DAC_data;
volatile unsigned int new_DAC_data;
volatile char DAC_data_changing;

void Init_REF(void){
    // Configure reference module
    PMMCTL0_H = PMMPW_H; // Unlock the PMM registers
    PMMCTL2 = INTREFEN; // Enable internal reference
    PMMCTL2 |= REFVSEL_2; // Select 2.5V reference
    while(!(PMMCTL2 & REFGENRDY)); // Poll till internal reference settles
}

void Init_DAC(void){
    DAC_data = 4000; // Value between 0x000 and 0x0FFF
    SAC3DAT = DAC_data; // Initial DAC data
    // Set up Interrupt for DAC Decrement
    new_DAC_data = 2000;
    DAC_data_changing = TRUE;
    TB0CTL |= TBIE; // Enable Overflow Interrupt

    SAC3DAC = DACSREF_1; // Select int Vref as DAC reference
    SAC3DAC |= DACLSEL_0; // DAC latch loads when DACDAT written
    // SAC3DAC |= DACIE; // generate an interrupt
    SAC3DAC |= DACEN; // Enable DAC
    SAC3OA = NMUXEN; // SAC Negative input MUX controL
    SAC3OA |= PMUXEN; // SAC Positive input MUX control
    SAC3OA |= PSEL_1; // 12-bit reference DAC source selected
    SAC3OA |= NSEL_1; // Select negative pin input
    SAC3OA |= OAPM; // Select low speed and low power mode
    SAC3PGA = MSEL_1; // Set OA as buffer mode
    SAC3OA |= SACEN; // Enable SAC
    SAC3OA |= OAEN; // Enable OA
}

void Update_DAC(unsigned int new_val){
    if (DAC_data_changing) {
        // Shouldn't be calling this, run error
        error_state();
        return;
    }

    if (new_val >= DAC_data) {
        // Safe to instantly change DAC_data
        DAC_data = new_val;
        SAC3DAT = DAC_data; // Set DAC data
        return;
    }
    // New Value is less, need to use overflow timer to decrement
    new_DAC_data = new_val;
    DAC_data_changing = TRUE;
    TB0CTL |= TBIE; // Enable Overflow Interrupt
}
