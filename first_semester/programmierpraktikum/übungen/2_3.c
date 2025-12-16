#include "stdio.h"
#include <math.h>

int main() {

    double a = 0;
    double b = 0;
    double c = 0;

    printf("a: ");
    scanf(" %lf", &a);
    printf("b: ");
    scanf(" %lf", &b);
    printf("c: ");
    scanf(" %lf", &c);

    double determinant = b * b - 4 * a * c;

    if (determinant < 0) {
        printf("Es gibt keine reelle Loesung.");
    } else if (determinant == 0) {
        double x1_2 = -b / (2 * a);
        printf("Die doppelte Nullstelle lautet %.2lf.", x1_2);
    } else {
        double x1 = (-b + sqrt(determinant)) / (2 * a);
        double x2 = (-b - sqrt(determinant)) / (2 * a);
        printf("Die beiden reellen Loesungen sind %.2lf und %.2lf.", x1, x2);
    }

    return 0;
}