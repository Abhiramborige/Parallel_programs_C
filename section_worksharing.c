#include<stdio.h>
#include<omp.h>
#define N 2

int main(){
  int i;
  float a[N], b[N], c[N], d[N];
  for(i=0; i<N; i++){
    a[i]=i*1.5;
    b[i]=i+15.50;
  }
  omp_set_num_threads(2);
  int tid, numt;
  #pragma omp parallel shared(a,b,c,d) private(i,tid)
  {
    tid=omp_get_thread_num();
    numt=omp_get_num_threads();
    printf("Thread ID: %d of %d is working\n", tid, numt);
    #pragma omp sections nowait
    {
      #pragma omp section
      for(i=0; i<N; i++){
        c[i]=a[i]+b[i];
      }

      #pragma omp section
      for(i=0; i<N; i++){
        d[i]=a[i]*b[i];
      }
      
      #pragma omp section
      {
        for(i=0; i<N; i++){
          printf("%f ",c[i]);
        }
        printf("\n");
      }

      #pragma omp section
      {
        for(i=0; i<N; i++){
          printf("%f ",d[i]);
        }
        printf("\n");
      }

    }
  }
}