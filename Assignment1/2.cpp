#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of threads: ";
    cin >> n;

    // Sequential output
    cout << "\nSequential Hello:\n";
    for (int i = 0; i < n; i++) {
        cout << "Hello, World from thread " << i << endl;
    }

    // Parallel output
    cout << "\nParallel Hello:\n";
    omp_set_num_threads(n);

    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        #pragma omp critical   // To avoid jumbled output
        cout << "Hello, World from thread " << ID << endl;
    }

    return 0;
}
