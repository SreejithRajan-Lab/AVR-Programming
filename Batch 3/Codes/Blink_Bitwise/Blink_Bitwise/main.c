/*
 * Blink_Bitwise.c
 *
 * Created: 24-01-2026 21:31:36
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>

int main(void)
{
   DDRB|=(1<<DDB5); // Configuring Pin 5 as Output
    while (1) 
    {
		PORTB|=(1<<PB5);
		_delay_ms(1000);
		PORTB&=~(1<<PB5);
		_delay_ms(1000);
	
    }
}

