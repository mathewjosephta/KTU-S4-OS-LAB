#include <stdio.h>
#include <string.h>

int main() {
    int n, i, j, min, found, completed = 0, num = 0, idle = 0, time = 0;
    float totalWT = 0.0, totalTT = 0.0;

    char names[20][20], ganttNames[40][20];
    int at[20], bt[20], wt[20], tt[20], ct[20], status[20] = {0};
    int startTimes[40], endTimes[40];

    // Input: Number of processes
    printf("ENTER THE NUMBER OF PROCESSES: ");
    scanf("%d", &n);

    // Input: Process details
    for (i = 0; i < n; i++) {
        printf("\nENTER DETAILS OF PROCESS %d", i + 1);
        printf("\nPROCESS NAME: ");
        scanf("%s", names[i]);
        printf("ARRIVAL TIME: ");
        scanf("%d", &at[i]);
        printf("BURST TIME: ");
        scanf("%d", &bt[i]);
    }

    // SJF Scheduling (Non-Preemptive)
    while (completed < n) {
        found = 0;
        min = -1;

        // Find process with the shortest burst time that has arrived
        for (j = 0; j < n; j++) {
            if (time >= at[j] && status[j] == 0) {
                if (!found || bt[j] < bt[min]) {
                    min = j;
                    found = 1;
                }
            }
        }

        if (!found) {
            // CPU remains idle
            if (!idle) {
                strcpy(ganttNames[num], "Idle");
                startTimes[num] = time;
                num++;
                idle = 1;
            }
            time++;
        } else {
            // Process execution
            if (idle) {
                endTimes[num - 1] = time;
                idle = 0;
            }
            strcpy(ganttNames[num], names[min]);
            startTimes[num] = time;
            time += bt[min];
            endTimes[num] = time;
            status[min] = 1;
            ct[min] = time;
            tt[min] = ct[min] - at[min];
            wt[min] = tt[min] - bt[min];
            totalWT += wt[min];
            totalTT += tt[min];
            num++;
            completed++;
        }
    }

    // Output: Process details
    printf("\nPROCESS NAME\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");
    for (i = 0; i < n; i++) {
        printf("    %s\t\t\t%d\t\t\t%d\t\t\t%d\n", names[i], ct[i], wt[i], tt[i]);
    }

    // Gantt Chart
    printf("\n\nGANTT CHART ");
    printf("\n\t--------------------------------------------------------------------\n\t");
    for (i = 0; i < num; i++) {
        printf("| %s ", ganttNames[i]);
    }
    printf("|");
    printf("\n\t--------------------------------------------------------------------\n\t");
    for (i = 0; i < num; i++) {
        printf("%d\t", startTimes[i]);
    }
    printf("%d\n", endTimes[num - 1]);

    // Output: Average waiting time & turnaround time
    printf("\nAVERAGE WAITING TIME: %.2f ms", totalWT / n);
    printf("\nAVERAGE TURNAROUND TIME: %.2f ms\n", totalTT / n);

    return 0;
}
