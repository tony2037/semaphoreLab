#include "common.h"

int main() {
	setbuf(stdout, NULL);
	int count = 100;
	int i = 0;
	int iRet = -1;
	const int timeout = 10;

	for (; i < count;) {
		iRet = LockByFile(LOCKFILE, timeout);
		if (0 > iRet) {
			goto LOOP_END;
		}
		printf("=== proc A acquire the lock (%d) ===\n", i);
		printf("proc A is doing something\n");
		printf("proc A: %d\n", i);

		UnLockByFile(LOCKFILE);
		printf("=== proc A release the lock (%d) ===\n\n", i);
		i++;
LOOP_END:
		continue;
	}

	printf("=== proc A exit ===\n");
}
