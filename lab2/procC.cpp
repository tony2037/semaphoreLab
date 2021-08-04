#include <errno.h>
#include <sys/stat.h>
#include "common.h"

int main() {
	int count = 10;
	int i = 0;
	int iRet = -1;
	int iStat = -1;
	const int timeout = 30;
	struct stat sb;

	for (; i < count;) {
		printf("=== proc C check cache file ===\n");
		printf("proc C is doing something\n");
		printf("proc C: %d\n", i);
		iStat = stat(CACHEFILE, &sb);
		if (-1 == iStat && ENOENT == errno) {
			printf("proc C: %s does not exist\n", CACHEFILE);
			goto LOOP_END;
		}
		else {
			printf("proc C: %s exist, remove the cache and release the lock\n", CACHEFILE);
			iRet = remove(CACHEFILE);
			if (0 == iRet) {
				printf("proc C: %s remove\n", CACHEFILE);
				UnLockByFile(LOCKFILE);
			}
		}


		printf("=== proc C loop end ===\n\n");
LOOP_END:
		i++;
		sleep(1);
		BZERO_STRUCT(sb);
		continue;
	}

	printf("=== proc C exit ===\n\n");
}
