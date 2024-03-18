#include <Arduino.h>

// Define memory adress for ddrb and portb
volatile uint8_t* ddrb = (volatile uint8_t*)0x24; // DDRB
volatile uint8_t* portb = (volatile uint8_t*)0x25; // PORTB

//Define memory adress for ddrd and portd
volatile uint8_t* ddrd = (volatile uint8_t*)0x2A; // DDRD
volatile uint8_t* portd = (volatile uint8_t*)0x2B; // PORTD

//Define memory adress for pinb
volatile uint8_t* pinb = (volatile uint8_t*)0x23; //PINB

int currentLED = 0;

void setup() {
 // Initialize the digital pins as output

 //Set pin 2 (PB2) as output
 *ddrd |= (1 << 2);
 //Set pin 3 (PB3) as output
 *ddrd |= (1 << 3);
 //Set pin 4 (PB4) as output
 *ddrd |= (1 << 4);
 //Set pin 13 (PB5) as output
 *ddrb |= (1 << 5); 
 //Set pin 8 (PB0) as input
 *ddrb &= ~(1 << 0);
}

void loop() {
  //If button is pressed
  if (*pinb & (1 << 0)){
    //Turn off LEDs
    *portd &= ~(1 << 2);
    *portd &= ~(1 << 3);
    *portd &= ~(1 << 4);
    *portb &= ~(1 << 5);
    delay(1000);
    //Turn on LEDs in order
    switch (currentLED) {
      case 0: 
        *portd |= (1 << 2);
        currentLED = 1;
        break;
      case 1:
        *portd |= (1 << 3);
        currentLED = 2;
        break;
      case 2:
        *portd |= (1 << 4);
        currentLED = 3;
        break;
      case 3:
        *portb |= (1 << 5);
        currentLED = 0;
        break;
    }
  }
}