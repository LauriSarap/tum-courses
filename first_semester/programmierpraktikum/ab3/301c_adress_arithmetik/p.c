#include <stdio.h>

int main()
{
	int a[] = {0x01234567, 0x89ABCDEF};

	printf("\n");
	printf("&a[0] = %p\n", &a[0]);
	printf("&a[1] = %p\n\n", &a[1]);
	printf("a     = %p\n", a);
	printf("a+1   = %p\n\n", a+1);

	printf("&a[1] - &a[0] = %ld\n\n", &a[1] - &a[0]);
}