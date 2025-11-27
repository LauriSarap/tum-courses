#include <stdio.h>

int main() {

    printf("Geben Sie bitte eine Dezimalzahl ein: ");

    int a = 0;
    scanf(" %i", &a);

    printf("Die zugehoerige Binaerzahl lautet: ");

    for (int i = 31; i >= 0; i--) {
        int bit = (a >> i) & 0x00000001;
        printf("%d", bit);
    }
    printf("\n");

    return 0;
}