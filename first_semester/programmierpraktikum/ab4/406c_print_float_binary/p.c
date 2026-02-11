#include <stdio.h>
#include <string.h>

void print_float_binary(float f)
{

	int i, max;

	max = sizeof(float) * 8 - 1;

	for (i = max; i>= 0; i--) {
		printf("%d", (*((int*)(&f)) >> i) & 1);
		if (i == max || i == max - 8) {
			printf(" ");
		}
	}
}

int main()
{
	float f;
	
	printf("Zahl: ");

	scanf("%f", &f);
	
	printf("Binäre Darstellung: ");

	print_float_binary(f);

	printf("\n");
}