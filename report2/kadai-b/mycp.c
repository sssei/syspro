#include <unistd.h> // read, close
#include <sys/types.h> // open
#include <sys/stat.h> //open
#include <fcntl.h> //open
#include <stdio.h> //perror
#include <stdlib.h> // exit
#include <sys/stat.h> //stat

#define BUF_SIZE 512

int str_cmp(const char* s1, const char* s2){
    int i = 0;
    while(1){
	if(s1[i] != s2[i]){
	    return 1;
	}
	if(s1[i] == '\0'){
	    return 0;
	}
	i++;
    }
}

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

void mycopy(const char *source, const char *target){
  char buf[BUF_SIZE];
  ssize_t read_size;
  int fd_s = file_open(source, O_RDONLY);
  int fd_t = file_open(target, O_WRONLY | O_CREAT);

  while(1){
    read_size = read(fd_s, buf, BUF_SIZE);
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

void permission(const char *source, const char *target){
    struct stat stat_buf ;
    if(stat(source, &stat_buf) == 0){
	if(chmod(target, stat_buf.st_mode & 0777) != 0){
	    perror("chmod: error");
	    exit(1);
	}
    }else{
	perror("stat: error");
	exit(1);
    }
}

int main(int argc, char *argv[]){
  if(argc != 3){
    write(2, "operand error\n", 14);
    exit(1);
  }

  if(str_cmp(argv[1], argv[2]) == 0){
      write(2, "cp: the same file\n", 18);
      exit(1);
  }
  mycopy(argv[1], argv[2]);
  permission(argv[1], argv[2]);
  
  return 0;
}
