#include <stdio.h>		// für printf
#include <stdlib.h>		// für atoi


int main(int argc, char * argv[])
{

    int summe = 0;
    for (int i = 0; argv[i]; i++) {
        summe += atoi(argv[i]);
    }
    printf("Summe: %i\n", summe);
}