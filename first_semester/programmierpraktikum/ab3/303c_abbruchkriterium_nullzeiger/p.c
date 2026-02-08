#include <stdio.h>

int main(int argc, char * argv[])
{

    for (int i = 1; argv[i]; i++) {
        printf("%s\n", argv[i]);
    }

}