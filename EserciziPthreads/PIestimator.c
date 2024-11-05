/*
    Suppose we toss darts randomly at a square dartboard, whose bullseye is at the
origin, and whose sides are 2 feet in length. 
    Suppose also that there’s a circle inscribed in the square dartboard. The radius of the circle is 1 foot, and it’s area is
square feet. 
    If the points that are hit by the darts are uniformly distributed (and we always hit the square),
    then the number of darts that hit inside the circle should approximately satisfy the equation: (number in circle / total number of tosses) = (pi / 4)
    since the ratio of the area of the circle to the area of the square is = 4.
    Write a Pthreads program that uses this method to estimate pi.
The main thread should read in the total number of tosses and print the estimate value
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

#define num_threads 4 //number of threads to use

int total_darts;
int circle_darts = 0;
double get_rand_minus_one_one(){
    return 2 * (rand() / (double)RAND_MAX) - 1;
}

pthread_mutex_t mutex;

//thread function
void* Throw_Darts(void* arg){
    int threadID = * (int*) arg;
    srand(time(NULL) + threadID); // Seed based on time and rank //retrieving the actual integer value that was stored in memory at the location arg points to.
    int darts_per_thread = total_darts / num_threads;
    int circledarts_per_thread = 0;
     //seed for the random number generator, used to generate random numbers for each thread in order to simulate the darts being thrown at random locations.

    for (int toss = 0; toss < darts_per_thread; toss++){
        double x = get_rand_minus_one_one();
        double y = get_rand_minus_one_one();

        if (x*x + y*y <= 1){
            circledarts_per_thread++;
        }
    }
    pthread_mutex_lock(&mutex);
    circle_darts += circledarts_per_thread;
    pthread_mutex_unlock(&mutex);
    //printf("Thread %d: Darts in circle = %d\n", *((int*)arg), circledarts_per_thread); // Debug output
    return NULL;
}

int main(){
    pthread_t threads[num_threads];
    int threadsIDs[num_threads];

    printf("Enter the total number of tosses: ");
    scanf("%d", &total_darts);

    pthread_mutex_init(&mutex, NULL); //inizializziamo mutex

    clock_t start_time = clock();

    for(int i = 0; i < num_threads; i++){
        threadsIDs[i] = i;
        pthread_create(&threads[i], NULL, Throw_Darts, &threadsIDs[i]);
    }

    for( int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }
    printf("%d, %d \n", circle_darts, total_darts);
    double pi_estimate = 4 * (circle_darts /((double) total_darts));
    double time = (double) (clock() - start_time) / CLOCKS_PER_SEC;

    printf("Estimate of pi = %f computed in %f seconds \n", pi_estimate, time);
    pthread_mutex_destroy(&mutex);
    //free(threads);
    return 0;
}