#ifndef _MYCP2_H_
#define _MYCP2_H_
#include <stdio.h>
#include <stdlib.h>

FILE* file_open(const char*, char*);

void file_write(const char*, size_t, FILE*);

void file_close(FILE*);

void mycopy2(const char*, const char*, int);

#endif
