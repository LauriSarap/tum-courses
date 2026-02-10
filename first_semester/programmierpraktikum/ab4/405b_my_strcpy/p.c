#include <stdio.h>
#include <string.h>


char *my_strcpy(char * restrict dst, const char * restrict src)
{











}


int main()
{
	char s[100], d[100];

	printf("Zeichenkette: ");

	fgets(s, 100, stdin);
	s[strcspn(s, "\n")] = '\0';

	printf("Kopierte Zeichenkette: %s\n", my_strcpy(d, s) );
}