#include <stdio.h>

void f(int b, int a)
{
	printf("a: %d\n", a);
	printf("b: %d\n", b);
}

int main()
{
	int a = 1, b = 2;

	f(a, b);
}