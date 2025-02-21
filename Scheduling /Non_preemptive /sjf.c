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

    // Sorting by Arrival Time (Bubble Sort)
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arrivalTime[j] > arrivalTime[j + 1]) {
                // Swap all values
                temp = arrivalTime[j];
                arrivalTime[j] = arrivalTime[j + 1];
                arrivalTime[j + 1] = temp;

                temp = burstTime[j];
                burstTime[j] = burstTime[j + 1];
                burstTime[j + 1] = temp;

                temp = id[j];
                id[j] = id[j + 1];
                id[j + 1] = temp;
            }
        }
    }

    // SJF Scheduling Execution
    int currentTime = 0, completed = 0, minIndex;
    int isCompleted[20] = {0}; // Track completed processes

    while (completed < n) {
        minIndex = -1;
        int minBurstTime = 1e9; // Very large value

        // Find the process with the shortest burst time that has arrived
        for (i = 0; i < n; i++) {
            if (!isCompleted[i] && arrivalTime[i] <= currentTime && burstTime[i] < minBurstTime) {
                minBurstTime = burstTime[i];
                minIndex = i;
            }
        }

        if (minIndex == -1) { // If no process is available, increment time
            currentTime++;
        } else {
            completionTime[minIndex] = currentTime + burstTime[minIndex];
            currentTime = completionTime[minIndex];
            turnAroundTime[minIndex] = completionTime[minIndex] - arrivalTime[minIndex];
            waitingTime[minIndex] = turnAroundTime[minIndex] - burstTime[minIndex];
            isCompleted[minIndex] = 1;
            completed++;

            totalTurnAroundTime += turnAroundTime[minIndex];
            totalWaitingTime += waitingTime[minIndex];
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

    return 0;
}
