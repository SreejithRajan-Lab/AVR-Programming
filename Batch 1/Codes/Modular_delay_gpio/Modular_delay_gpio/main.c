/*
 * Modular_delay.c
 *
 * Created: 26-09-2025 20:20:20
 * Author : sreej
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "sreejith.h"
#include "gpio.h"
#include<stdint.h>

int main(void)
{
 gpio_init();

    while (1) 
    {
		PORTB^=(1<<PORTB5);
		PORTB^=(1<<PORTB4);
		PORTB^=(1<<PORTB3);
		PORTB^=(1<<PORTB2);
		PORTB^=(1<<PORTB1);
		anees(2000);  // just used a student's name for delay. Its better to use a name which is close to the purpose.i need to get 2000ms delay
    }
}

