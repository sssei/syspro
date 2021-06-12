#include <string.h>
#include "parse.h"

void print_job_list(job*);
void execute_job(job*, char*[]);

int main(int argc, char *argv[], char *envp[]) {
    char s[LINELEN];
    job *curr_job;

    while(get_line(s, LINELEN)) {
        if(!strcmp(s, "exit\n"))
            break;

        curr_job = parse_line(s);

	execute_job(curr_job, envp);
	
        /* print_job_list(curr_job); */

        free_job(curr_job);
    }

    return 0;
}
