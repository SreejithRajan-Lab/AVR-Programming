/*
 * Blink_opt.c
 *
 * Created: 15-07-2025 11:46:22
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>

int main(void)
{

    while (1) 
    {
		DDRB|=(1<<PB5);
		PORTB^=(1<<PB5);
		_delay_ms(1000);
    }
}

