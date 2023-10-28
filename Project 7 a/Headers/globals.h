//------------------------------------------------------------------------------
//
//  Description: This file contains definitions of certain global variables shared between files
//
//  Samantha Pilgreen
//  Sept 2023
//------------------------------------------------------------------------------

#ifndef HEADERS_GLOBALS_H_
#define HEADERS_GLOBALS_H_

// Motor Globals
extern volatile unsigned char forward_start;

// Timer Globals
extern unsigned int Old_Time_Sequence;
extern unsigned char Time_Sequence_Changed;
extern int cycle_time;
extern int delay_start;

// Display Globals
extern volatile unsigned char update_display;
extern volatile char adc_char[5];

// Switch Globals
extern volatile char sw1_pressed;
extern volatile char sw2_pressed;

// Timer Interrupt Globals
extern volatile unsigned int Time_Sequence;
extern volatile unsigned int dc_count;  // Decasecond counter, counts once every 100 ms, or 0.1 sec.
extern volatile unsigned int time_count; // Timer B0CCR0 Config. Ex: 20 -> 20*100 ms = 2 sec.
extern volatile unsigned int time_count_B1CCR1; // Timer B1CCR1 Config. Ex: 10 -> 10*50 ms = 500 ms, 0.5 sec
extern volatile char timer_complete; // Timer B0CCR0 Complete
extern unsigned int debounce_sw1_ct;
extern unsigned int debounce_sw2_ct;
extern volatile char one_time;

// ADC Globals
extern unsigned int ADC_Channel;
extern volatile unsigned int ADC_L_Detect;
extern volatile unsigned int ADC_R_Detect;
extern volatile unsigned int ADC_Thumb;
extern unsigned int Thumb_counter;
extern volatile char adc_detected;
extern volatile char thumb_detected;

// DAC Globals
extern volatile unsigned int DAC_data;
extern volatile unsigned int new_DAC_data;
extern volatile char DAC_data_changing;

// Path Globals
extern char shape_state;
extern char next_shape;
extern char run_state;
extern int right_motor_count;
extern int left_motor_count;
extern int segment_time;
extern int action_stage;
extern int action_cycles;

#endif /* HEADERS_GLOBALS_H_ */
