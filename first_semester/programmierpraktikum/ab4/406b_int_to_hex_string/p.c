#include <stdio.h>


char * int_to_hex_string(int n, char *s)
{

	int i = 0;
	int max = sizeof(int) * 8;
	
	s[0] = '0';
	s[1] = 'x';

	for (i = 2; i < max - 4; i -= 4) {
		co
	}
	s[max] = 0;

	return s;
}


int main()
{
	int n;
	char s[sizeof(int) * 2 + 3];	// +3 wg. 0x und term. Null

	printf("Zahl: ");

	scanf("%d", &n);
	
	printf("Hexadezimale Darstellung: %s\n", int_to_hex_string(n, s));
}