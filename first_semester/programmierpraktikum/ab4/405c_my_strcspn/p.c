#include <stdio.h>


int my_strcspn(const char *s1, const char *s2)
{











}


int main()
{
	char s[100] = "abdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	printf("Zeichenkette: ");

	fgets(s, 100, stdin);
	s[my_strcspn(s, "\n")] = '\0';

	printf("Position ABC: %d\n", my_strcspn(s, "ABC") );
	printf("Position 0123C456: %d\n", my_strcspn(s, "0123C456") );
}