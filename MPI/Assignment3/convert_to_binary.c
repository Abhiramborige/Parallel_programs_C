#include <stdio.h>
#include <math.h>
#include<string.h>
#include<stdlib.h>

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
char* convert_deci_to_bin(int num){
  int rem=0;
  char* res=(char*)malloc(sizeof(char));
  int i=0;
  while(num!=0){
    rem=num%2;
    res=(char*)realloc(res, (i+1)*sizeof(char));
    num=num/2;
    char chr=rem+'0';
    res[i]=chr;
    i++;
  }
  return strrev(res);
}

int main(){
  printf("%d is the decimal\n",convert_bin_to_deci("101"));
  char* str=convert_deci_to_bin(10);
  printf("%s is the binary\n", str);
  char binary[5]="000";
  printf("%d\n",strcmp(binary,"001"));
  char* s=(char*)malloc(sizeof(char));
  for(int i=0; i<5; i++){
    s=(char*)realloc(s, (i+1)*sizeof(char));
    s[i]='a';
  }
  printf("%s\n",s);
}