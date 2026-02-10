#include <stdio.h>

int a, b, c;	// globale Variable

void f(int a)
{
	int b;

	a = 4;		// referenziert ausschließlich lokalen Parameter a
	b = 5;		// referenziert ausschließlich lokale Variable b
	c = 6;		// referenziert globale Variable c
}

int main()
{
	a = 1;
	b = 2;
	c = 3;

	f(a);

	printf("a: %d\n", a);	// 1
	printf("b: %d\n", b);	// 2
	printf("c: %d\n", c);	// 6
}