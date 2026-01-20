#include <stdlib.h>
#include <stdio.h>

enum Monat { Jan, Feb, Mrz, Apr, Mai, Jun, Jul, Aug, Sep, Okt, Nov, Dez };

struct Datum {
    short tag;
    enum Monat mon;
    unsigned int jahr;
};

enum Geschlecht { m, w };
struct Person {
    char vorname[30], nachname[30];
    enum Geschlecht geschlecht;
    struct Datum geburtsdatum;
};

struct Person *p1, *p2;

int main() {
    p1 = malloc(sizeof(struct Person));
    p2 = malloc(sizeof(struct Person));

    scanf("%s", p2->vorname);
    printf("Vorname: %s", (*p2).vorname);
    return 0;
}