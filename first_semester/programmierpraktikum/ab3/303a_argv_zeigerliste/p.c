#include <stdio.h>

int main(int argc, char * argv[])
{
	printf("argv: %p\n", argv);

	for(int i = 0; i <= argc; i++)
		printf("argv[%d]: %p\n", i, argv[i]);

	printf("\n");

	// Hier Code zur Ausgabe der Adressen angeben,
	// an denen die Zeiger der Zeigerliste stehen.



}