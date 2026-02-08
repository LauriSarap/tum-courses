#include <stdio.h>

int main(int argc, char * argv[])
{
	char eingabe[21] = "ABCDEFGHIJKLMNOPQRST";
	int l;

	printf("Bitte geben Sie einen Text ein: ");
	scanf("%20s", eingabe);

	// Hier Länge der Zeichenkette bestimmen und in 
	// Variable l ablegen.
	l = 0;
	while (eingabe[l]) {
		l++;
	}
	printf("\nLänge: %d\n", l);
}