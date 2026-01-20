#include <stdio.h>

int main()
{
	char a[4][4][4];

	printf("&a[0][0][0]: %p\n", &a[0][0][0]);
	printf("&a[0][1][0]: %p\n", &a[0][1][0]);
	printf("&a[1][0][0]: %p\n", &a[1][0][0]);
}