#include <stdio.h>

int main() {
    int *p = NULL;
    printf("Trying to read address 0...\n");
    printf("%d\n", *p); // This is the "Illegal Access"
    return 0;
}