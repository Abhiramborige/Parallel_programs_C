#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

int linear_search(int* array, int search_for, int size){
  int i, found=0;
  bool flag=false;
  omp_set_num_threads(4);
  #pragma omp parallel shared(flag, found) private(i)
  {
    #pragma omp for schedule(static) nowait private(i)
    for(i=0; i<size; i++){
      if(flag) {
        continue;
      }
      if(array[i]==search_for){
        flag=true;
        found=i;
      }
    }
  }
  return found;
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
  int index;
  int search_for;
  printf("What do you want to search for: ");
  scanf("%d",&search_for);
  t1=omp_get_wtime();
  index=linear_search(array, search_for, size);
  t2=omp_get_wtime();
  printf("The element %d is found at index %d\n",search_for, index);
  printf("Time taken to search for the element in array: %lf\n", t2-t1);
  return 0;
}