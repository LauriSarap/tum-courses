#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


// Struktur Song deklarieren
struct Song
{
	char name[20];
	int duration;
	struct Song *pNext;
};

// Deklaration der globalen Listen-Zeiger pFirst und pLast zur
// Speicherung der Adresse des ersten bzw. letzten Listen-Elements
struct Song *pFirst, *pLast;

void add_song_sorted_by_duration(struct Song *p)
{
	struct Song *p2;

	// Wenn die Liste leer ist
	if (pFirst == NULL) {
		pFirst = pLast = p;
		p->pNext = NULL;
		return;
	}
	// Liste ist nicht leer => In Schleife mit p2 die Liste durchlaufen

	for (p2 = pFirst; p2; p2 = p2->pNext){
		// Neues Element p vor dem ersten Element einfügen

		if (p2 == pFirst && p->duration < p2->duration){
			p -> pNext = pFirst;
			pFirst = p;
			break;
		}

		// Neues Element p irgendwo zwischen zwei Elementen einfügen

		else if (p2->pNext && p->duration < p2->pNext->duration){
			p-> pNext = p2->pNext;
			p2 ->pNext = p;
			break;
		}

		// Neues Element p am Schluss einfügen

		else if (p2->pNext == NULL){
			p2->pNext = p;
			p->pNext = NULL;
			pLast = p;
			break;
		}
	} // Schleife
}




struct Song* get_song()
{
	struct Song *p;

	p = malloc(sizeof(struct Song));

	if(p == NULL) return NULL;


	printf("Name: ");	
	scanf("%s", p->name);

	
	printf("Dauer: ");
	scanf("%d", &p->duration);

	return p;

}


void add_song_at_the_end(struct Song *p)
{
	// Wenn die Liste leer ist
	if (pFirst == NULL) {
		pFirst = pLast = p;
		p-> pNext = NULL;
	}
	else {
		pLast -> pNext = p;
		p->pNext = NULL;
		pLast = p;
		
	}

}

void add_song_at_the_beginning(struct Song *p)
{
	if (pFirst == NULL) {
		pFirst = pLast = p;
		p-> pNext = NULL;
	} else {
		p-> pNext = pFirst;
		pFirst = p;
	}
}

void print_all_songs()
{
	struct Song * p;

	for(p = pFirst; p; p = p->pNext)
	{
		printf("%s (%02d:%02d)\n", p->name, p->duration / 60, 
												p->duration % 60);
	}
}

int main()
{
	struct Song *p;

	pFirst = pLast = NULL;		// Liste explizit leer

	while(1)
	{
		p = get_song();

		if(p == NULL) return -1;		// Falls malloc fehlgeschlagen ist

		if(p->duration == 0)			// Abbruch wenn Song-Dauer = 0
		{
			free(p);
			break;
		}

		add_song_at_the_end(p);
		// add_song_at_the_beginning(p);
		// add_song_sorted_by_duration(p);
	}
	print_all_songs();
}
