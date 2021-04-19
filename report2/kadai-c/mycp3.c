#include <stdio.h>
#include <stdlib.h>

FILE* file_open(const char *pathname, char* flag){
  FILE *fp;
  if((fp = fopen(pathname, flag)) == NULL) {
    perror("open error");
    exit(1);
  }
  return fp;
}

void file_write(const char *buf, size_t bytes_size, FILE *fp){
  size_t write_size = fwrite(buf, bytes_size, 1, fp);
  if(write_size == 0){
    perror("write error");
    exit(1);
  }
  return;
}

void file_close(FILE *fp){
  if(fclose(fp) != 0){
    perror("close error");
    exit(1);
  }
  return;
}

void set_buf(FILE *fp){
  if(setvbuf(fp, NULL, _IONBF, 1) != 0){
    perror("setvbuf error");
    exit(1);
  }
  return;
}

void mycopy3(const char *source, const char *target, int buf_size){
  char buf[buf_size];
  ssize_t read_size;
  FILE *fp_s = file_open(source, "r");
  FILE *fp_t = file_open(target, "w");

  set_buf(fp_s);
  set_buf(fp_t);
  
  while(1){
    read_size = fread(buf, buf_size, 1, fp_s);
    if(read_size > 0){ 
      file_write(buf, read_size, fp_t);
    }else if(read_size == 0){
      break;
    }else{
      perror("read error");
      exit(1);
    }
  }

  file_close(fp_s);
  file_close(fp_t);

  return;
}
