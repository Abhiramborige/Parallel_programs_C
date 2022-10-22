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
  int i;

  #pragma omp parallel for default(shared) private(i) reduction(+:sum)
  for(i=0; i<MAX; i++){
    sum+=array[i];
  }
  #pragma omp critical
  
  t2=omp_get_wtime();
  printf("Sum is %d\nTime taken is %g\n",sum,t2-t1);
  return 0;
}