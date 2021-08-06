#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include "common.h"

void procB(void) {
	setbuf(stdout, NULL);
	int count = 100;
	int i = 0;
	int iRet = -1;
	int iStat = -1;
	const int timeout = 10;
	FILE *fp = NULL;
	struct stat sb;
	char buf[2] = {0};

	for (; i < count;) {
		iRet = LockByFile(LOCKFILE, timeout);
		if (0 > iRet) {
			goto LOOP_END;
		}
		printf("=== proc B acquire the lock (%d) ===\n", i);
		printf("proc B is doing something\n");
		printf("proc B: %d\n", i);
		iStat = stat(CACHEFILE, &sb);
		if (-1 == iStat && ENOENT == errno) {
			printf("proc B: %s does not exist\n", CACHEFILE);
			sprintf(buf, "%d", i);
			fp = fopen(CACHEFILE, "w");
			fwrite(buf, sizeof(char), strlen(buf), fp);
			goto LOOP_END;
		}
		else {
			printf("proc B: %s exist, this is fucking wrong\n", CACHEFILE);
		}

LOOP_END:
		printf("=== proc B loop end (%d) ===\n\n", i);
		i++;
		if (NULL != fp) {
			fclose(fp);
			fp = NULL;
		}
		BZERO_STRUCT(sb);
	}

	printf("=== proc B exit ===\n\n");
}
