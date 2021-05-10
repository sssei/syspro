#ifndef _REENTRANT
#define _REENTRANT
#endif
#ifndef _BB_H_
#define _BB_H_
#include <pthread.h>

extern pthread_mutex_t mutex;
extern pthread_cond_t cond_out;
extern pthread_cond_t cond_in;

int bb_get(void);
void bb_put(int);

#endif 
