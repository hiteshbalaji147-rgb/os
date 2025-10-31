#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Constants for the program
#define MAX_PROCESSES 10
#define MAX_NAME_LENGTH 20

// Structure to represent a process in FCFS scheduling
struct Process {
    int pid;                        // Process ID
    char name[MAX_NAME_LENGTH];     // Process name
    int arrival_time;               // Arrival time
    int burst_time;                 // Burst time (execution time)
    int completion_time;            // Completion time
    int turnaround_time;            // Turnaround time (CT - AT)
    int waiting_time;               // Waiting time (TAT - BT)
    int response_time;              // Response time (first execution - AT)
    int start_time;                 // Time when process starts execution
};

// Function to input process details from user
void inputProcesses(struct Process proc[], int n) {
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║  First Come First Serve (FCFS) Scheduling     ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
    
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        
        printf("Process %d:\n", i + 1);
        printf("  Name: ");
        scanf("%s", proc[i].name);
        
        printf("  Arrival Time: ");
        scanf("%d", &proc[i].arrival_time);
        
        printf("  Burst Time: ");
        scanf("%d", &proc[i].burst_time);
        
        // Initialize other fields
        proc[i].completion_time = 0;
        proc[i].turnaround_time = 0;
        proc[i].waiting_time = 0;
        proc[i].response_time = 0;
        proc[i].start_time = 0;
        
        printf("\n");
    }
}
