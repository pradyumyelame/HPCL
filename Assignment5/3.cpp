#include <iostream>   // For input/output
#include <omp.h>      // For OpenMP

// Define the matrix size
#define N 500

int main() {
    // Declare static matrix and vectors to avoid stack overflow
    static double A[N][N], x[N], y[N];
    int i, j;

    // Step 1: Initialize matrix A and vectors x, y
    for (i = 0; i < N; i++) {
        x[i] = i * 1.0;   // Initialize vector x with values: 0.0, 1.0, 2.0, ...
        y[i] = 0.0;       // Initialize result vector y with 0s
        for (j = 0; j < N; j++) {
            A[i][j] = i + j; // Fill matrix A with values based on row+column index
        }
    }

    // Step 2: Start timing
    double start = omp_get_wtime();

    // Step 3: Parallelize the outer loop using OpenMP
    #pragma omp parallel for private(j) shared(A, x, y)
    for (i = 0; i < N; i++) {
        double sum = 0.0;  // Each thread will have its own local sum (avoids data race)
        for (j = 0; j < N; j++) {
            sum += A[i][j] * x[j];  // Multiply matrix row by vector column element-wise
        }
        y[i] = sum;  // Store the result in vector y
    }

    // Step 4: End timing
    double end = omp_get_wtime();

    // Step 5: Print the time taken
    std::cout << "Matrix-Vector Multiplication done in " 
              << (end - start) << " seconds" << std::endl;

    return 0;
}
