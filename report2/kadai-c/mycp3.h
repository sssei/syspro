#ifndef _MYCP3_H_
#define _MYCP3_H_
#include <stdio.h>
#include <stdlib.h>

FILE* file_open(const char*, char*);

void file_write(const char*, size_t, FILE*);

void file_close(FILE*);

void mycopy3(const char*, const char*, int);

#endif
