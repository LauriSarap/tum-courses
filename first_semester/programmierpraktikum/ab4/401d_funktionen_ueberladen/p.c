#include <stdio.h>

int wert_verdoppeln(int a)
{
	return 2 * a;
}

double wert_verdoppeln(double a)
{
	return 2 * a;
}



int main()
{
	int wert;

	printf("Wert: ");
	scanf("%d", &wert);

	printf("Doppelter Wert: %d\n", wert_verdoppeln(wert) );
}
