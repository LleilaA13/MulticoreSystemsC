// Estimate pi using Montecralo method
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <time.h>

double random_double_in_range()
{
    return ((double)rand() / (float)RAND_MAX) * 2.0 - 1.0;
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int num_ranks, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &num_ranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Take note of the time to check time efficiency in the end
    double start_time = MPI_Wtime();

    // With the following command we ensure that every future call of rand()
    // will have a different unique seed
    srand(time(NULL) + rank);

    // in argv[1] is stored the total number of tosses
    int total_tosses = atoi(argv[1]);
    int local_tosses = total_tosses / num_ranks; // tosses per process

    int r = 1;        // radius of the circle
    int n_circle = 0; // number of points inside the circle (Locally)
    int toss;
    for (toss = 0; toss < local_tosses; toss++)
    {
        // Generating random coordinates to simulate the toss
        double x = random_double_in_range();
        double y = random_double_in_range();

        // Computing the distance from the center of the circle
        // REMARK: x^2 + y^2 = 1
        double dist = pow(x, 2) + pow(y, 2);

        // if the arrow falls inside the circle, we increment n_circle
        if (dist <= (float)r)
        {
            ++n_circle;
        }
    }

    // Debugging: check if the random seeds are actually working
    printf("I am rank %d and my local number of circle is %d\n", rank, n_circle);

    // Time to collect the outcomes of all processes!
    // Look at the slides or documentation to see how MPI_Reduce works in detail
    int global_n_circle;
    MPI_Reduce(&n_circle, &global_n_circle, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Process 0 is the one collecting the partial calculations
    if (rank == 0)
    {
        double final_time = MPI_Wtime() - start_time;

        // Use the formula provided on the slides to compute the approximation of pi
        float my_pi = (float)(global_n_circle * 4) / total_tosses;

        // Print the time taken and the value obtained
        printf("Time: %f\n", final_time);
        printf("Pi is approximated to: %f\n", my_pi);
    }

    MPI_Finalize();
    return 0;
}