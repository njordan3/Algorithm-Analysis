#include "math.h"
#include <iostream>

using namespace std;

void findPrime(int);

int main()
{
    findPrime(50);
    return 0;
}

void findPrime(int N)
{
    printf("Finding the prime numbers less than or equal to %i\n", N);
    int A[N];
    for (int p = 2; p <= N; p++) {
        A[p] = p;
    }
    int non_primes_found = 0;
    for (int p = 2; p <= floor(sqrt(N)); p++) {
        if (A[p] != 0) {
            int j = p * p;
            while (j <= N) {
                A[j] = 0;
                non_primes_found++;
                j = j + p;
            }
        }
    }
    int L[N - non_primes_found];
    int number_of_primes = 0;
    for (int p = 2; p <= N; p++) {
        if (A[p] != 0) {
            L[number_of_primes] = A[p];
            number_of_primes++;
        }
    }
    printf("Here are the primes I found:\n");
    for (int i = 0; i < number_of_primes; i++) {
        printf("%i ", L[i]);
    }
    printf("\n");
}
