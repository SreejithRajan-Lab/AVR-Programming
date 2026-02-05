/*
 * Blink.c
 *
 * Created: 01-09-2025 21:08:22
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>


int main(void)
{
	DDRB=0b00100000;
    /* Replace with your application code */
    while (1) 
    {
		PORTB=0b00100000;
		_delay_ms(1000);
		PORTB=0b00000000;
		_delay_ms(1000);
    }
}

