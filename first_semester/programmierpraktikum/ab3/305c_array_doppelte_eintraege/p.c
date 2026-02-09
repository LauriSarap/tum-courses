#include <stdio.h>
#include <stdbool.h>

int main()
{
	int a[700];
	int n = 0;
	unsigned int i, j;
	unsigned short found = 0;

	while (n < 700) {
		printf("Matrikelnummer: ");
		scanf("%i", &a[n]);
		if (a[n] == 0) {
			break;
		}
		n++;
	}

	for (i = 0; i < n; i++) {
		found = 0;
		for (j = 0; j < i; j++) {
			if (a[i] == a[j]) {
				found = 1;
			}
		}
		if (found == 0) {
			printf("%i\n", a[i]);
		}
	}

}
