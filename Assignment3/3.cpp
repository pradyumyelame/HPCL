#include <iostream>   
#include <omp.h>      

#define SIZE 200      

int main() {
    int i;                           
    float a[SIZE], result[SIZE];      
    float scalar = 2.5;              

   
    for (i = 0; i < SIZE; i++)
        a[i] = i * 1.0f;             

    // Static schedule with chunk size 10
    std::cout << "Static schedule (chunk=10):\n";
    #pragma omp parallel for schedule(static, 10)
    for (i = 0; i < SIZE; i++) {
        result[i] = a[i] + scalar;    
    }

    // Dynamic schedule with chunk size 5
    std::cout << "Dynamic schedule (chunk=5):\n";
    #pragma omp parallel for schedule(dynamic, 5)
    for (i = 0; i < SIZE; i++) {
        result[i] = a[i] + scalar;   
    }

    // Demonstrate nowait
    std::cout << "Using nowait clause:\n";
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (i = 0; i < SIZE; i++)
            result[i] = a[i] + scalar;

        #pragma omp single
        std::cout << "No wait after for-loop. Continuing...\n";
    }

    // Optional: Using ordered to maintain output order
    std::cout << "Ordered output of first 10 elements:\n";
    #pragma omp parallel for ordered schedule(static)
    for (i = 0; i < 10; i++) {
        #pragma omp ordered
        std::cout << "result[" << i << "] = " << result[i] << "\n";
    }

    return 0;
}
