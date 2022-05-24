// General Task 6

#include <iostream>
#include <mpi.h>

void task_six(int* argc, char** argv)
{
    MPI_Init(argc, &argv);

    // Размер стандартного коммуникатора
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Получение ранга
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
        // Собираем информацию о входящем сообщении
        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        printf("Process %d: obtained message status by probing it.\n", my_rank);

        // Получаем количество целочисленных данных в проверенном сообщении
        int count;
        MPI_Get_count(&status, MPI_INT, &count);

        // Выделяем буфер с размером, который мы узнали из входящего сообщения
        int* buffer = (int*)malloc(sizeof(int) * count);

        // Получаем сообщение и выводим данные на экран
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