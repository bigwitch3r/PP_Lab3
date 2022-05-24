// General Task 7

#include <iostream>
#include <mpi.h>

void task_seven(int* argc, char** argv)
{
	MPI_Init(argc, &argv);

	int nRank, nValue = 1, nTasks, end = 0;
	int flag = 0;

	MPI_Comm_rank(MPI_COMM_WORLD, &nRank);
	MPI_Comm_size(MPI_COMM_WORLD, &nTasks);

	MPI_Request request;
	MPI_Status status;

	if (nRank == 0)
	{
		nValue = 1;
		MPI_Isend(&nValue, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
		printf("Start!\n");

		MPI_Status pStatus;
		MPI_Irecv(&nValue, 1, MPI_INT, nTasks - 1, 0, MPI_COMM_WORLD, &request);
		MPI_Wait(&request, &status);
		MPI_Test(&request, &flag, &status);
		if (flag == 1) printf("True");
		printf("End!\n");
	}

	if (nRank != nTasks - 1)
	{

		MPI_Irecv(&nValue, 1, MPI_INT, nRank - 1, 0, MPI_COMM_WORLD, &request);
		MPI_Wait(&request, &status);
		MPI_Test(&request, &flag, &status);
		if (flag == 1) printf("True");

		MPI_Isend(&nValue, 1, MPI_INT, nRank + 1, 0, MPI_COMM_WORLD, &request);

		printf("Thread %d: received value %d sent to next thread %d", nRank, nValue, nRank + 1);
	}

	if (nRank == nTasks - 1)
	{

		MPI_Irecv(&nValue, 1, MPI_INT, nRank - 1, 0, MPI_COMM_WORLD, &request);
		MPI_Wait(&request, &status);
		MPI_Test(&request, &flag, &status);
		if (flag == 1) printf("True");

		MPI_Isend(&nValue, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);

		printf("Thread %d: received value %d sent to next thread %d", nRank, nValue, nRank + 1);
		end = 1;
	}

	MPI_Finalize();
}

/*

	MPI_Init(argc, &argv);

	int nRank, nValue = 1, nTasks, end = 0;

	MPI_Comm_rank(MPI_COMM_WORLD, &nRank);
	MPI_Comm_size(MPI_COMM_WORLD, &nTasks);

	MPI_Request request;
	MPI_Status status;

	if (nRank == 0)
	{
		nValue = 1;
		// MPI_Bsend(&nValue, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Isend(&nValue, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
		printf("Start!\n");

		MPI_Status pStatus;
		// MPI_Recv(&nValue, 1, MPI_INT, nTasks - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &pStatus);
		MPI_Irecv(&nValue, 1, MPI_INT, nTasks - 1, 0, MPI_COMM_WORLD, &request);
		MPI_Wait(&request, &status);
		printf("End!\n");
	}

	if (nRank != nTasks - 1)
	{

		// MPI_Recv(&nValue, 1, MPI_INT, nRank - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &pStatus);
		MPI_Irecv(&nValue, 1, MPI_INT, nRank - 1, 0, MPI_COMM_WORLD, &request);
		MPI_Wait(&request, &status);

		// MPI_Bsend(&nValue, 1, MPI_INT, nRank + 1, 0, MPI_COMM_WORLD);
		MPI_Isend(&nValue, 1, MPI_INT, nRank + 1, 0, MPI_COMM_WORLD, &request);

		printf("Thread %d: received value %d sent to next thread %d", nRank, nValue, nRank + 1);
	}

	if (nRank == nTasks - 1)
	{

		// MPI_Recv(&nValue, 1, MPI_INT, nRank - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &pStatus);
		MPI_Irecv(&nValue, 1, MPI_INT, nRank - 1, 0, MPI_COMM_WORLD, &request);
		MPI_Wait(&request, &status);

		// MPI_Bsend(&nValue, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Isend(&nValue, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);

		printf("Thread %d: received value %d sent to next thread %d", nRank, nValue, nRank + 1);
		end = 1;
	}

	MPI_Finalize();

*/