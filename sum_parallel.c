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
    int from, to, partial_sum=0;

    tid=omp_get_thread_num();
    numt=omp_get_num_threads();

    // Distribute the work here.
    from=(MAX/numt)*tid;
    to=(MAX/numt)*(tid+1)-1;
    if(tid==numt-1){
      to=MAX-1;
    }
    printf("Thread ID %d is working on the array starting from %d till %d\n",tid,from,to);

    for(i=from; i<=to; i++){
      //#pragma omp critical
      // this summing line is the section where only a single thread can enter the region.
      // used to deal with cases of mutual exclusion. Used to safeguard operations on shared variables.
      partial_sum+=array[i];
    }
    #pragma omp critical
    // commenting inside the loop and adding all partial sums in critical region.
    // in this way we can reduce synchronization.
    sum+=partial_sum;
  }
  t2=omp_get_wtime();
  printf("Sum is %d\nTime taken is %g\n",sum,t2-t1);
  return 0;
}