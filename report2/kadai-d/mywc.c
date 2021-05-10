#include <unistd.h> // read, close
#include <sys/types.h> // open
#include <sys/stat.h> //open
#include <fcntl.h> //open
#include <stdio.h> //perror
#include <stdlib.h> // exit
#include "string.h"

int word_flag = 0;
int line_flag = 0;

int file_open(const char *pathname, int flags){
  int fd;
  if((fd = open(pathname, flags)) < 0) {
    perror("open error");
    exit(1);
  }
  return fd;
}

void file_close(int fd){
  if(close(fd) < 0){
    perror("close error");
    exit(1);
  }
  return;
}

int count_line(const char *buf, int buf_size){
  int count = 0;
  int i;
  for(i = 0; i < buf_size; i++){
    if(line_flag == 1) count++;
    if(buf[i] == '\n'){
      line_flag = 1;
    }else{
      line_flag = 0;
    }
  }
  return count;
}

int count_word(const char *buf, int buf_size){
  int count = 0;
  int i;
  for(i = 0; i < buf_size; i++){
    if(buf[i] == ' ' || buf[i] == '\n'){
      word_flag = 1;
    }else{
      if(word_flag == 1){
	count++;
	word_flag = 0;
      }
    }
  }
  if(word_flag) count++;
  return count;
}

void print_result(int line_cnt, int word_cnt, int byte_cnt, const char *source){
  char buf[str_len(source) + 50];
  int ptr = 0;
  ptr += int2char(buf + ptr, line_cnt);
  buf[ptr] = ' ';
  ptr++;
  ptr += int2char(buf + ptr, word_cnt);
  buf[ptr] = ' ';
  ptr++;
  ptr += int2char(buf + ptr, byte_cnt);
  buf[ptr] = ' ';
  ptr++;
  str_join(buf + ptr, source);
  ptr += str_len(source);
  str_join(buf + ptr, "\n");
  ptr++;
  write(1, buf, ptr);
}

void mywc(const char *source, int buf_size){
  char buf[buf_size];
  ssize_t read_size;
  int fd = file_open(source, O_RDONLY);
  
  int line_cnt = 0;
  int word_cnt = 0;
  int byte_cnt = 0;
  
  while(1){
    read_size = read(fd, buf, buf_size);
    if(read_size > 0){ 
      byte_cnt += read_size;
      word_cnt += count_word(buf, read_size);
      line_cnt += count_line(buf, read_size);
    }else if(read_size == 0){
      break;
    }else{
      perror("read error");
      exit(1);
    }
  }

  file_close(fd);
  
  print_result(line_cnt + 1, word_cnt, byte_cnt, source);

  return;
}

int main(int argc, char *argv[]){
  if(argc != 2){
    write(2, "operand error\n", 14);
    exit(1);
  }

  mywc(argv[1], 8152);
  
  return 0;
}
