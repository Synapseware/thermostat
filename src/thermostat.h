#ifndef __THERMOSTAT__H_
#define __THERMOSTAT__H_


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>


#define THERMOSTAT_PIN		PB2
#define HEAT_ON				PB1
#define HEAT_OFF			PB0

#define TOGGLE_COUNT		3
#define TOGGLE_ON_DELAY		400
#define TOGGLE_OFF_DELAY	800


#endif