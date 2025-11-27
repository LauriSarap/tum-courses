#include <stdio.h>

// Function to print a byte in binary
void print_binary(unsigned char n) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
    printf("\n");
}

int main() {
    unsigned char a;

    a = 156;
    printf("%i\n", a);
    printf("%x\n", a);
    print_binary(a);

    // Bit Nr 5. von Variable a setzen
    a = a | 0x20;
    printf("%i\n", a);
    printf("%x\n", a);
    print_binary(a);

    // Bit Nr. 7 von Variable a löschen
    // Bitmaske: 0111 1111
    a = a & 0x7F;
    printf("%i\n", a);
    printf("%x\n", a);
    print_binary(a);
}