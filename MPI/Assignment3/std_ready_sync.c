#include<mpi.h>
#include<stdio.h>

int main(int argc, char** argv){

  MPI_Init(&argc, &argv);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  double t1,t2,t3;
  // send time as message to the processes so as to compute time taken effectively.
  if(world_rank==0){
    int number = 12345;
    t1=MPI_Wtime();
    MPI_Send(&t1, 1, MPI_DOUBLE, 1,0, MPI_COMM_WORLD);
    printf("Process %d sent number %lf to process 1 in standard mode\n", world_rank, t1);
    t2=MPI_Wtime();
    MPI_Rsend(&t2, 1, MPI_DOUBLE, 2,0, MPI_COMM_WORLD);
    printf("Process %d sent number %lf to process 2 in ready mode \n", world_rank, t2);
    t3=MPI_Wtime();
    MPI_Ssend(&t3, 1, MPI_DOUBLE, 3,0, MPI_COMM_WORLD);
    printf("Process %d sent number %lf to process 3 in synchronous mode\n", world_rank, t3);
  }
  else{
    double received;
    MPI_Recv(&received, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    if(world_rank==1)
      printf("Process %d received number %lf from process in time %lf seconds \n", world_rank, received, MPI_Wtime()-received);
    if(world_rank==2)
      printf("Process %d received number %lf from process in time %lf seconds \n", world_rank, received, MPI_Wtime()-received);
    if(world_rank==3)
      printf("Process %d received number %lf from process in time %lf seconds \n", world_rank, received, MPI_Wtime()-received);
  }
  MPI_Finalize();
}