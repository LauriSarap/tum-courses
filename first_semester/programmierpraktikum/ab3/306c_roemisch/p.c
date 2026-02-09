#include <stdio.h>

int main()
{

	char rds[15];
	int vs[15] = {0};
	unsigned int sum = 0;
	unsigned short l; 
	
	// Römische Zahl einlesen
	scanf("%s", rds);

	for (int i = 0; rds[i]; i++) {
		if (i == 14) {

		} else if (rds[i+1] == 'M' && rds[i] == 'C') {
			vs[i] = 900;
			l++;
			continue;
		} else if (rds[i+1] == 'D' && rds[i] == 'C') {
			vs[i] = 400;
			l++;
			continue;
		} else if (rds[i+1] == 'C' && rds[i] == 'X') {
			vs[i] = 90;
			l++;
			continue;
		} else if (rds[i+1] == 'L' && rds[i] == 'X') {
			vs[i] = 40;
			l++;
			continue;
		} else if (rds[i+1] == 'X' && rds[i] == 'I') {
			vs[i] = 9;
			l++;
			continue;
		} else if (rds[i+1] == 'V' && rds[i] == 'I') {
			vs[i] = 4;
			l++;
			continue;
		}

		if (i == 0) {

		} else if (rds[i] == 'M' && rds[i-1] == 'C') {
			continue;
		} else if (rds[i] == 'D' && rds[i-1] == 'C') {
			continue;
		} else if (rds[i] == 'C' && rds[i-1] == 'X') {
			continue;
		} else if (rds[i] == 'L' && rds[i-1] == 'X') {
			continue;
		} else if (rds[i] == 'X' && rds[i-1] == 'I') {
			continue;
		} else if (rds[i] == 'V' && rds[i-1] == 'I') {
			continue;
		}

		switch (rds[i]){
			case ('M'): vs[i] = 1000;
				break;
			case ('D'): vs[i] = 500;
				break;
			case ('C'): vs[i] = 100;
				break;
			case ('L'): vs[i] = 50;
				break;
			case ('X'): vs[i] = 10;
				break;
			case ('V'): vs[i] = 5;
				break;
			case ('I'): vs[i] = 1;
				break;
			default: return 0;
				break;
		}
		l++;
	}

	for (int i = 0; i < l+1; i++) {
		sum += vs[i];
	}

	printf("Der Wert ist %d.\n", sum);
	return 0;
}
