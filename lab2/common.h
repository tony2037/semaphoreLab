#include <string.h>

#define LOCKFILE "/tmp/lab2.lock"
#define BZERO_STRUCT(x) {do {memset(&x, 0, sizeof(x));} while(0);}
