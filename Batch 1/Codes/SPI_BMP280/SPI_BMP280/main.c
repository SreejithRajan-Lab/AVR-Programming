/*
 * main.c
 *
 * Created: 10-11-2025 21:03:59
 *  Author: sreej
 */ 
/*
 * uart.c
 *
 * Created: 01-11-2025 13:55:56
 *  Author: sreej
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include <stdint.h> // added for fixed-width signed types

int main(void)
{
	uint8_t chip_id;
	uint32_t msb, lsb, xlsb, temp;
	float var1, var2,t_fine_f,actual_temp;


	// calibration variables 
	uint16_t dig_T1 = 0;
	int16_t  dig_T2 = 0;
	int16_t  dig_T3 = 0;

	UART_Init();

	DDRB |= (1 << PB3) | (1 << PB5) | (1 << PB2); // MOSI, SCK, SS as outputs
	DDRB &= ~(1 << PB4);                           // MISO as input
	PORTB |= (1 << PB2);                           // SS high initially
	DDRD  |= (1 << PD3);                           // PD3 as output (LED)

	// ===== SPI SETUP =====
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // Enable SPI Master, Fosc/16
	_delay_ms(100); // allow BMP280 to power up

	// ===== READ CHIP ID =====
	PORTB &= ~(1 << PB2); // CSB low
	SPDR = 0xD0 | 0x80;   // Chip ID register (0xD0) with read bit
	while (!(SPSR & (1 << SPIF)));
	(void)SPDR;           // dummy read
	SPDR = 0x00;          // send dummy to receive data
	while (!(SPSR & (1 << SPIF)));
	chip_id = SPDR;
	PORTB |= (1 << PB2);  // CSB high
	_delay_ms(10);
	
	// wake from sleep
	PORTB &= ~(1 << PB2); // CSB low
	SPDR = 0xF4 & 0x7F;   // Chip ID register (0xF4) with read bit
	while (!(SPSR & (1 << SPIF)));
	(void)SPDR;           // dummy read
	SPDR = 0x27;          // send dummy to receive data
	while (!(SPSR & (1 << SPIF)));
	(void)SPDR;
	PORTB |= (1 << PB2);  // CSB high
	_delay_ms(10);
	
	//READ BACK CTRL_MEAS TO VERIFY MODE 
	uint8_t ctrl_meas;
	PORTB &= ~(1 << PB2);
	SPDR = 0xF4 | 0x80;       // read ctrl_meas (0xF4)
	while (!(SPSR & (1 << SPIF)));
	(void)SPDR;
	SPDR = 0x00;
	while (!(SPSR & (1 << SPIF)));
	ctrl_meas = SPDR;
	PORTB |= (1 << PB2);

	UART_TxString("CTRL_MEAS: ");
	UART_TxNumber(ctrl_meas);   //This should show 0x27
	UART_TxChar('\n');

	// READ TEMPERATURE CALIBRATION REGISTERS(dig 1, dig2, dig 3)
	
	{
		uint8_t b0, b1, b2, b3, b4, b5;
		PORTB &= ~(1 << PB2); // CSB low
		SPDR = 0x88 | 0x80;   // starting address 0x88 with read bit
		while (!(SPSR & (1 << SPIF)));
		(void)SPDR;

		// read byte 0 (0x88)
		SPDR = 0x00; 
		while (!(SPSR & (1 << SPIF))); b0 = SPDR;
		// read byte 1 (0x89)
		SPDR = 0x00; 
		while (!(SPSR & (1 << SPIF))); b1 = SPDR;
		// read byte 2 (0x8A)
		SPDR = 0x00; 
		while (!(SPSR & (1 << SPIF))); b2 = SPDR;
		// read byte 3 (0x8B)
		SPDR = 0x00; 
		while (!(SPSR & (1 << SPIF))); b3 = SPDR;
		// read byte 4 (0x8C)
		SPDR = 0x00; 
		while (!(SPSR & (1 << SPIF))); b4 = SPDR;
		// read byte 5 (0x8D)
		SPDR = 0x00; 
		while (!(SPSR & (1 << SPIF))); b5 = SPDR;

		PORTB |= (1 << PB2); // CSB high
		
		//shifting and or to get 16 bit values

		dig_T1 = (uint16_t)((b1 << 8) | b0);    
		dig_T2 = (int16_t)((b3 << 8) | b2);
		dig_T3 = (int16_t)((b5 << 8) | b4);

// Optional: print calibration values for debugging.

UART_TxString("Calib T1: ");
UART_TxNumber(dig_T1);
UART_TxChar('\n');

UART_TxString("Calib T2: ");
if (dig_T2 < 0) { UART_TxChar('-'); UART_TxNumber(-dig_T2); }
else { UART_TxNumber(dig_T2); }
UART_TxChar('\n');

UART_TxString("Calib T3: ");
if (dig_T3 < 0) { UART_TxChar('-'); UART_TxNumber(-dig_T3); }
else { UART_TxNumber(dig_T3); }
UART_TxChar('\n');

	}

	while (1)
	{
			// READ TEMPERATURE REGISTERS (0xFA, 0xFB, 0xFC) 
			PORTB &= ~(1 << PB2); // CSB low
			SPDR = 0xFA | 0x80;   // Temp MSB address + read bit
			while (!(SPSR & (1 << SPIF)));
			(void)SPDR;

			// read MSB
			SPDR = 0x00;
			while (!(SPSR & (1 << SPIF)));
			msb = SPDR;      // msb of temperature

			// read LSB
			SPDR = 0x00;
			while (!(SPSR & (1 << SPIF)));
			lsb = SPDR;

			// read XLSB
			SPDR = 0x00;
			while (!(SPSR & (1 << SPIF)));
			xlsb = SPDR;

			PORTB |= (1 << PB2); // CSB high
			
			temp = ((uint32_t)msb << 12) | ((uint32_t)lsb << 4) | ((uint32_t)xlsb >> 4);
		
		UART_TxString("Raw Temp: ");
		UART_TxNumber(temp);       // print raw temperature
		UART_TxChar('\n');

		// TEMPERATURE COMPENSATION (Floating-point, matches datasheet) 
		{
			
			float adc_Tf = (float)temp;  // convert raw temperature to float

			var1 = (((adc_Tf / 16384.0f) - ((float)dig_T1 / 1024.0f)) * (float)dig_T2);
			var2 = ((((adc_Tf / 131072.0f) - ((float)dig_T1 / 8192.0f)) *
			((adc_Tf / 131072.0f) - ((float)dig_T1 / 8192.0f))) * (float)dig_T3);

			t_fine_f = var1 + var2;
			actual_temp = t_fine_f / 5120.0f;     // final temperature in °C

		}


//JUST TO CHECK IF THE VALUES ARE IN RANGE

UART_TxString("var1: ");
UART_TxNumber(var1); 
UART_TxChar('\n');

UART_TxString("var2: "); 
UART_TxNumber(var2); 
UART_TxChar('\n');

UART_TxString("t_fine: "); 
UART_TxNumber(t_fine_f); 
UART_TxChar('\n');

// Print compensated temperature as signed value with two decimal places
	
			int32_t t_hundredths = (int32_t)(actual_temp * 100.0f); // 
			int32_t t_int = t_hundredths / 100;
			int32_t t_frac = t_hundredths % 100;
			if (t_frac < 0) t_frac = -t_frac; // make frac positive when negative temp

			// handle negative integer part if necessary
			if (t_int < 0 && t_frac > 0)
			{
				// e.g., -0.12 should print "-0.12"
				UART_TxChar('-');
				UART_TxNumber((uint16_t)(-t_int));
			}
			else
			{
				UART_TxNumber((uint16_t)t_int);
			}

			UART_TxChar('.');
			// print two digits for fraction (leading zero if needed)
			if (t_frac < 10)
			{
				UART_TxChar('0');
				UART_TxNumber((uint16_t)t_frac);
			}
			else
			{
				UART_TxNumber((uint16_t)t_frac);
			}

			UART_TxString(" C\n");
		
		/*if (chip_id == 0x58)
		{
			PORTD |= (1 << PD3);   // LED ON if BMP280 detected
		}
		else
		{
			PORTD &= ~(1 << PD3);  // LED OFF otherwise
		}*/

		_delay_ms(1000);
	}
}
