
#define F_CPU 16000000UL
#include <avr/io.h>

int main(void)
{
	// Set PD6 (OC0A pin, Arduino pin 6) as output
	
	DDRD |= (1 << DDD6);

	// Fast PWM mode (WGM00=1, WGM01=1)
	
	TCCR0A |= (1 << WGM00);
	TCCR0A |=(1 << WGM01);
	
	//Non-inverting on OC0A (COM0A1=1)
	
	TCCR0A |=(1 << COM0A1);

	// Prescaler = 64 (gives approximately 976 Hz PWM frequency at 16 MHz clock)
	TCCR0B |= (1 << CS01) | (1 << CS00);

	// Set duty cycle = 40% of 255(ie 102 as OCR0A)
	OCR0A = 102;

	while (1)
	{
		// Nothing here, PWM runs in hardware
	}
}