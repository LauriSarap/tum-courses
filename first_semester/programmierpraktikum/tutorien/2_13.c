#include <stdio.h>

int main() {

    printf("Geben Sie als Radius 0 ein, um das Programm zu beenden.\n");

    const double PI = 3.14159; // Kreiskonstante pi
    double r = 1.0;            // Radius der Kugel
    double A = 0.0;            // Oberfläche der Kugel
    double V;

    while (r != 0) {

        /* Radius vom Benutzer einlesen */
        printf("Kugelradius: ");
        scanf("%lf", &r);

        if (r == 0) {
            break;
        }

        /* Berechnungen durchführen */
        A = 4.0 * PI * r * r;
        V = 4. / 3. * PI * r * r * r;

        /* Ausgabe des Ergebnisses */
        printf("Radius: %.2lf\n", r);
        printf("Oberflaeche: %.2lf\n", A);
        printf("Volumen: %.2lf\n", V);
    }
}