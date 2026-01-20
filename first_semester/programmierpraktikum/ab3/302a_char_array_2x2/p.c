#include <stdio.h>

int main()
{
	char a[4][4][4];

	printf("&a[0][0][0]: %p\n", &a[0][0][0]);
	printf("&a[0][1][0]: %p\n", &a[0][1][0]);
	printf("&a[1][0][0]: %p\n", &a[1][0][0]);

	char b[2];
	printf("&b[0]: %p\n", &b[0]);
	printf("&b[1]: %p\n", &b[1]);

	// 0x16d8e2d58 + 4 = 0x16d8e2d5c
	// 0x16d8e2d58 + 16 = 0x16d8e2d68
	// 58 + 8 -> 60; 60 + 8 -> 68
}