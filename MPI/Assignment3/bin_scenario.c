#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>
#include<stdbool.h>

int convert_bin_to_deci(char* deci){
  int dec=0, i=0, rem;
  int n=atoi(deci);
  while (n!=0) {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    ++i;
  }
  return dec;
}
void revstr(char *str1){
  int i, len, temp;
  len = strlen(str1); 
  for (i = 0; i < len/2; i++)  {  
    temp = str1[i];  
    str1[i] = str1[len - i - 1];  
    str1[len - i - 1] = temp;  
  }
}  

char* convert_deci_to_bin(int num){
  int rem=0;
  char* res=(char*)malloc(sizeof(char));
  int i=0;
  if(num==0){
    res[i]='0';
    res[i+1]='\0';
    return res;
  }
  while(num!=0){
    rem=num%2;
    res=(char*)realloc(res, (i+1)*sizeof(char));
    num=num/2;
    char chr=rem+'0';
    res[i]=chr;
    i++;
  }
  res[i]='\0';
  revstr(res);
  return res;
}


int main(int argc, char *argv[]){
    int my_rank, world_size;
    char* binary=convert_deci_to_bin(0);
    int rank_control=0;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    /* while(true){ */

      if(my_rank==0){
        if(rank_control!=0){
          MPI_Recv(binary, 5,MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          printf("Process %d Received %s\n",my_rank, binary);
          if(strcmp(binary,"111")==0){
            MPI_Abort(MPI_COMM_WORLD, MPI_SUCCESS);
          }
          binary=convert_deci_to_bin(convert_bin_to_deci(binary)+1);
          rank_control++;
        }
        MPI_Send(binary, 5, MPI_CHAR, (my_rank+1)%3, 0, MPI_COMM_WORLD);
        printf("Sent %s binary number from %d process to %d process\n", binary, my_rank, (my_rank+1)%3);
      }
      else if(my_rank==1 || my_rank==2){
        
        MPI_Recv(binary, 5, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d Received %s\n",my_rank, binary);
        if(strcmp(binary,"111")==0){
          MPI_Abort(MPI_COMM_WORLD, MPI_SUCCESS);
        }
        binary=convert_deci_to_bin(convert_bin_to_deci(binary)+1);
        rank_control++;
        MPI_Send(binary, 5, MPI_CHAR, (my_rank+1)%3, 0, MPI_COMM_WORLD);
        printf("Sent %s binary number from %d process to %d process\n", binary, my_rank, (my_rank+1)%3);
      }
      else{
        printf("This processor with rank %d is not a part of the problem statement\n",my_rank);
      }

    /* } */
    
    MPI_Finalize();
}
