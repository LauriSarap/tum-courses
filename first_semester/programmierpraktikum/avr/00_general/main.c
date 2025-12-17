#include <avr/io.h>

int main(void) {

    DDRD |= (1<<PD0);

    if (sizeof(int) == 2) {
        PORTD = 1;
    }
    else {
        PORTD = 0;
    }

    while(1);
}
