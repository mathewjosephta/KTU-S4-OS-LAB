#include <stdio.h>
#include <string.h>

void main() {
    int number_of_processes, time_quantum, i, j, completed_processes = 0, current_time = 0;
    int total_waiting_time = 0, total_turnaround_time = 0;
    int executed_flag;

    char process_name[10][20]; // Process names (Full names allowed)
    int burst_time[10], arrival_time[10], waiting_time[10], turnaround_time[10], remaining_time[10];

    printf("Enter the number of processes: ");
    scanf("%d", &number_of_processes);

    // Input process details
    for (i = 0; i < number_of_processes; i++) {
        printf("Enter the process name: ");
        scanf("%s", process_name[i]);
        printf("Enter the arrival time: ");
        scanf("%d", &arrival_time[i]);
        printf("Enter the burst time: ");
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i]; // Remaining time initially equals burst time
    }

    // Input time quantum
    printf("\nEnter the time quantum: ");
    scanf("%d", &time_quantum);

    // Sorting processes based on arrival time
    for (i = 0; i < number_of_processes - 1; i++) {
        for (j = i + 1; j < number_of_processes; j++) {
            if (arrival_time[i] > arrival_time[j]) {
                // Swap process names using strcpy()
                char temp_name[20];
                strcpy(temp_name, process_name[i]);
                strcpy(process_name[i], process_name[j]);
                strcpy(process_name[j], temp_name);

                // Swap numerical values
                int temp = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = temp;

                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;

                temp = remaining_time[i];
                remaining_time[i] = remaining_time[j];
                remaining_time[j] = temp;
            }
        }
    }

    printf("\nGantt Chart:\n");
    printf("|");

    while (completed_processes < number_of_processes) {
        executed_flag = 0; // Track if any process ran in this cycle

        for (i = 0; i < number_of_processes; i++) {
            if (arrival_time[i] <= current_time && remaining_time[i] > 0) {
                executed_flag = 1; // At least one process executed

                if (remaining_time[i] <= time_quantum) {  
                    current_time += remaining_time[i];
                    printf(" %s (%d) |", process_name[i], current_time);
                    remaining_time[i] = 0;
                    turnaround_time[i] = current_time - arrival_time[i];
                    waiting_time[i] = turnaround_time[i] - burst_time[i];
                    completed_processes++;
                } else {  
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                    printf(" %s (%d) |", process_name[i], current_time);
                }
            }
        }

        // If no process ran, CPU is idle
        if (!executed_flag) {
            printf(" Idle (%d) |", current_time);
            current_time++;
        }
    }

    printf("\n\nProcess Name\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < number_of_processes; i++) {
        printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\n", process_name[i], burst_time[i], arrival_time[i], waiting_time[i], turnaround_time[i]);
    }

    // Calculate and print averages
    for (i = 0; i < number_of_processes; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_waiting_time / number_of_processes);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_turnaround_time / number_of_processes);
}
