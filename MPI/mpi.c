#include <stdio.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int my_rank, numprocs;
    MPI_Init(&argc,&argv);

    // get number of processors
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    // get rank of each processor
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

    // get the name of processor
    int  namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Get_processor_name(processor_name,&namelen);
    
    printf("Hello World! Process %d of %d on %s\n",my_rank,numprocs,processor_name);
    MPI_Finalize();
}
