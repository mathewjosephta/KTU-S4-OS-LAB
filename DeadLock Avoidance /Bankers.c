#include <stdio.h>

int main() {
    int P, R;
    printf("Enter the number of processes and resources: ");
    scanf("%d %d", &P, &R);
    
    int process[P], available[R], allocation[P][R], max[P][R], need[P][R];
    int work[R], finish[P], req[R], safeseq[P];
    
    printf("Enter the process IDs: ");
    for (int i = 0; i < P; i++) {
        scanf("%d", &process[i]);
    }
    
    printf("Enter the maximum resource matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    printf("Enter the allocated resource matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    
    printf("Enter the available resources: ");
    for (int i = 0; i < R; i++) {
        scanf("%d", &available[i]);
    }
    
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    int pid;
    printf("Enter the process ID to request resources: ");
    scanf("%d", &pid);
    
    if (pid < 0 || pid >= P) {
        printf("Invalid process ID.\n");
        return 1;
    }
    
    printf("Enter the resources requested: ");
    for (int i = 0; i < R; i++) {
        scanf("%d", &req[i]);
        if (req[i] > need[pid][i] || req[i] > available[i]) {
            printf("Error: Request exceeds need or available resources. Process must wait.\n");
            return 1;
        }
    }
    
    for (int i = 0; i < R; i++) {
        available[i] -= req[i];
        allocation[pid][i] += req[i];
        need[pid][i] -= req[i];
    }
    
    for (int i = 0; i < R; i++) work[i] = available[i];
    for (int i = 0; i < P; i++) finish[i] = 0;
    
    int count = 0, found;
    while (count < P) {
        found = 0;
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
                    for (int j = 0; j < R; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeseq[count++] = process[i];
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("Unsafe state! Request denied.\n");
            for (int i = 0; i < R; i++) {
                available[i] += req[i];
                allocation[pid][i] -= req[i];
                need[pid][i] += req[i];
            }
            return 1;
        }
    }
    
    printf("Safe state! Safe sequence: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", safeseq[i]);
    }
    printf("\n");
    
    printf("\nFinal Allocation, Need, and Available Resources:\n");
    printf("Process\tMax\tAlloc\tNeed\n");
    for (int i = 0; i < P; i++) {
        printf("%d\t", process[i]);
        for (int j = 0; j < R; j++) printf("%d ", max[i][j]);
        printf("\t");
        for (int j = 0; j < R; j++) printf("%d ", allocation[i][j]);
        printf("\t");
        for (int j = 0; j < R; j++) printf("%d ", need[i][j]);
        printf("\n");
    }
    
    printf("Available: ");
    for (int i = 0; i < R; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");
    
    return 0;
}
