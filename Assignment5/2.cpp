#include <iostream>   
#include <omp.h>     

#define N 1000

int main() {
    static double A[N][N];   
    double scalar = 5.0;    
    int i, j;

    
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j; 
        }
    }

    double start = omp_get_wtime(); 

   
    #pragma omp parallel for private(j) shared(A, scalar)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] *= scalar; 
        }
    }

    double end = omp_get_wtime(); 

    
    std::cout << "Matrix-Scalar Multiplication done in "
              << (end - start) << " seconds" << std::endl;

    return 0;
}
