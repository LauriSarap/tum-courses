/*
 * AVR Simulator - Drop-in replacement for <avr/io.h>
 * 
 * This allows AVR code to compile and run on a regular PC.
 * Include this instead of the real avr/io.h when using the simulator.
 */

#ifndef _AVR_IO_H_
#define _AVR_IO_H_

/* Include the main simulator header with all definitions */
#include "../avr_sim.h"

/*
 * Note: On real AVR hardware, <avr/io.h> includes chip-specific
 * definitions based on the -mmcu flag passed to avr-gcc.
 * 
 * This simulator provides a simplified subset for the ATmega1284p
 * that covers exercises 1-4 (GPIO operations).
 */

#endif /* _AVR_IO_H_ */
