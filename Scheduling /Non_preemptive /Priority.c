#include <stdio.h>
#include <string.h>

int main() {
    int n, i, j, min, found, lastScheduled = 0, num = 0, idle = 0;
    float totalWaitingTime = 0.0, totalTurnAroundTime = 0.0;

    // Arrays for process details
    char name[20][20], ganttChart[40][20];
    int arrivalTime[20], burstTime[20], priority[20], status[20], completionTime[20], waitingTime[20], turnAroundTime[20];
    int startTime[40], endTime[40];

    // Input: Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input: Process details
    for (i = 0; i < n; i++) {
        printf("\nEnter details of process %d", i + 1);
        printf("\nProcess Name: ");
        scanf("%s", name[i]);
        printf("Arrival Time: ");
        scanf("%d", &arrivalTime[i]);
        printf("Burst Time: ");
        scanf("%d", &burstTime[i]);
        printf("Priority: ");
        scanf("%d", &priority[i]);
        status[i] = 0; // Mark process as not executed yet
    }

    // Priority Scheduling Execution
    for (i = 0; lastScheduled < n;) {
        found = 0;

        // Find the highest priority process that has arrived
        for (j = 0; j < n; j++) {
            if (i >= arrivalTime[j] && status[j] == 0) {
                if (found == 0) {
                    min = j;
                    found = 1;
                } else if ((priority[min] > priority[j]) || (priority[min] == priority[j] && arrivalTime[min] > arrivalTime[j])) {
                    min = j;
                }
            }
        }

        if (idle == 0 && found == 0) {
            // CPU is idle if no process has arrived
            strcpy(ganttChart[num], "Idle");
            startTime[num] = i;
            i++;
            idle = 1;
        } else if (found == 1) {
            if (idle == 1) {
                endTime[num] = i;
                num++;
                idle = 0;
            }

            // Execute process
            strcpy(ganttChart[num], name[min]);
            status[min] = 1;
            startTime[num] = i;
            endTime[num] = i + burstTime[min];

            // Update process times
            i = endTime[num];
            completionTime[min] = endTime[num];
            turnAroundTime[min] = completionTime[min] - arrivalTime[min];
            waitingTime[min] = turnAroundTime[min] - burstTime[min];

            num++;
            lastScheduled++;
        } else {
            i++;
        }
    }

    // Output Results
    printf("\nProcess Name\tCompletion Time (ms)\tWaiting Time (ms)\tTurnaround Time (ms)\n\n");
    for (i = 0; i < n; i++) {
        printf("%s\t\t%d\t\t\t%d\t\t\t%d\n", name[i], completionTime[i], waitingTime[i], turnAroundTime[i]);
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];
    }

    // Print Gantt Chart
    printf("\n\nGANTT CHART ");
    printf("\n\t------------------------------------------------------\n\t");
    for (i = 0; i < num; i++) {
        printf("| %s ", ganttChart[i]);
    }
    printf("|");
    printf("\n\t------------------------------------------------------\n\t");
    for (i = 0; i < num; i++) {
        printf("%d\t", startTime[i]);
    }
    printf("%d\n", endTime[num - 1]);

    // Print Average Times
    printf("\nAverage Waiting Time: %.2f ms", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f ms\n", totalTurnAroundTime / n);

    return 0;
}
