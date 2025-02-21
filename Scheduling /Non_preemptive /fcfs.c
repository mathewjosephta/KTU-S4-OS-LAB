#include <stdio.h>

int main() {
    int n, i, j, temp;
    int id[20], arrivalTime[20], burstTime[20];
    int completionTime[20], turnAroundTime[20], waitingTime[20];
    float totalTurnAroundTime = 0, totalWaitingTime = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (i = 0; i < n; i++) {
        id[i] = i + 1;
        printf("\nEnter Arrival Time and Burst Time for Process %d: ", id[i]);
        scanf("%d %d", &arrivalTime[i], &burstTime[i]);
    }

    // Sorting by Arrival Time (Bubble Sort inside main)
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arrivalTime[j] > arrivalTime[j + 1]) {
                // Swap Arrival Time
                temp = arrivalTime[j];
                arrivalTime[j] = arrivalTime[j + 1];
                arrivalTime[j + 1] = temp;

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

    // Calculate Completion Time dynamically
    int currentTime = 0;  // Tracks the CPU time
    for (i = 0; i < n; i++) {
        if (currentTime < arrivalTime[i]) {  // If CPU is idle
            currentTime = arrivalTime[i];
        }
        completionTime[i] = currentTime + burstTime[i];
        currentTime = completionTime[i];

        // Calculate Turnaround Time & Waiting Time
        turnAroundTime[i] = completionTime[i] - arrivalTime[i];
        waitingTime[i] = turnAroundTime[i] - burstTime[i];

        totalTurnAroundTime += turnAroundTime[i];
        totalWaitingTime += waitingTime[i];
    }

    // Display Results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", id[i], arrivalTime[i], burstTime[i],
               completionTime[i], turnAroundTime[i], waitingTime[i]);
    }

    // Display Average Times
    printf("\nAverage Turnaround Time: %.2f", totalTurnAroundTime / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);

    return 0;
}
