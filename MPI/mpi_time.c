#include <mpi.h>
#include <stdio.h>

/*NOTE: The MPI_Wtime calls can be placed anywhere between the MPI_Init
and MPI_Finalize calls.*/

int main(int argc, char **argv) {
  int node;
  double mytime; /*declare a variable to hold the time returned*/

  MPI_Init(&argc, &argv);
  mytime = MPI_Wtime(); /*get the time just before work to be timed*/
  MPI_Comm_rank(MPI_COMM_WORLD, &node);

  printf("Hello World from Node %d\n", node);

  mytime = MPI_Wtime() - mytime; /*get the time just after work is done
                                   and take the difference */
  printf("Timing from node %d is %lf seconds.\n", node, mytime);
  MPI_Finalize();
}