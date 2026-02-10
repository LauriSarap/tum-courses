#include <stdio.h>


int to_lowercase(char *s)
{

}

int main()
{
	char s[100], i;

	printf("Zeichenkette: ");

	fgets(s, 100, stdin);
	s[strcspn(s, "\n")] = '\0';

	i = to_lowercase(s);

	printf("In Kleinbuchstaben: %s\n", s);
	printf("Geänderte Zeichen: %d\n", i);

}