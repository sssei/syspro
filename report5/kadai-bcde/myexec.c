#define _GNU_SOURCE // execvpe 
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include "parse.h"

#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

void execute_job(job* curr_job, char* envp[]){
  process *curr_proc;
  curr_proc = curr_job->process_list;
  int fd[2];
  int pids[LINELEN];
  int i, p_cnt = 0;
  int fdin = STDIN_FILENO;
  int status, f;
  pid_t pid;

  while(curr_proc != NULL){
    if(pipe(fd) == -1) handle_error("pipe");
    if((pid = fork()) == -1){
      handle_error("fork");
    }else if(pid == 0){
      dup2(fdin, STDIN_FILENO);
      if(curr_proc->next != NULL){
	dup2(fd[1], STDOUT_FILENO);
      }
      if(curr_proc->input_redirection){
	f = open(curr_proc->input_redirection, O_RDONLY);
	dup2(f, STDIN_FILENO);
      }
      if(curr_proc->output_redirection){
	if(curr_proc->output_option == TRUNC){
	  f = open(curr_proc->output_redirection, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	}else{
	  f = open(curr_proc->output_redirection, O_WRONLY | O_CREAT | O_APPEND, 0666);
	}
	dup2(f, STDOUT_FILENO);
      }
      close(fd[0]);
      execvpe(curr_proc->program_name, curr_proc->argument_list, envp);
      handle_error("execve");
    }else{
      pids[p_cnt] = pid;
      p_cnt++;
      close(fd[1]);
      fdin = fd[0];
      curr_proc = curr_proc->next;
    }
  }

  for(i = 0; i < p_cnt; i++){
    waitpid(pids[i], &status, WUNTRACED);
  }
  
  return;
}
