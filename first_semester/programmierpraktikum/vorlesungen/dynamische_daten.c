#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p1, *p2;
    p1 = malloc(sizeof(int));
    p2 = malloc(sizeof(int));

    *p1 = 25;
    *p2 = *p1;
    *p2 = 30;

    printf("%i, %i", *p1, *p2);
}