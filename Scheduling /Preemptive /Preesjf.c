#include <stdio.h>
#include <limits.h>

int main() {
    int n, i, j, temp;
    int id[20], arrivalTime[20], burstTime[20], remainingTime[20];
    int completionTime[20], turnAroundTime[20], waitingTime[20];
    float totalTurnAroundTime = 0, totalWaitingTime = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (i = 0; i < n; i++) {
        id[i] = i + 1;
        printf("\nEnter Arrival Time and Burst Time for Process %d: ", id[i]);
        scanf("%d %d", &arrivalTime[i], &burstTime[i]);
        remainingTime[i] = burstTime[i]; // Initialize remaining burst time
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

                // Swap Remaining Time
                temp = remainingTime[j];
                remainingTime[j] = remainingTime[j + 1];
                remainingTime[j + 1] = temp;

                // Swap Process ID
                temp = id[j];
                id[j] = id[j + 1];
                id[j + 1] = temp;
            }
        }
    }

    // SRTF Scheduling Execution
    int currentTime = 0, completed = 0, minIndex;
    int gantt[100], ganttIndex = 0; // Store Gantt Chart process execution

    while (completed < n) {
        minIndex = -1;
        int minRemainingTime = INT_MAX;

        // Find process with the shortest remaining time that has arrived
        for (i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && remainingTime[i] > 0 && remainingTime[i] < minRemainingTime) {
                minRemainingTime = remainingTime[i];
                minIndex = i;
            }
        }

        if (minIndex != -1) {
            gantt[ganttIndex++] = id[minIndex]; // Store executed process in Gantt chart
            remainingTime[minIndex]--;
            currentTime++;

            if (remainingTime[minIndex] == 0) {
                completionTime[minIndex] = currentTime;
                turnAroundTime[minIndex] = completionTime[minIndex] - arrivalTime[minIndex];
                waitingTime[minIndex] = turnAroundTime[minIndex] - burstTime[minIndex];
                totalTurnAroundTime += turnAroundTime[minIndex];
                totalWaitingTime += waitingTime[minIndex];
                completed++;
            }
        } else {
            gantt[ganttIndex++] = -1; // Idle time in Gantt chart
            currentTime++; // CPU idle time
        }
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

    // Display Gantt Chart
    printf("\nGantt Chart:\n|");
    for (i = 0; i < ganttIndex; i++) {
        if (gantt[i] == -1)
            printf(" IDLE |");
        else
            printf(" P%d |", gantt[i]);
    }
    printf("\n");

    return 0;
}
