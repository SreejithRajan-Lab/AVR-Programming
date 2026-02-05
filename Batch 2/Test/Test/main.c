#include <avr/io.h>

int main(void)
{

	// 1. Set OC0B (PD5) as output
	DDRD |= (1 << PD5) ;
	DDRB |= (1<<PB5);
  // PD5 = OC0B

	// 2. Set Phase Correct PWM mode (WGM00 = 1, WGM01 = 0)
	// WGM02 = 0 by default in TCCR0B
	TCCR0A |= (1 << WGM00);
	TCCR0A &= ~(1 << WGM01);

	// 3. Non-inverting mode on OC0B (COM0B1 = 1, COM0B0 = 0)
	TCCR0A |= (1 << COM0B1);
	TCCR0A &= ~(1 << COM0B0);

	// 4. Set prescaler = 64 ? CS01 = 1, CS00 = 1
	TCCR0B |= (1 << CS01) | (1 << CS00);
	TCCR0B &= ~(1 << CS02);

	// 5. Set duty cycle (0–255)
	OCR0B = 255;   // 50% duty
	PORTB|=(1<<PB5);
	while(1)
	{
	
		// PWM hardware handles everything
	}
}
