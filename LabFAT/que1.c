#include <omp.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int ackermann(int m, int n, int ans){
  int res=0;
  #pragma omp parallel private(res) shared(ans,m,n)
  {
    if (m==0){
      #pragma omp task
      res=n+1;
    }
    else if(m>0 && n==0){
      #pragma omp task
      res=ackermann(m-1,1, ans);
    }
    else if(m>0 && n>0){
      #pragma omp task
      res=ackermann(m-1, ackermann(m,n-1,ans), ans);
    }
    #pragma omp barrier
    ans+=res;
  }
  return ans;
}


int main() {
  int m, n;
  printf("Enter the value of m: ");
  scanf("%d", &m);
  printf("Enter the value of n: ");
  scanf("%d", &n);
  double t1,t2;
  t1=omp_get_wtime();
  int res=ackermann(m,n,0);
  printf("The result of ackermann function is %d\n",res);
  t2=omp_get_wtime();
  printf("The time taken is %lf seconds\n",t2-t1);
}