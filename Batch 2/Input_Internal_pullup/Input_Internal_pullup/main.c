/*
 * Input_Internal_pullup.c
 *
 * Created: 22-11-2025 20:57:27
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>


int main(void)
{
DDRD&=~(1<<DDD2); // Making Pin d2 as input
PORTD|=(1<<PD2); // Making internal pull up for PD2
DDRB|=(1<<DDB5); // Making PB5 as output
    while (1) 
    {
		if(!(PIND&(1<<PD2))) // checking if Pin PD2 is Low
		{
			PORTB|=(1<<PB5);  // PB5= High
		}
		else
		{
			PORTB&=~(1<<PB5); //PB5=LOW
		}
    }
}

