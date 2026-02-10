#include <stdio.h>

void f(void)
{



}

int main()
{
	int i, n;

	printf("Anzahl: ");
	scanf("%d", &n);

	for(i = 0; i < n; i++)
		f();
}