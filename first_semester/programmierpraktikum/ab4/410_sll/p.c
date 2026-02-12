#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


// Struktur Song deklarieren

struct Song {
	char name[20];
	int duration;
	struct Song *pNext; 
};


// Deklaration der globalen Listen-Zeiger pFirst und pLast zur
// Speicherung der Adresse des ersten bzw. letzten Listen-Elements
struct Song *pFirst, *pLast;


void enter_songs_at_the_end()
{
	// Zeiger p auf Struktur Song deklarieren
	struct Song *p;

	while(1)
	{
		// Speicher für Struktur Song allozieren und Zeiger 
		// auf das erste Byte in Variable p ablegen
		p = malloc(sizeof(struct Song));
		if (p==NULL) return;



		// Lied-Name in Variable name der Song-Struktur einlesen
		printf("Name: ");
		scanf("%s", p->name);


		// Dauer in Variable Duration der Song-Struktur einlesen
		printf("Dauer: ");
		scanf("%d", &(p->duration));

		// Allozierten Speicher wieder freigeben und Endlos-Schleife 
		// verlassen, falls Dauer 0 eingegeben wurde
		if (p->duration == 0) {
			free(p);
			break;
		}

		// Wenn die Liste leer ist
		if (pFirst == NULL) {
			pFirst = pLast = p;
			p-> pNext = NULL;
		} else {
			pLast -> pNext = p;
			p-> pNext = NULL;
			pLast = p;
		}
	}
}


void print_all_songs()
{
	struct Song * p;

	for (p = pFirst; p; p = p->pNext) {
		printf("%s (%02d:%02d)\n", p->name, p->duration / 60, p->duration % 60);
	}
}

int main()
{
	pFirst = pLast = NULL;		// point nowhere
	
	enter_songs_at_the_end();
	print_all_songs();
}

