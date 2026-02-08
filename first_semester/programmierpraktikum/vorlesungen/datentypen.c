#include <stdio.h>

int main() {

    float a = 2.0;
    int b = 2;
    short c = 5.0;
    long d = 6.0;

    char e = 'e';
    char ee[] = "Hallo";

    printf("Size of float: %lu\n", sizeof(a));
    printf("Size of int: %lu\n", sizeof(b));
    printf("Size of short: %lu\n", sizeof(c));
    printf("Size of long: %lu\n", sizeof(d));
    printf("Size of char: %lu\n", sizeof(e));
    printf("Size of char array: %lu\n", sizeof(ee));

    return 0;
}