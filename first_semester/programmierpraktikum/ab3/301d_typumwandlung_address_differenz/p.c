#include <stdio.h>

int main()
{
	int a[] = {0x01234567, 0x89ABCDEF};

	long int d;

	// Berechnung der Differenz in Speicherstellen/Bytes
	d = (void*) &a[1] - (void*) &a[0];


	printf("Differenz &a[1] - &a[0] in Speicherstellen/Bytes: %ld\n", d);
}