#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int q_iterativ(int n)
{
	int q[n+1];								// Array auf dem Stack
	// int *q = malloc(sizeof(int) * (n+1)); // Alternativ Array auf dem Heap












}

int main()
{
	int n, q;
	double time;
	clock_t start, end;

	printf("n: ");
	scanf("%d", &n);

	start = clock();		// Start-Zeit merken
	q = q_iterativ(n);		// Berechnung durchführen
	end = clock();			// End-Zeit merken

	printf("Q-Zahl: %d\n", q);

	time = (double)(end - start) / CLOCKS_PER_SEC; 

	if(time >= 1)
		printf("Zeit: %lf s\n", time );
	else if(time >= 0.001)
		printf("Zeit: %lf ms\n", time * 1000 );
	else
		printf("Zeit: %lf µs\n", time * 1000000 );
}