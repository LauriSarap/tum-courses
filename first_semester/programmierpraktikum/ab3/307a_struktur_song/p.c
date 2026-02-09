#include <stdio.h>

// Strukturdefinition
typedef struct Song {
	char name[20];
	int duration;
} Song;

int main()
{
	Song s;


	printf("Name: ");
	scanf("%s", s.name);

	printf("Duration: ");
	scanf("%i", &(s.duration));

	int minutes = s.duration / 60;
	int seconds = s.duration % 60;
	printf("%s (%02d:%02d)\n", s.name, minutes, seconds);
}
