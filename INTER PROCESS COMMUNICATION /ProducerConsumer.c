// Producer.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>

#define SHMSZ 27 

int main()
{
    int shmid;
    char c;
    key_t key = 6780;
    char *shm, *s;

    // Create shared memory
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("Error On SHMGET");
        exit(1);
    }

    // Attach shared memory
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("Error On SHMAT");
        exit(1);
    }

    // Store characters in shared memory
    s = shm;
    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;

    *s = '\0';  // Null-terminate the string

    // Print stored data
    putchar('\n');
    for (s = shm; *s != '\0'; s++) {
        putchar(*s);
        printf(" ");
    }
    putchar('\n');
    putchar('\n');

    // Wait for client to indicate it is done
    while (*shm != '*')
        sleep(1);

    // Detach and remove shared memory
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

//Comsumer.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>

#define SHMSZ 27 

int main()
{
    int shmid;
    key_t key = 6780;
    char *shm, *s;

    // Access shared memory
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("Error On SHMGET");
        exit(1);
    }

    // Attach shared memory
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("Error On SHMAT");
        exit(1);
    }

    // Print data from shared memory
    putchar('\n');
    for (s = shm; *s != '\0'; s++) {
        putchar(*s);
        printf(" ");
    }
    putchar('\n');
    putchar('\n');

    // Signal server by modifying shared memory
    *shm = '*';

    // Detach shared memory
    shmdt(shm);

    return 0;
}
