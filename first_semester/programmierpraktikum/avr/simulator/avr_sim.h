/*
 * AVR ATmega1284p Simulator
 * 
 * Drop-in replacement for <avr/io.h> that allows AVR code to run on a PC.
 * Provides full type definitions for IDE intellisense.
 *
 * Hardware simulated:
 *   - LED on PD0 (directly driven)
 *   - Button on PD3 (active low with pull-up)
 *
 * Keyboard controls:
 *   - 'b' or SPACE: Toggle button press (simulates PD3)
 *   - 'q' or ESC: Quit simulator
 */

#ifndef AVR_SIM_H
#define AVR_SIM_H

#include <stdint.h>
#include <stddef.h>  /* for sizeof() */

/*============================================================================
 * AVR Data Types
 * 
 * On real AVR (8-bit microcontroller):
 *   - char:      8 bit  (1 byte)
 *   - short:     16 bit (2 bytes)
 *   - int:       16 bit (2 bytes)  <-- Different from PC!
 *   - long:      32 bit (4 bytes)
 *   - long long: 64 bit (8 bytes)
 *   - float:     32 bit (4 bytes)
 *   - double:    32 bit (4 bytes)  <-- Same as float on AVR!
 *
 * On PC (this simulator):
 *   - int is typically 32 bit
 *   - double is typically 64 bit
 * 
 * Keep this in mind when testing sizeof() exercises!
 *============================================================================*/

/*============================================================================
 * Port Registers - Data Direction (DDRn)
 * 
 * Each bit controls whether the corresponding pin is INPUT or OUTPUT:
 *   - Bit = 0: Pin is INPUT  (can read external signals)
 *   - Bit = 1: Pin is OUTPUT (can drive voltage high/low)
 * 
 * Example: DDRD = 0b00000001 sets PD0 as output, PD1-PD7 as inputs
 *============================================================================*/

/** Data Direction Register for Port A (PA0-PA7) */
extern volatile uint8_t DDRA;

/** Data Direction Register for Port B (PB0-PB7) */
extern volatile uint8_t DDRB;

/** Data Direction Register for Port C (PC0-PC7) */
extern volatile uint8_t DDRC;

/** 
 * Data Direction Register for Port D (PD0-PD7)
 * 
 * In our setup:
 *   - PD0: LED (set as OUTPUT with DDRD |= 1)
 *   - PD3: Button (keep as INPUT, DDRD bit 3 = 0)
 */
extern volatile uint8_t DDRD;

/*============================================================================
 * Port Registers - Output (PORTn)
 * 
 * When pin is OUTPUT (DDR bit = 1):
 *   - PORT bit = 0: Drive pin LOW  (0V, GND)
 *   - PORT bit = 1: Drive pin HIGH (5V, Vcc)
 * 
 * When pin is INPUT (DDR bit = 0):
 *   - PORT bit = 0: Input is high-impedance (floating)
 *   - PORT bit = 1: Enable internal pull-up resistor (pin pulled to HIGH)
 * 
 * Example: PORTD = 1 drives PD0 HIGH (LED on if DDRD bit 0 is set)
 *============================================================================*/

/** Port A Output Register */
extern volatile uint8_t PORTA;

/** Port B Output Register */
extern volatile uint8_t PORTB;

/** Port C Output Register */
extern volatile uint8_t PORTC;

/** 
 * Port D Output Register
 * 
 * Common operations:
 *   PORTD |= 1;   // Set bit 0 (LED ON)
 *   PORTD &= ~1;  // Clear bit 0 (LED OFF)  
 *   PORTD ^= 1;   // Toggle bit 0
 */
extern volatile uint8_t PORTD;

/*============================================================================
 * Port Registers - Input (PINn)
 * 
 * Reading PINn returns the actual voltage level on each pin:
 *   - Bit = 0: Pin is at LOW voltage (0V)
 *   - Bit = 1: Pin is at HIGH voltage (5V)
 * 
 * For OUTPUT pins: reflects what you're driving
 * For INPUT pins: reflects external signal (or pull-up if enabled)
 * 
 * Example: if (PIND & 8) checks if PD3 is HIGH
 *          (8 = 0b00001000, bit 3)
 *============================================================================*/

/** Port A Input Register (read actual pin states) */
extern volatile uint8_t PINA;

/** Port B Input Register */
extern volatile uint8_t PINB;

/** Port C Input Register */
extern volatile uint8_t PINC;

/** 
 * Port D Input Register
 * 
 * Button check: ((PIND & 8) == 0) means button PRESSED
 * (Button pulls PD3 to GND when pressed, so bit 3 becomes 0)
 */
extern volatile uint8_t PIND;

/*============================================================================
 * Status Register (SREG)
 * 
 * Bit 7 (I): Global Interrupt Enable
 *   - Set with sei() to enable interrupts
 *   - Clear with cli() to disable interrupts
 *============================================================================*/

/** Status Register - bit 7 is Global Interrupt Enable */
extern volatile uint8_t SREG;

/*============================================================================
 * Bit Position Helpers
 * 
 * These make code more readable:
 *   DDRD |= (1 << PD0);   // Same as DDRD |= 1;
 *   PORTD |= (1 << PD0);  // Same as PORTD |= 1;
 *============================================================================*/

/* Port D pin positions */
#define PD0 0
#define PD1 1
#define PD2 2
#define PD3 3
#define PD4 4
#define PD5 5
#define PD6 6
#define PD7 7

/* Port A pin positions */
#define PA0 0
#define PA1 1
#define PA2 2
#define PA3 3
#define PA4 4
#define PA5 5
#define PA6 6
#define PA7 7

/* Port B pin positions */
#define PB0 0
#define PB1 1
#define PB2 2
#define PB3 3
#define PB4 4
#define PB5 5
#define PB6 6
#define PB7 7

/* Port C pin positions */
#define PC0 0
#define PC1 1
#define PC2 2
#define PC3 3
#define PC4 4
#define PC5 5
#define PC6 6
#define PC7 7

/*============================================================================
 * Convenience Macros for Common Operations
 *============================================================================*/

/** Set a bit: reg |= (1 << bit) */
#define _BV(bit) (1 << (bit))

/** Set bit in register */
#define sbi(reg, bit) ((reg) |= (1 << (bit)))

/** Clear bit in register */
#define cbi(reg, bit) ((reg) &= ~(1 << (bit)))

/*============================================================================
 * Simulator Internal - Main Function Renaming
 *============================================================================*/

int avr_main(void);
#define main avr_main

#endif /* AVR_SIM_H */
