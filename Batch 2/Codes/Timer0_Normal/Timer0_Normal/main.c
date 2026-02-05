/*
 * Timer0_Normal.c
 *
 * Created: 25-11-2025 21:10:56
 * Author : sreej
 */ 
# define F_CPU 16000000UL
#include <avr/io.h>

void delay_1s(void)
{
	
	// set timer 0 in normal mode
	TCNT0=0; // Load minimum value of counter
	TCCR0A&=~(1<<WGM00);
	TCCR0A&=~(1<<WGM01);
	TCCR0B &= ~(1<<WGM02);
	
	// set no prescaling 
	TCCR0B&=~(1<<CS02);
	TCCR0B&=~(1<<CS01);	
	TCCR0B|=(1<<CS00);
	
	// Repeat 62500 times for getting 1 s delay
	 for(long int i =0; i<62500;i++)
	 {
		 
		 while(!(TIFR0&(1<<TOV0))); // checking TOV0 flag
		 TIFR0|=(1<<TOV0); // writing 1 to make TOV0=0; Strange rule !
	 }
		
}

int main(void)
{
  DDRB|=(1<<DDB5);
    while (1) 
    {
		PORTB^=(1<<PB5);
		delay_1s();
		
    }
}

