#include <stdio.h>

int main()
{
	int a[4][4][4];

	printf("&a[0][0][0]: %p\n", &a[0][0][0]);
	printf("&a[0][1][0]: %p\n", &a[0][1][0]);
	printf("&a[1][0][0]: %p\n", &a[1][0][0]);

	// 0x16d5e2c88 + 16 = 0x16d5e2c98
	// 0x16d5e2c88 + 64 = 0x16d5e2cc8
}