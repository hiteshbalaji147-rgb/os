#include <stdio.h>
#include <stdbool.h>

// Structure to represent a process
struct Process {
    int pid;              // Process ID
    int arrival_time;     // Arrival time
    int burst_time;       // Burst time
    int completion_time;  // Completion time
    int waiting_time;     // Waiting time
    int turnaround_time;  // Turnaround time
    bool completed;       // Completion status
};

// Function to input process details
void inputProcesses(struct Process proc[], int n) {
    printf("Shortest Job First (SJF) Scheduling Algorithm\n");
    printf("==============================================\n\n");
    
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Process P%d:\n", i + 1);
        printf("  Arrival Time: ");
        scanf("%d", &proc[i].arrival_time);
        printf("  Burst Time: ");
        scanf("%d", &proc[i].burst_time);
        proc[i].completed = false;
        proc[i].completion_time = 0;
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
        printf("\n");
    }
}
