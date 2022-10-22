#include <omp.h>
#include <stdio.h>

int main() {
  omp_set_num_threads(4);
  int numt;
  #pragma omp parallel default(shared)
  {
    int tid;
    // more conventional way of work to be done by single thread
    // when no wait is claused, one thread will execute single region and synchronization is removed.
    // nowait is generally used to rmeove implicit barriers created by worksharing constructs.
    #pragma omp single nowait
    {
      // single is implicit barrier whereas barrier is explicit one.
      for(int j=0; j<100000000; j++);
      numt = omp_get_num_threads();
    }

    tid = omp_get_thread_num();

    // because using two parallel regions is simly a overhead, we use barrier.
    // #pragma omp barrier
    // removing barrier because single construct is used.
    printf("Thread ID: %d of %d\n", tid, numt);
  }
}