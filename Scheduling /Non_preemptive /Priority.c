#include <stdio.h>
#include <limits.h>

int main() {
    // Declare variables
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    // Arrays to store process details
    int processes[n], burst_time[n], priority[n], completed[n];
    int wt[n], tat[n], ct[n], start[n];
    float arrival_time[n], currentTime = 0;
    
    // Input process details
    printf("Enter arrival times, burst times, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1; // Assign process numbers
        completed[i] = 0; // Mark all processes as incomplete initially
        printf("Arrival time for Process %d: ", processes[i]);
        scanf("%f", &arrival_time[i]);
        printf("Burst time for Process %d: ", processes[i]);
        scanf("%d", &burst_time[i]);
        printf("Priority for Process %d: ", processes[i]);
        scanf("%d", &priority[i]);
    }
    
    int completedCount = 0; // Track number of completed processes
    printf("\nGantt Chart:\n");
    
    // Process execution loop
    while (completedCount < n) {
        int minIndex = -1, highestPriority = INT_MAX;
        
        // Find the highest priority process that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (!completed[i] && arrival_time[i] <= currentTime) {
                if (minIndex == -1 || priority[i] < highestPriority || 
                    (priority[i] == highestPriority && arrival_time[i] < arrival_time[minIndex])) {
                    highestPriority = priority[i];
                    minIndex = i;
                }
            }
        }
        
        if (minIndex == -1) {
            // If no process is available, the CPU is idle
            printf("| Idle (%d) ", (int)currentTime);
            currentTime++;
        } else {
            // If a process is available, execute it
            if (currentTime < arrival_time[minIndex]) {
                printf("| Idle (%d) ", (int)currentTime);
                currentTime = arrival_time[minIndex];
            }
            printf("| P%d (%d) ", processes[minIndex], (int)currentTime);
            
            start[minIndex] = currentTime;
            wt[minIndex] = currentTime - arrival_time[minIndex]; // Calculate waiting time
            currentTime += burst_time[minIndex]; // Move current time forward
            ct[minIndex] = currentTime; // Completion time
            tat[minIndex] = burst_time[minIndex] + wt[minIndex]; // Turnaround time
            completed[minIndex] = 1; // Mark process as completed
            completedCount++;
        }
    }
    printf("|\n");
    
    // Calculate and display results
    int total_wt = 0, total_tat = 0;
    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%.1f\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrival_time[i], burst_time[i], priority[i], wt[i], tat[i], ct[i]);
    }
    
    // Print average waiting time and turnaround time
    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);
    
    return 0;
}
