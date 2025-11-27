#include <stdio.h>

int main() {
    printf("Bitte geben Sie die Obergrenze ein: ");
    int g = 0;
    scanf(" %i", &g);

    for (int i = 2; i <= g; i++) {
        int count = 0;
        for (int j = 1; j <= i; j++) {
            int remainder = i % j;
            if (remainder == 0) {
                count++;
            }
        }

        if (count <= 2) {
            printf("%5i", i);
        }
    }

    return 0;
}