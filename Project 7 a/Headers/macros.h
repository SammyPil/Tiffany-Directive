//------------------------------------------------------------------------------
//
//  Description: This file contains the define macros used in the other files
//
//  Samantha Pilgreen
//  Sept 2023
//------------------------------------------------------------------------------

#ifndef MACROS_H_
#define MACROS_H_

#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1
#define TEST_PROBE           (0x01) // 0 TEST PROBE
#define TRUE                 (0x01) //
#define FALSE                (0x00) //

// Clock Macros
#define MCLK_FREQ_MHZ           (8) // MCLK = 8MHz
#define CLEAR_REGISTER     (0X0000)

// Motor Macros
#define MOTOR_PERIOD           (20)
// Account for the drift to the right by making the left motor shut off sooner
#define STRAIGHT_LEFT_PERIOD   (15)

#define RIGHT_TURN_PERIOD      (18)
#define LEFT_TURN_PERIOD       (12)

#define MOTOR_PAUSE_TIME      (100)
#define MOTOR_RUN_TIME        (350)

// Path Macros
#define NONE                  ('N')
#define START_PAUSE           ('a')
#define FORWARD_1             ('b')
#define BIG_PAUSE             ('d')
#define CCW_TURN              ('e')
//#define PAUSE_1               ('c')
//#define REVERSE               ('d')
//#define PAUSE_2               ('e')
//#define FORWARD_2             ('f')
//#define PAUSE_3               ('g')
//#define TURN_CW               ('h')
//#define PAUSE_4               ('i')
//#define TURN_CCW              ('j')
//#define PAUSE_5               ('k')

#define LINE_FOUND_1            ('y')
#define LINE_FOUND_2            ('z')

#define WAIT                  ('W')
#define START                 ('S')
#define RUN                   ('R')
#define END                   ('E')

// Timers
#define RESET_REGISTER     (0x0000)
#define TB0CCR0_INTERVAL    (50000) // 8,000,000/2/8/[1/100msec]
#define TB0CCR1_INTERVAL    (50000) // 8,000,000/2/8/[1/100msec]
#define TB0CCR2_INTERVAL    (50000) // 8,000,000/2/8/[1/100msec]
#define TB1CCR0_INTERVAL    (50000) // 8,000,000/4/8/[1/200msec]
#define TB1CCR1_INTERVAL     (2500) // 8,000,000/4/8/[1/10msec]

// Interrupts
#define FIFTY_MS_COUNT          (4) // 50ms * 4 = 200 ms or 0.2 sec
#define DEBOUNCE_COUNT         (10) // 100 ms * 10 = 1000 ms or 1 sec
#define ADC_COUNT               (2) // 25 ms * 2 = 50 ms or 0.05 sec
#define THUMB_COUNT            (50) // 50 * 10 ms = 500 ms or 0.5 sec
#define WAIT_1_SEC             (10) // 100 ms * 10 = 1000 ms or 1 sec
#define WAIT_2_SEC             (20) // 100 ms * 20 = 2000 ms or 2 sec
#define WAIT_3_SEC             (30) // 100 ms * 30 = 3000 ms or 3 sec
#define WAIT_5_SEC             (50) // 100 ms * 50 = 5000 ms or 5 sec
#define TIMERB0_CCR0_VECTOR        (TIMER0_B0_VECTOR)
#define TIMERB0_CCR1_2_OVFL_VECTOR (TIMER0_B1_VECTOR)
#define TIMERB1_CCR0_VECTOR        (TIMER1_B0_VECTOR)
#define TIMERB1_CCR1_2_OVFL_VECTOR (TIMER1_B1_VECTOR)



// PWM
#define PWM_PERIOD           (TB3CCR0)
#define LCD_BACKLITE_DIMMING (TB3CCR1)
#define RIGHT_FORWARD_SPEED  (TB3CCR2)
#define RIGHT_REVERSE_SPEED  (TB3CCR3)
#define LEFT_FORWARD_SPEED   (TB3CCR4)
#define LEFT_REVERSE_SPEED   (TB3CCR5)

#define WHEEL_PERIOD       (50005)
#define WHEEL_OFF              (0)
#define SLOW               (15000)
#define FAST               (50000)
#define PERCENT_100        (50000)
#define PERCENT_80         (30000)

// DAC




#endif /* MACROS_H_ */
