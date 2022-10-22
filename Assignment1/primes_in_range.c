#include<stdio.h>
#include<omp.h>
#include<stdbool.h>

bool isPrime(int n){
  if(n==1){
    return false;
  }
  else if(n==2){
    return true;
  }
  for(int i=2; i<n; i++){
    if(n%i==0){
      return false;
    }
  }
  return true;
}

int main(){
  int n;
  printf("Enter the max of range: ");
  scanf("%d",&n);

  int count=0;
  omp_set_num_threads(4);
  #pragma omp parallel default(shared)
  {
    #pragma omp for reduction(+:count)
    for(int i=1; i<=n; i++){
      double t1=omp_get_wtime();
      if(isPrime(i)){
        count+=1;
      }
      double t2=omp_get_wtime();
      printf("The time taken for computation of %d is %lf\n",i,t2-t1);
    }
  }
  printf("The total primes in the range 1 to %d is %d\n",n,count);
  return 0;
}