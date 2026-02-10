#include <stdio.h>


void f(int a)
{
	int b;

	printf("Wert von b: %d\n", b);	// Wert von b nicht definiert

	b = a;
}

int main()
{
	int a, b;

	printf("Wert eingeben: ");
	scanf("%d", &a);

	f(a);
	f(a);
}