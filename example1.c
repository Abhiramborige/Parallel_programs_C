#include <omp.h>
#include <stdio.h>
int main() {
  omp_set_num_threads(4);
  int tid,numt;
  printf("Processor count: %d\n",omp_get_num_procs());
  // specifying private and shared variables.
  #pragma omp parallel private(tid) shared(numt)
  {
    tid = omp_get_thread_num();
    if(tid==0) numt = omp_get_num_threads();

    // introducing long task
    for(int j=0; j<100000000; j++);

    printf("Thread ID: %d of %d\n", tid, numt);
    // threads wait here till all complete their execution.
  }
}

/* 
1. omp_set_dynamic: This indicates that the number of threads available in upcoming parallel region can be adjusted by the runtime. 
2. omp_get_max_threads: This returns the the integer that is equal to or greater than the number of threads that would be available if a parallel region without num_threads were defined at that point in code.
3. omp_set_nested: This enables nested parallelism.
4. omp_test_lock: This attempts to set a lock but diesnt block thread execution.
5. omp_get_wtime: Example of time exection. Returns the time in seconds from the point of time elapsed.
6. omp_get_wtick: Returns the number of seconds between the processor clock ticks.

 */