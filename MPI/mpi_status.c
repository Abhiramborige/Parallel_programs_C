#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  printf("Abhiram\n");
  if (my_rank == 0) {
    int buffer_sent = 12345;
    int tag = 67890;
    printf("MPI process %d sends value %d with tag %d\n", my_rank, buffer_sent,
           tag);
    MPI_Ssend(&buffer_sent, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
  } else {
    int buffer_received;
    MPI_Status status;
    MPI_Recv(&buffer_received, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,
             MPI_COMM_WORLD, &status);

    printf(
        "MPI Process %d received value %d from rank %d with tag %d and error "
        "code %d\n",
        my_rank, buffer_received, status.MPI_SOURCE, status.MPI_TAG,
        status.MPI_ERROR);
  }
  MPI_Finalize();
  return 0;
}