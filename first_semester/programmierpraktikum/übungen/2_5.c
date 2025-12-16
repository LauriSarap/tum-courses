#include <stdio.h>

int main() {

    int j = 0;

    int istSchaltjahr = 0;

    printf("Jahreszahl: ");
    scanf("%i", &j);

    if (j == 0) {
        istSchaltjahr = 0;
    } else if (j % 400 == 0) {
        istSchaltjahr = 1;
    } else if (j % 100 == 0) {
        istSchaltjahr = 0;
    } else if (j % 4 == 0) {
        istSchaltjahr = 1;
    }

    // Ausgabe
    if (istSchaltjahr)
        printf("%i war ein Schaltjahr.\n", j);
    else
        printf("%i war kein Schaltjahr.\n", j);
}