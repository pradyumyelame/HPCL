#include <iostream>
#include <omp.h>
#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0; // number of items currently in buffer

// Producer function
void produce_item(int item, int tid) {
    std::cout << "Producer Thread " << tid << ": Produced " << item << std::endl;
}

// Consumer function
void consume_item(int item, int tid) {
    std::cout << "Consumer Thread " << tid << ": Consumed " << item << std::endl;
}

int main() {
    int i;
    
    // Parallel region with sections – shared variables and private loop variable
    #pragma omp parallel sections shared(buffer, count) private(i)
    {
        // Producer Section
        #pragma omp section
        {
            int tid = omp_get_thread_num(); // Thread ID for producer
            for (i = 1; i <= 10; ) {
                #pragma omp critical
                {
                    if (count < BUFFER_SIZE) { // If buffer is not full
                        buffer[count] = i;
                        count++;
                        produce_item(i, tid);
                        i++; // Move to next item only when produced
                    }
                }
                #pragma omp flush // Ensures memory consistency across threads
            }
        }

        // Consumer Section
        #pragma omp section
        {
            int tid = omp_get_thread_num(); // Thread ID for consumer
            for (i = 1; i <= 10; ) {
                #pragma omp critical
                {
                    if (count > 0) { // If buffer has items
                        int item = buffer[count - 1];
                        count--;
                        consume_item(item, tid);
                        i++; // Consume only when available
                    }
                }
                #pragma omp flush // Synchronize memory
            }
        }
    }

    return 0;
}
