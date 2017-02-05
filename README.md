thermostat
==========

Just a basic thermostat for one of the bedrooms.  It is based on a cheap wireless outlet, and using an ATTiny13, the thermostat can control the remote to turn the head on and off.


## Wiring
### Thermostat

B wire:  	connect to ground
W/Aux wire:	pull up to +V with a 10k resistor

### Remote
Wiring header is attached as in the picture, but here's a text summary:
Black		ground
Brown		switch common
Red			on switch
Orange		off switch


## Operation
When the thermostat detects low temperature, it activates a relay which shorts the B & W/Aux pins.  The ATTiny13 detects the short and toggles the MOSFET controlling the on switch 3 times for a duration of 1 second each.  When the thermostat shuts the heat off, the W/Aux pin is pulled back high.  The ATTiny13 detects the open circuit and toggles the MOSFET controlling the off switch 3 times for a duration of 1 second each.


