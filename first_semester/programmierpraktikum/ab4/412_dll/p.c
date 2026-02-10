#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


// Struktur Song deklarieren
struct Song
{




};

// Deklaration der globalen Listen-Zeiger pFirst und pLast zur
// Speicherung der Adresse des ersten bzw. letzten Listen-Elements





void get_song(struct Song **p)
{
	// Zur Laufzeit Speicher für einen Song allozieren und den Zeiger auf
	// diesen Speicher in der Variable p des Funktionsaufrufers
	// (der Hauptfunktion main) ablegen


	// Zurückspringen, falls Speicher nicht zugewiesen werden konnte


	printf("Name: ");
	
	// Name in die Variable "name" der allozierten Struktur einlesen;
	// dabei sollen auch Namen mit Leerzeichen wie z.B. "Mein Song" 
	// eingelesen weden können


	
	printf("Dauer: ");

	// Dauer in die Variable "dauer" der allozierten Struktur einlesen
	// Würde hier mit scanf eingelesen werden, würde das \n im Puffer
	// bleiben und beim nächsten Aufruf von fgets beim Einlesen des
	// Namens als Zeile eingelesen werden. Deswegen muss die Dauer
	// ebenfalls mit fgets eingelesen werden, damit das \n konsumiert 
	// wird und aus dem Puffer verschwindet
	// Hinweis: mit atoi (Ascii to Integer) kann eine Zeichenkette aus
	// Ziffern in eine Zahl umgewandelt werden



}


void add_song_at_the_end(struct Song *p)
{
	// Wenn die Liste leer ist






	// Sonst, wenn die Liste nicht leer ist







}

void add_song_at_the_beginning(struct Song *p)
{
	// Wenn die Liste leer ist






	// Wenn die Liste nicht leer ist







}

void print_all_songs()
{
	struct Song * p;

	for(p = pFirst; p; p = p->pNext)
	{
		if(p->duration < 3600)
			printf("%s (%02d:%02d)\n", p->name, p->duration / 60, 
													p->duration % 60);
		else
			printf("%s (%02d:%02d:%02d)\n", p->name, p->duration / 3600, 
												p->duration % 3600 / 60, 
												p->duration % 60);
	}
}


void print_all_songs_reverse_order()
{
	struct Song * p;

	for(p = pLast; p; p = p->pPrevious)
	{
		if(p->duration < 3600)
			printf("%s (%02d:%02d)\n", p->name, p->duration / 60, 
													p->duration % 60);
		else
			printf("%s (%02d:%02d:%02d)\n", p->name, p->duration / 3600, 
												p->duration % 3600 / 60, 
												p->duration % 60);
	}
}


void add_song_sorted_by_duration(struct Song *pNew)
{
	struct Song *p;

	// Liste solange durchlaufen wie die Dauer des neuen Elements pNew
	// größer ist als die Dauer des aktuellen Listenelement p


	// Fall A: 
	// Die Liste ist leer







	// Fall B:
	// Die Liste ist nicht leer und bereits das erste Listenelement
	// ist größer als pNew => pNew vor dem ersten Element einfügen









	// Fall C:
	// Die Liste ist nicht leer und es wurde die komplette Liste durch-
	// laufen, ohne ein Element zu finden dessen Dauer größer als die
	// Dauer des neuen Elements pNew ist => pNew hinten anfügen









	// Fall D:
	// Sonst, d.h. die Liste ist nicht leer und das neue Listenelement 
	// pNew musste weder vorne noch hinten angefügt werden 
	// => pNew irgendwo in der Mitte vor dem Element p einfügen








}









int main()
{
	struct Song *p;

	while(1)
	{
		get_song(&p);

		if(p == NULL) return -1;	// Fehler bei malloc

		if(p->duration == 0)		// Abbruch
		{
			free(p);
			break;
		}

		add_song_at_the_end(p);
		// add_song_at_the_beginning(p);
		// add_song_sorted_by_duration(p);
	}
	print_all_songs();
	// print_all_songs_reverse_order();
}
