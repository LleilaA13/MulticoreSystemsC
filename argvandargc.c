#include <mpi.h>
#include <stdio.h>
// * argc is argument count, non negative, that counts the number of command-line args passed to the program, including the program's name.
// * argv is an array of pointers to char.  (command-line arguments)
int main(int argc, char** argv){ 
    //? initialize the MPI environment. This sets up MPI to start communication among processes.
    /*? & is used to obtain the memory address, argv and argc passes in case MPI needs to interpret
    any command-line arguments.*/
    MPI_Init(&argc,  &argv); 

    int rank; // var to store the rank (ID) of the current process
    //? MPI_COMM_WORLD is a communicator that includes all processes started by MPI.
    //? When you call MPI_Comm_rank, MPI determines the rank of the process in the MPI_COMM_WORLD communicator.
    //? then it stores the rank in the memory location of the variable rank, bc you passes a pointer to rank (&rank).
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //this fct needs to modify vars def outside of their scope, 
                                        //and they can onyl do so by working with pointers to those vars.
    printf("I am rank %d and argv[0] is %s argv[1] is %s \n", rank, argv[0], argv[1]);

    MPI_Finalize();
    return 0;

}