//------------------------------------------------------------------------------
//
//  Description: This file contains the functions related to
//  initializing the global variables to their default values
//  Samantha Pilgreen
//  Sept 2023
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include "Headers/functions.h"
#include "Headers/macros.h"
#include "Headers/globals.h"

extern char display_line[4][11];
volatile unsigned char update_display;
extern char *display[4];

// Timer Globals
unsigned char Time_Sequence_Changed;
int cycle_time;
int delay_start;

// Switch Globals
volatile char sw1_pressed;
volatile char sw2_pressed;


// Path Globals
char shape_state;
char next_shape;
char run_state;
int right_motor_count;
int left_motor_count;
int segment_time;
int action_stage;
int action_cycles;

// Interrupt Globals
volatile unsigned int Time_Sequence;
volatile unsigned int dc_count;
volatile unsigned int time_count;
volatile unsigned int time_count_B1CCR1;
volatile char timer_complete;
volatile char one_time;
unsigned int debounce_sw1_ct;
unsigned int debounce_sw2_ct;

// ADC Globals
unsigned int ADC_Channel;
volatile unsigned int ADC_L_Detect;
volatile unsigned int ADC_R_Detect;
volatile unsigned int ADC_Thumb;
unsigned int Thumb_counter;
volatile char adc_detected;
volatile char thumb_detected;

// DAC Globals
volatile char DAC_data_changing;

void Init_Conditions(void){
//------------------------------------------------------------------------------
    //Initialize the display line strings to be empty
    int i;
    for(i=0;i<11;i++){
    display_line[0][i] = RESET_STATE;
    display_line[1][i] = RESET_STATE;
    display_line[2][i] = RESET_STATE;
    display_line[3][i] = RESET_STATE;
    }
    display_line[0][10] = 0;
    display_line[1][10] = 0;
    display_line[2][10] = 0;
    display_line[3][10] = 0;

    display[0] = &display_line[0][0];
    display[1] = &display_line[1][0];
    display[2] = &display_line[2][0];
    display[3] = &display_line[3][0];
    update_display = FALSE;

    // Initialize Timer Variables
    Time_Sequence_Changed = FALSE;
    cycle_time = RESET_STATE;
    delay_start = RESET_STATE;

    // Initialize Timer Interrupt Variables
    Time_Sequence = RESET_STATE;
    dc_count = RESET_STATE;
    time_count = RESET_STATE;
    time_count_B1CCR1 = RESET_STATE;
    timer_complete = FALSE;
    one_time = FALSE;
    debounce_sw1_ct = RESET_STATE;
    debounce_sw2_ct = RESET_STATE;

    // Initialize Switch Variables
    sw1_pressed = FALSE;
    sw2_pressed = FALSE;

    // Initialize Path Variables
    shape_state = NONE;
//    next_shape = CIRCLE;
    run_state = START;
    right_motor_count = RESET_STATE;
    left_motor_count = RESET_STATE;
    segment_time = RESET_STATE;
    action_stage = RESET_STATE;
    action_cycles = RESET_STATE;

    // Initialize ADC Variables
    ADC_Channel = RESET_STATE;
    ADC_L_Detect = RESET_STATE;
    ADC_R_Detect = RESET_STATE;
    ADC_Thumb = RESET_STATE;
    Thumb_counter = RESET_STATE;
    adc_detected = FALSE;
    thumb_detected = FALSE;

    // Initialize DAC Variables
    DAC_data_changing = FALSE;


    // Interrupts are disabled by default, enable them.
    enable_interrupts();
//------------------------------------------------------------------------------
}


