#include <stdio.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int world_rank, world_size;
    MPI_Init(&argc,&argv);
    // get rank of each processor
    MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int token;
    if (world_rank != 0) {
        MPI_Recv(&token, 1, MPI_INT, world_rank - 1, 0,
                MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received token %d from process %d\n",
              world_rank, token, world_rank - 1);
    } else {
        // Set the token's value if you are process 0
        token = -1;
    }
    MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % world_size,
            0, MPI_COMM_WORLD);

    // Now process 0 can receive from the last process.
    if (world_rank == 0) {
        MPI_Recv(&token, 1, MPI_INT, world_size - 1, 0,
                MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received token %d from process %d\n",
              world_rank, token, world_size - 1);
    }
    
    MPI_Finalize();
}
