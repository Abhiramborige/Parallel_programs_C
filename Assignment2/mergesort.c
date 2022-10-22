#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>

int* merge_arrays(int* array, int l, int m, int r){
  int n1=m-l+1;
  int n2=r-m;
  
  // temporary arrays
  int L[n1], R[n2];
  
  for (int i=0; i<n1; i++){
    L[i]=array[l+i];
  }
  for (int j=0; j<n2; j++){
    R[j]=array[m+1+j];
  }
  
  int i = 0;
  int j = 0;
  int k = l;

  // using two pointers, inserting into the array
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      array[k] = L[i];
      i++;
    }
    else {
      array[k] = R[j];
      j++;
    }
    k++;
  }

  // Copy the remaining elements of L[] and R[], if any left
  while (i < n1) {
    array[k] = L[i];
    i++;
    k++;
  }
  while (j < n2) {
    array[k] = R[j];
    j++;
    k++;
  }
  return array;
}

void merge_sort(int* array, int l, int r){
  if(l>=r)return;
  int m=(l+r)/2;
  #pragma omp task
  merge_sort(array, l, m);
  #pragma omp task
  merge_sort(array, m+1, r);
  #pragma omp taskwait
  merge_arrays(array, l, m, r);
}

int* array_generator(int size){
  int* array=(int*)malloc(size*sizeof(int*));
  srand(time(0));
  for(int i=0; i<size; i++){
    // numbers in range 1 to 1000.
    array[i]=(rand()%1000)+1;
  }
  return array;
}

int main(){
  int size;
  printf("Enter the size of array: ");
  scanf("%d",&size);
  int* array=array_generator(size);
  for(int i=0; i<size; i++){
    printf("%d ",array[i]);
  }
  printf("\n");

  double t1,t2;
  t1=omp_get_wtime();
  omp_set_num_threads(4);
  #pragma omp parallel
  {
    #pragma omp single nowait
    merge_sort(array, 0, size-1);
  }
  t2=omp_get_wtime();
  printf("Time taken to sort the array: %lf\n", t2-t1);

  printf("The sorted array is:\n");
  for(int i=0; i<size; i++){
    printf("%d ",array[i]);
  }
}