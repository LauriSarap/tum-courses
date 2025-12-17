#include <avr/io.h>

int main(void) {
    DDRD |= (1 << PD0);
    PORTD = 0xFE;

    char i = 'f';

    while(1) {
        if (!((1 << PD3) & PIND)) {
            if (i == 'f') {
                PORTD ^= (1<<PD0);
                i = 'o';
            }
        } else {
            i = 'f';
        }
    }
}