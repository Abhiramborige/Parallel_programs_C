#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

int* fibonacci(int n){
  int first=0, second=1, next;
  int* result=(int*)malloc(n*(sizeof(int)));
  omp_lock_t lock;
  omp_init_lock(&lock);
  omp_set_num_threads(4);
  #pragma omp parallel firstprivate(n)
  {
    #pragma omp for
    for (int i=0; i<n; i++){
      omp_set_lock(&lock);
      if (i<=1){
        next=i;
      }
      else{
        next=first+second;
        #pragma omp task shared(first, second, next)
        first=second;
        #pragma omp task shared(first, second, next)
        second=next;
      }
      #pragma omp taskwait
      result[i]=next;
      omp_unset_lock(&lock);
    }
    omp_destroy_lock(&lock);
  }
  return result;
}


int main(){
  int n;
  printf("Enter the length of fibonacci series: ");
  scanf("%d", &n);
  int *result=(int*)malloc(n*(sizeof(int)));
  result=fibonacci(n);
  printf("First %d terms of Fibonacci series are:\n", n);
  for(int i=0; i<n; i++){
    printf("%d ", result[i]);
  }
}