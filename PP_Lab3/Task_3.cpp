// General Task 3

#include <iostream>
#include <mpi.h>

void task_three(int* argc, char** argv)
{
	// TODO: Доделать
	MPI_Init(argc, &argv);

	int nRank, nValue, nTasks, receivedValue = 0;
	int buffsize = sizeof(nValue);

	MPI_Comm_rank(MPI_COMM_WORLD, &nRank);
	MPI_Comm_size(MPI_COMM_WORLD, &nTasks);

	int* buffer = (int*)malloc(buffsize + MPI_BSEND_OVERHEAD);
	MPI_Status pStatus;

	for (int i = 0; i = nTasks - 1; i++)
	{
		if (nRank == 0)
		{
			MPI_Recv(&receivedValue, 1, MPI_INT, nTasks - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &pStatus);
			if (receivedValue != 0)
			{
				printf("Thread %d received value %d from thread %d\n", nRank, receivedValue, pStatus.MPI_SOURCE);
			}

			nValue = 1;

			MPI_Buffer_attach(buffer, buffsize + MPI_BSEND_OVERHEAD);
			MPI_Bsend(&nValue, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
			printf("Thread %d send value %d to thread %d\n", nRank, nValue, 1);

		}
		else
		{
			MPI_Recv(&receivedValue, 1, MPI_INT, i - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &pStatus);
			printf("Thread %d received value %d from thread %d\n", nRank, receivedValue, pStatus.MPI_SOURCE);

			MPI_Buffer_attach(buffer, buffsize + MPI_BSEND_OVERHEAD);
			MPI_Bsend(&receivedValue, 1, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
			printf("Thread %d send value %d to thread %d\n", nRank, nValue, i + 1);
		}
	}
	
	MPI_Finalize();
}