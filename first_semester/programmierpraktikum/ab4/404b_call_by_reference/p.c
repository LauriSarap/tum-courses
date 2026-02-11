#include <stdio.h>

void f(int* a)
{
	*a = 2;
}

int main()
{
	int a = 1;

	f(&a);

	printf("Wert von a in main: %d\n", a);
}