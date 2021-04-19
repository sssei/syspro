#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(){
  int i;
  struct timespec start, end;
  clock_gettime(CLOCK_REALTIME, &start);
  getpid();
  clock_gettime(CLOCK_REALTIME, &end);  

  long long elapsed_sec = 1000 * 1000 * 1000 * (end.tv_sec - start.tv_sec);
  elapsed_sec += end.tv_nsec - start.tv_nsec;
  double elapsed_time = (double) elapsed_sec / (1000 * 1000 * 1000);
  printf(" one time  : %.9lf sec\n", elapsed_time);

  clock_gettime(CLOCK_REALTIME, &start);
  for(i = 0; i < 1000; i++) getpid(); 
  clock_gettime(CLOCK_REALTIME, &end);  

  elapsed_sec = 1000 * 1000 * 1000 * (end.tv_sec - start.tv_sec);
  elapsed_sec += end.tv_nsec - start.tv_nsec;
  elapsed_time = (double) elapsed_sec / (1000 * 1000 * 1000);
  printf("1000 times  : %.9lf sec\n", elapsed_time);
  
  return 0;
}
