#include<stdio.h>
#include<omp.h>

int do_some_work(int id){
  for(int i=0; i<id*100000000; i++);
  return id;
}

int main(){
  omp_lock_t lock;
  omp_init_lock(&lock);
  int id,tmp;
  #pragma omp parallel shared(lock) private(id,tmp)
  {
    id=omp_get_thread_num();
    tmp=do_some_work(id);
    omp_set_lock(&lock);
    printf("%d %d\n",id,tmp);
    omp_unset_lock(&lock);
  }
  omp_destroy_lock(&lock);
}