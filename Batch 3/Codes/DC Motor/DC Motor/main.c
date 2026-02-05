/*
 * DC Motor.c
 *
 * Created: 27-01-2026 21:47:42
 * Author : sreej
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>

int main(void)
{
	DDRB|=(1<<DDB5)|(1<<DDB4); // Configuring Pin 4&5 as Output
	while (1)
	{
		//Direction 1
		PORTB|=(1<<PB5); //pb5 high
		PORTB&=~(1<<PB4); //pb4 low
		_delay_ms(2000);
		//Stop
		PORTB&=~(1<<PB5); //pb5 low
		PORTB&=~(1<<PB4); // pb4 low
		_delay_ms(2000);
		//Direction 2
		PORTB&=~(1<<PB5); //pb5 low
		PORTB|=(1<<PB4);  //pb4 high
		_delay_ms(2000);
		//Stop
		PORTB&=~(1<<PB5); //pb5 low
		PORTB&=~(1<<PB4); //pb4 low 
		_delay_ms(2000);
		
	}
}

