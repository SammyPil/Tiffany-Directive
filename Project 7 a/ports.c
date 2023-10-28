/*
 * ports.c
 *
 *  Created on: Sep 11, 2023
 *      Author: kptum
 */
#include  "msp430.h"
#include  "Headers/ports.h"
#include  "Headers/functions.h"


void Init_Ports(void) {
    // Initialize all ports to default values
    Init_Port1();
    Init_Port2();
    Init_Port3();
    Init_Port4();
    Init_Port5();
    Init_Port6();
}

void Init_Port1(void) {
    // Initialize all pins of port 1 to default values
    P1OUT = 0x00; // P1 set Low
    P1DIR = 0x00; // Set P1 direction to input

    // P1 Pin 0 (GPIO OUT)
    P1SEL0 &= ~RED_LED;  // RED_LED GPIO operation
    P1SEL1 &= ~RED_LED;  // RED_LED GPIO operation
    P1OUT &= ~RED_LED;  // Initial Value = Low / Off
    P1DIR |= RED_LED;  // Direction = output

    // P1 Pin 1
    P1SELC |= V_A1_SEEED; // ADC input for A1_SEEED

    // P1 Pin 2
    P1SELC |= V_DETECT_L; // ADC input for V_DETECT_L

    // P1 Pin 3
    P1SELC |= V_DETECT_R; // ADC input for V_DETECT_R

    // P1 Pin 4
    P1SELC |= V_A4_SEEED; // ADC input for V_A4_SEEED

    // P1 Pin 5
    P1SELC |= V_THUMB; // ADC input for V_THUMB

    // P1 Pin 6
    P1SEL0 |= UCA0RXD;  // UCA0RXD operation
    P1SEL1 &= ~UCA0RXD;  // UCA0RXD operation

    // P1 Pin 7
    P1SEL0 |= UCA0TXD;  // UCA0TXD operation
    P1SEL1 &= ~UCA0TXD;  // UCA0TXD operation

}

void Init_Port2(void) {
    // Initialize all pins of port 2 to default values
    P2OUT = 0x00; // P2 set Low
    P2DIR = 0x00; // Set P2 direction to input

    // P2 Pin 0
    P2SEL0 &= ~SLOW_CLK; // SLOW_CLK GPIO operation
    P2SEL1 &= ~SLOW_CLK; // SLOW_CLK GPIO operation
    P2OUT &= ~SLOW_CLK; // Initial Value = Low / Off
    P2DIR |= SLOW_CLK; // Direction = output

    // P2 Pin 1
    P2SEL0 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
    P2SEL1 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
    P2OUT &= ~CHECK_BAT; // Initial Value = Low / Off
    P2DIR |= CHECK_BAT; // Direction = output

    // P2 Pin 2
    P2SEL0 &= ~IR_LED; // P2_2 GPIO operation
    P2SEL1 &= ~IR_LED; // P2_2 GPIO operation
    P2OUT |= IR_LED; // Initial Value = High / On
    P2DIR |= IR_LED; // Direction = output

    // P2 Pin 3
    P2SEL0 &= ~SW2; // SW2 set as I/0
    P2SEL1 &= ~SW2; // SW2 set as I/0
    P2DIR &= ~SW2; // SW2 Direction = input
    P2PUD |= SW2; // Configure pull-up resistor SW2
    P2REN |= SW2; // Enable pull-up resistor SW2
    P2IES |= SW2; // SW2 Hi/Lo edge interrupt
    P2IFG &= ~SW2; // IFG SW2 cleared
    P2IE |= SW2; // SW2 interrupt Enabled

    // P2 Pin 4
    P2SEL0 &= ~IOT_RUN_RED; // IOT_RUN_CPU GPIO operation
    P2SEL1 &= ~IOT_RUN_RED; // IOT_RUN_CPU GPIO operation
    P2OUT &= ~IOT_RUN_RED; // Initial Value = Low / Off
    P2DIR |= IOT_RUN_RED; // Direction = output

    // P2 Pin 5
    P2SEL0 &= ~DAC_ENB; // DAC_ENB GPIO operation
    P2SEL1 &= ~DAC_ENB; // DAC_ENB GPIO operation
    P2OUT |= DAC_ENB; // Initial Value = High
    P2DIR |= DAC_ENB; // Direction = output

    // P2 Pin 6
    P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
    P2SEL1 |= LFXOUT; // LFXOUT Clock operation

    // P2 Pin 7
    P2SEL0 &= ~LFXIN; // LFXIN Clock operation
    P2SEL1 |= LFXIN; // LFXIN Clock operation
}

void Init_Port3(void) {
    // Initialize all pins of port 3 to default values
    P3OUT = 0x00; // P3 set Low
    P3DIR = 0x00; // Set P3 direction to input

    // P3 Pin 0 (Test Probe, VSS???)
    P3SEL0 &= ~TEST_PROBE; // TEST_PROBE operation
    P3SEL1 |= TEST_PROBE; // TEST_PROBE operation
    // No initial value???)
    P3DIR &= ~TEST_PROBE;  // TEST_PROBE operation

    //P3 Pin 1
    P3SEL0 |= OA2O; // OA2O operation
    P3SEL1 |= OA2O; // OA2O operation

    //P3 Pin 2
    P3SEL0 |= OA2N; // OA2N operation
    P3SEL1 |= OA2N; // OA2N operation

    //P3 Pin 3
    P3SEL0 |= OA2P; // OA2P operation
    P3SEL1 |= OA2P; // OA2P operation

    //P3 Pin 4
    P3SEL0 &= ~SMCLK_OUT; // SMCLK_OUT GPIO operation
    P3SEL1 &= ~SMCLK_OUT; // SMCLK_OUT GPIO operation
    P3DIR |= SMCLK_OUT;  // Direction = output

    //P3 Pin 5 (GPIO IN FOR NOW)
    P3SEL0 &= ~DAC_CNTL; // DAC_CNTL GPIO operation
    P3SEL1 &= ~DAC_CNTL; // DAC_CNTL GPIO operation
    P3DIR &= ~DAC_CNTL;  // Direction = input

    //P3 Pin 6 (GPIO IN FOR NOW)
    P3SEL0 &= ~IOT_LINK_GRN; // IOT_LINK_GRN GPIO operation
    P3SEL1 &= ~IOT_LINK_GRN; // IOT_LINK_GRN GPIO operation
    P3DIR &= ~IOT_LINK_GRN;  // Direction = input

    //P3 Pin 7 (GPIO IN FOR NOW)
    P3SEL0 &= ~IOT_EN; // IOT_EN GPIO operation
    P3SEL1 &= ~IOT_EN; // IOT_EN GPIO operation
    P3DIR &= ~IOT_EN;  // Direction = input

}

void Init_Port4(void) {
    // Initialize all pins of port 4 to default values
    P4OUT = 0x00; // P4 set Low
    P4DIR = 0x00; // Set P4 direction to input

    // P4 Pin 0
    P4SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
    P4SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
    P4OUT &= ~RESET_LCD; // Initial Value = Low / Off
    P4DIR |= RESET_LCD; // Direction = output

    // P4 Pin 1
    P4SEL0 &= ~SW1; // SW1 set as I/0
    P4SEL1 &= ~SW1; // SW1 set as I/0
    P4DIR &= ~SW1; // SW1 Direction = input
    P4PUD |= SW1; // Configure pull-up resistor SW1
    P4REN |= SW1; // Enable pull-up resistor SW1
    P4IES |= SW1; // SW1 Hi/Lo edge interrupt
    P4IFG &= ~SW1; // IFG SW1 cleared
    P4IE |= SW1; // SW1 interrupt Enabled

    // P4 Pin 2
    P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
    P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation

    // P4 Pin 3
    P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
    P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation

    // P4 Pin 4
    P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
    P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
    P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]
    P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output

    // P4 Pin 5
    P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
    P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation

    // P4 Pin 6
    P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
    P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation

    // P4 Pin 7
    P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
    P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation
}

void Init_Port5(void) {
    // Initialize all pins of port 5 to default values
    P5OUT = 0x00; // P5 set Low
    P5DIR = 0x00; // Set P5 direction to input

    // P5 Pin 0
    P5SELC |= V_BAT; // ADC input for V_BAT

    // P5 Pin 1
    P5SELC |= V_5_0; // ADC input for V_BAT

    // P5 Pin 2
    P5SELC |= V_DAC; // ADC input for V_DAC

    // P5 Pin 3
    P5SELC |= V_3_3; // ADC input for V_3_3

    // P5 Pin 4 (GPIO IN FOR NOW)
    P5SEL0 &= IOT_BOOT;  // IOT_BOOT GPIO operation
    P5SEL1 &= ~IOT_BOOT;  // IOT_BOOT GPIO operation
    P5DIR &= ~IOT_BOOT;  // Direction = input


}

void Init_Port6(void) {
    // Initialize all pins of port 6 to default values
    P6OUT = 0x00; // P6 set Low
    P6DIR = 0x00; // Set P6 direction to input

    // P6 Pin 0 (GPIO OUT FOR NOW)
    P6SEL1 &= ~LCD_BACKLITE;  // LCD_BACKLITE PWM operation
    P6SEL0 |= LCD_BACKLITE;  // LCD_BACKLITE PWM operation
    P6DIR |= LCD_BACKLITE;  // Direction = output

    // P6 Pin 1 (GPIO OUT FOR NOW)
    P6SEL1 &= ~R_FORWARD;  // R_FORWARD PWM operation
    P6SEL0 |= R_FORWARD;  // R_FORWARD PWM operation
    P6DIR |= R_FORWARD;  // Direction = output

    // P6 Pin 2 (GPIO OUT FOR NOW)
    P6SEL1 &= ~R_REVERSE;  // R_REVERSE PWM operation
    P6SEL0 |= R_REVERSE;  // R_REVERSE PWM operation
    P6DIR |= R_REVERSE;  // Direction = output

    // P6 Pin 3 (GPIO OUT FOR NOW)
    P6SEL1 &= ~L_FORWARD;  // L_FORWARD PWM operation
    P6SEL0 |= L_FORWARD;  // L_FORWARD PWM operation
    P6DIR |= L_FORWARD;  // Direction = output

    // P6 Pin 4 (GPIO OUT FOR NOW)
    P6SEL1 &= ~L_REVERSE;  // L_REVERSE PWM operation
    P6SEL0 |= L_REVERSE;  // L_REVERSE PWM operation
    P6DIR |= L_REVERSE;  // Direction = output

    // P6 Pin 5 (GPIO IN FOR NOW)
    P6SEL0 &= ~P6_5;  // P6_5 GPIO operation
    P6SEL1 &= ~P6_5;  // P6_5 GPIO operation
    P6DIR &= ~P6_5;  // Direction = input

    // P6 Pin 6 (GPIO OUT NOW)
    P6SEL0 &= ~GRN_LED;  // GRN_LED GPIO operation
    P6SEL1 &= ~GRN_LED;  // GRN_LED GPIO operation
    P6OUT &= ~GRN_LED;  // Initial Value = Low / Off
    P6DIR |= GRN_LED;  // Direction = output
}


