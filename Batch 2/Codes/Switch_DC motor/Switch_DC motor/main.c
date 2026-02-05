/*
 * Switch_DC motor.c
 *
 * Created: 20-11-2025 21:00:17
 * Author : sreej
 */ 

#include <avr/io.h>

void CW(void);
void CCW(void);
void STP(void);

int main(void)
{
	
DDRD &= ~((1 << DDD2) | (1 << DDD3)); //Initializing pin D2 and D3 as input
DDRB|=(1<<DDB5)|(1<<DDB4);//initialising D4 and D5 as output

while (1)
{
	if ( (PIND & (1 << PD2)) && !(PIND & (1 << PD3)) ) // checking if PD2=1 and PD3=0

	{
		
		CW();
	}
	else if ( (PIND & (1 << PD3)) && !(PIND & (1 << PD2)) ) //  checking if PD2=0 and PD3=1
	{
	CCW();
	}
	else
	{
	STP();
	}
}
}

void CW()
{
	//Pin 1 on 2 off
	PORTB|=(1<<PB4);
	PORTB&=~(1<<PB5);
}
void STP()
{
	
	//Pin 1 and 2 off
	PORTB&=~(1<<PB4);
	PORTB&=~(1<<PB5);
}
void CCW()
	{
	//pin 2 on 1 off
	PORTB&=~(1<<PB4);
	PORTB|=(1<<PB5);
	}
	
