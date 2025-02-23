/* Implementation of  Fork system call */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main() {
    int sum = 0, i, n;
    pid_t pid;
    printf("Enter the number: ");
    scanf("%d", &n);
    pid = fork();
    if (pid < 0) {
        printf("Error creating process\n");
        return 1;
    }
    else if (pid > 0) {
        for (i = 0; i < n; i++) {
            sum += i;
        }
        printf("Parent Sum: %d\n", sum);
    }
    else {
        int diff = 0;
        for (i = 0; i < n; i++) {
            diff -= i;
        }
    printf("Child Diff: %d\n", diff);
    }
return 0;
}

//SAMPLE OUTPUT
/*
Enter the number: 10
Parent Sum: 45
Child Diff: -45


=== Code Execution Successful ===
*/
