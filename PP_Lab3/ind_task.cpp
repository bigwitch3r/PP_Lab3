#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <chrono>
#include <list>
#include <iostream>
#include <mpi.h>

void ind_task(int* argc, char** argv)
{
    MPI_Init(argc, &argv);

    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int dtime = -1;

    if (my_rank == 0)
    {
        const int SIZE = 10000;

        float results[SIZE];

        auto begin = std::chrono::steady_clock::now();

        for (int i = 0; i < SIZE; i++)
        {
            results[i] = (i + 0.5) * (i + 0.5);
            // printf("%f\n", results[i]);
        }

        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

        int dtime = elapsed_ms.count();

        int buffsize = sizeof(elapsed_ms);
        int size = buffsize + MPI_BSEND_OVERHEAD;

        int* buffer = (int*)malloc(size);
        MPI_Buffer_attach(buffer, size);

        MPI_Bsend(&dtime, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }

    if (my_rank == 1)
    {
        MPI_Status status;

        MPI_Recv(&dtime, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("TIME PASSED: %d\n", dtime);
    }
    

    MPI_Finalize();
}
