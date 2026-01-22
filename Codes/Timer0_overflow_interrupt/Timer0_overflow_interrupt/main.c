/*
 * Timer0_overflow_interrupt.c
 *
 * Created: 29-09-2025 20:47:31
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include<stdint.h>
 volatile uint16_t count=0;
ISR(TIMER0_OVF_vect)   // INTERRUPT SERVICE ROUTINE ( TIMER0_OVF_vect = INTERRUPT VECTOR TABLE "ADDRESS" FOR TIMER OVERFLOW INTERRUPT)
{
	count++;
	if(count>=977)
	{
		PORTB^=(1<<PORTB5);
		count=0;
	}
	
}

int main(void)
{
	sei(); // enable global interrupt 
	DDRB|=(1<<DDB5);
	TCCR0A=0; // NORMAL MODE 
	TCCR0B|=(1<<CS00)|(1<<CS01); //64 PRESCALAR
	TIMSK0|=(1<<TOIE0); // enabling timer overflow interrupt for timer 0 in normal mode
	
	
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

