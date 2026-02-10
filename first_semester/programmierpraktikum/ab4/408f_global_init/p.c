#include <stdio.h>

long a;			// wird implizit mit 0 initialisiert
long b = 1;		// wird explizit mit 1 initialisiert

int main()
{
	long c;		// wird nicht automatisch initialisiert

	printf("a: %ld\n", a);		// 0
	printf("b: %ld\n", b);		// 1
	printf("c: %ld\n", c);		// undefiniert
}