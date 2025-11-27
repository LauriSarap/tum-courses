#include <stdio.h>

int main() {
    int i = 0;
    int benutzerZahl = 0;

    printf("Ganze Zahl: ");
    scanf("%i", &benutzerZahl);

    for (i = benutzerZahl; i <= 33; i++) {
        printf(" %2i", i);
    }

    printf("\n");
}
