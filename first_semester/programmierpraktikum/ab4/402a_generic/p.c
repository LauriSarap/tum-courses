#include <stdio.h>

// Makro wert_verdoppeln(x) mit _Generic-Ausdruck
#define wert_verdoppeln(x) _Generic ((x), int: wert_werdoppeln_int, double: wert_werdoppeln_double )(x)

int wert_werdoppeln_int(int x) {
	return 2*x;
}

double wert_werdoppeln_double(double x) {
	return 2*x;
}


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
