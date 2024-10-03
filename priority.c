#include <stdio.h>

int main() {
    int i, sum = 0, n, bt[20], tt[20], wt[20], p[20], priority[20], temp;
    float wt_avg = 0, tt_avg = 0;

    printf("\nEnter the number of Processes(Max 20): ");
    scanf("%d", &n);

    printf("\nEnter the Burst Time and Priority of Each Process:\n");
    for (int j = 0; j < n; j++) {
        p[j] = j + 1;
        printf("P%d : ", j + 1);
        scanf("%d %d", &bt[j], &priority[j]);
    }

    // Sorting processes based on priority
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (priority[j] > priority[j + 1]) {
                temp = priority[j];
                priority[j] = priority[j + 1];
                priority[j + 1] = temp;

                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Calculating turnaround time and waiting time
    for (i = 0; i < n; i++) {
        sum += bt[i];
        tt[i] = sum;
        wt[i] = tt[i] - bt[i];
        wt_avg += wt[i];
        tt_avg += tt[i];
    }

    wt_avg /= n;
    tt_avg /= n;

    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i], bt[i], priority[i], wt[i], tt[i]);

    printf("\nAverage Waiting Time: %.2f ms", wt_avg);
    printf("\nAverage Turnaround Time: %.2f ms\n", tt_avg);
    printf("\t\t\t Gantt Chart \t\t\t\n");
    printf("0");
    for (i = 0; i < n; i++)
        printf("  P%d  %d", p[i], tt[i]);
    printf("\n");
    return 0;
}
