#include "bb.h"
#include <pthread.h>
#include <stdio.h>
#include <assert.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_out = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_in = PTHREAD_COND_INITIALIZER;

void *thread_get(void *arg){
  int res = bb_get();
  printf("%d\n", res);
  pthread_exit(NULL);
}

void *thread_put(void *arg){
  int *i = (int *)arg;
  bb_put(*i);
  pthread_exit(NULL);
}
  
int main(){
  int i,j;
  pthread_t thread[20];

  /* Test for checking if all the item can be got in the same order as put */
  for(i = 0; i < 10; i++){
    bb_put(i);
  }
  for(i = 0; i < 10; i++){
    assert(bb_get() == i);
  }

  /* Insert and get parallelly */
  for(i = 0; i < 5000; i++){
    for(j = 0; j < 20; j++){
      if(pthread_create(&thread[j], NULL, thread_put, &i) != 0){
	printf("error: pthread_create\n");
	return 1;
      }
    }
    for(j = 0; j < 20; j++){
      if(pthread_create(&thread[j], NULL, thread_get, NULL) != 0){
	printf("error: pthread_create\n");
	return 1;
      }
    }
  }

  return 0;
}
