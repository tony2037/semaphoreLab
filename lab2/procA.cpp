#include "common.h"

int main() {
	int count = 10;
	int i = 0;
	int iRet = -1;
	const int timeout = 10;

	for (; i < count;) {
		iRet = LockByFile(LOCKFILE, timeout);
		if (0 > iRet) {
			goto LOOP_END;
		}
		printf("=== proc A acquire the lock ===\n");
		sleep(1);
		printf("proc A is doing something\n");
		printf("proc A: %d\n", i);

		UnLockByFile(LOCKFILE);
		printf("=== proc A release the lock ===\n\n");
		i++;
LOOP_END:
		continue;
	}

	printf("=== proc A exit ===\n");
}
