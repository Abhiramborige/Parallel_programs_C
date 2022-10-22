#include<stdio.h>
#include<omp.h>

int main(){
  int x=44;int i;
  #pragma omp parallel for firstprivate(x)
    for(i=0; i<10; i++){
      x=i;
      printf("Thread no. %d and x = %d\n", omp_get_thread_num(), x);
    }
    printf("X is %d",x);
}