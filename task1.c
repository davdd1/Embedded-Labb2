#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

volatile uint8_t* ddrb = (volatile uint8_t*)0x24; // DDRB
volatile uint8_t* portb = (volatile uint8_t*)0x25; // PORTB

volatile uint8_t* portd = (volatile uint8_t*)0x2B; // PORTD
volatile uint8_t* pind = (volatile uint8_t*)0x29; // PIND


void setup()
{
    *ddrb |= (1 << PB5);      // Set pin 13/Inbuild LED as output
}

void loop()
{
    uint8_t pd7State = *pind & (1 << PD7);       // Read the state of pin 7
    *portd |= (1 << PD7);        // Set pin 7 to HIGH
    if (pd7State)
    {
        // If pin 7 is HIGH, blink the LED with 200ms delay
        *portb |= (1 << PB5);
        delay(200);
        *portb &= ~(1 << PB5);
        delay(200);
    }
    else
    {
        // If pin 7 is LOW, blink the LED with 2000ms delay
        *portb |= (1 << PB5);
        delay(2000);
        *portb &= ~(1 << PB5);
        delay(2000);
    }
}