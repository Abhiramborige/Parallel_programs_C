#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

// for inputting large arrays, use merge parallel sort instead of this.
int* sort_array(int* array, int size){
  int temp=0;
  for (int i=0; i<size; i++){
    for (int j=i+1; j<size; j++) {
      if(array[i]>array[j]){ 
          temp=array[i];    
          array[i]=array[j];
          array[j]=temp;    
      }
    }
  }
  return array;
}

int binary_search(int* array, int search_for, int low, int high){
  int answer, i;
  bool flag=false;
  omp_set_num_threads(4);
  #pragma omp parallel shared(array, answer, flag) private(i)
  {
    #pragma omp for schedule(dynamic) nowait private(i)
    for(i=low; i<=high; i++){
      int mid=(low+high)/2;
      if(flag) continue;
      if (array[mid]==search_for){
        answer=mid;
        flag=true;
      }
      if (array[mid]<search_for){
        low=mid+1;
      }
      if (array[mid]>search_for){
        high=mid-1;
      }
    }
  }
  return answer;
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

  // sort is not part of parallel execution as it is not part of binary search.
  array=sort_array(array, size);
  printf("After sorting:\n");
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
  index=binary_search(array, search_for, 0, size-1);
  t2=omp_get_wtime();
  printf("The element %d is found at index %d\n",search_for, index);
  printf("Time taken to search for the element in array: %lf\n", t2-t1);
  return 0;
}