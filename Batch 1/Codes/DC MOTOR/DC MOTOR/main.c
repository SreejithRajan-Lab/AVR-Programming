/*
 * DC MOTOR.c
 *
 * Created: 10-09-2025 21:26:54
 * Author : sreej
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>


int main(void)
{
	DDRB|=(1<<DDB5);
	DDRB|=(1<<DDB4);

	while (1)
	{

		PORTB|=(1<<PORTB5);
		PORTB&=~(1<<PORTB4);
		_delay_ms(5000);   //CW
		PORTB&=~(1<<PORTB4); 
		PORTB&=~(1<<PORTB5);
		_delay_ms(5000); //STOP
		PORTB|=(1<<PORTB4);
		PORTB&=~(1<<PORTB5);
		_delay_ms(5000);//CCW
		PORTB&=~(1<<PORTB4);
		PORTB&=~(1<<PORTB5);
		_delay_ms(5000);//STOP
	}
}

