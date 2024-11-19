/* Implement matrix-matrix multiplication in MPI. Let’s assume that you run this on p processes
(from 0 to p-1). The two input matrices are generated randomly by rank p-1. The order of the
matrices must be read from argv (which means you can use an array but you need to allocate
dynamic memory). After the resulting matrix has been computed, it must be stored into rank 0
memory.
• Check if the resulting matrix is correct (e.g., by doing the same computation sequentially)
• Try to think about possible different ways of implementing it */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <stdbool.h>
#include <time.h>

int* matrix_allocation(int rows, int cols){
    return (int*)malloc(rows * cols* sizeof(int));
}
void gen_matrix(int* matrix, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            matrix[i * cols + j] = (int)(rand() % 10);
        }
    }
}
void seq_check_mul(int* mat1, int* mat2, int* seqres_mat, int row1, int col1, int col2) {
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            seqres_mat[i * col2 + j] = 0;
            for (int k = 0; k < col1; k++) {
                seqres_mat[i * col2 + j] += mat1[i * col1 + k] * mat2[k * col2 + j];
            }
        }
    }
}

int main(int argc, char** argv){
    int rank, size;

    //? MPI initialization:
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int scatter_root = size - 1;

    int row1 = atoi(argv[1]);
    int col1 = atoi(argv[2]);

    int row2 = atoi(argv[3]);
    int col2 = atoi(argv[4]);

    if (col1 != row2){
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    //int dim1 = row1 * col1;
    int dim2 = row2 * col2;

    int* mat1 = NULL;
    int* mat2 = NULL;
    int* res_mat = NULL;

    
        mat1 = matrix_allocation(row1, col1);
        mat2 = matrix_allocation(row2, col2);
        res_mat = matrix_allocation(row1, col2);

        gen_matrix(mat1, row1, col1);
        gen_matrix(mat2, row2, col2);

    int rows_per_proc = (row1 / size);
    //int remainder = row1 % size; 
    int* local_mat1 = (int*)malloc(rows_per_proc * col1 * sizeof(int));
    int* localres_mat = (int*)malloc(rows_per_proc * col2 * sizeof(int));

    MPI_Bcast(mat2, dim2, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(mat1, rows_per_proc * col1, MPI_INT, local_mat1, rows_per_proc * col1, MPI_INT, 0, MPI_COMM_WORLD);


    for (int i = 0; i < rows_per_proc; i++) {
        for (int j = 0; j < col2; j++) {
            localres_mat[i * col2 + j] = 0;
            for (int k = 0; k < col1; k++) {
                localres_mat[i * col2 + j] += local_mat1[i * col1 + k] * mat2[k * col2 + j];
            }
        }
    }

    

    MPI_Gather(localres_mat, rows_per_proc * col2, MPI_INT, res_mat, rows_per_proc * col2, MPI_INT, 0, MPI_COMM_WORLD);
        // Rank 0 will print the result matrix and check correctness
    if (rank == 0) {
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
                printf("%d ", res_mat[i * col2 + j]);
            }
            printf("\n");
        }

    //! SEQUENTIAL CHECK:
        int* seqres_mat = matrix_allocation(row1, col2);
        seq_check_mul(mat1, mat2, seqres_mat, row1, col1, col2);

        printf("Result Matrix(SEQUENTIAL):\n");
        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col2; j++) {
                printf("%d ", seqres_mat[i * col2 + j]);
            }
            printf("\n");
        }

    //! Compare the results
        bool correct = true;
        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col2; j++) {
                if (res_mat[i * col2 + j] != seqres_mat[i * col2 + j]) {
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

        free(seqres_mat);
    }

    // Clean up
    free(mat1);
    free(mat2);
    free(res_mat);
    free(local_mat1);
    free(localres_mat);

    MPI_Finalize();
    return 0;
    }




