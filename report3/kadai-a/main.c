#include "btree.c"
#include <pthread.h>
#include <stdio.h>

int main(){
    pthread_t thread;
    int i = 1;
    tnode *tree;
    
    tree = btree_create();
    if(pthread_create(&thread, NULL, ) != 0){
	perror("thread create error");
	exit(1);
    }
}
