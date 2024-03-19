#include <stdio.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

volatile uint8_t* ddrb = (volatile uint8_t*)0x24; // DDRB
volatile uint8_t* portb = (volatile uint8_t*)0x25; // PORTB

volatile uint8_t* ddrd = (volatile uint8_t*)0x2A; // DDRD
volatile uint8_t* portd = (volatile uint8_t*)0x2B; // PORTD

unsigned long previousMillis[4] = {0, 0, 0, 0}; // Array to store previous millis for each LED
const unsigned long interval[4] = {1000, 1500, 2000, 2500}; // Blink interval for each LED

bool ledState[4] = {false}; // Array to store LED states

void setup() {
    // Initialize the digital pins as output

    // Set pin 13 (PB2) as output
    *ddrd |= (1 << 2);
    // Set pin 13 (PB3) as output
    *ddrd |= (1 << 3);
    // Set pin 13 (PB4) as output
    *ddrd |= (1 << 4);
    // Set pin 13 (PB5) as output
    *ddrb |= (1 << 5); 
}

void loop() {
    unsigned long currentMillis = millis(); // Get the current time
    
    // Check if it's time to toggle each LED
    for (int i = 0; i < 4; i++) {
        if (currentMillis - previousMillis[i] >= interval[i]) {
            previousMillis[i] = currentMillis;
            toggleLED(i);
            delay(10);
        }
    }
}

bool allOtherLedsOff(int index) {
    // Check if all other LEDs are off
    for (int i = 0; i < 4; i++) {
        if (i != index && ledState[i]) {
            return false; // Another LED is on
        }
    }
    return true; // All other LEDs are off
}

void turnOnLED(int pin) {
    if(allOtherLedsOff(pin)){
        // Turn on the LED based on the pin number
        switch(pin) {
            case 0:
                *portd |= (1 << 2); // Turn on LED connected to pin PD2
                break;
            case 1:
                *portd |= (1 << 3); // Turn on LED connected to pin PD3
                break;
            case 2:
                *portd |= (1 << 4); // Turn on LED connected to pin PD4
                break;
            case 3:
                *portb |= (1 << 5); // Turn on LED connected to pin PB5
                break;
            default:
                break;
        }
    } else {
        delay(250);
        turnOffAll();
        // Turn on the LED based on the pin number
        switch(pin) {
            case 0:
                *portd |= (1 << 2); // Turn on LED connected to pin PD2
                break;
            case 1:
                *portd |= (1 << 3); // Turn on LED connected to pin PD3
                break;
            case 2:
                *portd |= (1 << 4); // Turn on LED connected to pin PD4
                break;
            case 3:
                *portb |= (1 << 5); // Turn on LED connected to pin PB5
                break;
            default:
                break;
        }
    }
}

void turnOffLED(int pin) {
    // Turn off the LED based on the pin number
    switch(pin) {
        case 0:
            *portd &= ~(1 << 2); // Turn off LED connected to pin PD2
            break;
        case 1:
            *portd &= ~(1 << 3); // Turn off LED connected to pin PD3
            break;
        case 2:
            *portd &= ~(1 << 4); // Turn off LED connected to pin PD4
            break;
        case 3:
            *portb &= ~(1 << 5); // Turn off LED connected to pin PB5
            break;
        default:
            break;
    }
}

void toggleLED(int index) {    
    ledState[index] = !ledState[index]; // Switch LED state

    if (ledState[index]) {
        turnOnLED(index);
    } else {
        turnOffLED(index);
    }
}

void turnOffAll() {
    // Turn off all LEDs
    for (int i = 0; i < 4; i++) {
        turnOffLED(i);
    }
}