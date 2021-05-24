#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include "parse.h"

static void execute_process(process* curr_proc, int read_fd, int write_fd, char* envp[]){
    pid_t pid;
    int status;

    if((pid = fork()) == 0){
	if(read_fd > 0) dup2(read_fd, 0);
	if(write_fd > 0) dup2(write_fd, 1);
	if(curr_proc->input_redirection){
	    int fd = open(curr_proc->input_redirection, O_RDONLY);
	    dup2(fd, 0);
	}
	if(curr_proc->output_redirection){
	    int fd = open(curr_proc->output_redirection, O_WRONLY);
	    dup2(fd, 1);
	}
	execve(curr_proc->program_name, curr_proc->argument_list, envp);
    }else{
	waitpid(pid, &status, WUNTRACED);
    }

    return;
}
    
void execute_job(job* curr_job, char* envp[]){
    process *curr_proc, *next_proc;
    curr_proc = curr_job->process_list;
    next_proc = curr_proc->next;
    int fd[2];
    int ret;

    if(next_proc == NULL){
	execute_process(curr_proc, -1, -1, envp);	
    }else{
	ret = pipe(fd);
	if(ret == -1){
	    perror("pipe");
	    exit(1);
	}
	execute_process(curr_proc, -1, fd[1], envp);
	execute_process(curr_proc->next, fd[0], -1, envp);
    }


    return;
}
