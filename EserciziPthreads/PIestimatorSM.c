
//? Modify the mutex version of the pi calculation program so that it uses a semaphore instead of a mutex.

//my code doesnt work fix it                                        
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define num_threads 4 //number of threads to use

int total_darts;
int circle_darts = 0;

sem_t semaphore;

double get_rand_minus_one_one(){
    return 2 * (rand() / (double)RAND_MAX) - 1;
}
//thread function
void* Throw_Darts(void* arg){
    int threadID = * (int*) arg; //retrieving the actual integer value that was stored in memory at the location arg points to.
    srand(time(NULL) + threadID); 
    int darts_per_thread = total_darts / num_threads;
    int circledarts_per_thread = 0;


    for (int toss = 0; toss < darts_per_thread; toss++){
        double x =  get_rand_minus_one_one();
        double y =  get_rand_minus_one_one();
            if (x*x + y*y <= 1){
                circledarts_per_thread++;
            }
    }
    
    sem_wait(&semaphore);
    circle_darts += circledarts_per_thread;
    sem_post(&semaphore);

    printf("Thread %d: Darts in circle = %d\n", threadID, circledarts_per_thread); // Debug output
    return NULL;
}

int main(){
    pthread_t threads[num_threads];
    int threadsIDs[num_threads];

    printf("Enter the total number of tosses: ");
    scanf("%d", &total_darts);

    sem_init(&semaphore, 0, 1);

    clock_t start_time = clock();

    for(int i = 0; i < num_threads; i++){
        threadsIDs[i] = i;
        pthread_create(&threads[i], NULL, Throw_Darts, &threadsIDs[i]);
    }

    for( int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }
        
    sem_destroy(&semaphore);

    printf("%d, %d\n", circle_darts, total_darts);
    double pi_estimate = 4.0 * (circle_darts /(double) total_darts);
    double time = (double) (clock() - start_time) / CLOCKS_PER_SEC;

    printf("Estimate of pi = %f computed in %f seconds \n", pi_estimate, time);

    //free(threads);
    return 0;
}