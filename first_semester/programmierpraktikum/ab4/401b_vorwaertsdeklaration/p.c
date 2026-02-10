#include <stdio.h>

// Hier Vorwärts-Deklaration einfügen

int wert_verdoppeln(int);

int main()
{
	int wert;

	printf("Wert: ");
	scanf("%d", &wert);

	printf("Doppelter Wert: %d\n", wert_verdoppeln(wert) );
}

int wert_verdoppeln(int a)
{
	return 2 * a;
}