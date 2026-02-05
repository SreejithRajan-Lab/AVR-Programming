/*
 * switch_interface.c
 *
 * Created: 20-11-2025 20:43:27
 * Author : sreej
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>


int main(void)
{
    DDRD&=~(1<<DDD2); //  configure DDD2 as input
    DDRB|=(1<<DDB5);  // Configure DDB5 as output

    while (1) 
    {
		if(PIND&(1<<PD2)) // check whether PD2=1
		{
			PORTB|=(1<<PB5); // making PB5=1
		}
		else
		{
			PORTB&=~(1<<PB5); // MAKING PB5=0;
		}

    }
}

