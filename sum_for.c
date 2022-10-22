#include<stdio.h>
#include<omp.h>
#define MAX 100000000
int array[MAX];

int main(){
  int sum=0;
  double t1,t2;
  for(int i=0; i<MAX; i++){
    array[i]=1;
  }
  t1=omp_get_wtime();
  int tid, numt,i;

  // In parallel, Sum is wrong – because of race condition
  // More time – cache coherence
  #pragma omp parallel default(shared) private(i,tid)
  {
    // from and to define the range of array on which a thread has to make operations.
    int partial_sum=0;

    tid=omp_get_thread_num();
    numt=omp_get_num_threads();

    printf("Thread ID %d is working on the array\n",tid);

    // we distribute the iterations amongst the threads using for directive
    #pragma omp for
    for(i=0; i<MAX; i++){
      partial_sum+=array[i];
    }
    #pragma omp critical
    sum+=partial_sum;
  }
  t2=omp_get_wtime();
  printf("Sum is %d\nTime taken is %g\n",sum,t2-t1);
  return 0;
}