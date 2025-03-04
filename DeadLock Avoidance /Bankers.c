#include <stdio.h>

int P, R; // Number of processes and resources
int available[100], max[100][100], allocation[100][100], need[100][100];

void inputData() {
    printf("Enter number of processes and resources: ");
    scanf("%d %d", &P, &R);

    printf("Enter available resources: ");
    for (int i = 0; i < R; i++)
        scanf("%d", &available[i]);

    printf("Enter max resources matrix:\n");
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &max[i][j]);

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j]; // Calculate need matrix directly
        }
}

int isSafe() {
    int work[100], finish[100] = {0}, safeSequence[100], count = 0;

    for (int i = 0; i < R; i++) 
        work[i] = available[i];

    while (count < P) {
        int found = 0;

        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int canAllocate = 1;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = 0;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < R; j++)
                        work[j] += allocation[i][j];

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is in an UNSAFE state.\n");
            return 0;
        }
    }

    printf("System is in a SAFE state.\nSafe sequence: ");
    for (int i = 0; i < P; i++)
        printf("%d ", safeSequence[i]);
    printf("\n");

    return 1;
}

int main() {
    inputData();
    isSafe();
    return 0;
}
