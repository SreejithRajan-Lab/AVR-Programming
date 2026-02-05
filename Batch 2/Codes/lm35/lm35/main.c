/*
 * lm35.c
 *
 * Created: 23-12-2025 20:49:06
 * Author : sreej
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>

void ADC_Init(void)
{
	
	ADMUX|=(1<<REFS0); //ADC reference voltage 5 v;
	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // PRESCALAR 128
	
}
uint16_t ADC_Read(uint8_t channel)
{
	
channel &=0x07;// limiting the channel to 7
ADMUX = (ADMUX&0XF0)|channel; // CHANNEL SELECTION
ADCSRA|=(1<<ADSC); // START CONVERSION
while(ADCSRA & (1 << ADSC));
return(ADCL|(ADCH<<8));
}
int main(void)
{
	uint16_t adc_value;
	lcd_init();
	ADC_Init();
    /* Replace with your application code */
    while (1) 
    {
		adc_value=ADC_Read(0);
		float temp = adc_value*0.488; //Converting adc value to temperature.
		lcd_clear();
		lcd_set_cursor(0,0);
		lcd_print("Temperature:");
		lcd_set_cursor(1,0);
		lcd_print_float(temp);
		lcd_data(0xDF);
		lcd_print("C");
		_delay_ms(500);
		
    }
}

