// Problem 2: Matrix Addition with malloc, collapse, schedule, and speedup analysis
#include <iostream>
#include <vector>
#include <omp.h>
#include <iomanip> // For std::setw and formatting

void matrix_addition(int size) {
    // Use vectors for automatic memory management
    std::vector<std::vector<float>> A(size, std::vector<float>(size));
    std::vector<std::vector<float>> B(size, std::vector<float>(size));
    std::vector<std::vector<float>> C(size, std::vector<float>(size));

    double start, end;
    double base_time = 0.0;

    // Initialize matrices
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }

    std::cout << "\nMatrix Size: " << size << " x " << size << "\n";
    std::cout << "Threads\tTime (s)\tSpeedup\n";

    // Test with different thread counts (1, 2, 4, 8)
    for (int t = 1; t <= 8; t *= 2) {
        omp_set_num_threads(t);
        start = omp_get_wtime();

        // Parallel matrix addition
        #pragma omp parallel for collapse(2) schedule(static)
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                C[i][j] = A[i][j] + B[i][j];
            }
        }

        end = omp_get_wtime();
        double time_taken = end - start;

        if (t == 1) {
            base_time = time_taken; // Store baseline for speedup calculation
        }

        double speedup = base_time / time_taken;
        std::cout << t << "\t" << std::fixed << std::setprecision(6) 
                  << time_taken << "\t" << std::setprecision(2) 
                  << speedup << "\n";
    }
}

int main() {
    std::vector<int> sizes = {250, 500, 750, 1000, 2000};

    std::cout << "2D Matrix Addition using OpenMP (Speedup Analysis)\n";

    for (int size : sizes) {
        matrix_addition(size);
    }

    return 0;
}
