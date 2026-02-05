/*
 * sreejith.c
 *
 * Created: 26-09-2025 20:33:13
 *  Author: sreej
 */ 
#define F_CPU 16000000UL
#include<avr/io.h>
void timer0_init(void) //define timer0_init()
{
	TCCR0A|=(1<<WGM01); //CTC MODE
	OCR0A=249; // for count 250 setpoint
	TCNT0=0; // making timer counter 0
	TCCR0B|=(1<<CS00);
	TCCR0B|=(1<<CS01); //prescalar 64
	TIFR0|=(1<<OCF0A); // setting flag to 0 by writing one 
}

void anees(uint16_t ms) // define anees
{
	timer0_init();
	while(ms--) // creates delay for "ms" milliseconds 
	{
		while(!(TIFR0&(1<<OCF0A))) // 1ms LOOP
		{
			
		}
		TIFR0|=(1<<OCF0A);
	}
	
}