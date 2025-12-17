#include <avr/io.h>

#define MAX 65535

int main(void) {

    DDRD |= (1<<PD0);
    PORTD |= (0<<PD0);

    volatile unsigned int i;

    while (1) {
        for (i = 0; i < MAX; i++);

        PORTD ^= (1<<PD0);
    }
}