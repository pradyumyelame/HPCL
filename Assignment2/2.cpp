#include <iostream>      
#include <omp.h>        

int main() {
    long num_steps = 100000000;    
    double step = 1.0 / num_steps; 
    double sum = 0.0;              
    int num_threads;              

    
    std::cout << "Enter number of threads: ";
    std::cin >> num_threads;
    omp_set_num_threads(num_threads); 

    
    double start = omp_get_wtime();

   
    #pragma omp parallel
    {
        double x;                 
        double local_sum = 0.0;    

      
        #pragma omp for
        for (int i = 0; i < num_steps; i++) {
            x = (i + 0.5) * step;                  
            local_sum += 4.0 / (1.0 + x * x);     
        }

       
        #pragma omp atomic
        sum += local_sum;
    }

    // Calculate final Pi value
    double pi = step * sum;

    // End timing
    double end = omp_get_wtime();

    // Output the result
    std::cout << "Estimated Pi = " << std::fixed << pi << "\n";
    std::cout << "Time taken with " << num_threads << " threads: "
              << (end - start) << " seconds\n";

    return 0;
}
