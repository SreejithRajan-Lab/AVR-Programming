/*
 * Delay_timer0_normal.c
 *
 * Created: 17-09-2025 20:47:25
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>

void delay_1s(void)
{
	unsigned int i;
	unsigned int count= 976;
	for(i=0; i<count;i++)
	{
	TCNT0=0;
	TCCR0A=0;
	TCCR0B|=(1<<CS00);
	TCCR0B|=(1<<CS01); //PRESCALAR 64
	TIFR0|=(1<<TOV0); // making timer overflow flag 0
	   while (!(TIFR0 & (1 << TOV0))); //waiting timer overflow flag to set so that we get 16us delay 
}
}

int main(void)
{
  DDRB|=(1<<DDB5); // PB5 AS OUTPUT
    while (1) 
    {
		PORTB^=(1<<PORTB5);
		delay_1s();
    }
}

