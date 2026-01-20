#include <stdio.h>

int main() {

    int* p[5];

    printf("%li\n", sizeof(p[0]));

    for (size_t i = 0; i < 6; i++) {
        printf("%p\n", &p[i]);
    }

}