#include <stdio.h>

int rekursive_summe(int n, int **n0, int **nn)
{













}

int main()
{
	int n;
	int *n0 = NULL, *nn = NULL;

	printf("n: ");
	scanf("%d", &n);

	if(n < 0) return -1;

	printf("Ergebnis: %d\n", rekursive_summe(n, &n0, &nn));
	printf("n0: %p\n", n0);
	printf("nn: %p\n", nn);
	printf("Stack-Distance: %ld Bytes\n", (void*) nn - (void*) n0);
}