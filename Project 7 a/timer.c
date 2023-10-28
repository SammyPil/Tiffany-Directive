//------------------------------------------------------------------------------
//
//  Description: This file contains code to setup Timer B0
//
//  Samantha Pilgreen
//  Oct 2023
//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "Headers/functions.h"
#include  "Headers/globals.h"
#include  "Headers/macros.h"

//--------------------------------------------------------------------
// Timer initialization sets up all timers used (currently Timer B0)
void Init_Timers(void) {
    Init_Timer_B0();
    Init_Timer_B1();
    Init_Timer_B3();
}
// Timer B0 initialization sets up both B0_0, B0_1-B0_2 and overflow
void Init_Timer_B0(void) {
    //--------------------------------------------------------------------
    // Timer B0 initialization sets up both B0_0, B0_1-B0_2 and overflow
    TB0CTL = RESET_REGISTER; // Clear TB0 Control Register
    TB0EX0 = RESET_REGISTER; // Clear TBIDEX Register
    TB0CTL |= TBSSEL__SMCLK; // SMCLK source
    TB0CTL |= MC__CONTINOUS; // Continuous up to 0xFFFF and overflow
    TB0CTL |= ID__2; // Divide clock by 2
    TB0EX0 |= TBIDEX__8; // Divide clock by an additional 8
    TB0CTL |= TBCLR; // Resets TB0R
    // #pragma vector = TIMER0_B0_VECTOR
    // Capture Compare 0
    TB0CCR0 = TB0CCR0_INTERVAL; // CCR0
    TB0CCTL0 &= ~CCIFG; // CCR0 Clear interrupt flag
    TB0CCTL0 &= ~CCIE; // CCR0 disable interrupt
    // Capture Compare 1,2, Overflow
    // #pragma vector = TIMER0_B1_VECTOR
    // Capture compare 1
    TB0CCR1 = TB0CCR1_INTERVAL;// CCR1
    TB0CCTL1 &= ~CCIFG; // CCR1 Clear interrupt flag
    TB0CCTL1 &= ~CCIE; // CCR1 disable interrupt
    // Capture compare 2
    TB0CCR2 = TB0CCR2_INTERVAL;// CCR2
    TB0CCTL2 &= ~CCIFG; // CCR2 Clear interrupt flag
    TB0CCTL2 &= ~CCIE; // CCR2 disable interrupt
    // Overflow
    TB0CTL &= ~TBIFG; // Clear Overflow Interrupt flag
    TB0CTL &= ~TBIE; // Disable Overflow Interrupt
    //--------------------------------------------------------------------
}

// Timer B1 initialization sets up both B1_0, B1_1-B1_2 and overflow
void Init_Timer_B1(void) {
    //--------------------------------------------------------------------
    // Timer B0 initialization sets up both B0_0, B0_1-B0_2 and overflow
    TB1CTL = RESET_REGISTER; // Clear TB0 Control Register
    TB1EX0 = RESET_REGISTER; // Clear TBIDEX Register
    TB1CTL |= TBSSEL__SMCLK; // SMCLK source
    TB1CTL |= MC__CONTINOUS; // Continuous up to 0xFFFF and overflow
    TB1CTL |= ID__4; // Divide clock by 2
    TB1EX0 |= TBIDEX__8; // Divide clock by an additional 8
    TB1CTL |= TBCLR; // Resets TB1R
    // #pragma vector = TIMER1_B0_VECTOR
    // Capture Compare 0
    TB1CCR0 = TB1CCR0_INTERVAL; // CCR0
    TB1CCTL0 &= ~CCIFG; // CCR0 Clear interrupt flag
    TB1CCTL0 |= CCIE; // CCR0 enable interrupt
    // Capture Compare 1,2, Overflow
    // #pragma vector = TIMER1_B1_VECTOR
    // Capture compare 1
    TB1CCR1 = TB1CCR1_INTERVAL;// CCR1L 50 ms
    TB1CCTL1 &= ~CCIFG; // CCR1 Clear interrupt flag
    TB1CCTL1 &= ~CCIE; // CCR1 disable interrupt
    // Capture compare 2
//    TB1CCR2 = TB0CCR2_INTERVAL;// CCR2
    TB1CCTL2 &= ~CCIFG; // CCR2 Clear interrupt flag
    TB1CCTL2 &= ~CCIE; // CCR2 disable interrupt
    // Overflow
    TB1CTL &= ~TBIE; // Disable Overflow Interrupt
    TB1CTL &= ~TBIFG; // Clear Overflow Interrupt flag
    //--------------------------------------------------------------------
}

void Init_Timer_B3(void) {
//------------------------------------------------------------------------------
// SMCLK source, up count mode, PWM Right Side
// TB3.1 P6.0 LCD_BACKLITE
// TB3.2 P6.1 R_FORWARD
// TB3.3 P6.2 R_REVERSE
// TB3.4 P6.3 L_FORWARD
// TB3.5 P6.4 L_REVERSE
//------------------------------------------------------------------------------
    TB3CTL = TBSSEL__SMCLK; // SMCLK
    TB3CTL |= MC__UP; // Up Mode
    TB3CTL |= TBCLR; // Clear TAR

    PWM_PERIOD = WHEEL_PERIOD; // PWM Period [Set to 50005]
    TB3CCTL1 = OUTMOD_7; // CCR1 reset/set
    LCD_BACKLITE_DIMMING = PERCENT_80; // P6.0 Right Forward PWM duty cycle
    TB3CCTL2 = OUTMOD_7; // CCR2 reset/set
    RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Right Forward PWM duty cycle
    TB3CCTL3 = OUTMOD_7; // CCR3 reset/set
    RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM duty cycle
    TB3CCTL4 = OUTMOD_7; // CCR4 reset/set
    LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.3 Left Forward PWM duty cycle
    TB3CCTL5 = OUTMOD_7; // CCR5 reset/set
    LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.4 Left Reverse PWM duty cycle
//------------------------------------------------------------------------------
}
