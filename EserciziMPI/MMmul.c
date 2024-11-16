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



int* gen_mat(int rows, int cols, int rank){
    int * matrix;
    matrix = (int*)malloc(rows * cols * sizeof(int));
    return matrix;
}

int main(int argc, char** argv){
    int rank, size;
    
    //? MPI initialization:
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, rank);
    MPI_Comm_size(MPI_COMM_WORLD, size);

    int scatter_proc = size - 1;

    int row1 = atoi(argv[1]);
    int col1 = atoi(argv[2]);

    int row2 = atoi(argv[3]);
    int col2 = atoi(argv[4]);


    if (col1 != row2){
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int dim1 = row1 * col1;
    int dim2 = row2 * col2;

    int* matrix1 = gen_mat(row1, col1, rank);
    int* matrix2 = gen_mat(row2, col2, rank);
    int* partialmat1 = new_mat((row1 / size), col1, rank);
    int* res_partial = new_mat((row1 / size), col2, rank);

    if(rank == size - 1){
        for (int i = 0; i < dim1; i++){
            matrix1[i] = rand() % 10;
        }

        for (int i = 0; i < dim2; i++){
            matrix2 = rand() % 10;
        }
    }

    int rows_per_proc = (row1 / size) * col1;

    MPI_Bcast(matrix2, dim2, MPI_INT, scatter_proc, MPI_COMM_WORLD);

    if (rank == size -1){
        MPI_Scatter(matrix1, rows_per_proc, MPI_INT, MPI_IN_PLACE, rows_per_proc, MPI_INT, (size - 1), MPI_COMM_WORLD);
        
        for (int r = 0; r < (row1 / size); r++) {     // For each row of mat_1
            for (int c = 0; c < col2; c++) {          // For each col of mat_2
                int val = 0;
                for (int e = 0; e < col1; e++) {      // For each element of the column of mat_1
                    val = val + matrix1[(r * col1) + e] + matrix2[(c * col1) + e];
                }
                res_partial[(r * col2) + c] = val;
            }

    }

}