#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int countPrimes_v1(int g) {
    if (g < 2)
        return 0;
    int primeCount = 0;
    for (int i = 2; i <= g; i++) {
        int count = 0;
        for (int j = 1; j <= i; j++) {
            if (i % j == 0)
                count++;
        }
        if (count == 2)
            primeCount++;
    }
    return primeCount;
}

int countPrimes_v2(int g) {
    if (g < 2)
        return 0;
    int primeCount = 0;
    for (int i = 2; i <= g; i++) {
        int isPrime = 1;

        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                isPrime = 0;
                break;
            }
        }
        if (isPrime) {
            primeCount++;
        }
    }
    return primeCount;
}

int countPrimes_v3(int g) {
    if (g < 2)
        return 0;
    int primeCount = 1;
    for (int i = 3; i <= g; i += 2) {
        int isPrime = 1;
        for (int j = 3; j * j <= i; j += 2) {
            if (i % j == 0) {
                isPrime = 0;
                break;
            }
        }
        if (isPrime)
            primeCount++;
    }
    return primeCount;
}

int countPrimes_v4(int g) {
    if (g < 2)
        return 0;
    int primeCount = 0;
    if (g >= 2)
        primeCount++;
    if (g >= 3)
        primeCount++;

    for (int i = 5; i <= g; i += 6) {
        int isPrime = 1;
        for (int j = 5; j * j <= i; j += 6) {
            if (i % j == 0 || i % (j + 2) == 0) {
                isPrime = 0;
                break;
            }
        }
        if (isPrime)
            primeCount++;

        if (i + 2 <= g) {
            isPrime = 1;
            for (int j = 5; j * j <= i + 2; j += 6) {
                if ((i + 2) % j == 0 || (i + 2) % (j + 2) == 0) {
                    isPrime = 0;
                    break;
                }
            }
            if (isPrime)
                primeCount++;
        }
    }
    return primeCount;
}

int countPrimes_v5(int g) {
    if (g < 2)
        return 0;

    char *isPrime = malloc(g + 1);
    memset(isPrime, 1, g + 1);

    isPrime[0] = isPrime[1] = 0;

    for (int i = 2; i * i <= g; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= g; j += i) {
                isPrime[j] = 0;
            }
        }
    }

    int count = 0;
    for (int i = 2; i <= g; i++) {
        if (isPrime[i])
            count++;
    }

    free(isPrime);
    return count;
}

int countPrimes_v6(int g) {
    if (g < 2)
        return 0;
    if (g == 2)
        return 1;

    int size = (g / 2) + 1;
    char *isPrime = malloc(size);
    memset(isPrime, 1, size);

    isPrime[0] = 0;

    for (int i = 1; 2 * i + 1 <= g; i++) {
        if (isPrime[i]) {
            int num = 2 * i + 1;
            for (long long j = (long long)num * num; j <= g; j += 2 * num) {
                isPrime[j / 2] = 0;
            }
        }
    }

    int count = 1;
    for (int i = 1; 2 * i + 1 <= g; i++) {
        if (isPrime[i])
            count++;
    }

    free(isPrime);
    return count;
}

#include <math.h>

int countPrimes_v7(int g) {
    if (g < 2)
        return 0;

    int sqrtG = (int)sqrt(g) + 1;
    int segmentSize = 32768;

    char *isSmallPrime = malloc(sqrtG + 1);
    memset(isSmallPrime, 1, sqrtG + 1);
    isSmallPrime[0] = isSmallPrime[1] = 0;

    for (int i = 2; i * i <= sqrtG; i++) {
        if (isSmallPrime[i]) {
            for (int j = i * i; j <= sqrtG; j += i) {
                isSmallPrime[j] = 0;
            }
        }
    }

    int *smallPrimes = malloc(sqrtG * sizeof(int));
    int numSmallPrimes = 0;
    for (int i = 2; i <= sqrtG; i++) {
        if (isSmallPrime[i])
            smallPrimes[numSmallPrimes++] = i;
    }

    char *segment = malloc(segmentSize);
    int count = 0;

    for (int low = 2; low <= g; low += segmentSize) {
        int high = low + segmentSize - 1;
        if (high > g)
            high = g;

        memset(segment, 1, segmentSize);

        for (int i = 0; i < numSmallPrimes; i++) {
            int p = smallPrimes[i];
            int start = ((low + p - 1) / p) * p;
            if (start == p)
                start += p;

            for (int j = start; j <= high; j += p) {
                segment[j - low] = 0;
            }
        }

        for (int i = 0; i <= high - low; i++) {
            if (segment[i])
                count++;
        }
    }

    free(isSmallPrime);
    free(smallPrimes);
    free(segment);
    return count;
}

double benchmark(int (*func)(int), int g, const char *name) {
    clock_t start = clock();
    int result = func(g);
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%s; %i primes in %.6f sec\n", name, result, time);
    return time;
}

int main() {

    int g = 0;
    printf("Please give the upper bound for finding primes: ");
    scanf(" %i", &g);

    // benchmark(countPrimes_v1, g, "v1: Count divisors");
    benchmark(countPrimes_v2, g, "v2: Sqrt + break");
    benchmark(countPrimes_v3, g, "v3: Skip evens");
    benchmark(countPrimes_v4, g, "v4: 6k±1");
    benchmark(countPrimes_v5, g, "v5: Sieve of Eratosthenes");
    benchmark(countPrimes_v6, g, "v6: Odd Sieve");
    benchmark(countPrimes_v7, g, "v7: Segmented Sieve");
    return 0;
}