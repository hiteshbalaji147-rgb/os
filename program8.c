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

// Function to sort processes by arrival time (FCFS order)
void sortByArrivalTime(struct Process proc[], int n) {
    struct Process temp;
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Sort by arrival time, if equal then by process ID
            if (proc[j].arrival_time > proc[j + 1].arrival_time ||
                (proc[j].arrival_time == proc[j + 1].arrival_time && 
                 proc[j].pid > proc[j + 1].pid)) {
                
                // Swap processes
                temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

// Function to implement FCFS scheduling algorithm
void fcfsScheduling(struct Process proc[], int n) {
    int current_time = 0;
    int total_idle_time = 0;
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║           Execution Timeline                   ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
    
    for (int i = 0; i < n; i++) {
        // Check if CPU is idle
        if (current_time < proc[i].arrival_time) {
            int idle_time = proc[i].arrival_time - current_time;
            printf("Time %d-%d: CPU IDLE (%d units)\n", 
                   current_time, proc[i].arrival_time, idle_time);
            total_idle_time += idle_time;
            current_time = proc[i].arrival_time;
        }
        
        // Process starts execution
        proc[i].start_time = current_time;
        proc[i].response_time = proc[i].start_time - proc[i].arrival_time;
        
        printf("Time %d-%d: Process %s (P%d) executing [Burst: %d]\n",
               current_time, current_time + proc[i].burst_time,
               proc[i].name, proc[i].pid, proc[i].burst_time);
        
        // Update current time
        current_time += proc[i].burst_time;
        
        // Calculate times
        proc[i].completion_time = current_time;
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
    }
    
    printf("\nTotal CPU Idle Time: %d units\n", total_idle_time);
}

// Function to display Gantt Chart
void displayGanttChart(struct Process proc[], int n) {
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║              Gantt Chart                       ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
    
    // Top border
    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < proc[i].burst_time; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n");
    
    // Process names
    printf("|");
    for (int i = 0; i < n; i++) {
        int spaces = proc[i].burst_time * 2 - strlen(proc[i].name);
        int left_space = spaces / 2;
        int right_space = spaces - left_space;
        
        for (int j = 0; j < left_space; j++) printf(" ");
        printf("%s", proc[i].name);
        for (int j = 0; j < right_space; j++) printf(" ");
        printf("|");
    }
    printf("\n");
    
    // Bottom border
    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < proc[i].burst_time; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n");
    
    // Time markers
    printf("%d", proc[0].start_time);
    for (int i = 0; i < n; i++) {
        int spaces = proc[i].burst_time * 2;
        for (int j = 0; j < spaces; j++) printf(" ");
        printf("%d", proc[i].completion_time);
    }
    printf("\n");
}
