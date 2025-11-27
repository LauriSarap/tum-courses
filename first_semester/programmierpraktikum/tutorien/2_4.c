#include <math.h>
#include <stdio.h>

int main() {
    double a, b, c, d;

    printf("a: ");
    scanf("%lf", &a);

    printf("b: ");
    scanf("%lf", &b);

    printf("c: ");
    scanf("%lf", &c);

    d = b * b - 4 * a * c;

    // 1 reelle Lösung
    if (d == 0.0)
        printf("Die doppelte Nullstelle lautet %.2lf.\n", -b / (2 * a));

    // 2 reelle Lösungen
    else if (d > 0)
        printf("Die beiden reellen Loesungen sind %.2lf und %.2lf.\n", (-b + sqrt(d)) / (2 * a),
               (-b - sqrt(d)) / (2 * a));

    else // keine reelle Lösung
        printf("Es gibt keine reelle Loesung.\n");
}