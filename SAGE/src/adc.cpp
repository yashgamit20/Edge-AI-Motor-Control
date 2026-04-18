#include <avr/io.h>
#include "adc.h"

void ADC_init(void)
{
    // AVcc = reference (5V)
    ADMUX = (1 << REFS0);

    // Enable ADC + Prescaler = 128 (for 16MHz → 125kHz ADC clock)
    ADCSRA = (1 << ADEN) | 
             (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_read(uint8_t channel)
{
    // Select channel (0–7)
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    // Start conversion
    ADCSRA |= (1 << ADSC);

    // Wait for completion
    while (ADCSRA & (1 << ADSC));

    return ADC;
}