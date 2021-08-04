#include <errno.h>
#include <sys/stat.h>
#include "common.h"

int main() {
	int count = 10;
	int i = 0;
	int iRet = -1;
	int iStat = -1;
	const int timeout = 10;
	FILE *fp = NULL;
	struct stat sb;

	for (; i < count;) {
		iRet = LockByFile(LOCKFILE, timeout);
		if (0 > iRet) {
			goto LOOP_END;
		}
		printf("=== proc B acquire the lock ===\n");
		sleep(1);
		printf("proc B is doing something\n");
		printf("proc B: %d\n", i);
		iStat = stat(CACHEFILE, &sb);
		if (-1 == iStat && ENOENT == errno) {
			printf("proc B: %s does not exist\n", CACHEFILE);
			fp = fopen(CACHEFILE, "w");
			goto LOOP_END;
		}
		else {
			printf("proc B: %s exist, this is fucking wrong\n", CACHEFILE);
		}

		printf("=== proc B loop end ===\n\n");
		i++;
LOOP_END:
		if (NULL != fp) {
			fclose(fp);
			fp = NULL;
		}
		BZERO_STRUCT(sb);
		continue;
	}

	printf("=== proc B exit ===\n\n");
}
