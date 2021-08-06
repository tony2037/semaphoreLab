#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include "semaphore.h"

#define PROCESS_NAME        "proc2"

int main (int argc, char *argv[])
{
    int semid;
	int fd, i, poll_num;
	int wd;
	nfds_t nfds;
	struct pollfd fds[1];

	fd = inotify_init1(IN_NONBLOCK);
	if (fd == -1) {
	   perror("inotify_init1");
	   exit(EXIT_FAILURE);
    }

	// FIXME
	wd = inotify_add_watch(fd, CACHE_FILE, IN_DELETE_SELF);
	if (-1 == wd) {
		fprintf(stderr, "Cannot watch '%s': %s\n", CACHE_FILE, strerror(errno));
        exit(EXIT_FAILURE);
    }

	nfds = 1;
	fds[0].fd = fd;                 /* Inotify input */
	fds[0].events = POLLIN;
    
    printf("%s - get the semaphore\n", PROCESS_NAME);
    semid = init_semaphore(KEY_SEM_EXAMPLE, -1);
    if (semid == -1) {
        perror(PROCESS_NAME);
        exit(EXIT_FAILURE);
    }
    
    printf("%s - wait the semaphore\n", PROCESS_NAME);
    if (SEM_P(semid) != 0) {
        perror(PROCESS_NAME);
        exit(EXIT_FAILURE);
    }
    
    printf("%s - enter critical section\n", PROCESS_NAME);
    //sleep(5);
    //printf("%s - exit critical section\n", PROCESS_NAME);
    
	poll_num = poll(fds, nfds, -1);
	if (poll_num == -1) {
		fprintf(stderr, "poll: %s\n", strerror(errno));
		perror("poll\n");
		exit(EXIT_FAILURE);
	}
	if (fds[0].revents & POLLIN) {
		/* Inotify events are available. */
		printf("The cache file has been removed : %s - signal the semaphore\n", PROCESS_NAME);
		printf("%s - exit critical section\n", PROCESS_NAME);
		SEM_V(semid);
		
		exit(EXIT_SUCCESS);
	}
}
