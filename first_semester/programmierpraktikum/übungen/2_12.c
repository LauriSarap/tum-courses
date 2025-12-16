#include <stdio.h>

int main() {
    char antwort = 'd';

    for (int i = 0; i < 1000000; i++) {
        printf("\n");
        printf("Menue\n");

        printf("a)  Mensa Innenstadt\n");
        printf("b)  Steinheil\n");
        printf("c)  Thai Magie\n");
        printf("d)  Beenden\n");
        printf("\n");

        printf("Bitte waehlen Sie eine Aktion aus: ");
        scanf(" %c", &antwort);

        if (antwort == 'a' || antwort == 'A') {
            printf("Es gibt Krautspaetzle. Verdauungsschlaf am Nachmittag.\n");
        } else if (antwort == 'b' || antwort == 'B') {
            printf("Grosses Schnitzel mit Bratkartoffeln.\n");
        } else if (antwort == 'c' || antwort == 'C') {
            printf("Menue 503. Es lebe die Mikrowelle.\n");
        } else if (antwort == 'd' || antwort == 'D') {
            break;
        }
    }
}