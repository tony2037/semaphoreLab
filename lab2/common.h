#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LOCKFILE "/tmp/lab2.lock"
#define BZERO_STRUCT(x) {do {memset(&x, 0, sizeof(x));} while(0);}

#define CACHEFILE "/tmp/procB.cache"

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};

static inline int GetSemKey(const char *);

static inline int GetSem(const char *, int);

int LockByFile(const char *, int);

void UnLockByFile(const char *);

void procA(void);
void procB(void);
void procC(void);
