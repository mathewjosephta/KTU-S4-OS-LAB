/*AIM : To implement Client server program using Shared memory*/

// Server.c - Creates and writes to shared memory
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>   // For sleep()

#define SHMSZ 27  // Define the size of shared memory

int main()
{
    int shmid;         // Variable to store shared memory ID
    char c;            // Character variable for storing alphabets
    key_t key = 6780;  // Unique key for shared memory
    char *shm, *s;     // Pointers to shared memory

    // Step 1: Create shared memory with the given key
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("Error On SHMGET"); // Print error if creation fails
        exit(1);
    }

    // Step 2: Attach shared memory to the server's address space
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("Error On SHMAT"); // Print error if attachment fails
        exit(1);
    }

    // Step 3: Store lowercase letters (a-z) into shared memory
    s = shm; // Assign shared memory pointer
    for (c = 'a'; c <= 'z'; c++)
        *s++ = c; // Store each character sequentially

    *s = '\0';  // Null-terminate the string to indicate end of data

    // Step 4: Print stored data (for verification)
    putchar('\n');
    for (s = shm; *s != '\0'; s++) {
        putchar(*s);
        printf(" ");
    }
    putchar('\n');
    putchar('\n');

    // Step 5: Wait for client to signal completion (*shm = '*')
    while (*shm != '*')
        sleep(1); // Wait for client

    // Step 6: Cleanup - Detach and remove shared memory
    shmdt(shm);                   // Detach from shared memory
    shmctl(shmid, IPC_RMID, NULL); // Remove shared memory segment

    return 0;
}



// Client.c - Reads from shared memory and signals server
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>   // For sleep()

#define SHMSZ 27  // Define the size of shared memory

int main()
{
    int shmid;         // Variable to store shared memory ID
    key_t key = 6780;  // Same unique key as the server
    char *shm, *s;     // Pointers to shared memory

    // Step 1: Access the existing shared memory segment
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("Error On SHMGET"); // Print error if access fails
        exit(1);
    }

    // Step 2: Attach shared memory to the client's address space
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("Error On SHMAT"); // Print error if attachment fails
        exit(1);
    }

    // Step 3: Read and print data from shared memory
    putchar('\n');
    for (s = shm; *s != '\0'; s++) {
        putchar(*s);
        printf(" ");
    }
    putchar('\n');
    putchar('\n');

    // Step 4: Signal server that client has finished reading
    *shm = '*'; // Modify shared memory to notify server

    // Step 5: Detach shared memory
    shmdt(shm); // Detach from shared memory

    return 0;
}

/*
SAMPLE OUTPUT

Server Output
a b c d e f g h i j k l m n o p q r s t u v w x y z 

Client Output
a b c d e f g h i j k l m n o p q r s t u v w x y z 
*/
