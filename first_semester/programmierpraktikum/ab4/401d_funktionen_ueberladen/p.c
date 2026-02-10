#include <stdio.h>

int wert_verdoppeln_int(int a)
{
	return 2 * a;
}

double wert_verdoppeln_double(double a)
{
	return 2 * a;
}


int main()
{
	int wert;

	printf("Wert: ");
	scanf("%d", &wert);

	printf("Doppelter Wert: %d\n", wert_verdoppeln_int(wert) );
}
