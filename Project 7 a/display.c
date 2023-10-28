//------------------------------------------------------------------------------
//
//  Description: This file contains the functions related to changing the values of the LCD Display
//
//  Samantha Pilgreen
//  Sept 2023
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  <string.h>
#include  "Headers/functions.h"
#include  "Headers/macros.h"


// Global Variables
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern char display_line[4][11];
volatile char adc_char[5];

void Display_Process(void){
  // update_display is a variable updated in LCD.obj that determines whether or not the LCD is ready to update the screen
  // If the LCD is ready to update, perform the update when given the indication that the text has changed, through
  // the display_changed variable.
  if(update_display){
    update_display = FALSE;
    if(display_changed){
      display_changed = FALSE;
      Display_Update(0,0,0,0);
    }
  }
}

void display_update_line1(char display_1[11]) {
    strcpy(display_line[0], display_1);
    display_changed = TRUE;
}


void adc_line(char line, char location){
    // ADC Line insert
    // Take the HEX to BCD value in the array adc_char and place it
    // in the desired location on the desired line of the display.
    // char line => Specifies the line 1 thru 4
    // char location => Is the location 0 thru 9
    int i;
    unsigned int real_line;
    real_line = line - 1;
    for(i=1; i < 4; i++) {
        display_line[real_line][i+location-1] = adc_char[i];
    }
    display_changed = TRUE;
}

