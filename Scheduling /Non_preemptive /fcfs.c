#include <stdio.h>

void inputProcesses(int n, int id[], int arrivalTime[], int burstTime[]) {
    for (int i = 0; i < n; i++) {
        id[i] = i + 1;
        printf("\nEnter Arrival Time and Burst Time for Process %d: ", id[i]);
        scanf("%d %d", &arrivalTime[i], &burstTime[i]);
    }
}

void sortByArrivalTime(int n, int id[], int arrivalTime[], int burstTime[]) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arrivalTime[j] > arrivalTime[j + 1]) {
                // Swap arrival time
                temp = arrivalTime[j];
                arrivalTime[j] = arrivalTime[j + 1];
                arrivalTime[j + 1] = temp;

                // Swap burst time
                temp = burstTime[j];
                burstTime[j] = burstTime[j + 1];
                burstTime[j + 1] = temp;

                // Swap process ID
                temp = id[j];
                id[j] = id[j + 1];
                id[j + 1] = temp;
            }
        }
    }
}

void calculateTimes(int n, int arrivalTime[], int burstTime[], int completionTime[],
                    int turnAroundTime[], int waitingTime[], float *totalTAT, float *totalWT) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < arrivalTime[i]) {
            currentTime = arrivalTime[i];
        }

        completionTime[i] = currentTime + burstTime[i];
        currentTime = completionTime[i];

        turnAroundTime[i] = completionTime[i] - arrivalTime[i];
        waitingTime[i] = turnAroundTime[i] - burstTime[i];

        *totalTAT += turnAroundTime[i];
        *totalWT += waitingTime[i];
    }
}

void displayResults(int n, int id[], int arrivalTime[], int burstTime[], int completionTime[],
                    int turnAroundTime[], int waitingTime[], float totalTAT, float totalWT) {
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", id[i], arrivalTime[i], burstTime[i],
               completionTime[i], turnAroundTime[i], waitingTime[i]);
    }

    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
}

int main() {
    int n;
    int id[20], arrivalTime[20], burstTime[20];
    int completionTime[20], turnAroundTime[20], waitingTime[20];
    float totalTAT = 0, totalWT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    inputProcesses(n, id, arrivalTime, burstTime);
    sortByArrivalTime(n, id, arrivalTime, burstTime);
    calculateTimes(n, arrivalTime, burstTime, completionTime, turnAroundTime, waitingTime, &totalTAT, &totalWT);
    displayResults(n, id, arrivalTime, burstTime, completionTime, turnAroundTime, waitingTime, totalTAT, totalWT);

    return 0;
}
