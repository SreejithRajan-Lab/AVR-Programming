/*
 * delay.c
 *
 * Created: 19-09-2025 23:51:16
 *  Author: sreej
 */ 
#include <avr/io.h>
#include "delay.h"
#include<stdint.h>

void timer0_init(void)
{
		TCCR0A|=(1<<WGM01); //CTC MODE
		OCR0A=249; // SETPOINT EQUAL TO 250
		TCNT0=0; // INITIAL VALUE OF TIMER IS 0
		TCCR0B|=(1<<CS00);
		TCCR0B|=(1<<CS01); // prescalar of 64
		TIFR0 |=(1<<OCF0A); // Writing 1 to OCF0A bit of TIFR0 REGISTER TO RESET IT (BECAUSE AVR PEOPLE ARE MAD)
		
}
void delay_ms(uint16_t ms)
{

	while(ms--)
	{
			TIFR0 |=(1<<OCF0A);
		while(!(TIFR0&(1<<OCF0A)))
		{
			//exact 1ms delay
		}
		
	}
	
}