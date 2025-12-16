/*
 * AVR Simulator - Drop-in replacement for <avr/interrupt.h>
 * Interrupt support will be added later.
 */

#ifndef _AVR_INTERRUPT_H_
#define _AVR_INTERRUPT_H_

#include "../avr_sim.h"

// Interrupt Service Routine macro - stub for now
// Will be expanded later for full interrupt support
#define ISR(vector)                                                                                \
    void vector##_handler(void) __attribute__((unused));                                           \
    void vector##_handler(void)

// Global interrupt control (stubs for now)
#define sei() (SREG |= 0x80)
#define cli() (SREG &= ~0x80)

// Interrupt vectors (stubs)
#define INT0_vect INT0
#define INT1_vect INT1
#define TIMER0_OVF_vect TIMER0_OVF
#define TIMER1_OVF_vect TIMER1_OVF

#endif /* _AVR_INTERRUPT_H_ */
