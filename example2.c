#include <omp.h>
#include <stdio.h>

void main(void) {
  int base, pow, tid, result = 1;
  printf("Enter base value:");
  scanf("%d", &base);
  printf("\nEnter power value:");
  scanf("%d", &pow);
  omp_set_num_threads(pow);

  #pragma omp parallel shared(pow)
  {
    tid = omp_get_thread_num();
    result = result * base;
    printf("result %d\n", result);
  }
  printf("Exponential of number %d^%d:\t%d\n", base, pow, result);
}