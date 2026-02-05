/*
 * dc_motor.c
 *
 * Created: 15-11-2025 20:57:06
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
DDRD|=(1<<DDD2)|(1<<DDD3); //Initializing pin D2 and D3 as input
 
    while (1) 
    {
		//Pin 1 on 2 off
		PORTD|=(1<<PD2);
		PORTD&=~(1<<PD3);
		_delay_ms(5000);
		
		//Pin 1 and 2 off
		PORTD&=~(1<<PD2);
		PORTD&=~(1<<PD3);
		_delay_ms(3000);
		
		//pin 2 on 1 off
		PORTD&=~(1<<PD2);
		PORTD|=(1<<PD3);
		_delay_ms(5000);
		
		//pin 1 and 2 off
		PORTD&=~(1<<PD2);
		PORTD&=~(1<<PD3);
		_delay_ms(3000);
    }
}

