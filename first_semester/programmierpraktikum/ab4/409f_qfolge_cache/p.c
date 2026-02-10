#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void init_cache(int n, int* cache)
{








}

int q_rekursiv_cache(int n, int *cache)
{







}


int main()
{
	int n, q, *cache;
	double time;
	clock_t start, end;


	printf("n: ");
	scanf("%d", &n);

	cache = malloc(sizeof(int) * (n + 1));
	if(cache == NULL) return -1;

	init_cache(n, cache);

	start = clock();
	q = q_rekursiv_cache(n, cache);
	end = clock();

	printf("Q-Zahl: %d\n", q);

	time = (double)(end - start) / CLOCKS_PER_SEC;

	if(time > 1)
		printf("Zeit: %lf s\n", time );
	else if(time > 0.001)
		printf("Zeit: %lf ms\n", time * 1000 );
	else
		printf("Zeit: %lf µs\n", time * 1000000 );
}