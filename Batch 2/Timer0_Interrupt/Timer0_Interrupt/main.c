/*
 * Timer0_Interrupt.c
 *
 * Created: 04-12-2025 20:43:55
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t count=0;
ISR(TIMER0_OVF_vect)  // interrupt service routine 
{
	if(count>977)
	{
		PORTB^=(1<<PB5);
		count=0;
	}
	else
	{
		count++;
	}
	
}
int main(void)
{
DDRB|=(1<<DDB5);
 sei();
 TCNT0=0;
 TCCR0A&=~(1<<WGM00)|(1<<WGM01); // normal mode
 TCCR0B |= (1 << CS01) | (1 << CS00); // prescalar 64
 TCCR0B &= ~(1 << CS02);
 TIMSK0|=(1<<TOIE0); // Enabling timer 0 overflow interrupt
    while (1) 
    {
    }
}

