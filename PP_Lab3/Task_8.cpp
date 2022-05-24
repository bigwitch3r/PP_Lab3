// General Task 8

#include <iostream>
#include <mpi.h>

void task_eight(int* argc, char** argv)
{
    MPI_Init(argc, &argv);

    // Get the number of processes and check only 3 processes are used
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 3)
    {
        printf("This application is meant to be run with 3 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Get my rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0)
    {
        // The "master" MPI process sends the messages.
        int buffer[2] = { 12345, 67890 };
        int count = 2;
        MPI_Request requests[2];
        int recipient_rank_of_request[2];

        // Send first message to process 1
        printf("[Process %d] Sends %d to process 1.\n", my_rank, buffer[0]);
        MPI_Issend(&buffer[0], 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &requests[0]);
        recipient_rank_of_request[0] = 1;

        // Send second message to process 2
        printf("[Process %d] Sends %d to process 2.\n", my_rank, buffer[1]);
        MPI_Issend(&buffer[1], 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &requests[1]);
        recipient_rank_of_request[1] = 2;

        int index;
        int ready;

        // Check if one of the requests finished
        MPI_Testany(count, requests, &index, &ready, MPI_STATUS_IGNORE);
        if (ready)
            printf("MPI_Issend to process %d completed.\n", index + 1);
        else
            printf("None of the MPI_Issend completed for now.\n");

        // Tell receivers they can now issue the first MPI_Recv.
        MPI_Barrier(MPI_COMM_WORLD);

        // Receivers tell us the MPI_Recv is complete.
        MPI_Barrier(MPI_COMM_WORLD);

        // Check if one of the requests finished
        MPI_Testany(count, requests, &index, &ready, MPI_STATUS_IGNORE);
        if (ready)
            printf("MPI_Issend to process %d completed.\n", recipient_rank_of_request[index]);
        else
            printf("None of the MPI_Issend completed for now.\n");

        // Tell receivers they can now issue the second MPI_Recv.
        MPI_Barrier(MPI_COMM_WORLD);

        // Receivers tell us the second MPI_Recv is complete.
        MPI_Barrier(MPI_COMM_WORLD);

        // Check if one of the requests finished
        MPI_Testany(count, requests, &index, &ready, MPI_STATUS_IGNORE);
        if (ready)
            printf("MPI_Issend to process %d completed.\n", recipient_rank_of_request[index]);
        else
            printf("None of the MPI_Issend completed for now.\n");
    }
    else
    {
        // The "slave" MPI processes receive the messages.

        // Wait until the first MPI_Testany is issued.
        MPI_Barrier(MPI_COMM_WORLD);

        if (my_rank == 1)
        {
            int received;
            MPI_Recv(&received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("[Process %d] Received value %d.\n", my_rank, received);
        }

        // Tell that the first MPI_Recv is issued.
        MPI_Barrier(MPI_COMM_WORLD);

        // Wait until the second MPI_Testany is issued.
        MPI_Barrier(MPI_COMM_WORLD);

        if (my_rank == 2)
        {
            int received;
            MPI_Recv(&received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("[Process %d] Received value %d.\n", my_rank, received);
        }

        // Wait for the second MPI_Recv to be issued.
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Finalize();
}

/*

WAIT ALL

    MPI_Init(argc, &argv);

    // Get the number of processes and check only 3 processes are used
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 3)
    {
        printf("This application is meant to be run with 3 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Get my rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0)
    {
        // The "master" MPI process sends the message.
        int buffer[2] = { 12345, 67890 };
        MPI_Request requests[2];
        printf("MPI process %d sends the values %d & %d.\n", my_rank, buffer[0], buffer[1]);
        MPI_Isend(&buffer[0], 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &requests[0]);
        MPI_Isend(&buffer[1], 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &requests[1]);

        // Wait for both routines to complete
        MPI_Waitall(2, requests, MPI_STATUSES_IGNORE);
        printf("Process %d: both messages have been sent.\n", my_rank);
    }
    else
    {
        // The "slave" MPI processes receive the message.
        int received;
        MPI_Recv(&received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received value %d.\n", my_rank, received);
    }

    MPI_Finalize();

*/

/*

wait any

MPI_Init(argc, &argv);

    // Get the number of processes and check only 3 processes are used
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 3)
    {
        printf("This application is meant to be run with 3 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Get my rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0)
    {
        // The "master" MPI process sends the messages.
        int buffer[2] = { 12345, 67890 };
        MPI_Request requests[2];
        int recipient_rank_of_request[2];

        // Send first message to process 1
        printf("[Process %d] Sends %d to process 1.\n", my_rank, buffer[0]);
        MPI_Isend(&buffer[0], 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &requests[0]);
        recipient_rank_of_request[0] = 1;

        // Send second message to process 2
        printf("[Process %d] Sends %d to process 2.\n", my_rank, buffer[1]);
        MPI_Isend(&buffer[1], 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &requests[1]);
        recipient_rank_of_request[1] = 2;

        // Wait for one of non-blocking sends to complete
        int index;
        MPI_Waitany(2, requests, &index, MPI_STATUS_IGNORE);
        printf("[Process %d] The non-blocking send to process %d is complete.\n", my_rank, recipient_rank_of_request[index]);

        // Wait for the other non-blocking send to complete
        MPI_Waitany(2, requests, &index, MPI_STATUS_IGNORE);
        printf("[Process %d] The non-blocking send to process %d is complete too.\n", my_rank, recipient_rank_of_request[index]);
    }
    else
    {
        // The "slave" MPI processes receive the message.
        int received;
        MPI_Recv(&received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("[Process %d] Received value %d.\n", my_rank, received);
    }

    MPI_Finalize();

*/

/*

test all

MPI_Init(argc, &argv);

    // Get the number of processes and check only 3 processes are used
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 3)
    {
        printf("This application is meant to be run with 3 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Get my rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0)
    {
        // The "master" MPI process receives the messages.
        int message_1;
        int message_2;
        MPI_Request requests[2];
        int ready;

        MPI_Irecv(&message_1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &requests[0]);
        MPI_Irecv(&message_2, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &requests[1]);

        // This MPI_Testall is guaranteed to fail since the corresponding MPI_Ssends have not been issued yet.
        MPI_Testall(2, requests, &ready, MPI_STATUSES_IGNORE);
        if (ready)
            printf("[Process 0] First attempt: both receives are complete.\n");
        else
            printf("[Process 0] First attempt: not both receives are complete yet.\n");

        // We can tell other processes to start sending messages
        MPI_Barrier(MPI_COMM_WORLD);

        // We wait for the other processes to tell us their MPI_Ssend is complete
        MPI_Barrier(MPI_COMM_WORLD);

        // This MPI_Testall is guaranteed to succeed since the corresponding MPI_Ssends are all complete.
        MPI_Testall(2, requests, &ready, MPI_STATUSES_IGNORE);
        if (ready)
            printf("[Process 0] Second attempt: both receives are complete.\n");
        else
            printf("[Process 0] Second attempt: not both receives are complete yet.\n");
    }
    else
    {
        // The "slave" MPI processes send the messages.
        int message = (my_rank == 1) ? 12345 : 67890;

        // Wait for the MPI_Testall #1 to be done.
        MPI_Barrier(MPI_COMM_WORLD);

        MPI_Ssend(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

        // Tell the sender it can now issue the MPI_Testall #2.
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Finalize();

*/