#include <iostream>     
#include <omp.h>       


long long fib(int n) {
    
    if (n < 2) return n;

    long long x, y;

    
    #pragma omp task shared(x) firstprivate(n)
    x = fib(n - 1);

    
    #pragma omp task shared(y) firstprivate(n)
    y = fib(n - 2);

    // Wait until both tasks (fib(n - 1) and fib(n - 2)) are completed
    #pragma omp taskwait

    return x + y; 
}

int main() {
    int n = 10; 
    long long result;

    // Start timestamp using OpenMP wall clock time
    double start = omp_get_wtime();

    // Parallel region begins
    #pragma omp parallel
    {
        // Only one thread starts the recursive Fibonacci calculation
        #pragma omp single
        result = fib(n);
    }

    // End timestamp
    double end = omp_get_wtime();

    // Output the result
    std::cout << "Fibonacci(" << n << ") = " << result << std::endl;
    std::cout << "Time taken: " << (end - start) << " seconds" << std::endl;

    return 0;
}
