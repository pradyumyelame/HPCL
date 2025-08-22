#include <iostream>
#include <omp.h>

#define N 1000000

int main() {
    static int arr[N], prefix[N];

    // Step 1: Initialize array
    for (int i = 0; i < N; i++)
        arr[i] = 1; // Fill array with 1s

    // Step 2: Start timing
    double start = omp_get_wtime();

    // Step 3: Initialize first element of prefix sum
    prefix[0] = arr[0];

    // Step 4: Compute prefix sum (sequential dependency – note: this naive parallelization may not give correct results)
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 1; i < N; i++) {
            prefix[i] = prefix[i - 1] + arr[i];
        }
    }

    // Step 5: End timing
    double end = omp_get_wtime();

    // Step 6: Output time taken
    std::cout << "Prefix sum done in " << (end - start) << " seconds" << std::endl;

    return 0;
}
