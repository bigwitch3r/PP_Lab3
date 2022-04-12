// General Task 2

#include <iostream>
#include <mpi.h>

void task_two_single(int* argc, char** argv)
{
    int numtasks, rank, provided;

    MPI_Init_thread(argc, &argv, MPI_THREAD_SINGLE, &provided);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    printf("Task 2 (SINGLE): Process %d, Total Processes: %d\n", rank, numtasks);
    printf("Task 2 (SINGLE): Multithread Support Level is %d\n", provided);

    MPI_Finalize();
}

void task_two_funneled(int* argc, char** argv)
{
    int numtasks, rank, provided;

    MPI_Init_thread(argc, &argv, MPI_THREAD_FUNNELED, &provided);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    printf("Task 2 (SINGLE): Process %d, Total Processes: %d\n", rank, numtasks);
    printf("Task 2 (SINGLE): Multithread Support Level is %d\n", provided);

    MPI_Finalize();
}

void task_two_serialized(int* argc, char** argv)
{
    int numtasks, rank, provided;

    MPI_Init_thread(argc, &argv, MPI_THREAD_SERIALIZED, &provided);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    printf("Task 2 (SINGLE): Process %d, Total Processes: %d\n", rank, numtasks);
    printf("Task 2 (SINGLE): Multithread Support Level is %d\n", provided);

    MPI_Finalize();
}

void task_two_multiple(int* argc, char** argv)
{
    int numtasks, rank, provided;

    MPI_Init_thread(argc, &argv, MPI_THREAD_MULTIPLE, &provided);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    printf("Task 2 (SINGLE): Process %d, Total Processes: %d\n", rank, numtasks);
    printf("Task 2 (SINGLE): Multithread Support Level is %d\n", provided);

    MPI_Finalize();
}