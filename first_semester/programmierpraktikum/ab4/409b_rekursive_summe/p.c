#include <stdio.h>

int rekursive_summe(int n)
{

	if (n == 0) return 0;
	
	return n + (rekursive_summe(n-1));
}

int main()
{
	int n;

	printf("n: ");
	scanf("%d", &n);

	if(n < 0) return -1;

	printf("Ergebnis: %d\n", rekursive_summe(n));
}