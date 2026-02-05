/*
 * Blink_XOR.c
 *
 * Created: 15-11-2025 20:30:43
 * Author : sreej
 */ 

/*
 * Blink.c
 *
 * Created: 13-11-2025 20:45:56
 * Author : sreej
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>

int main(void)
{
DDRD|=(1<<DDD2);		// Set DDD2(PD2) as Output
    while (1)
    {
		PORTD^=(1<<PD2); // Set PD2=1
		_delay_ms(1000);
		
    }
}



