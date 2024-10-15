#include <stdio.h>

// Function to display the chart for both scheduling policies
void display_chart(int processes[], int n, int arrival_time[], int burst_time[], int waiting_time[], int turnaround_time[], const char* scheduling) {
    printf("\n%s Scheduling\n", scheduling);
    printf("-------------------------------------------------\n");
    printf("| Process | Arrival Time | Burst Time | Waiting Time | Turnaround Time |\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("|   P%d    |      %d       |     %d     |      %d       |       %d        |\n", processes[i], arrival_time[i], burst_time[i], waiting_time[i], turnaround_time[i]);
    }
    printf("-------------------------------------------------\n");
}

// Function to calculate FCFS scheduling
void fcfs(int processes[], int n, int burst_time[], int arrival_time[]) {
    int waiting_time[n], turnaround_time[n], completion_time[n];
    int total_wait_time = 0, total_turnaround_time = 0;

    // Calculating completion time
    completion_time[0] = arrival_time[0] + burst_time[0];
    for (int i = 1; i < n; i++) {
        if (arrival_time[i] > completion_time[i - 1]) {
            completion_time[i] = arrival_time[i] + burst_time[i];
        } else {
            completion_time[i] = completion_time[i - 1] + burst_time[i];
        }
    }

    // Calculating turnaround time and waiting time
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = completion_time[i] - arrival_time[i];
        waiting_time[i] = turnaround_time[i] - burst_time[i];
        total_wait_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // Display the chart
    display_chart(processes, n, arrival_time, burst_time, waiting_time, turnaround_time, "FCFS");

    // Display average waiting time and turnaround time
    printf("\nAverage Waiting Time (FCFS): %.2f", (float)total_wait_time / n);
    printf("\nAverage Turnaround Time (FCFS): %.2f\n", (float)total_turnaround_time / n);
}

// Function to calculate SJF scheduling
void sjf(int processes[], int n, int burst_time[], int arrival_time[]) {
    int waiting_time[n], turnaround_time[n], completion_time[n];
    int total_wait_time = 0, total_turnaround_time = 0;
    int is_completed[n], current_time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
    }

    while (completed != n) {
        int idx = -1, min_burst = 1e9;
        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && is_completed[i] == 0) {
                if (burst_time[i] < min_burst) {
                    min_burst = burst_time[i];
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            current_time += burst_time[idx];
            completion_time[idx] = current_time;
            turnaround_time[idx] = completion_time[idx] - arrival_time[idx];
            waiting_time[idx] = turnaround_time[idx] - burst_time[idx];
            total_wait_time += waiting_time[idx];
            total_turnaround_time += turnaround_time[idx];
            is_completed[idx] = 1;
            completed++;
        } else {
            current_time++;
        }
    }

    // Display the chart
    display_chart(processes, n, arrival_time, burst_time, waiting_time, turnaround_time, "SJF");

    // Display average waiting time and turnaround time
    printf("\nAverage Waiting Time (SJF): %.2f", (float)total_wait_time / n);
    printf("\nAverage Turnaround Time (SJF): %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], arrival_time[n];
    printf("Enter the process IDs, arrival times, and burst times:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i], &arrival_time[i], &burst_time[i]);
    }

    // Perform FCFS scheduling
    fcfs(processes, n, burst_time, arrival_time);

    // Perform SJF scheduling
    sjf(processes, n, burst_time, arrival_time);

    return 0;
}
