#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include "semaphore.h"

#define PROCESS_NAME        "proc2"

int main (int argc, char *argv[])
{
    int semid;
    
    sleep(1);
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
    sleep(5);
    printf("%s - exit critical section\n", PROCESS_NAME);
    
    printf("%s - signal the semaphore\n", PROCESS_NAME);
    SEM_V(semid);
    
    exit(EXIT_SUCCESS);
}
