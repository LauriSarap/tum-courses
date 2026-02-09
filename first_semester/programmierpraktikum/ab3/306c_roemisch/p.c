#include <ctype.h>
#include <stdio.h>

int main()
{
	char rds[15];
	unsigned int sum = 0;
	int last_chunk = 4000;
	char prev = '\0';
	int repeat = 0;

	printf("Römische Zahl: ");
	if (scanf("%14s", rds) != 1) {
		return 0;
	}

	for (int i = 0; rds[i]; i++) {
		rds[i] = toupper((unsigned char)rds[i]);
	}

	for (int i = 0; rds[i]; ) {
		int value = 0;
		int next_value = 0;

		switch (rds[i]) {
			case 'M': value = 1000; break;
			case 'D': value = 500; break;
			case 'C': value = 100; break;
			case 'L': value = 50; break;
			case 'X': value = 10; break;
			case 'V': value = 5; break;
			case 'I': value = 1; break;
			default: return 0;
		}

		if (rds[i] == prev) {
			repeat++;
			if (!(rds[i] == 'I' || rds[i] == 'X' || rds[i] == 'C' || rds[i] == 'M') || repeat > 4) {
				return 0;
			}
		} else {
			prev = rds[i];
			repeat = 1;
		}

		if (rds[i + 1]) {
			switch (rds[i + 1]) {
				case 'M': next_value = 1000; break;
				case 'D': next_value = 500; break;
				case 'C': next_value = 100; break;
				case 'L': next_value = 50; break;
				case 'X': next_value = 10; break;
				case 'V': next_value = 5; break;
				case 'I': next_value = 1; break;
				default: return 0;
			}
		}

		if (next_value && value < next_value) {
			if (!((rds[i] == 'I' && (rds[i + 1] == 'V' || rds[i + 1] == 'X')) ||
				(rds[i] == 'X' && (rds[i + 1] == 'L' || rds[i + 1] == 'C')) ||
				(rds[i] == 'C' && (rds[i + 1] == 'D' || rds[i + 1] == 'M'))) || repeat > 1) {
				return 0;
			}
			if (next_value - value > last_chunk) {
				return 0;
			}
			sum += next_value - value;
			last_chunk = next_value - value;
			prev = rds[i + 1];
			repeat = 1;
			i += 2;
			continue;
		}

		if (value > last_chunk) {
			return 0;
		}
		sum += value;
		last_chunk = value;
		i++;
	}

	printf("Der Wert ist %d.\n", sum);
	return 0;
}
