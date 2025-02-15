#include <stdio.h>

// Main function
int main() {
    int n;  // Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    // Declaring arrays for storing process details
    int processes[n], burst_time[n], waiting_time[n], turnaround_time[n], completion_time[n], completed[n], start[n];
    float arrival_time[n], currentTime = 0;
    
    // Taking input: Arrival Time and Burst Time for each process
    printf("Enter arrival times and burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;  // Process ID
        completed[i] = 0;  // Mark process as incomplete
        
        printf("Arrival time for Process %d: ", processes[i]);
        scanf("%f", &arrival_time[i]);
        
        printf("Burst time for Process %d: ", processes[i]);
        scanf("%d", &burst_time[i]);
    }
    
    int completedCount = 0;  // Tracks how many processes are completed
    printf("\nGantt Chart:\n|");  // Gantt Chart Visualization
    
    // Scheduling using Shortest Job Next (SJN)
    while (completedCount < n) {
        int minIndex = -1;  // Index of the process with the shortest burst time
        int minBurst = 1e9;  // Set initial burst time to a large value
        
        // Find the shortest available process
        for (int i = 0; i < n; i++) {
            if (!completed[i] && arrival_time[i] <= currentTime && burst_time[i] < minBurst) {
                minBurst = burst_time[i];
                minIndex = i;
            }
        }
        
        // If no process is available, increase the time (CPU is idle)
        if (minIndex == -1) {
            currentTime++;
        } else {
            // Processing the selected process
            start[minIndex] = currentTime;
            waiting_time[minIndex] = currentTime - arrival_time[minIndex];  // Waiting time calculation
            currentTime += burst_time[minIndex];  // Move the time forward
            completion_time[minIndex] = currentTime;  // Set completion time
            turnaround_time[minIndex] = burst_time[minIndex] + waiting_time[minIndex];  // Turnaround time calculation
            completed[minIndex] = 1;  // Mark the process as completed
            completedCount++;  // Increment completed count
            
            // Print process in Gantt Chart
            printf(" P%d |", processes[minIndex]);
        }
    }
    
    // Display process details in tabular format
    int total_wt = 0, total_tat = 0;
    printf("\n\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += waiting_time[i];
        total_tat += turnaround_time[i];
        printf("%d\t\t%.1f\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrival_time[i], burst_time[i], waiting_time[i], turnaround_time[i], completion_time[i]);
    }
    
    // Calculating and displaying averages
    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);
    
    return 0;  // Successful execution
}
