// ? 4.1. Write a Pthreads program that implements the histogram program in Chapter 2.


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define thread_count 4  // number of threads
#define bins 5         // number of bins of the histogram
#define data_size 20 // number of data points

int histogram[bins] = {0}; //initialize the histogram array to 0
float data[data_size] = {1.3, 2.9, 0.4, 0.3, 1.3, 4.4, 1.7, 0.4, 3.2, 0.3,
                        4.9, 2.4, 3.1, 4.4, 3.9, 0.4, 4.2, 4.5, 4.9, 0.9}; //from the slides

//the histogram is shared among threads, use mutex to prevent race conditions:

pthread_mutex_t mutex;

void* Update_histogram(void* arg){
    int threadID = * (int *) arg;
    int start = threadID * (data_size / thread_count);
    int end = (threadID + 1) * (data_size / thread_count);

    int i;
    for( i = start; i < end; i++){
        int bin = (int) (data[i] / (5.0 / bins)); //element of our array divided by the width of bins in order to locate each data[i] into the corresponding bin.

        pthread_mutex_lock(&mutex);  // Lock mutex for safe histogram update
        histogram[bin]++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(){
    pthread_t threads[thread_count];
    int threadIDs[thread_count];
     pthread_mutex_init(&mutex, NULL);  // Initialize mutex
    
    for (int i = 0; i < thread_count; i++ ){
        threadIDs[i] = i;
        pthread_create(&threads[i], NULL, Update_histogram, &threadIDs[i]);
    }

    for (int i = 0; i < thread_count; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex); // Destroy the mutex

     // Print the histogram
    printf("Histogram:\n");
    for (int i = 0; i < bins; i++) {
        printf("Bin %d: %d\n", i, histogram[i]);
    }

    return 0;
}


