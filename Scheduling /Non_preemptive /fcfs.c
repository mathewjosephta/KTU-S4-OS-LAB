#include <stdio.h>

int main() {
    int n, i;
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

    // Calculate Completion Time
    completionTime[0] = arrivalTime[0] + burstTime[0];

    for (i = 1; i < n; i++) {
        if (completionTime[i - 1] >= arrivalTime[i])
            completionTime[i] = completionTime[i - 1] + burstTime[i];
        else
            completionTime[i] = arrivalTime[i] + burstTime[i];
    }

    // Calculate Turnaround Time and Waiting Time
    for (i = 0; i < n; i++) {
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
