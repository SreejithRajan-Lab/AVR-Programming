/*
 * Delay_Modular_Timer0.c
 *
 * Created: 19-09-2025 23:44:53
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include "delay.h"

int main(void) 
{
    DDRB|=(1<<DDB5);
	timer0_init();
    while (1) 
    {
		PORTB ^=(1<<PORTB5);
		delay_ms(5000);
    }
}

