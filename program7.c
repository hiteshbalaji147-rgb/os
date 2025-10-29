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
