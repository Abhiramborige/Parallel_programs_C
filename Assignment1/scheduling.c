#include<stdio.h>
#include<omp.h>
#define CHUNKSIZE 2
#define N 10

// function to invoke some computation of varying workload in different iterations
void func(int n){
  for(int i=0; i<n*1000000; i++);
}

int main(){
  int chunk, i;
  
  chunk=CHUNKSIZE;
  omp_set_num_threads(8);
  double t1,t2,t3;
  
  #pragma omp parallel default(shared) private(i)
  {
    t1=omp_get_wtime();
    // static
    #pragma omp for schedule(static, chunk)
    for(i=0; i<N; i++){
      func(i);
    }
    #pragma omp single
    t1=omp_get_wtime()-t1;

    t2=omp_get_wtime();
    // dynamic
    #pragma omp for schedule(dynamic, chunk)
    for(i=0; i<N; i++){
      func(i);
    }
    #pragma omp single
    t2=omp_get_wtime()-t2;

    t3=omp_get_wtime();
    // guided
    #pragma omp for schedule(guided, chunk)
    for(i=0; i<N; i++){
      func(i);
    }
    #pragma omp single
    t3=omp_get_wtime()-t3;

    #pragma omp master
    {
      printf("Time taken by static scheduling is %f\n",t1);
      printf("Time taken by dynamic scheduling is %f\n",t2);
      printf("Time taken by guided scheduling is %f\n",t3);
    }
  }
}