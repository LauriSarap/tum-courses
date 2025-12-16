/*
 * AVR ATmega1284p Simulator
 *
 * Drop-in replacement for <avr/io.h> that allows AVR code to run on a PC.
 * Simulates GPIO registers for learning purposes.
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

/*============================================================================
 * AVR Register Definitions
 *============================================================================*/

/* Data Direction Registers (0 = input, 1 = output) */
extern volatile uint8_t DDRA;
extern volatile uint8_t DDRB;
extern volatile uint8_t DDRC;
extern volatile uint8_t DDRD;

/* Port Output Registers */
extern volatile uint8_t PORTA;
extern volatile uint8_t PORTB;
extern volatile uint8_t PORTC;
extern volatile uint8_t PORTD;

/* Pin Input Registers */
extern volatile uint8_t PINA;
extern volatile uint8_t PINB;
extern volatile uint8_t PINC;
extern volatile uint8_t PIND;

/* Status Register (bit 7 = global interrupt enable) */
extern volatile uint8_t SREG;

/*============================================================================
 * Main Function Renaming
 *
 * This macro renames the user's main() to avr_main().
 * The simulator provides its own main() that sets up the UI,
 * then calls avr_main().
 *============================================================================*/

int avr_main(void); /* Forward declaration */

#define main avr_main

#endif /* AVR_SIM_H */
