#include <stdio.h>

int main() {
    int n, quantum, time = 0, completed = 0;
    int id[20], arrivalTime[20], burstTime[20], remainingTime[20], completionTime[20], turnaroundTime[20], waitingTime[20];
    float totalTAT = 0, totalWT = 0;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        id[i] = i + 1;
        printf("\nEnter Arrival Time and Burst Time for Process %d: ", id[i]);
        scanf("%d %d", &arrivalTime[i], &burstTime[i]);
        remainingTime[i] = burstTime[i];
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &quantum);

    while (completed < n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0 && arrivalTime[i] <= time) {
                if (remainingTime[i] > quantum) {
                    time += quantum;
                    remainingTime[i] -= quantum;
                } else {
                    time += remainingTime[i];
                    remainingTime[i] = 0;
                    completionTime[i] = time;
                    turnaroundTime[i] = completionTime[i] - arrivalTime[i];
                    waitingTime[i] = turnaroundTime[i] - burstTime[i];
                    completed++;
                }
                executed = 1;
            }
        }
        if (!executed) 
            time++; 
    }

    printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        totalTAT += turnaroundTime[i];
        totalWT += waitingTime[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", id[i], arrivalTime[i], burstTime[i], 
               completionTime[i], turnaroundTime[i], waitingTime[i]);
    }
    
    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);

    return 0;
}
