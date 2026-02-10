#include <stdio.h>	 // Funktionsdeklaration von printf und scanf
#include <math.h>	 // Funk.-Dekl. für cos aus der C-Standard-Bibliothek
#include "my_math.h" // Funktionsdeklaration unserer Funktion
					 // (die in my_math.c implementiert sind)
int main()
{
	double d;

	printf("Zahl: ");
	scanf("%lf", &d);

	printf("my_cos: %.17lf\n", my_cos(d));	// unsere Funktion
	printf("cos:    %.17lf\n", cos(d));		// aus C-Standard-Bibliothek
}