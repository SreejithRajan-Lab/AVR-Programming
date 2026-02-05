/*
 * gpio.c
 *
 * Created: 26-09-2025 21:54:39
 *  Author: sreej
 */ 
#define F_CPU 16000000UL
#include<avr/io.h>
 void gpio_init(void)
 {
	 DDRB|=(1<<DDB5);
	 DDRB|=(1<<DDB4);
	 DDRB|=(1<<DDB3);
	 DDRB|=(1<<DDB2);
	 DDRB|=(1<<DDB1);
 }