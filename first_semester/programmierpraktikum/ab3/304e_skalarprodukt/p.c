#include <stdio.h>

void read(double vektor[3]) {
	for (int i = 0; i < 3; i++) {
		printf("Element %i: ", i+1);
		scanf("%lf", &vektor[i]);
	}
	printf("\n");
}

int main()
{
	printf("Erster Vektor\n");
	double vektor1[3];
	read(vektor1);

	printf("Zweiter Vektor\n");
	double vektor2[3];
	read(vektor2);

	unsigned int i;
	double sum = 0;
	for (i = 0; i < 3; i++) {
		sum += vektor1[i] * vektor2[i];
	}

	printf("Das Skalarprodukt beträgt %.2lf.\n", sum);
}
