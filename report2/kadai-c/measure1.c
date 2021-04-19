#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "mycp.h"

int main(){
  struct timespec start, end;
  
  clock_gettime(CLOCK_REALTIME, &start);
  mycopy("sourcefile", "targetfile1", 1);
  clock_gettime(CLOCK_REALTIME, &end);  

  long long elapsed_sec = 1000 * 1000 * 1000 * (end.tv_sec - start.tv_sec);
  elapsed_sec += end.tv_nsec - start.tv_nsec;
  double elapsed_time = (double) elapsed_sec / (1000 * 1000 * 1000);
  printf(" one byte  : %.9lf sec\n", elapsed_time);

  clock_gettime(CLOCK_REALTIME, &start);
  mycopy("sourcefile", "targetfile2", 8192);
  clock_gettime(CLOCK_REALTIME, &end);  

  elapsed_sec = 1000 * 1000 * 1000 * (end.tv_sec - start.tv_sec);
  elapsed_sec += end.tv_nsec - start.tv_nsec;
  elapsed_time = (double) elapsed_sec / (1000 * 1000 * 1000);
  printf("8192 bytes : %.9lf sec\n", elapsed_time);

  return 0;
}
