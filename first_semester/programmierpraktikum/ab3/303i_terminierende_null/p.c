#include <stdio.h>

int main(int argc, char * argv[])
{
	char eingabe[21] = "ABCDEFGHIJKLMNOPQRST";
	int i = 0;

	printf("Bitte geben Sie einen Text ein: ");
	scanf("%20s", eingabe);

	printf("# ");
	for(i = 0; i < 21; i++)
	{
		printf(" %c ", eingabe[i]);
	}
	printf("\n");
}