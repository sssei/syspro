#ifndef _REENTRANT
#define _REENTRANT
#endif
#include "bb.h"
#define BUFF_SIZE 11

int bb_buf[BUFF_SIZE];
int buf_in = 0;
int buf_out = 0;

int bb_get(void){
  pthread_mutex_lock(&mutex);
  while(buf_in == buf_out){
    pthread_cond_wait(&cond_in, &mutex);    
  }
  int res = bb_buf[buf_out];
  buf_out = (buf_out + 1) % BUFF_SIZE;
  pthread_cond_signal(&cond_out);
  pthread_mutex_unlock(&mutex);
  return res;
}

void bb_put(int i){
  pthread_mutex_lock(&mutex);
  while(buf_out == (buf_in + 1) % BUFF_SIZE){
    pthread_cond_wait(&cond_out, &mutex);
  }
  bb_buf[buf_in] = i;
  buf_in = (buf_in + 1) % BUFF_SIZE;
  pthread_cond_signal(&cond_in);
  pthread_mutex_unlock(&mutex);
  return;
}
