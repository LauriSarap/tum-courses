#include <stdio.h>

typedef struct Song
{
	char name[20];
	int duration;
} Song;


int main()
{

	Song s[100];
	int i, l;

	for (i = 0; i < 100; i++) {
		printf("Name: ");
		scanf("%s", s[i].name);

		printf("Duration: ");
		scanf("%d", &(s[i].duration));

		if (s[i].duration == 0) break;
	}

	for (l = 0; l < i; l++) {
		printf("%s (%02d:%02d)\n", s[l].name, s[l].duration/60, s[l].duration%60);
	}
}