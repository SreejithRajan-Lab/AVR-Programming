/*
 * BMP280.c
 *
 * Created: 06-01-2026 20:42:08
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

int main(void)
{
	UART_Init();
	uint8_t chip_id,msb,lsb,xlsb,T1_L,T1_U,T2_L,T2_U,T3_L,T3_U,T_int,T_frac;
	uint32_t temp;
	uint16_t dig_T1,dig_T2;
	int dig_T3,T_new;
	float var1,var2;
	float t_fine,T;
	DDRB|=(1<<DDB3)|(1<<DDB5)|(1<<DDB2); // MOSI, SCK AND CSB are configured as output
	DDRB&=~(1<<DDB4); //MISO is configured as input
	
	SPCR |= ((1 << SPE) |( 1 << MSTR) | (1 << SPR0));
	SPCR &= ~((1 << SPR1) |( 1 << CPHA) | (1 << CPOL));
	
    while (1) 
    {
		PORTB&=~(1<<PB2); //Selecting slave
		SPDR= (0XD0|0X80); // Ensuring 1 on MSB (Reading)
		while (!(SPSR & (1<<SPIF))); // Waiting until flag is set
		(void)SPDR; // reading SPDR(for dummy garbage value)
		
		SPDR=0X00;    // Sending dummy to read the data from BMP280
		while (!(SPSR & (1<<SPIF)));//waiting until flag is set.
		chip_id = SPDR;   // reading chip ID
		
		PORTB|=(1<<PB2); // De selecting slave 
		
		
		//Enabling measurement by writing 0x27 to 0xF4 register of bmp280
		
			PORTB&=~(1<<PB2); //Selecting slave
		SPDR= (0XF4&0X7F); // Ensuring 1 on MSB (Writing)
		while (!(SPSR & (1<<SPIF))); // Waiting until flag is set
		(void)SPDR; // reading SPDR(for dummy garbage value)
		
		SPDR=0X27;    // writing to F4 the data from BMP280
		while (!(SPSR & (1<<SPIF)));//waiting until flag is set.
		(void)SPDR;   // dummy reading
		PORTB|=(1<<PB2); // De selecting slave 
		
		// Reading Data from 0xFA
		
		PORTB&=~(1<<PB2); //Selecting slave
		SPDR= (0XFA|0X80); // Ensuring 1 on MSB (Reading)
		while (!(SPSR & (1<<SPIF))); // Waiting until flag is set
		(void)SPDR; // reading SPDR(for dummy garbage value)
		
		SPDR=0X00;    // Sending dummy to read the data from BMP280
		while (!(SPSR & (1<<SPIF)));//waiting until flag is set.
		msb = SPDR;   // reading chip ID
		
		//Reading Data from 0XFB
		
		SPDR=0X00;    // Sending dummy to read the data from BMP280
		while (!(SPSR & (1<<SPIF)));//waiting until flag is set.
		lsb = SPDR;   // reading chip ID
		
		SPDR=0X00;    // Sending dummy to read the data from BMP280
		while (!(SPSR & (1<<SPIF)));//waiting until flag is set.
		xlsb = SPDR;   // reading chip ID
		
		temp = ((uint32_t)msb << 12) | ((uint32_t)lsb << 4) | ((uint32_t)xlsb >> 4);
		PORTB|=(1<<PB2); // De selecting slave 
		
		//Reading temperature compensation values 
		
		PORTB&=~(1<<PB2); //Selecting slave
		SPDR= (0X88|0X80); // Ensuring 1 on MSB (Reading)
		while (!(SPSR & (1<<SPIF))); // Waiting until flag is set
		(void)SPDR; // reading SPDR(for dummy garbage value)
		
		SPDR=0X00;    // Sending dummy to read the data from BMP280
		while (!(SPSR & (1<<SPIF)));//waiting until flag is set.
		T1_L = SPDR;   // reading chip ID
		
		//Reading Data from 0XFB
		
		SPDR=0X00;    // Sending dummy to read the data from BMP280
		while (!(SPSR & (1<<SPIF)));//waiting until flag is set.
		T1_U = SPDR;   // reading chip ID
		
		SPDR=0X00;    // Sending dummy to read the data from BMP280
		while (!(SPSR & (1<<SPIF)));//waiting until flag is set.
		T2_L = SPDR;   // reading chip ID
		
			
		SPDR=0X00;    // Sending dummy to read the data from BMP280
		while (!(SPSR & (1<<SPIF)));//waiting until flag is set.
		T2_U = SPDR;   // reading chip ID
		
		SPDR=0X00;    // Sending dummy to read the data from BMP280
		while (!(SPSR & (1<<SPIF)));//waiting until flag is set.
		T3_L = SPDR;   // reading chip ID
		
		
		SPDR=0X00;    // Sending dummy to read the data from BMP280
		while (!(SPSR & (1<<SPIF)));//waiting until flag is set.
		T3_U = SPDR;   // reading chip ID
		PORTB|=(1<<PB2); // De selecting slave 
		
		
		dig_T1 = ((uint16_t)T1_U << 8) |T1_L;
		dig_T2 = ((uint16_t)T2_U << 8) |T2_L;
		dig_T3 = ((uint16_t)T3_U << 8) |T3_L;
		
		var1 = ((temp/16384.0f)-(dig_T1/1024.0f))* dig_T2;
		var2 = ((temp/131072.0f)-(dig_T2/8192.0f))* dig_T3;
		t_fine=var1+var2;
		T=t_fine/5190.0f;
		  
		T_new=T*100;    
		T_int = T_new/100;  
		T_frac = T_new%100;
				
UART_TxNumber(T_int);
UART_TxChar('.');
if(T_frac<10)
{
UART_TxChar('0');	
}
UART_TxNumber(T_frac);
UART_TxChar('\n');

_delay_ms(1000);
    }
}

