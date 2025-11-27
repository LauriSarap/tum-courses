#include <stdio.h>
#include <ctype.h>

int main() {

    char buchstabe;

    printf("Bitte geben Sie einen Grossbuchstaben ein: ");
    scanf("%c", &buchstabe);
    printf("%c\n", tolower(buchstabe));

    return 0;
}