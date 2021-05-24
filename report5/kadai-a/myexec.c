#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

void shift_argv(char* argv[]){
  int i;
  for(i = 0; argv[i+1] != NULL; i++){
    strcpy(argv[i], argv[i+1]);
  }
  argv[i] = NULL;
  return;
}

int main(int argc, char* argv[], char* envp[]){
  pid_t pid;
  int status;
  
  if((pid = fork()) == 0){
    // child process
    shift_argv(argv);
    execve(argv[0], argv, envp);
  }else{
    //parent process
    waitpid(pid, &status, WUNTRACED);
  }

  return 0;
}
