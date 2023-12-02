#include <stdio.h>

// Function to implement Round Robin scheduling
void roundRobin(int processes[], int n, int burst_time[], int quantum) {
    int waiting_time[n], turnaround_time[n];
    int remaining_time[n];

    // Copy burst_time[] to remaining_time[]
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
        waiting_time[i] = 0;
        turnaround_time[i] = 0;
    }

    int time = 0; // Current time

    // Continue the loop until all processes are done
    while (1) {
        int done = 1; // Assume all processes are done

        // Traverse all processes
        for (int i = 0; i < n; i++) {
            // If burst time of a process is greater than 0, process is not done yet
            if (remaining_time[i] > 0) {
                done = 0; // Set done to false

                // If remaining time is greater than quantum, execute for the quantum time
                if (remaining_time[i] > quantum) {
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else { // If remaining time is less than or equal to quantum, execute for remaining time
                    time += remaining_time[i];
                    waiting_time[i] = time - burst_time[i];
                    remaining_time[i] = 0;
                }
            }
        }

        // If all processes are done, break out of the loop
        if (done == 1)
            break;
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++)
        turnaround_time[i] = burst_time[i] + waiting_time[i];

    // Display the results
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++)
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], waiting_time[i], turnaround_time[i]);
}

// Driver code
int main() {
    int processes[] = {1, 2, 3};
    int n = sizeof(processes) / sizeof(processes[0]);

    int burst_time[] = {10, 5, 8};
    int quantum = 2;

    roundRobin(processes, n, burst_time, quantum);

    return 0;
}
