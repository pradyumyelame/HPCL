<<<<<<< HEAD
#include <iostream>   
=======
#include <iostream>    
>>>>>>> 413e451 (Added OpenMP programs)
#include <omp.h>       
#define SIZE 20       

int main() {
    const float scalar = 5.0;    
    float A[SIZE], B[SIZE];      

<<<<<<< HEAD
    
    for (int i = 0; i < SIZE; i++)
        A[i] = static_cast<float>(i);  

   
    double start = omp_get_wtime();

  
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        int tid = omp_get_thread_num();        
        B[i] = A[i] + scalar;                 
        std::cout << "Thread " << tid << " processed index " << i << std::endl;
    }

   
    double end = omp_get_wtime();

   
=======
   
    for (int i = 0; i < SIZE; i++)
        A[i] = static_cast<float>(i);  

    
    double start = omp_get_wtime();

    // Parallel vector-scalar addition using OpenMP
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        int tid = omp_get_thread_num();       
        B[i] = A[i] + scalar;                  
        std::cout << "Thread " << tid << " processed index " << i << std::endl;
    }

    // Record the end time
    double end = omp_get_wtime();

    // Display the total time taken for the operation
>>>>>>> 413e451 (Added OpenMP programs)
    std::cout << "Time taken: " << end - start << " seconds" << std::endl;

    return 0;
}
