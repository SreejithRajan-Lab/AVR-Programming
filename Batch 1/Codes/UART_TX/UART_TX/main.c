/*
 * UART_TX.c
 *
 * Created: 17-10-2025 20:53:14
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	UBRR0H = 0;
	UBRR0L = 103;            // set baud rate as 9600
	UCSR0B |= (1 << TXEN0);  // Enable transmission
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);  // 8-bit data mode

	char a[] = "Hello\n";  //This is our data
	int i;

	while (1)
	{
		for(i = 0; a[i] != '\0'; i++)
		{
			while(!(UCSR0A & (1 << UDRE0))); // wait until UDR0 is ready
			UDR0 = a[i];
		}
		_delay_ms(1000);
	}
}

