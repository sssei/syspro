#include "string.h"

size_t str_len(const char* str){
  size_t len;
  for(len = 0; str[len] != '\0'; len++);
  return len;
}

void str_join(char* str1, const char* str2){
  int i;
  int str1_len = str_len(str1);
  for(i = 0; i <= str_len(str2); i++){
    str1[str1_len + i] = str2[i];
  }

  return;
}

int int2char(char *buf, int num){
  int num_size = 0;
  int i;
  int n = num;
  int mod = 1;
  if(num == 0){
    buf[0] = '0';
    return 1;
  }
  while(n){
    n /= 10;
    num_size++;
    mod *= 10;
  }
  mod /= 10;
  for(i = 0; i < num_size; i++){
    buf[i] = (num / mod) % 10 + '0';
    mod /= 10;
  }
  buf[i] = '\0';
  return num_size;
}




