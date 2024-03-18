#include <Arduino.h>

void setup()
{
    DDRB |= (1 << PB5);
    DDRD &= ~(1 << PD7);
}

void loop()
{
    uint8_t pd7State = PIND & (1 << PD7);
    PORTD |= (1 << PD7);
    if (pd7State)
    {
        PORTB |= (1 << PB5);
        delay(200);
        PORTB &= ~(1 << PB5);
        delay(200);
    }
    else
    {
        PORTB |= (1 << PB5);
        delay(2000);
        PORTB &= ~(1 << PB5);
        delay(2000);
    }
}