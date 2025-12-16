#include <stdio.h>


int main()
{
	const double PI = 3.14159;	// Kreiskonstante pi
	double r = 0.0;				// Radius der Kugel
	double A = 0.0;				// Oberfläche der Kugel

	// Radius vom Benutzer einlesen
	printf("Kugelradius: ");
	scanf("%lf", &r);

	// Oberfläche berechnen
	A = 4.0 * PI * r * r;

	// Hier Code zur Volumenberechnung angeben
    double V;
	V = 4.0 / 3.0 * PI * r * r * r;

	// Ausgabe des Ergebnisses
	printf("Radius: %.2lf\n", r);
	printf("Oberflaeche: %.2lf\n", A);
    printf("Volumen: %.2lf\n", V);

}