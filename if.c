#include<stdio.h>
#include<omp.h>

void test(int val){
  #pragma omp parallel if (val!=2)
  if (omp_in_parallel()){
    #pragma omp single
    printf("val is %d, parallelised with %d threads\n", val, omp_get_num_threads());
  }
  else{
    printf("val is %d, serialized\n", val);
  }
}

int main(){
  omp_set_num_threads(2);
  test(0);
  test(1);
  test(2);
}