#include <unistd.h> // read, close
#include <sys/types.h> // open
#include <sys/stat.h> //open
#include <fcntl.h> //open
#include <stdio.h> //perror
#include <stdlib.h> // exit

int file_open(const char *pathname, int flags){
  int fd;
  if((fd = open(pathname, flags)) < 0) {
    perror("open error");
    exit(1);
  }
  return fd;
}

void file_write(int fd, const char *buf, size_t bytes_size){
  const char* ptr = buf;
  const char* const endp = buf + bytes_size;

  while(ptr < endp){
    ssize_t write_size = write(fd, buf, bytes_size);
    if(write_size < 0){
      perror("write error");
      exit(1);
    }
    ptr += write_size;
  }
  return;
}

void file_close(int fd){
  if(close(fd) < 0){
    perror("close error");
    exit(1);
  }
  return;
}

void mycopy(const char *source, const char *target, int buf_size){
  char buf[buf_size];
  ssize_t read_size;
  int fd_s = file_open(source, O_RDONLY);
  int fd_t = file_open(target, O_WRONLY | O_CREAT);

  while(1){
    read_size = read(fd_s, buf, buf_size);
    if(read_size > 0){ 
      file_write(fd_t, buf, read_size);
    }else if(read_size == 0){
      break;
    }else{
      perror("read error");
      exit(1);
    }
  }

  file_close(fd_s);
  file_close(fd_t);

  return;
}

