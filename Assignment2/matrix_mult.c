#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<stdlib.h>

typedef struct matrix{
  int rows;
  int columns;
  int** array;
} matrix;

// matrix multiplication function here.
matrix* matrix_multiplication(matrix *mat1, matrix *mat2){
  matrix *mat3;
  mat3 = (matrix*)malloc(sizeof(matrix));
  mat3->rows=mat1->rows;
  mat3->columns=mat2->columns;
  mat3->array=(int**)malloc(mat3->rows * sizeof(int*));
  // writing as seperate for memory allocation because time taken for this must not be considered.
  for (int i=0; i<mat3->rows; i++) {
      mat3->array[i]=(int*)malloc(mat3->columns * sizeof(int));
  }

  omp_set_num_threads(4);
  #pragma omp parallel shared(mat1, mat2,  mat3)
  {
    #pragma omp for schedule(dynamic)
    for (int i=0; i<mat3->rows; i++) {
      int tid=omp_get_thread_num();
      for (int j=0; j<mat3->columns; j++) {
        //printf("Thread ID %d is working on %d row of matrix 1 and %d column of matrix 2\n",tid, i, j);
        // printing is consuming time, so commented it.
        int temp=0;
        mat3->array[i][j]=0;
        for (int k=0; k<mat2->rows; k++) {
          temp += mat1->array[i][k] * mat2->array[k][j];
        }
          mat3->array[i][j]=temp;
      }
    }
  }
  return mat3;
}

void print_matrix(matrix* mat){
  for (int i=0; i<mat->rows; i++) {
    for (int j=0; j<mat->columns; j++) {
      printf("%d ", mat->array[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int a[10][10], b[10][10], c[10][10];
  matrix *mat1, *mat2;
  // memory allocation
  mat1 = (matrix*)malloc(sizeof(matrix));
  mat2 = (matrix*)malloc(sizeof(matrix));
  printf("Enter no. of rows and columns for first matrix\n");
  scanf("%d %d", &mat1->rows, &mat1->columns);
  printf("Enter no. of rows and columns for second matrix\n");
  scanf("%d %d", &mat2->rows, &mat2->columns);

  if (mat1->columns==mat2->rows) {
    srand(time(0));
    mat1->array=(int**)malloc(mat1->rows * sizeof(int*));
    for (int i=0; i<mat1->rows; i++) {
      mat1->array[i]=(int*)malloc(mat1->columns * sizeof(int));
      for (int j=0; j<mat1->columns; j++) {
        // numbers in range 1 to 10.`
        mat1->array[i][j]=(rand()%10)+1;
      }
    }
    mat2->array=(int**)malloc(mat2->rows * sizeof(int*));
    for (int i=0; i<mat2->rows; i++) {
      mat2->array[i]=(int*)malloc(mat2->columns * sizeof(int));
      for (int j=0; j<mat2->columns; j++) {
        // numbers in range 1 to 10.
        mat2->array[i][j]=(rand()%10)+1;
      }
    }
    printf("The first matrix is:\n");
    print_matrix(mat1);
    printf("The second matrix is:\n");
    print_matrix(mat2);

    double t1,t2;
    t1=omp_get_wtime();
    matrix *mat3=matrix_multiplication(mat1, mat2);
    t2=omp_get_wtime();
    printf("The multiplication of matrices 1 and 2 is:\n");
    print_matrix(mat3);
    printf("The time taken for multiplicaiton is %lf\n",t2-t1);
  }
  else {
    printf("Invalid row column count");
  }
}