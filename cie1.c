#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int isPrime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; ++i)
        if (num % i == 0) return 0;
    return 1;
}

int main() {
    int n = 20;
    int serialCount = 0, parallelCount = 0;
    double start, end;

    start = omp_get_wtime();
    for (int i = 1; i <= n; ++i) {
        if (isPrime(i)) serialCount++;
    }
    end = omp_get_wtime();
    double serialTime = end - start;

    start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) reduction(+:parallelCount)
    for (int i = 1; i <= n; ++i) {
        if (isPrime(i)) parallelCount++;
    }
    end = omp_get_wtime();
    double parallelTime = end - start;

    printf("Serial Count of primes = %d\n", serialCount);
    printf("Parallel Count of primes = %d\n", parallelCount);
    printf("Execution time (serial): %.5f seconds\n", serialTime);
    printf("Execution time (parallel): %.5f seconds\n", parallelTime);

    return 0;
}
