#include <stdio.h>

int main()
{
	char a[2][2];

	printf("&a[0][0]: %p\n", &a[0][0]);
	printf("&a[0][1]: %p\n", &a[0][1]);
	printf("&a[1][0]: %p\n", &a[1][0]);
	printf("&a[1][1]: %p\n", &a[1][1]);
}