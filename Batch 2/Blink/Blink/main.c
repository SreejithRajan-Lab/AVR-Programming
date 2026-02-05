/*
 * Blink.c
 *
 * Created: 13-11-2025 20:45:56
 * Author : sreej
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>

int main(void)
{
DDRD|=(1<<DDD2);		// Set DDD2(PD2) as Output
    while (1)
    {
		PORTD|=(1<<PD2); // Set PD2=1
		_delay_ms(1000);
		PORTD&=~(1<<PD2);	// Set PD2=0
		_delay_ms(1000);
    }
}

