#include <stdio.h>


char * int_to_hex_string(int n, char *s)
{



















}


int main()
{
	int n;
	char s[sizeof(int) * 2 + 3];	// +3 wg. 0x und term. Null

	printf("Zahl: ");

	scanf("%d", &n);
	
	printf("Hexadezimale Darstellung: %s\n", int_to_hex_string(n, s));
}