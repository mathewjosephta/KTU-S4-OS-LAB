#include <stdio.h>

int main() {
    int n, i, j, temp, maxPriorityIndex;
    int id[20], arrivalTime[20], burstTime[20], priority[20];
    int completionTime[20], turnAroundTime[20], waitingTime[20];
    float totalTurnAroundTime = 0, totalWaitingTime = 0;
    int isCompleted[20] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        id[i] = i + 1;
        printf("\nEnter Arrival Time, Burst Time, and Priority for Process %d: ", id[i]);
        scanf("%d %d %d", &arrivalTime[i], &burstTime[i], &priority[i]);
    }

    // Sorting by Arrival Time
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arrivalTime[j] > arrivalTime[j + 1]) {
                temp = arrivalTime[j]; arrivalTime[j] = arrivalTime[j + 1]; arrivalTime[j + 1] = temp;
                temp = burstTime[j]; burstTime[j] = burstTime[j + 1]; burstTime[j + 1] = temp;
                temp = priority[j]; priority[j] = priority[j + 1]; priority[j + 1] = temp;
                temp = id[j]; id[j] = id[j + 1]; id[j + 1] = temp;
            }
        }
    }

    int currentTime = 0, completed = 0;

    printf("\nGantt Chart:\n|");

    while (completed < n) {
        maxPriorityIndex = -1;
        for (i = 0; i < n; i++) {
            if (!isCompleted[i] && arrivalTime[i] <= currentTime) {
                if (maxPriorityIndex == -1 || priority[i] < priority[maxPriorityIndex]) {  // Lower value = higher priority
                    maxPriorityIndex = i;
                }
            }
        }

        if (maxPriorityIndex == -1) {
            printf(" IDLE |");
            currentTime++;
        } else {
            currentTime += burstTime[maxPriorityIndex];
            completionTime[maxPriorityIndex] = currentTime;
            turnAroundTime[maxPriorityIndex] = completionTime[maxPriorityIndex] - arrivalTime[maxPriorityIndex];
            waitingTime[maxPriorityIndex] = turnAroundTime[maxPriorityIndex] - burstTime[maxPriorityIndex];

            totalTurnAroundTime += turnAroundTime[maxPriorityIndex];
            totalWaitingTime += waitingTime[maxPriorityIndex];

            isCompleted[maxPriorityIndex] = 1;
            completed++;

            printf(" P%d |", id[maxPriorityIndex]);
        }
    }

    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", id[i], arrivalTime[i], burstTime[i], priority[i], completionTime[i], turnAroundTime[i], waitingTime[i]);
    }

    printf("\nAverage Turnaround Time: %.2f", totalTurnAroundTime / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);

    return 0;
}
