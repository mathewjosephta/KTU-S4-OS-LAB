/* To Implement inter-Process Communication using Shared Memory and Display the largest elemnt and smallest elemnt from n numbers*/

#include <stdio.h>      // For input-output functions
#include <sys/types.h>  // Defines data types used in system calls
#include <sys/ipc.h>    // For interprocess communication (IPC) keys
#include <sys/shm.h>    // For shared memory system calls
#include <stdlib.h>     // For exit() function
#include <unistd.h>     // For fork() to create a child process
#include <sys/wait.h>   // For wait() function

int main()
{
    int shmid;               // Shared memory ID
    key_t key = 5678;        // Unique key to identify shared memory
    int *shm, *it;           // Pointers to shared memory
    int i, n, pid, big, small;  // Variables for processing

    // Prompt user to enter the number of elements
    printf("Enter The Count\n");
    scanf("%d", &n);

    size_t shmsz = n * sizeof(int);  // Calculate required memory size

    // Create a shared memory segment
    if ((shmid = shmget(key, shmsz, IPC_CREAT | 0666)) < 0) {
        perror("Error On SHMGET"); // Print error message if shared memory creation fails
        exit(1);
    }

    // Attach the shared memory segment to the process
    if ((shm = shmat(shmid, NULL, 0)) == (int *)-1) {
        perror("Error On SHMAT"); // Print error message if attachment fails
        exit(1);
    }

    // Store user input into shared memory
    it = shm;
    printf("Enter The Elements\n");
    for (i = 0; i < n; i++, it++)
        scanf("%d", it); // Read elements into shared memory

    // Create a child process
    pid = fork();

    // Check if fork was successful
    if (pid < 0) {
        perror("Error on fork"); // Print error if fork fails
        exit(1);
    }
    else if (pid > 0)  // Parent process
    {
        wait(NULL);  // Wait for the child process to complete execution

        // Find the largest number in the array
        it = shm;
        big = it[0];  // Assume first element is the largest

        for (i = 1; i < n; i++) {
            if (big < it[i])
                big = it[i];  // Update if a larger element is found
        }
        printf("\nLargest Element Is  : %d \n", big);

        // Detach and remove shared memory
        shmdt(shm);  // Detach shared memory from parent process
        shmctl(shmid, IPC_RMID, NULL); // Remove shared memory segment
    }
    else  // Child process
    {
        // Find the smallest number in the array
        it = shm;
        small = it[0];  // Assume first element is the smallest

        for (i = 1; i < n; i++) {
            if (small > it[i])
                small = it[i];  // Update if a smaller element is found
        }
        printf("Smallest Element Is  : %d \n", small);

        // Detach shared memory from child process
        shmdt(shm);
        exit(0); // Child process exits
    }

    return 0;
}

/*
SAMPLE OUTPUT

Enter The Count
5
Enter The Elements
3 8 1 9 6

Smallest Element Is  : 1
Largest Element Is  : 9

*/
