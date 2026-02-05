/*
 * Button.c
 *
 * Created: 15-07-2025 12:04:15
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>


int main(void)
{
 DDRB|=(1<<PB5);
 DDRB&= ~(1<<PB4);
 //PORTB|=(1<<PB4);
    while (1) 
    {
		
		if(PINB&(1<<PB4))
		{
			PORTB|=(1<<PB5);
		}
		else
		{
				PORTB&=~(1<<PB5);
		}
    }
}

