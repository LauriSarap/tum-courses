#include <stdio.h>	 // Funktionsdeklaration von printf und scanf
#include <math.h>	 // Funk.-Dekl. für cos aus der C-Standard-Bibliothek
#include "my_math.h" // Funktionsdeklaration unserer Funktionen
					 // (die in my_math.c implementiert sind)

int main()
{
	double d;

	printf("Zahl: ");
	scanf("%lf", &d);

	printf("my_sqrt: %.17lf\n", my_sqrt(d));	// unsere Funktion
	printf("sqrt:    %.17lf\n", sqrt(d));		// aus C-Standard-Bibliothek
}