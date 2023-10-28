/*
 * led.c
 *
 *  Created on: Sep 11, 2023
 *      Author: kptum
 */
#include "msp430.h"
#include "Headers/ports.h"
#include "Headers/functions.h"

void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns off both LEDs
  P1OUT &= ~RED_LED;
  P6OUT &= ~GRN_LED;
//------------------------------------------------------------------------------
}


