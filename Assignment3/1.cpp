#include <iostream>
#include <omp.h>

#define SIZE 1000

int main() {
    float a[SIZE], b[SIZE], result = 0.0f;

    // Initialize arrays
    for (int i = 0; i < SIZE; i++) {
        a[i] = static_cast<float>(i);
        b[i] = static_cast<float>(SIZE - i);
    }

    // Parallel dot product using reduction
    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < SIZE; i++) {
        result += a[i] * b[i];
    }

    std::cout << "Scalar (Dot) Product = " << result << std::endl;
    return 0;
}
