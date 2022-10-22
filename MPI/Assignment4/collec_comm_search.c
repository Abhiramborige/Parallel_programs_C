#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* create_rand_nums(int size){
  int* array=(int*)malloc(size*sizeof(float*));
  srand(time(0));
  for(int i=0; i<size; i++){
    // numbers in range 1 to 10.
    array[i]=(rand()%10)+1;
  }
  return array;
}

int main(int argc, char **argv) {
  srand(time(NULL));
  int elements_per_proc = 10;
  double start, end;

  MPI_Init(NULL, NULL);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Barrier(MPI_COMM_WORLD);
  start = MPI_Wtime();

  int *rand_nums = NULL;
  int num;
  int count = 0;
  if (world_rank == 0) {
    rand_nums=create_rand_nums(elements_per_proc*world_size);
    printf("The elements are: ");
    for(int i=0; i<elements_per_proc*world_size; i++){
      printf("%d ",rand_nums[i]);
    }
    printf("\n");
    num = rand() % 10;
    printf("Element to be searched is %d\n", num);
  }

  int *sub_rand_nums = (int *)malloc(sizeof(int) * elements_per_proc);

  MPI_Scatter(rand_nums, elements_per_proc, MPI_INT, sub_rand_nums, elements_per_proc, MPI_INT, 0,MPI_COMM_WORLD);
  MPI_Bcast(&num, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);

  for (int i = 0; i < elements_per_proc; i++) {
    if (sub_rand_nums[i] == num) {
      count++;
      printf("Element %d found at index : %d\n", num, world_rank * elements_per_proc + i);
    }
  }

  if (world_rank == 0) {
    free(rand_nums);
  }
  free(sub_rand_nums);

  MPI_Barrier(MPI_COMM_WORLD);
  end = MPI_Wtime();

  if (world_rank == 0) {
    printf("Time taken: %lf seconds\n\n", end - start);
  }
  MPI_Finalize();
}