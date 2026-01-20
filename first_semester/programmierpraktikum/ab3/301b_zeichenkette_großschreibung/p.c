#include <stddef.h>
#include <stdio.h>

int main()
{
    char zeichenkette[] = "Heute ist ein guter Tag!";

    for (size_t i = 0; i < sizeof(zeichenkette); i++) {

        if (zeichenkette[i] >= 'a' && zeichenkette[i] <= 'z') {
            zeichenkette[i] = zeichenkette[i] - ('a' - 'A');
        }
    }

    printf("%s\n", zeichenkette);
    printf("%i", ('a' - 'A'));
}