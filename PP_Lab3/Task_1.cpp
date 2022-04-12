
#include <iostream>
#include <mpi.h>

void task_one(int* argc, char** argv)
{
    int numtasks, rank;

    MPI_Init(argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    printf("Task 1: Process %d, Total Processes: %d\n", rank, numtasks);

    MPI_Finalize();
}