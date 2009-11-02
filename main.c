//
//	main.c
//	Blink an LED on the ATMEGA168 microcontroller to verify operation.
//
//	University of Manitoba Society of Automotive Engineers (UMSAE)
//	Formula 2010
//
//	Michael Jean <michael.jean@shaw.ca>
//

#include <avr/interrupt.h>
#include <avr/io.h>

//
//	Timer 0 interrupt service routine.
//
//	Count to one second, then toggle the LED.
//

ISR(TIMER0_COMPA_vect)
{
	static uint16_t ticks = 0;
	
	if (++ticks > 1000)
	{
		PORTB ^= _BV (PB0);
		ticks = 0;
	}
}

//
//	Configure the GPIO ports.
//
//	Port:Pin	Direction	Function
//	========	=========	========
//	PB0			Output		LED supply pin
//

void
setup_ports (void)
{
	DDRB = _BV (PB0);
}

//
//	Configure the on-board timers.
//
//	Timer	Frequency	Function
//	=====	=========	========
//	0		1 kHz		Toggle LED after one second
//

void
setup_timers (void)
{
	TCCR0A = _BV (WGM01);
	TCCR0B = _BV (CS01) | _BV (CS00);
	TIMSK0 = _BV (OCIE0A);
	OCR0A =	 250;
}

//
//	Main entry point of the microcontroller.
//

int 
main(void)
{
	setup_ports ();
	setup_timers ();
	
	sei ();
	
	for (;;)
		;
	
    return 0;
}
