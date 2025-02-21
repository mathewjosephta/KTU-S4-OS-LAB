#include <stdio.h>
#include <limits.h>

int main() {
    int n, i, j, temp;
    int id[20], burstTime[20], waitingTime[20], turnAroundTime[20], completionTime[20], start[20];
    float arrivalTime[20], totalWaitingTime = 0, totalTurnAroundTime = 0;
    int completed[20] = {0}, completedCount = 0;
    float currentTime = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (i = 0; i < n; i++) {
        id[i] = i + 1;
        printf("\nEnter Arrival Time and Burst Time for Process %d: ", id[i]);
        scanf("%f %d", &arrivalTime[i], &burstTime[i]);
    }

    // Sorting by Arrival Time using Bubble Sort
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arrivalTime[j] > arrivalTime[j + 1]) {
                // Swap Arrival Time
                float tempFloat = arrivalTime[j];
                arrivalTime[j] = arrivalTime[j + 1];
                arrivalTime[j + 1] = tempFloat;

                // Swap Burst Time
                temp = burstTime[j];
                burstTime[j] = burstTime[j + 1];
                burstTime[j + 1] = temp;

                // Swap Process ID
                temp = id[j];
                id[j] = id[j + 1];
                id[j + 1] = temp;
            }
        }
    }

    // Shortest Job Next (SJN) Scheduling
    printf("\nGantt Chart:\n|");
    while (completedCount < n) {
        int minIndex = -1, minBurst = INT_MAX;

        for (i = 0; i < n; i++) {
            if (!completed[i] && arrivalTime[i] <= currentTime && burstTime[i] < minBurst) {
                minBurst = burstTime[i];
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            currentTime++; // CPU idle
        } else {
            start[minIndex] = currentTime;
            waitingTime[minIndex] = currentTime - arrivalTime[minIndex];
            completionTime[minIndex] = currentTime + burstTime[minIndex];
            currentTime += burstTime[minIndex];

            turnAroundTime[minIndex] = completionTime[minIndex] - arrivalTime[minIndex];
            totalWaitingTime += waitingTime[minIndex];
            totalTurnAroundTime += turnAroundTime[minIndex];

            completed[minIndex] = 1;
            completedCount++;
            printf(" P%d |", id[minIndex]);
        }
    }
    printf("\n");

    // Display Process Details
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%.1f\t\t%d\t\t%d\t\t%d\t\t%d\n", id[i], arrivalTime[i], burstTime[i], 
               waitingTime[i], turnAroundTime[i], completionTime[i]);
    }

    // Display Average Times
    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnAroundTime / n);

    return 0;
}
