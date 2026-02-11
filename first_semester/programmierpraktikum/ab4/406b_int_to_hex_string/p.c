#include <stdio.h>


char * int_to_hex_string(int n, char *s)
{

	int i = 0;
	int tmp;
	int max = sizeof(int) * 8;
	int total_hexa_digits = max/4;
	
	s[0] = '0';
	s[1] = 'x';

	for (i = 0; i < total_hexa_digits; i += 1) {
		int shift_amount = max - 4 - (i*4);

		tmp = (n >> shift_amount) & 0xF;
		if (tmp <= 9) {
			s[i+2] = tmp + '0';
		} else {
			s[i+2] = tmp + 'a' - 10;
		}
	}


	s[total_hexa_digits + 2] = '\0';

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