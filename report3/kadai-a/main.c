#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include "btree.h"
#define THREAD_NUM 10

typedef struct{
  int value;
  tnode **tree;
}thread_data;

void *threadFunc(void *arg){
  thread_data* t = (thread_data*)arg;
  int i;
  for(i = 0; i < 1000; i++){
    btree_insert(t->value + i, t->tree);    
  }
  pthread_exit(NULL);
}

int main(){
  pthread_t thread[THREAD_NUM];
  tnode *tree;
  int i;

  tree = btree_create();

  for(i = 0; i < THREAD_NUM; i++){
    thread_data t = {i * 1000, &tree};
    if(pthread_create(&thread[i], NULL, threadFunc, &t) != 0){
      printf("Thread creation failed\n");
      return 1;
    }
  }

  for(i = 0; i < THREAD_NUM; i++){
    if(pthread_join(thread[i], NULL) != 0){
      printf("Thread join failed\n");
      return 1;
    }
  }
  
  btree_dump(tree);
  btree_destroy(&tree);
  return 0;
}
