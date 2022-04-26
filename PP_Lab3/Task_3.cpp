// General Task 3

#include <iostream>
#include <mpi.h>

void task_three(int* argc, char** argv)
{
	MPI_Init(argc, &argv);

	int nRank, nValue = 1, nTasks, end = 0;
	int buffsize = sizeof(nValue);

	MPI_Comm_rank(MPI_COMM_WORLD, &nRank);
	MPI_Comm_size(MPI_COMM_WORLD, &nTasks);

	int size = buffsize + MPI_BSEND_OVERHEAD;

	int* buffer = (int*)malloc(size);
	MPI_Buffer_attach(buffer, size);

	if (nRank == 0)
	{
		nValue = 1;
		MPI_Bsend(&nValue, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("Start!\n");

		MPI_Status pStatus;
		MPI_Recv(&nValue, 1, MPI_INT, nTasks - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &pStatus);
		printf("End!\n");
	}

	if (nRank != nTasks - 1)
	{
		MPI_Status pStatus;
		MPI_Recv(&nValue, 1, MPI_INT, nRank - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &pStatus);
		MPI_Bsend(&nValue, 1, MPI_INT, nRank + 1, 0, MPI_COMM_WORLD);
		printf("Thread %d: received value %d sent to next thread %d", nRank, nValue, nRank + 1);
	}

	if (nRank == nTasks - 1)
	{
		MPI_Status pStatus;
		MPI_Recv(&nValue, 1, MPI_INT, nRank - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &pStatus);
		MPI_Bsend(&nValue, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		printf("Thread %d: received value %d sent to next thread %d", nRank, nValue, nRank + 1);
		end = 1;
	}

	MPI_Finalize();
}