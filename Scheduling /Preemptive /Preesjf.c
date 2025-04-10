#include <stdio.h>
#include <limits.h>

void input(int n, int id[], int arrivalTime[], int burstTime[], int remainingTime[]) {
    int i;
    for (i = 0; i < n; i++) {
        id[i] = i + 1;
        printf("\nEnter Arrival Time and Burst Time for Process %d: ", id[i]);
        scanf("%d %d", &arrivalTime[i], &burstTime[i]);
        remainingTime[i] = burstTime[i];
    }
}

void sortByArrival(int n, int id[], int arrivalTime[], int burstTime[], int remainingTime[]) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arrivalTime[j] > arrivalTime[j + 1]) {
                temp = arrivalTime[j];
                arrivalTime[j] = arrivalTime[j + 1];
                arrivalTime[j + 1] = temp;

                temp = burstTime[j];
                burstTime[j] = burstTime[j + 1];
                burstTime[j + 1] = temp;

                temp = remainingTime[j];
                remainingTime[j] = remainingTime[j + 1];
                remainingTime[j + 1] = temp;

                temp = id[j];
                id[j] = id[j + 1];
                id[j + 1] = temp;
            }
        }
    }
}

void schedule(int n, int id[], int arrivalTime[], int burstTime[], int remainingTime[],
              int completionTime[], int turnAroundTime[], int waitingTime[],
              int gantt[], int ganttInfo[]) {
    
    int currentTime = 0;
    int completed = 0;
    int minIndex, minRemainingTime, i;

    while (completed < n) {
        minIndex = -1;
        minRemainingTime = INT_MAX;

        for (i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && remainingTime[i] > 0 && remainingTime[i] < minRemainingTime) {
                minRemainingTime = remainingTime[i];
                minIndex = i;
            }
        }

        if (minIndex != -1) {
            gantt[ganttInfo[0]] = id[minIndex];
            ganttInfo[0] = ganttInfo[0] + 1;

            remainingTime[minIndex]--;
            currentTime++;

            if (remainingTime[minIndex] == 0) {
                completionTime[minIndex] = currentTime;
                turnAroundTime[minIndex] = completionTime[minIndex] - arrivalTime[minIndex];
                waitingTime[minIndex] = turnAroundTime[minIndex] - burstTime[minIndex];
                ganttInfo[1] = ganttInfo[1] + turnAroundTime[minIndex];
                ganttInfo[2] = ganttInfo[2] + waitingTime[minIndex];
                completed++;
            }
        } else {
            gantt[ganttInfo[0]] = -1;
            ganttInfo[0] = ganttInfo[0] + 1;
            currentTime++;
        }
    }
}

void displayTable(int n, int id[], int arrivalTime[], int burstTime[],
                  int completionTime[], int turnAroundTime[], int waitingTime[],
                  int totalTAT, int totalWT) {
    int i;
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", id[i], arrivalTime[i], burstTime[i],
               completionTime[i], turnAroundTime[i], waitingTime[i]);
    }

    printf("\nAverage Turnaround Time: %.2f", (float)totalTAT / n);
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWT / n);
}

void displayGantt(int gantt[], int length) {
    int i;
    printf("\nGantt Chart:\n|");
    for (i = 0; i < length; i++) {
        if (gantt[i] == -1) {
            printf(" IDLE |");
        } else {
            printf(" P%d |", gantt[i]);
        }
    }
    printf("\n");
}

int main() {
    int n;
    int id[20], arrivalTime[20], burstTime[20], remainingTime[20];
    int completionTime[20], turnAroundTime[20], waitingTime[20];
    int gantt[100], ganttInfo[3]; // [0] = index, [1] = total TAT, [2] = total WT

    ganttInfo[0] = 0;
    ganttInfo[1] = 0;
    ganttInfo[2] = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    input(n, id, arrivalTime, burstTime, remainingTime);
    sortByArrival(n, id, arrivalTime, burstTime, remainingTime);
    schedule(n, id, arrivalTime, burstTime, remainingTime,
             completionTime, turnAroundTime, waitingTime, gantt, ganttInfo);
    displayTable(n, id, arrivalTime, burstTime, completionTime, turnAroundTime, waitingTime,
                 ganttInfo[1], ganttInfo[2]);
    displayGantt(gantt, ganttInfo[0]);

    return 0;
}
