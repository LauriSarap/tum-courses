#include <stdio.h>

int g;	// globale Variable

void f()
{
	printf("Wert von g: %d\n", g);
}

int main()
{
	printf("Wert eingeben: ");
	scanf("%d", &g);

	f();

	printf("Stack überschreiben\n");
	
	f();
}