#include <stdio.h>
#include <limits.h>

void findWaitingTime(int processes[], int n, int bt[], float at[], int wt[], int ct[], int start[]) {
    int completed[n], completedCount = 0;
    float currentTime = 0;
    for (int i = 0; i < n; i++) completed[i] = 0;
    
    while (completedCount < n) {
        int minIndex = -1, minBurst = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= currentTime && bt[i] < minBurst) {
                minBurst = bt[i];
                minIndex = i;
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

void findAvgTime(int processes[], int n, int bt[], float at[]) {
    int wt[n], tat[n], ct[n], start[n];
    findWaitingTime(processes, n, bt, at, wt, ct, start);
    findTurnAroundTime(processes, n, bt, wt, tat);

    int total_wt = 0, total_tat = 0;
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%.1f\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], at[i], bt[i], wt[i], tat[i], ct[i]);
    }
    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);
}

void printGanttChart(int processes[], int n, int bt[], float at[]) {
    int completed[n], completedCount = 0, start[n], ct[n];
    float currentTime = 0;
    for (int i = 0; i < n; i++) completed[i] = 0;
    
    printf("\nGantt Chart:\n|");
    while (completedCount < n) {
        int minIndex = -1, minBurst = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= currentTime && bt[i] < minBurst) {
                minBurst = bt[i];
                minIndex = i;
            }
        }
        
        if (minIndex == -1) {
            currentTime++;
        } else {
            start[minIndex] = currentTime;
            currentTime += bt[minIndex];
            ct[minIndex] = currentTime;
            completed[minIndex] = 1;
            completedCount++;
            printf(" P%d |", processes[minIndex]);
        }
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    int processes[n], burst_time[n];
    float arrival_time[n];
    printf("Enter arrival times and burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Arrival time for Process %d: ", processes[i]);
        scanf("%f", &arrival_time[i]);
        printf("Burst time for Process %d: ", processes[i]);
        scanf("%d", &burst_time[i]);
    }
    
    printGanttChart(processes, n, burst_time, arrival_time);
    findAvgTime(processes, n, burst_time, arrival_time);
    
    return 0;
}


/*OUTPUT
Enter the number of processes: 3
Enter arrival times and burst times for each process:
Arrival time for Process 1: 0
Burst time for Process 1: 7
Arrival time for Process 2: 0
Burst time for Process 2: 3
Arrival time for Process 3: 0
Burst time for Process 3: 4

Gantt Chart:
| P2 | P3 | P1 |

Process	 Arrival Time	Burst Time	Waiting Time	Turnaround Time	Completion Time
1		0.0		7		7		14		14
2		0.0		3		0		3		3
3		0.0		4		3		7		7

Average Waiting Time: 3.33
Average Turnaround Time: 8.00


=== Code Execution Successful ===*/
