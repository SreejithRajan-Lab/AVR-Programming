/*
 * PWM_Phase Correct.c
 *
 * Created: 29-11-2025 21:11:10
 * Author : sreej
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include<util/delay.h>


int main(void)
{
	DDRD|=(1<<DDD6);  // Configure PD6 as output
	//Configuring for phase correct PWM
	
	TCCR0A|=(1<<WGM00);
	TCCR0A&=~(1<<WGM01);
	
	//Configuring for non inverting PWM
	
	TCCR0A|=(1<<COM0A1);
	TCCR0B&=~(1<<COM0A0);
	
	// Confugure for prescalar =8
	
	TCCR0B&=~(1<<CS02);
	TCCR0B&=~(1<<CS00);
	TCCR0B|=(1<<CS01);
	
	//OCR0A=128;
	
    /* Replace with your application code */
    while (1) 
    {
		for(int i=0; i<=255;i++)
		{
			OCR0A=i;
			_delay_ms(10);
		}
		
			for(int i=255; i>0;i--)
			{
				OCR0A=i;
				_delay_ms(10);
			}
		
		
    }
}

