#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // Added this to resolve 'wait' function error

void main() {
    int shmid;
    key_t key = 7800;
    long shmsz = 0;
    int *shm, *it;
    int i, j, n, pid, temp;

    printf("Enter The Count\n");
    scanf("%d", &n);
    shmsz = n * sizeof(int); // Changed long to int for correct allocation

    if ((shmid = shmget(key, shmsz, IPC_CREAT | 0666)) < 0) {
        printf("Error On SHMGET\n");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (int *)-1) {
        printf("Error On SHMAT\n");
        exit(1);
    }

    it = shm;
    printf("Enter The Elements\n");
    for (i = 0; i < n; i++, it++)
        scanf("%d", it);

    printf("\nEntered Elements Are: ");
    it = shm; // Reset pointer to beginning of shared memory
    for (i = 0; i < n; i++)
        printf("%d ", it[i]);
    printf("\n");

    pid = fork();
    if (pid < 0)
        perror("Error");
    else {
        if (pid > 0) { // Parent process - Sort the elements
            it = shm;
            for (i = 0; i < n; i++) {
                for (j = i + 1; j < n; j++) {
                    if (it[i] > it[j]) {
                        temp = it[i];
                        it[i] = it[j];
                        it[j] = temp;
                    }
                }
            }
            wait(NULL); // Wait for child process to finish
        } else { // Child process - Print sorted elements
            sleep(1); // Give time for sorting to complete
            it = shm;
            printf("Sorted Elements Are: ");
            for (i = 0; i < n; i++)
                printf("%d ", it[i]);
            printf("\n");
        }
    }
}
