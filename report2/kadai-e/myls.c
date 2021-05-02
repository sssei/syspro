#define _GNU_SOURCE
#include <dirent.h>     /* Defines DT_* constants */
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#define handle_error(msg)				\
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct linux_dirent {
    unsigned long  d_ino;
    off_t          d_off;
    unsigned short d_reclen;
    char           d_name[];
};

#define BUF_SIZE 1024

void print_mode(uintmax_t mode){
    printf("%s", (mode & 0400 ) ? "r" : "-" );    
    printf("%s", (mode & 0200 ) ? "w" : "-" );    
    printf("%s", (mode & 0100 ) ? "x" : "-" );
    printf("%s", (mode & 0040 ) ? "r" : "-" );
    printf("%s", (mode & 0020 ) ? "w" : "-" );
    printf("%s", (mode & 0010 ) ? "x" : "-" );    
    printf("%s", (mode & 0004 ) ? "r" : "-" );
    printf("%s", (mode & 0002 ) ? "w" : "-" );
    printf("%s ", (mode & 0001 ) ? "x" : "-" );    
    return;
}

int main(int argc, char *argv[]) {
    int fd;
    long nread;
    char buf[BUF_SIZE];
    struct linux_dirent *d;
    struct stat sb;
    char d_type;

    fd = open(argc > 1 ? argv[1] : ".", O_RDONLY | O_DIRECTORY);
    if (fd == -1)
	handle_error("open");

    while(1){
	nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
	if (nread == -1)
	    handle_error("getdents");

	if (nread == 0)
	    break;

	for (long bpos = 0; bpos < nread;) {
	    d = (struct linux_dirent *) (buf + bpos);
	    d_type = *(buf + bpos + d->d_reclen - 1);
	    bpos += d->d_reclen;
	    if(*d->d_name == '.') continue;	    
	    printf("%s", (d_type == DT_REG) ?  "-" :
		   (d_type == DT_DIR) ?  "d" :
		   (d_type == DT_FIFO) ? "p" :
		   (d_type == DT_SOCK) ? "s" :
		   (d_type == DT_LNK) ?  "l" :
		   (d_type == DT_BLK) ?  "b" :
		   (d_type == DT_CHR) ?  "c" : "?");
	    if(lstat(d->d_name, &sb) == -1){
		handle_error("lstat");
	    }
	    print_mode(sb.st_mode);
	    printf("%s\n", d->d_name);
	  
	}
    }

    exit(EXIT_SUCCESS);
}
