#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_TERMS 100000000 // Total number of terms in the series
#define NUM_THREADS 4       // Number of threads

// Global array to store partial sums from each thread
double partial_sums[NUM_THREADS];

// Thread function to compute partial sum
void* calculate_partial_sum(void* arg) {
    int thread_id = *(int*)arg;
    long start = thread_id * (NUM_TERMS / NUM_THREADS);
    long end = (thread_id + 1) * (NUM_TERMS / NUM_THREADS);
    double sum = 0.0;

    // Calculate partial sum for this thread's range
    for (long k = start; k < end; k++) {
        sum += (k % 2 == 0 ? 1.0 : -1.0) / (2 * k + 1);
    }

    // Store the result in the global array
    partial_sums[thread_id] = sum;

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, calculate_partial_sum, &thread_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Combine results from all threads
    double pi_estimate = 0.0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pi_estimate += partial_sums[i];
    }
    pi_estimate *= 4.0;

    printf("Estimated Pi: %.15f\n", pi_estimate);

    return 0;
}
