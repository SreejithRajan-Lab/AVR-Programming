/*
 * Modular_timer.c
 * This code implements a delay function using timer0 and modular concepts. 
 * Created: 02-12-2025 20:24:22
 * Author : sreej
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "delay.h"     // " " is usually used for user defined headers


int main(void)
{
  DDRB|=(1<<DDB5);  // Set PB5 as output
  timer0_init();  // user function for timer 0 configuration 
    while (1) 
    {
		PORTB^=(1<<PB5);
		delay_ms(5000);     // user defined function for delay
    }
}    

