#include "thermostat.h"



//-----------------------------------------------------------------------------
// initialize hardware
void init(void)
{
	// enable switch sensor on DOOR_PIN
	DDRB	&=	(1<<THERMOSTAT_PIN);		// sensor pin is input
	PORTB	|=	(1<<THERMOSTAT_PIN);		// enable pullup resistor on sensor pin

	// configure remote pins (output, low)
	PORTB	&=	~((1<<HEAT_ON) | (1<<HEAT_OFF));
	DDRB	|=	(1<<HEAT_ON) | (1<<HEAT_OFF);

	// disable the watchdog
	cli();
	MCUSR &= ~(1<<WDRF);
	WDTCR |= (1<<WDCE) | (1<<WDE);
	WDTCR = 0x00;
	sei();
}


//-----------------------------------------------------------------------------
// Returns 1 if the thermostat is on, 0 if it's closed
uint8_t isThermostatOn(void)
{
	// switch is configured as NO.  with pullup enabled, pin is high
	// when heat is off and low when heat is on.
	if ((PINB & (1<<THERMOSTAT_PIN)) == 0)
		return 1;

	return 0;
}


//-----------------------------------------------------------------------------
// Turns the heat on
void turnHeatOn(void)
{
	// failsafe - ensure the other button is off
	PORTB	&=	~(1<<HEAT_OFF);

	for (uint8_t i = 0; i < TOGGLE_COUNT; i++)
	{
		PORTB	|=	(1<<HEAT_ON);
		_delay_ms(TOGGLE_ON_DELAY);
		PORTB	&=	~(1<<HEAT_ON);
		_delay_ms(TOGGLE_OFF_DELAY);
	}
}


//-----------------------------------------------------------------------------
// Turns the heat on
void turnHeatOff(void)
{
	// failsafe - ensure the other button is off
	PORTB	&=	~(1<<HEAT_ON);

	for (uint8_t i = 0; i < TOGGLE_COUNT; i++)
	{
		PORTB	|=	(1<<HEAT_OFF);
		_delay_ms(TOGGLE_ON_DELAY);
		PORTB	&=	~(1<<HEAT_OFF);
		_delay_ms(TOGGLE_OFF_DELAY);
	}
}


//-----------------------------------------------------------------------------
// main
int main(void)
{
	init();

	uint8_t heatIsOn = 0;
	PORTB	&=	~((1<<HEAT_ON) | (1<<HEAT_OFF));

	turnHeatOff();

	while(1)
	{
		if (isThermostatOn())
		{
			if (!heatIsOn)
			{
				turnHeatOn();
				heatIsOn = 1;
			}
		}
		else
		{
			if (heatIsOn)
			{
				turnHeatOff();
				heatIsOn = 0;
			}
		}
	}
}
