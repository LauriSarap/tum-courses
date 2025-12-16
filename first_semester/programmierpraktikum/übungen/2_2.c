#include <stdio.h>

int main() {
    char zeichen = 0;

    printf("Einstellige roemische Ziffer: ");
    scanf(" %c", &zeichen);

    switch (zeichen) {
        case 'I':
            printf("Der Wert betraegt 1.\n");
            break;
        case 'V':
            printf("Der Wert betraegt 5.\n");
            break;
        case 'X':
            printf("Der Wert betraegt 10.\n");
            break;
        case 'L':
            printf("Der Wert betraegt 50.\n");
            break;
        case 'C':
            printf("Der Wert betraegt 100.\n");
            break;
        case 'D':
            printf("Der Wert betraegt 500.\n");
            break;
        case 'M':
            printf("Der Wert betraegt 1000.\n");
            break;
        default:
            printf("Es wurde keine roemische Ziffer eingegeben.\n");
    }
}