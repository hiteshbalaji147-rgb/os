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
