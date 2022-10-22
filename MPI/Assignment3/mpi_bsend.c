#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Illustrates how to send a message in a blocking asynchronous fashion.
 * @details This application is meant to be used with 2 processes; 1 sender and
 * 1 receiver. The sender will declare a buffer containing enough space for 1
 * message that will contain 1 integer. It then attaches the buffer to MPI and
 * issues the MPI_Bsend. Finally, it detaches the buffer and frees it, while the
 * receiver prints the message received.
 **/
int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  // Get the number of processes and check only 2 are used.
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  if (my_rank == 0) {
    // Attaching the buffer to the send call
    int attach_buffer_size = MPI_BSEND_OVERHEAD + sizeof(int);
    char* attach_buffer = (char*)malloc(attach_buffer_size);
    MPI_Buffer_attach(attach_buffer, attach_buffer_size);

    // Making MPI_Bsend to process 1
    int buffer_sent = 12345;
    printf("Process %d sent value %d.\n", my_rank, buffer_sent);
    MPI_Bsend(&buffer_sent, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

    // Detach the buffer
    MPI_Buffer_detach(&attach_buffer, &attach_buffer_size);
    // free the memory
    free(attach_buffer);
  }
  else if (my_rank == 1) {
    // Receiving the message from any source and with any status message
    int received;
    MPI_Recv(&received, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received value: %d.\n", my_rank, received);
  }
  else{
    printf("The process %d is not part of the problem statement\n",my_rank);
  }

  MPI_Finalize();
}
