/* Implement matrix-matrix multiplication in Pthreads. Let’s assume that you run this on p processes
(from 0 to p-1). The two input matrices are generated randomly by rank p-1. The order of the
matrices must be read from argv (which means you can use an array but you need to allocate
dynamic memory). After the resulting matrix has been computed, it must be stored into rank 0
memory.
• Check if the resulting matrix is correct (e.g., by doing the same computation sequentially)
• Try to think about possible different ways of implementing it */



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#define num_threads 4
int *mat1, *mat2, *res;
int row1, col1, row2, col2;


int* matrix_alloc(int rows, int cols){
    return (int*)malloc(rows * cols * sizeof(int));
}

void gen_matrix(int* matrix, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            matrix[i * cols + j] = (int)(rand() % 10);
        }
    }
}

void seq_check_mul(int* mat1, int* mat2, int* seq_mat, int row1, int col1, int col2){
    for(int i = 0; i < row1; i++){
        for(int j = 0; j < col2; j++){
            seq_mat[i * col2 + j] = 0;
            for(int k= 0; k < col1; k++){
                seq_mat[i * col2 + j] += mat1[i * col1 + k] * mat2[k * col2 + j];
            }
        }
    }
}

void* compute_matrix(void* arg){
    int tID = *(int*)arg;

    int row_per_thread = row1 / num_threads;
    int start_row = tID * row_per_thread;
    int end_row =  start_row + row_per_thread;
    //int end_row = (tID == num_threads - 1) ? row1 : start_row + row_per_thread;

    for(int i = start_row; i < end_row; i++){
        for(int j = 0; j < col2; j++){
            res[i * col2 + j] = 0;
            for(int k = 0; k < col1; k++){
                res[i * col2 + j] += mat1[i * col1 + k] * mat2[k * col2 + j];
            }
        }
    }

    return NULL;
}

int main(int argc, char** argv){
    pthread_t thread_handles[num_threads];
    int* ids = (int*) malloc(sizeof(int)*num_threads);

    row1 = atoi(argv[1]);
    col1 = atoi(argv[2]);

    row2 = atoi(argv[3]);
    col2 = atoi(argv[4]);

    mat1 = matrix_alloc(row1, col1);
    mat2 = matrix_alloc(row2, col2);
    res = matrix_alloc(row1, col2);

    gen_matrix(mat1, row1, col1);
    gen_matrix(mat2, row2, col2);
    
    for (int t = 0; t < num_threads; t++) {
        ids[t] = t;
        pthread_create(&thread_handles[t], NULL, compute_matrix, &ids[t]);
    }

    // Wait for all threads to complete
    for (int t = 0; t < num_threads; t++) {
        pthread_join(thread_handles[t], NULL);
    }

            printf("Matrix 1:\n");
        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col1; j++) {
                printf("%d ", mat1[i * col1 + j]);
            }
            printf("\n");
        }

        printf("Matrix 2:\n");
        for (int i = 0; i < row2; i++) {
            for (int j = 0; j < col2; j++) {
                printf("%d ", mat2[i * col2 + j]);
            }
            printf("\n");
        }

        printf("Result Matrix (PARALLEL):\n");
        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col2; j++) {
                printf("%d ", res[i * col2 + j]);
            }
            printf("\n");
        }

    //! SEQUENTIAL CHECK:
        int* seq_mat = matrix_alloc(row1, col2);
        seq_check_mul(mat1, mat2, seq_mat, row1, col1, col2);

        printf("Result Matrix(SEQUENTIAL):\n");
        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col2; j++) {
                printf("%d ", seq_mat[i * col2 + j]);
            }
            printf("\n");
        }

    //! Compare the results
        bool correct = true;
        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col2; j++) {
                if (res[i * col2 + j] != seq_mat[i * col2 + j]) {
                    correct = false;
                    break;
                }
            }
        }

        if (correct) {
            printf("The results are correct!\n");
        } else {
            printf("The results are incorrect!\n");
        }


    // Clean up
    free(mat1);
    free(mat2);
    free(res);
    free(seq_mat);
    free(ids);

    return 0;

}