#include <omp.h>
#include <stdio.h>

int ackermann(int m, int n){
  int res;
  if (m==0){  
    return n+1;
  }
  else if(m>0 && n==0){
    return ackermann(m-1,1);
  }
  else if(m>0 && n>0){
    return ackermann(m-1, ackermann(m,n-1));
  }
}

int main() {
  int m, n;
  printf("Enter the value of m: ");
  scanf("%d", &m);
  printf("Enter the value of n: ");
  scanf("%d", &n);
  double t1,t2;
  t1=omp_get_wtime();
  int res=ackermann(m,n);
  printf("The result of ackermann function is %d\n",res);
  t2=omp_get_wtime();
  printf("The time taken is %lf seconds\n",t2-t1);
}