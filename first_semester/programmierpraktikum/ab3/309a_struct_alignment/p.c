#include <stdio.h>

struct Alignment
{
	int i;
	long l;
} ;

int main(int argc, char * argv[])
{
	struct Alignment s;

	s.i = 1;
	s.l = 2;

	printf("sizeof(s):  %ld\n", sizeof(s) );

	printf("&s:         %p\n", &s);
	printf("&s.i:       %p\n", &s.i);
	printf("&s.l:       %p\n", &s.l);

	printf("Padding:  0x%08x\n", (unsigned int) *(&s.i + 1) );
}
