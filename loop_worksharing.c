#include<stdio.h>
#include<omp.h>
#define CHUNKSIZE 1
#define N 8

int main(){
  int nthreads, tid, chunk, i;
  float a[N], b[N], c[N];
  for (i=0; i<N; i++){
    a[i]=b[i]=i*1.0;
  }
  chunk=CHUNKSIZE;
  omp_set_num_threads(4);
  #pragma omp parallel default(shared) private(i,tid)
  {
    tid=omp_get_thread_num();
    if(tid==0){
      nthreads=omp_get_num_threads();
      printf("Number of threads is %d\n",nthreads);
    }
    printf("Thread %d is starting...\n",tid);

    // schedule describes how iterations of the loop are divided among the threads in team
    double t1=omp_get_wtime();
    #pragma omp for schedule(static, chunk)
    for(i=0; i<N; i++){
      c[i]=a[i]+b[i];
      printf("Thread %d: c[%d]=%f\n",tid,i,c[i]);
    }
    double t2=omp_get_wtime();
    printf("%f\n",t2-t1);
  }
}