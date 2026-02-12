#include <stdio.h>

void f(void)
{
	static int i = 0;
	printf("Wert von i: %i\n", i++);
}

int main()
{
	int i, n;

	printf("Anzahl: ");
	scanf("%d", &n);

	for(i = 0; i < n; i++)
		f();
}