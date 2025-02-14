#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    int processes[n], burst_time[n], priority[n], completed[n], wt[n], tat[n], ct[n], start[n];
    float arrival_time[n], currentTime = 0;
    
    printf("Enter arrival times, burst times, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        completed[i] = 0;
        printf("Arrival time for Process %d: ", processes[i]);
        scanf("%f", &arrival_time[i]);
        printf("Burst time for Process %d: ", processes[i]);
        scanf("%d", &burst_time[i]);
        printf("Priority for Process %d: ", processes[i]);
        scanf("%d", &priority[i]);
    }
    
    int completedCount = 0;
    printf("\nGantt Chart:\n");
    
    while (completedCount < n) {
        int minIndex = -1, highestPriority = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (!completed[i] && arrival_time[i] <= currentTime) {
                if (minIndex == -1 || priority[i] < highestPriority || (priority[i] == highestPriority && arrival_time[i] < arrival_time[minIndex])) {
                    highestPriority = priority[i];
                    minIndex = i;
                }
            }
        }
        
        if (minIndex == -1) {
            printf("| Idle (%d) ", (int)currentTime);
            currentTime++;
        } else {
            if (currentTime < arrival_time[minIndex]) {
                printf("| Idle (%d) ", (int)currentTime);
                currentTime = arrival_time[minIndex];
            }
            printf("| P%d (%d) ", processes[minIndex], (int)currentTime);
            start[minIndex] = currentTime;
            wt[minIndex] = currentTime - arrival_time[minIndex];
            currentTime += burst_time[minIndex];
            ct[minIndex] = currentTime;
            tat[minIndex] = burst_time[minIndex] + wt[minIndex];
            completed[minIndex] = 1;
            completedCount++;
        }
    }
    printf("|\n");
    
    int total_wt = 0, total_tat = 0;
    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%.1f\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrival_time[i], burst_time[i], priority[i], wt[i], tat[i], ct[i]);
    }
    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);
    
    return 0;
}
