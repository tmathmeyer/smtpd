
#ifndef SMTPD
#define SMTPD

#include "parse.h"


#define MAX(A,B) (A>B?A:B)
#define ABS(A) (A>0?A:-A)

typedef struct sample {
    struct sample* next;
    status* data;
} sample;

int analyze(sample* motionlist);
int daemon_function();





#endif