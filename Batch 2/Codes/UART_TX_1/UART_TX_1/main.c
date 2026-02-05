/*
 * UART_TX_1.c
 *
 * Created: 31-12-2025 21:04:50
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>


int main(void)
{
	char a='A';
    UBRR0H=0;
	UBRR0L=103; //Set baud rate to 9600
	UCSR0C|=(1<<UCSZ01)|(1<<UCSZ00); // 8bit mode;
	UCSR0C&=~((1<<UPM01)|(1<<UPM00)|(1<<USBS0)); // No parity and 1 stop bit
	UCSR0B|=(1<<TXEN0); // Enable transmitter
    while (1) 
    {
		UDR0=a;
		while(!(UCSR0A&(1<<UDRE0))); // wait until the transmission is complete
		_delay_ms(1000);
		
    }
}

