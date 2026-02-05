/*
 * Timer0_Normal.c
 *
 * Created: 03-02-2026 21:50:13
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>

void delay_1ms()
{
	
	for(int i=0;i<977;i++)  // repeating the process 62500 times to get 1 s delay
	{
	while(!(TIFR0&(1<<TOV0))); // wait until TOV0=1. IE till overflow happens 
	TIFR0|=(1<<TOV0); //Writing 1 to TOV0 bit to make it 0. AVR People are crazy
	}
}



int main(void)
{
TCNT0=0;  // Initial value of TCNT0 =0;

// Configuring Timer 0 for normal mode
TCCR0A &=~(1<<WGM00);
TCCR0A &=~(1<<WGM01);

// Configuring Timer0 for 64 prescalar condition 

TCCR0B|=(1<<CS00)|(1<<CS01);
TCCR0B&=~(1<<CS02);
//CONFIGURING A PIN FOR LED
DDRB|=(1<<PB5); //Configuring pin 5 as output
    while (1) 
    {
		PORTB|=(1<<PB5);  //PB5 is on 
		delay_1ms();
		PORTB&=~(1<<PB5);
		delay_1ms();
    }
}

