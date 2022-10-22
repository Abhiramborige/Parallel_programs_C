#include<stdio.h>
#include<omp.h>

void get_min(int* array, int n, int global_min){
  int min=global_min;
  int i;
  /* #pragma omp for private(i) */
  for(i=0; i<n; i++){
    if(array[i]<min){
      min=array[i];
    }
  }
  #pragma omp critical
  if(min<global_min){
    global_min=min;
  }
  printf("Min element is %d\n",global_min);
}

void get_max(int* array, int n, int global_max){
  int max=global_max;
  int i;
  /* #pragma omp for private(i) */
  for(i=0; i<n; i++){
    if(array[i]>max){
      max=array[i];
    }
  }
  #pragma omp critical
  if(max>global_max){
    global_max=max;
  }
  printf("Max element is %d\n",global_max);
}

int main(){
  int n;
  printf("Enter the number of elements: ");
  scanf("%d",&n);
  int array[n];
  printf("Enter the elements:\n");
  for (int i=0; i<n; i++){
    scanf("%d",&array[i]);
  }

  omp_set_num_threads(4);
  int global_max=__WINT_MIN__, global_min=__INT_MAX__;
  double t1,t2,t3,t4;
  #pragma omp parallel shared(array,n, global_max, global_min)
  {
    #pragma omp sections
    {
      #pragma omp section
      {
        t1=omp_get_wtime();
        get_min(array, n, global_min);
        t2=omp_get_wtime();
      }
      #pragma omp section
      {
        t3=omp_get_wtime();
        get_max(array, n, global_max);
        t4=omp_get_wtime();
      }
    }
    #pragma omp master
    {
      printf("Time taken for max calculation is %lf\n",t4-t3);
      printf("Time taken for min calculation is %lf\n",t2-t1);
    }
  }
  return 0;
}