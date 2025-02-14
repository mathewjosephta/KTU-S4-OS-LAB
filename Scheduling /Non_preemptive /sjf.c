#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    int processes[n], burst_time[n], waiting_time[n], turnaround_time[n], completion_time[n], completed[n], start[n];
    float arrival_time[n], currentTime = 0;
    
    printf("Enter arrival times and burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        completed[i] = 0;
        printf("Arrival time for Process %d: ", processes[i]);
        scanf("%f", &arrival_time[i]);
        printf("Burst time for Process %d: ", processes[i]);
        scanf("%d", &burst_time[i]);
    }
    
    int completedCount = 0;
    printf("\nGantt Chart:\n|");
    
    while (completedCount < n) {
        int minIndex = -1;
        int minBurst = 1e9;
        
        for (int i = 0; i < n; i++) {
            if (!completed[i] && arrival_time[i] <= currentTime && burst_time[i] < minBurst) {
                minBurst = burst_time[i];
                minIndex = i;
            }
        }
        
        if (minIndex == -1) {
            currentTime++;
        } else {
            start[minIndex] = currentTime;
            waiting_time[minIndex] = currentTime - arrival_time[minIndex];
            currentTime += burst_time[minIndex];
            completion_time[minIndex] = currentTime;
            turnaround_time[minIndex] = burst_time[minIndex] + waiting_time[minIndex];
            completed[minIndex] = 1;
            completedCount++;
            printf(" P%d |", processes[minIndex]);
        }
    }
    
    int total_wt = 0, total_tat = 0;
    printf("\n\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += waiting_time[i];
        total_tat += turnaround_time[i];
        printf("%d\t\t%.1f\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrival_time[i], burst_time[i], waiting_time[i], turnaround_time[i], completion_time[i]);
    }
    
    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);
    
    return 0;
}



/*OUTPUT
Enter the number of processes: 4
Enter arrival times and burst times for each process:
Arrival time for Process 1: 0
Burst time for Process 1: 7
Arrival time for Process 2: 2
Burst time for Process 2: 4
Arrival time for Process 3: 4
Burst time for Process 3: 1
Arrival time for Process 4: 5
Burst time for Process 4: 4

Gantt Chart:
| P1 | P3 | P2 | P4 |

Process	Arrival Time	Burst Time	Waiting Time	Turnaround Time	Completion Time
1		0.0		7		0		7		7
2		2.0		4		6		10		12
3		4.0		1		3		4		8
4		5.0		4		7		11		16

Average Waiting Time: 4.00
Average Turnaround Time: 8.00*/
