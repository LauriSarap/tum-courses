#include <avr/io.h>

#define SET_LED_ON   (PORTD |= (1 << PD0))
#define SET_LED_OFF  (PORTD &= ~(1 << PD0))
#define TOGGLE_LED   (PORTD ^= (1 << PD0))

int main(void) {
    DDRD |= (1 << PD0);
    
    SET_LED_ON;

    return 0;
}