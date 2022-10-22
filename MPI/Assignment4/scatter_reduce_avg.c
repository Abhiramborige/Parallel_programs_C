#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float* create_rand_nums(int size){
  float* array=(float*)malloc(size*sizeof(float*));
  srand(time(0));
  for(int i=0; i<size; i++){
    // numbers in range 1 to 10.
    array[i]=(rand()%10)+1;
  }
  return array;
}

float compute_avg(float* arr, int size){
  int res;
  for(int i=0; i<size; i++){
    res=res+arr[i];
  }
  return res/size;
}

int main(int argc, char **argv) {
  srand(time(NULL));
  int elements_per_proc = 10;
  double start, end;

  MPI_Init(&argc, &argv);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  printf("The number of processes are: %d\n",world_size);
  MPI_Barrier(MPI_COMM_WORLD);
  start = MPI_Wtime();

  float *rand_nums = NULL;
  if (world_rank == 0) {
    printf("Abhiram Borige 19BCI0005\n");
    rand_nums=create_rand_nums(elements_per_proc*world_size);
    printf("The elements are: ");
    for(int i=0; i<elements_per_proc*world_size; i++){
      printf("%lf ",rand_nums[i]);
    }
    printf("\n");
  }

  float *sub_rand_nums = (float *)malloc(sizeof(float) * elements_per_proc);

  MPI_Scatter(rand_nums, elements_per_proc, MPI_FLOAT, sub_rand_nums, elements_per_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);

  float sub_avg = compute_avg(sub_rand_nums, elements_per_proc);
  float sub_avgs = 0;
  MPI_Reduce(&sub_avg, &sub_avgs, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
  if (world_rank == 0) {
    float avg = sub_avgs / world_size;
    printf("The average is %lf\n",avg);
  }

  MPI_Barrier(MPI_COMM_WORLD);
  end = MPI_Wtime();
  if (world_rank == 0) {
    printf("Time taken: %lf seconds\n\n", end - start);
  }

  MPI_Finalize();
}