#ifndef _MYCP_H_
#define _MYCP_H_

int file_open(const char*, int);

void file_write(int, const char*, size_t);

void file_close(int);

void mycopy(const char*, const char*, int);

#endif
