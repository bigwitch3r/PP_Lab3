// General Task 6

#include <iostream>
#include <mpi.h>

void task_six(int* argc, char** argv)
{
    MPI_Init(argc, &argv);

    // ������ ������������ �������������
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // ��������� �����
    enum role_ranks { SENDER, RECEIVER };
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    switch (my_rank)
    {
    case SENDER:
    {
        int buffer[3] = { 123, 456, 789 };
        printf("Process %d: sending a message containing 3 ints (%d, %d, %d), but the receiver is not aware of the length.\n", my_rank, buffer[0], buffer[1], buffer[2]);
        MPI_Send(buffer, 3, MPI_INT, RECEIVER, 0, MPI_COMM_WORLD);
        break;
    }
    case RECEIVER:
    {
        // �������� ���������� � �������� ���������
        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        printf("Process %d: obtained message status by probing it.\n", my_rank);

        // �������� ���������� ������������� ������ � ����������� ���������
        int count;
        MPI_Get_count(&status, MPI_INT, &count);

        // �������� ����� � ��������, ������� �� ������ �� ��������� ���������
        int* buffer = (int*)malloc(sizeof(int) * count);

        // �������� ��������� � ������� ������ �� �����
        MPI_Recv(buffer, count, MPI_INT, SENDER, 0, MPI_COMM_WORLD, &status);
        printf("Process %d: received message with all %d ints:", my_rank, count);
        for (int i = 0; i < count; i++)
        {
            printf(" %d", buffer[i]);
        }
        printf(".\n");
        break;
    }
    }

    MPI_Finalize();
}