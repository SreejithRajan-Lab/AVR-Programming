/*
 * Timer0_Prescalar.c
 *
 * Created: 27-11-2025 20:26:24
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>

void delay_1s(void)   // defining a function for delay
{
	
	for(int i=0;i<61;i++)             // repeating the loop for 61 times to get 1 second delay
	{
		while(!(TIFR0&(1<<TOV0)));    // waiting for timer flag to set
		TIFR0|=(1<<TOV0);             // resetting the timer flag
	}
	
}

int main(void)
{
  TCNT0=0;										// initial value of timer =0
  TCCR0A&=~(1<<WGM00|WGM01);					// configuring timer0 in notrmal mode 
  TCCR0B|=(1<<CS02|1<<CS00);                    // configuring timer 0 with prescalar=1024
  TCCR0B&=~(1<<CS01);
  DDRB|=(1<<DDB5);								// configuring PB5 as output
    while (1) 
    {
		PORTB^=(1<<PB5);   //   Toggling PB5
		delay_1s();        // calling user defined delay funtion 
    }
}

