//Pthreads matrix-vector multiplication
//FAI MAIN

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define m 7
#define n 5
#define thread_count 3

double A[m][n]; // Define the matrix A
double x[n];    // Define the vector x
double y[m];    // Define the result vector y
void *PthreadsMV(void *arg) {
    int i, j;
    int my_rank = *((int *) arg);
    int local_m = m / thread_count;
    int my_first_row = my_rank * local_m;
    int my_last_row = (my_rank + 1) * local_m - 1;
    for (i = my_first_row; i <= my_last_row; i++) {
        y[i] = 0.0;
        for (j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    return NULL;
}
