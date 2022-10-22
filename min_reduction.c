#include<stdio.h>
#include<omp.h>
#define N 10

int min(int a, int b){
  if(a<b){
    return a;
  }
  else{
    return b;
  }
}

int main(){
  int arr[N]={95,33,17,54,65,55,26,38,94,56};
  int x=arr[0];
  omp_set_num_threads(4);
  #pragma omp parallel shared(arr)
  {
    #pragma omp parallel for reduction(min:x)
    for (int i=0; i<N; i++)
      x = min(x,arr[i]);
  }
  printf("%d is the smallest\n",x);
}