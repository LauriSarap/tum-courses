#include <stdio.h>

int main() {
  int zahl = 0;

  printf("Bitte geben Sie eine ganze Zahl ein: ");
  scanf("%i", &zahl);

  if (zahl == 0)
    printf("Sie haben Null eingegeben.\n");
  else if (zahl > 0)
    printf("Sie haben eine Zahl groesser Null eingegeben.\n");
  else if (zahl < 0)
    printf("Sie haben eine Zahl kleiner Null eingegeben.\n");
}