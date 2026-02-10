#include <stdio.h>

int rekursive_summe(int n)
{



}

int main()
{
	int n;

	printf("n: ");
	scanf("%d", &n);

	if(n < 0) return -1;

	printf("Ergebnis: %d\n", rekursive_summe(n));
}