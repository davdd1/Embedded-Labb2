#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// Define memory adress for ddrb and portb
volatile uint8_t* ddrb = (volatile uint8_t*)0x24; // DDRB
volatile uint8_t* portb = (volatile uint8_t*)0x25; // PORTB

//Define memory adress for ddrd and portd
volatile uint8_t* ddrd = (volatile uint8_t*)0x2A; // DDRD
volatile uint8_t* portd = (volatile uint8_t*)0x2B; // PORTD

//Define memory adress for pinb
volatile uint8_t* pinb = (volatile uint8_t*)0x23; //PINB

int buttons = 0;
int pressCount = 0;

void setup() {
 // Initialize the digital pins as output

 //Set pin 2 (PB2) as output
 *ddrd |= (1 << 2);
 //Set pin 3 (PB3) as output
 *ddrd |= (1 << 3);
 //Set pin 4 (PB4) as output
 *ddrd |= (1 << 4);
 //Set pin 4 (PB4) as output
 *ddrd |= (1 << 5);
 //Set pin 13 (PB5) as output
 *ddrb |= (1 << 5); 
 
 //Set pin 8 (PB0) as input
 *ddrb &= ~(1 << 0);
 //Set pin 9 (PB1) as input
 *ddrb &= ~(1 << 1);
 //Set pin 10 (PB2) as input
 *ddrb &= ~(1 << 2);
 //Set pin 11 (PB3) as input
 *ddrb &= ~(1 << 3);
}

void loop() {
  // Turn ON/OFF LED 3
  if (*pinb & (1 << 0)){
    if (*portd & (1 << 3)){
      *portd &= ~(1 << 3);
    } else {
      *portd |= (1 << 3);
    }
    delay(500);
    buttons++;
    pressCount++;
  }
  // Turn ON/OFF LED 2
  if (*pinb & (1 << 1)){
    if (*portd & (1 << 4)){
      *portd &= ~(1 << 4);
    } else {
      *portd |= (1 << 4);
    }
    delay(500);
    buttons++;
    pressCount++;
  }
 // Turn ON/OFF LED 1
  if (*pinb & (1 << 2)){
    if (*portd & (1 << 5)){
      *portd &= ~(1 << 5);
    } else {
      *portd |= (1 << 5);
    }
    delay(500);
    buttons++;
    pressCount++;
  }
  // Turn ON/OFF Built in LED
  if (*pinb & (1 << 3)){
    if (*portb & (1 << 5)){
      *portb &= ~(1 << 5);
    } else {
      *portb |= (1 << 5);
    }
    delay(500);
    buttons++;
    pressCount++;
  }
  // Turn ON green LED for 3 sec
  if ((buttons > 1) || (pressCount > 9)){
    *portd |= (1 << 2);
    delay(3000);
    *portd &= ~(1 << 2);
    if (pressCount > 9){
      pressCount = 0;
    }
  }
  buttons = 0;
}