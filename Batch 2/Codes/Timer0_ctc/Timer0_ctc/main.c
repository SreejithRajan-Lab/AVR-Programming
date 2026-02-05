/*
 * Timer0_ctc.c
 *
 * Created: 27-11-2025 21:13:53
 * Author : sreej
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

void delay_1s(void)   // defining delay function
{
	
	for(int i=0;i<100;i++)     // repeat 100 times to get 1 second delay with 1024 prescalar and Compare value of 156(0x9C)
	{
		
		while(!(TIFR0&(1<<OCF0A)));  // wait until OCF0A flag is set(ie TCNT0=OCR0A);
		TIFR0|=(1<<OCF0A);             // Reset OCF0A Flag
	}
}
int main(void)
{
	TCNT0=0;            // Load minimum value of counter
	OCR0A=0x9C;          // load compare value , viz 156(0x9C)
	
	// Configure timer in CTC MODE 
	TCCR0A|=(1<<WGM01);   
	TCCR0A&=~(1<<WGM00);
	
	// Configure timer for 1024 prescalar
	TCCR0B|=(1<<CS02|1<<CS00);
	TCCR0B&=~(1<<CS01);
	
 DDRB|=(1<<DDB5);// configure pb5 as output
    while (1) 
    {
		PORTB^=(1<<PB5); // toggle pb5
		delay_1s(); // calling delay function
    }
}

