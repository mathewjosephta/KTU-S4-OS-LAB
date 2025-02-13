#include <stdio.h>
#include <limits.h>

void findWaitingTime(int processes[], int n, int bt[], float at[], int priority[], int wt[], int ct[], int start[]) {
    int completed[n], completedCount = 0;
    float currentTime = 0;
    for (int i = 0; i < n; i++) completed[i] = 0;
    
    while (completedCount < n) {
        int minIndex = -1, highestPriority = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= currentTime) {
                if (minIndex == -1 || priority[i] < highestPriority || (priority[i] == highestPriority && at[i] < at[minIndex])) {
                    highestPriority = priority[i];
                    minIndex = i;
                }
            }
        }
        
        if (minIndex == -1) {
            currentTime++;
        } else {
            start[minIndex] = currentTime;
            wt[minIndex] = currentTime - at[minIndex];
            currentTime += bt[minIndex];
            ct[minIndex] = currentTime;
            completed[minIndex] = 1;
            completedCount++;
        }
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findAvgTime(int processes[], int n, int bt[], float at[], int priority[]) {
    int wt[n], tat[n], ct[n], start[n];
    findWaitingTime(processes, n, bt, at, priority, wt, ct, start);
    findTurnAroundTime(processes, n, bt, wt, tat);

    int total_wt = 0, total_tat = 0;
    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%.1f\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], at[i], bt[i], priority[i], wt[i], tat[i], ct[i]);
    }
    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n");
}

void printGanttChart(int processes[], int n, int bt[], float at[], int priority[]) {
    int completed[n], completedCount = 0, start[n], ct[n];
    float currentTime = 0;
    for (int i = 0; i < n; i++) completed[i] = 0;
    
    printf("\nGantt Chart:\n");
    while (completedCount < n) {
        int minIndex = -1, highestPriority = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= currentTime) {
                if (minIndex == -1 || priority[i] < highestPriority || (priority[i] == highestPriority && at[i] < at[minIndex])) {
                    highestPriority = priority[i];
                    minIndex = i;
                }
            }
        }
        
        if (minIndex == -1) {
            printf("| Idle (%d) ", (int)currentTime);
            currentTime++;
        } else {
            if (currentTime < at[minIndex]) {
                printf("| Idle (%d) ", (int)currentTime);
                currentTime = at[minIndex];
            }
            printf("| P%d (%d) ", processes[minIndex], (int)currentTime);
            start[minIndex] = currentTime;
            currentTime += bt[minIndex];
            ct[minIndex] = currentTime;
            completed[minIndex] = 1;
            completedCount++;
        }
    }
    printf("|\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    int processes[n], burst_time[n], priority[n];
    float arrival_time[n];
    printf("Enter arrival times, burst times, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Arrival time for Process %d: ", processes[i]);
        scanf("%f", &arrival_time[i]);
        printf("Burst time for Process %d: ", processes[i]);
        scanf("%d", &burst_time[i]);
        printf("Priority for Process %d: ", processes[i]);
        scanf("%d", &priority[i]);
    }
    
    printGanttChart(processes, n, burst_time, arrival_time, priority);
    findAvgTime(processes, n, burst_time, arrival_time, priority);
    
    return 0;
}
