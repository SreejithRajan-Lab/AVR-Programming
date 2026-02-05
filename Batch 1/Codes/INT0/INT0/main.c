/*
 * INT0.c
 *
 * Created: 03-10-2025 21:02:04
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect)   // interrupt service routine for INT0
{
	
	PORTB^=(1<<PORTB5); // toggling PB5
	_delay_ms(10);
}


int main(void)
{
 DDRD&=~(1<<DDD2); //Making PD2 as input.
 DDRB|=(1<<DDB5); // making PB5 as output
 PORTD|=(1<<PORTD2);  // Enable internal pull up to make pd2 normally high
 
 EIMSK|=(1<<INT0);// enable int0 at EIMSK register
 EICRA|=(1<<ISC01);// enable falling edge detection in EICRA register
 sei();     // enabling global interrupt at SREG
    while (1) 
    {
	
    }
}

