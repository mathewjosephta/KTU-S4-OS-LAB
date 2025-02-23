#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>   // For fork()
#include <sys/wait.h> // For wait()

int main()
{
    int shmid;
    key_t key = 5678;
    int *shm, *it;
    int i, n, pid, big, small;

    printf("Enter The Count\n");
    scanf("%d", &n);

    size_t shmsz = n * sizeof(int);  // Corrected sizeof type

    // Create shared memory
    if ((shmid = shmget(key, shmsz, IPC_CREAT | 0666)) < 0) {
        perror("Error On SHMGET");
        exit(1);
    }

    // Attach shared memory
    if ((shm = shmat(shmid, NULL, 0)) == (int *)-1) {
        perror("Error On SHMAT");
        exit(1);
    }

    it = shm;
    printf("Enter The Elements\n");
    for (i = 0; i < n; i++, it++)
        scanf("%d", it);

    pid = fork();

    if (pid < 0) {
        perror("Error on fork");
        exit(1);
    }
    else if (pid > 0)  // Parent process
    {
        wait(NULL);  // Wait for the child process to finish
        it = shm;
        big = it[0];

        for (i = 1; i < n; i++) {
            if (big < it[i])
                big = it[i];
        }
        printf("\nLargest Element Is  : %d \n", big);

        // Detach and remove shared memory
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
    }
    else  // Child process
    {
        it = shm;
        small = it[0];

        for (i = 1; i < n; i++) {
            if (small > it[i])
                small = it[i];
        }
        printf("Smallest Element Is  : %d \n", small);

        // Detach shared memory in child process
        shmdt(shm);
        exit(0);
    }

    return 0;
}
