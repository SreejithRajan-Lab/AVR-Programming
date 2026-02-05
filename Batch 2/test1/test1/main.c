/*
 * ATmega328P : Read RTC (DS3231/DS1307) via I2C and print on UART
 * Clock: 16 MHz (External)
 * UART: 9600 baud
 * SDA = PC4, SCL = PC5
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>      // For snprintf()

#define RTC_ADDRESS 0x68    // DS1307 / DS3231 address


/********************* UART SECTION ************************/
void UART_init(unsigned int ubrr)
{
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;

    UCSR0B = (1 << TXEN0);                          // Enable TX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);         // 8N1
}

void UART_sendChar(char c)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
}

void UART_sendString(const char *s)
{
    while (*s) UART_sendChar(*s++);
}


/********************* I2C (TWI) SECTION ********************/
void TWI_init(void)
{
    TWSR = 0x00;        // Prescaler = 1
    TWBR = 72;          // ~100kHz at 16MHz
}

void TWI_start(void)
{
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

void TWI_stop(void)
{
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void TWI_write(uint8_t data)
{
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

uint8_t TWI_readACK(void)
{
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while (!(TWCR & (1<<TWINT)));
    return TWDR;
}

uint8_t TWI_readNACK(void)
{
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    return TWDR;
}


/********************* BCD CONVERSION ***********************/
uint8_t bcd_to_dec(uint8_t value)
{
    return ((value >> 4) * 10) + (value & 0x0F);
}


/********************* CORRECTED RTC READ ********************/
void RTC_read(uint8_t *sec, uint8_t *min, uint8_t *hour)
{
    // Set register pointer to 00h (seconds register)
    TWI_start();
    TWI_write((RTC_ADDRESS << 1) | 0);   // SLA+W
    TWI_write(0x00);                     // Register pointer

    // IMPORTANT: REPEATED START (Fix for SimulIDE)
    TWI_start();
    TWI_write((RTC_ADDRESS << 1) | 1);   // SLA+R

    *sec  = bcd_to_dec(TWI_readACK());
    *min  = bcd_to_dec(TWI_readACK());
    *hour = bcd_to_dec(TWI_readNACK());

    TWI_stop();
}


/********************* MAIN PROGRAM *************************/
int main(void)
{
    UART_init(103);       // 9600 baud at 16MHz
    TWI_init();

    uint8_t hour, min, sec;
    char buffer[20];

    while (1)
    {
        UART_sendString("Before RTC\r\n");

        RTC_read(&sec, &min, &hour);

        UART_sendString("After RTC\r\n");

        snprintf(buffer, sizeof(buffer),
                 "%02u:%02u:%02u\r\n",
                 hour, min, sec);

        UART_sendString(buffer);

        _delay_ms(1000);
    }
}
