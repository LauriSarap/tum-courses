#include <stdio.h>
#include <string.h>

int string_to_lowercase(char *s)
{















}

int main()
{
	char s[100], i;

	printf("Zeichenkette: ");

	fgets(s, 100, stdin);
	s[strcspn(s, "\n")] = '\0';

	printf("Anzahl geänderte Zeichen: %d\n", i = string_to_lowercase(s));
	printf("Geänderte Zeichenkette: %s\n", s);
}
