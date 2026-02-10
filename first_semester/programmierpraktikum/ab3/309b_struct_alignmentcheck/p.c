#include <stdio.h>

struct Alignment
{
	char c1;
	int i;
	char c2;
} ;

int main(int argc, char * argv[])
{
	struct Alignment s;

	s.c1 = 'a';
	s.i = 1;
	s.c2 = 'b';

	printf("sizeof(s): %ld\n", sizeof(s));

	printf("&s:    %p\n", &s);
	printf("&s.c1:  %p\n", &s.c1);
	printf("&s.i:  %p\n", &s.i);
	printf("&s.c2:  %p\n", &s.c2);

	printf("Padding: 0x%08x\n", (unsigned int) *(&s.i + 1));



}
