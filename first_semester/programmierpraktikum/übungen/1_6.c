#include <stdio.h>

int main() {

    char a = 'A';

    printf("%lu\n", sizeof(a));
    printf("Hex: 0x%02x\n", a);
    printf("Decimal: %d\n", a);
    printf("Binary: ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (a >> i) & 1);
    }
    printf("\n");

    return 0;
}