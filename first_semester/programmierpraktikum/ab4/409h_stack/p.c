#include <stdio.h>
#include <time.h>
#include <unistd.h>

void rekursiv(int n)
{
	struct timespec ts = { .tv_sec = 0, .tv_nsec = 100000000};	// 100 ms

	char page[4020];			// ergibt insgesamt genau 4096 Byte/4k page

	nanosleep(&ts, NULL);		// 100 ms warten

	printf("Seiten: %4d - Adresse: %p\n", n, page);

	rekursiv(n+1);				// rekursiver Aufruf
}

int main()
{
	printf("30 Sekunden warten ...\n");

	struct timespec ts = { .tv_sec = 30, .tv_nsec = 0}; 	// 30 Sekunden
	nanosleep(&ts, NULL);		// 30 s warten
	
	rekursiv(1);
}