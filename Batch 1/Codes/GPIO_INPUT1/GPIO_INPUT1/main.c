/*
 * GPIO_INPUT1.c
 *
 * Created: 08-09-2025 20:26:13
 * Author : sreej
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>


int main(void)
{
    DDRB=0b00100000;
	DDRD=0b00000000;
	PORTD=0b00000001;
    while (1) 
    {
		if(PIND==0b00000000)
		{
			PORTB=0b00100000;
		}
		else
		{
			PORTB=0b00000000;
		}
		
    }
}

