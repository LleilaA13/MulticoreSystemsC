#include <stdio.h>
/*
int main(void){
    printf("Hello world \n");
    return 0;
}
*/
#include <mpi.h>
int main(void){
    int r = MPI_Init(NULL, NULL); //prende due puntatori, fa tutto il set up per far comunicare i processi
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   
    if( r != MPI_SUCCESS){
        printf("Error starting MPI program. Terminating \n");
        MPI_Abort(MPI_COMM_WORLD, r);
    }
    if(rank == 0){
        printf("\n I'm process %d of %d. \n", rank, size);
        int i;
        for(i = 1; i < size; i++){
            char str[256];
            MPI_Recv(str, 256, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); //mssg va sullo Stack 
            printf("%s", str);
        }
    }else{
        char str[256];
        sprintf(str, "hello world! i'm process %d of %d. \n", rank, size);
        MPI_Send(str, 256, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }


    //printf("Hello world \n");
    //printf("\n I'm process %d of %d. \n", rank, size);//prende due puntatori, fa tutto i lset up per far comunicare i processi
    MPI_Finalize(); //per chiudere la libreria, liberare risorse

    return 0;
}                           