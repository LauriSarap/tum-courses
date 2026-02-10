#include <stdio.h>

unsigned long fakultaet(unsigned long n)
{
	if(n == 0) return 1;

	else return n * fakultaet(n-1);
}

int main()
{
	int n;

	printf("n: ");
	scanf("%d", &n);

	if(n < 0) return -1;

	printf("%d! = %ld\n", n, fakultaet(n) );
}