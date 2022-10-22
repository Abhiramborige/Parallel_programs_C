#include<stdio.h>
#include<omp.h>

int main(){
  
  int rows, cols, vec_length;
  printf("Enter the number of rows in matrix: ");
  scanf("%d", &rows);
  printf("Enter the number of columns in matrix: ");
  scanf("%d", &cols);
  int matrix[rows][cols];
  for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++){
      scanf("%d", &matrix[i][j]);
    }
  }
  printf("Enter the length of vector: ");
  scanf("%d", &vec_length);
  int vector[vec_length];
  for(int j=0; j<vec_length; j++){
    scanf("%d", &vector[j]);
  }

  omp_set_num_threads(4);
  int result[cols];
  #pragma omp parallel shared(result,vector) if(vec_length==cols)
  {
    if(omp_in_parallel()){
      int tid=omp_get_thread_num();
      printf("The current running thread is %d.\n",tid);
      #pragma omp for
      for(int i=0; i<rows; i++){
        result[i]=0;
        for(int j=0; j<cols; j++){
          #pragma critical
          result[i]=result[i]+(matrix[i][j]*vector[j]);
        }
      }
      #pragma omp single
      {
        printf("The multiplication result is: \n");
        for(int i=0; i<rows; i++){
          printf("%d ", result[i]);
        }
      }
    }
    else{
      printf("Cannot do vector matrix multiplication\n");
    }
  }
  return 0;
}