#include <errno.h>
#include <sys/stat.h>
#include "common.h"

void procC(void) {
	setbuf(stdout, NULL);
	int count = 100;
	int i = 0;
	int iRet = -1;
	int iStat = -1;
	const int timeout = 30;
	struct stat sb;
	FILE *fp = NULL;
	long fileSize = 0;
	char *buffer = NULL;

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
			fp = fopen(CACHEFILE, "r");
			fseek (fp , 0 , SEEK_END);
			fileSize = ftell(fp);
			rewind(fp);
			buffer = (char*) malloc (sizeof(char) * fileSize);
			fread(buffer, 1, fileSize, fp);
			printf("proc C: %s exist (%s), remove the cache and release the lock\n", CACHEFILE, buffer);
			iRet = remove(CACHEFILE);
			if (0 == iRet) {
				printf("proc C: %s remove (%s)\n", CACHEFILE, buffer);
				UnLockByFile(LOCKFILE);
			}
		}


		printf("=== proc C loop end ===\n\n");
LOOP_END:
		if (NULL != buffer) {
			free(buffer);
			buffer = NULL;
		}
		if (NULL != fp) {
			fclose(fp);
			fp = NULL;
		}
		BZERO_STRUCT(sb);
		i++;
	}

	printf("=== proc C exit ===\n\n");
}
