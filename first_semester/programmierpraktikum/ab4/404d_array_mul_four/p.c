#include <stdio.h>

void array_mul_four(int length, int a[])
{
    for (int i = 0; i < length; i++) {
        a[i] *= 4;
        printf("%i\n", a[i]);
    }
    printf("\n");

}

int main()
{

    int array[100];
    int i;
    
    for (i = 0; i < sizeof(array); i++) {
        printf("Zahl: ");
        scanf("%i", &array[i]);
        if (array[i] == 0) break;
    }

    array_mul_four(i, array);


}
