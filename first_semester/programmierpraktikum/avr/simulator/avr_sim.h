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
 * SOLUTION: Use AVR_STRICT_TYPES mode or the avr_* type aliases below.
 *============================================================================*/

/*============================================================================
 * AVR-Compatible Type Aliases
 * 
 * Use these to get true AVR behavior in the simulator:
 *   avr_int    = int16_t   (signed 16-bit,   -32768 to 32767)
 *   avr_uint   = uint16_t  (unsigned 16-bit, 0 to 65535)
 *   avr_long   = int32_t   (signed 32-bit)
 *   avr_ulong  = uint32_t  (unsigned 32-bit)
 *   avr_char   = int8_t    (signed 8-bit)
 *   avr_uchar  = uint8_t   (unsigned 8-bit)
 *============================================================================*/

typedef int8_t   avr_char;
typedef uint8_t  avr_uchar;
typedef int16_t  avr_int;
typedef uint16_t avr_uint;
typedef int32_t  avr_long;
typedef uint32_t avr_ulong;

/*============================================================================
 * How to Experience AVR Overflow Issues in the Simulator
 * 
 * To reproduce exercise 2.6 problems, replace standard types with AVR types:
 * 
 *   INSTEAD OF:                    USE:
 *   volatile int i;                volatile avr_int i;
 *   volatile unsigned int i;       volatile avr_uint i;
 *   volatile long i;               volatile avr_long i;
 *   volatile unsigned long i;      volatile avr_ulong i;
 * 
 * Example for exercise 2.6:
 *   #define MAX 33000
 *   volatile avr_int i;           // Will overflow! (max 32767)
 *   for (i = 0; i < MAX; i++);    // Infinite loop - never reaches 33000
 * 
 *   volatile avr_uint i;          // Works up to 65535
 *   for (i = 0; i < MAX; i++);    // This works!
 * 
 *   #define MAX 65536
 *   volatile avr_uint i;          // Will overflow! (max 65535)  
 *   for (i = 0; i < MAX; i++);    // Infinite loop - 65535+1 wraps to 0
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
 * Cycle-Accurate Simulation (Exercise 2.6h)
 * 
 * LIMITATION: There is NO way in standard C to intercept "i++" on a local
 * variable and add type-specific delays. Your PC executes 16-bit and 32-bit 
 * increments in the same time - the timing difference is a hardware property
 * of the 8-bit AVR that cannot be simulated without changing code.
 * 
 * MINIMAL CODE CHANGE: Replace "i++" with "INC(i)" in your for loop:
 * 
 *   for (i = 0; i < MAX; INC(i));
 * 
 * INC() uses C11 _Generic to auto-detect avr_uint vs avr_ulong and adds
 * proportional delays (32-bit is 2x slower, just like on real AVR).
 *============================================================================*/

/* Busy-wait to simulate AVR cycle cost */
static inline void _avr_delay_16(void) {
    for (volatile int j = 0; j < 80; j++) __asm__ volatile("");
}
static inline void _avr_delay_32(void) {
    for (volatile int j = 0; j < 160; j++) __asm__ volatile("");  /* 2x slower */
}

/* Type-generic increment with AVR-accurate cycle delays */
#define INC(x) (_Generic((x), \
    avr_ulong:  (_avr_delay_32(), (x)++), \
    avr_long:   (_avr_delay_32(), (x)++), \
    default:    (_avr_delay_16(), (x)++) \
))

/*============================================================================
 * Simulator Internal - Main Function Renaming
 *============================================================================*/

int avr_main(void);
#define main avr_main

#endif /* AVR_SIM_H */
