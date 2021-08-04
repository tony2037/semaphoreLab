#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>

#include "common.h"

using namespace std;

static inline int GetSemKey(const char *szFile) {
	int err = -1;
	int keySem = -1;
	FILE *fp = NULL;

	if (0 > access(szFile, F_OK)) {
		//Create file for semaphore
		if (NULL == (fp = fopen(szFile, "w"))) {
			printf("failed to fopen(%s), errno=%m", szFile);
			goto Err;
		}
	}

	keySem = ftok(szFile, 0);
	if (0 > keySem) {
		printf("failed to ftok(%s), errno=%m", szFile);
		goto Err;
	}
	err = keySem;
Err:
	if (fp) {
		fclose(fp);
	}
	return err;
}

static inline int GetSem(const char *szFile, int maxSem) {
	int ret = -1;
	int err = -1;
	int semid = -1;
	int keySem = -1;
	union semun op;

	if (0 > (ret = GetSemKey(szFile))) {
		printf("failed to ftok(%s), errno=%m", szFile);
		goto Err;
	}
	keySem = ret;

	if (0 <= (semid = semget(keySem, 1, 0666 | IPC_CREAT | IPC_EXCL))) {
		op.val = maxSem;
		if (0 > semctl(semid, 0, SETVAL, op)) {
			printf("semctl fail (%s) errno = %m", szFile);
			goto Err;
		}
	} else if (EEXIST == errno) {
		semid = semget(keySem, 1, 0666);

		if (0 > semid) {
			printf("semget fail (%s) errno = %m", szFile);
			goto Err;
		}
	}

	err = semid;

Err:
	return err;
}

int LockByFile(const char *szFilePath, int timeOut) {
	int semid = -1;
	int ret = -1;
	int err = -1;
	struct sembuf sb;
	struct timespec timeout;
	mode_t origUmask = umask(0000);

	umask(0022);
	if (0 > (ret = GetSem(szFilePath, 1))) {
		goto Err;
	}
	semid = ret;

	BZERO_STRUCT(sb);
	sb.sem_num = 0;
	sb.sem_op = -1;
	sb.sem_flg = SEM_UNDO;

	BZERO_STRUCT(timeout);
	timeout.tv_sec = timeOut;

	if (0 > semtimedop(semid, &sb, 1, &timeout)) {
		if (EAGAIN == errno) {
			printf("time is expired");
		} else {
			printf("semop fail semid %X errno = %m\n", semid);
		}
		goto Err;
	}

	err = semid;
Err:
	umask(origUmask);
	return err;
}

void UnLockByFile(const char *szFilePath) {	

	int semid;
	struct sembuf sb;
	int ret = -1;
	mode_t origUmask = umask(0000);

	umask(0022);
	if (0 > (ret = GetSem(szFilePath, 1))) {
		goto Err;
	}
	semid = ret;

	if (0 > semid) {
		printf("Bad parameter");
		goto Err;
	}

	BZERO_STRUCT(sb);
	sb.sem_num = 0;
	sb.sem_op = 1;
	sb.sem_flg = SEM_UNDO;

	if (0 > semop(semid, &sb, 1)) {
		printf("semop fail semid %d errno = %m", semid);
	}

Err:
	umask(origUmask);
	return; 
}
