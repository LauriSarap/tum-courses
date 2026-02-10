#include <stdio.h>
#include <time.h>

int q_rekursiv(int n, int f)
{
	int r;

	printf("Calling q_rekursiv_%d(%d)\n", f, n);

	if(n <= 2) 
	{
		printf("Returning 1 from q_rekursiv_%d(%d)\n", f, n);
		return 1;
	}

	r = q_rekursiv(n - q_rekursiv(n-1, 1) , 2)
							+ q_rekursiv(n - q_rekursiv(n-2, 3), 4);

	printf("Returning %d from q_rekursiv_%d(%d)\n", r, f, n);

	return r;

}


int main()
{
	int i, n, q;
	double time;
	clock_t start, end;

	printf("n: ");
	scanf("%d", &n);

	start = clock();
	q = q_rekursiv(n, 0);
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