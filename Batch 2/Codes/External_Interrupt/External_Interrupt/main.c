/*
 * External_Interrupt.c
 *
 * Created: 06-12-2025 20:19:08
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect)   // interrupt service routine for external interrupt 0
{
	
PORTB|=(1<<PB5);  // toggling LED
_delay_ms(10000);
}

int main(void)
{
 sei();  // Enabling global interrupt 
 DDRD&=~(1<<PD2);
 DDRB|=(1<<DDB5)|(1<<DDB4); // Making port b5 as output
 EIMSK|=(1<<INT0);   // enabling external interrupt 0
 EICRA|=(1<<ISC00)|(1<<ISC01);  // configuring interrupt for rising edge
    while (1) 
    {
		PORTB&=~(1<<PB5);
		PORTB^=(1<<PB4);
		_delay_ms(1000);
    }
}

