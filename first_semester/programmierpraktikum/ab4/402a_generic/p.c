#include <stdio.h>

// Makro wert_verdoppeln(x) mit _Generic-Ausdruck





// Funktion zum Verdoppeln von Integer-Werten





// Funktion zum Verdoppeln von Double-Werten





int main()
{
	int wert_int;
	double wert_double;

	printf("Integer-Wert: ");
	scanf("%d", &wert_int);

	printf("Double-Wert: ");
	scanf("%lf", &wert_double);

	printf("Doppelter Integer-Wert: %d\n", wert_verdoppeln(wert_int) );
	printf("Doppelter Double-Wert: %.2lf\n", wert_verdoppeln(wert_double) );
}
