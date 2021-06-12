#include <signal.h>
#include <stdio.h>
#include <string.h> // memset
#include <stdlib.h>

volatile int count = 0;

static void increment(){
  count++;
  return;
}


int main(){
  struct sigaction act;

  memset(&act, 0, sizeof act);
  act.sa_handler = increment;
  if(sigaction(SIGINT, &act, NULL) < 0){
    perror("sigaction");
    exit(1);
  }

  while(1){
    if(count >= 10){
      printf("exit\n");
      return 0;
    }
  }
  
}
