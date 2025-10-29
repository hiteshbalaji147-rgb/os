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

// Function to implement SJF scheduling
void sjfScheduling(struct Process proc[], int n) {
    int completed = 0;
    int current_time = 0;
    
    printf("\nExecution Timeline:\n");
    printf("===================\n");
    
    while (completed < n) {
        int shortest = -1;
        int min_burst = 9999;
        
        // Find process with shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (!proc[i].completed && proc[i].arrival_time <= current_time) {
                if (proc[i].burst_time < min_burst) {
                    min_burst = proc[i].burst_time;
                    shortest = i;
                }
                // If burst times are equal, choose process that arrived first
                else if (proc[i].burst_time == min_burst && 
                         proc[i].arrival_time < proc[shortest].arrival_time) {
                    shortest = i;
                }
            }
        }
        
        if (shortest == -1) {
            // No process available, CPU idle
            current_time++;
        } else {
            // Execute the selected process
            printf("Time %d: Process P%d (Burst: %d) starts execution\n",
                   current_time, proc[shortest].pid, proc[shortest].burst_time);
            
            current_time += proc[shortest].burst_time;
            proc[shortest].completion_time = current_time;
            proc[shortest].turnaround_time = proc[shortest].completion_time - proc[shortest].arrival_time;
            proc[shortest].waiting_time = proc[shortest].turnaround_time - proc[shortest].burst_time;
            proc[shortest].completed = true;
            completed++;
            
            printf("Time %d: Process P%d completed\n\n", current_time, proc[shortest].pid);
        }
    }
}

// Function to display results and statistics
void displayResults(struct Process proc[], int n) {
    float total_wt = 0, total_tat = 0;
    int total_completion_time = 0;
    
    printf("\n\nProcess Scheduling Results:\n");
    printf("============================\n");
    printf("Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    printf("=======\t=======\t=====\t==========\t==========\t=======\n");
    
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
        if (proc[i].completion_time > total_completion_time) {
            total_completion_time = proc[i].completion_time;
        }
        
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", 
               proc[i].pid, proc[i].arrival_time, proc[i].burst_time,
               proc[i].completion_time, proc[i].turnaround_time, 
               proc[i].waiting_time);
    }
    
    printf("\n========================================\n");
    printf("Performance Metrics:\n");
    printf("========================================\n");
    printf("Average Waiting Time: %.2f units\n", total_wt / n);
    printf("Average Turnaround Time: %.2f units\n", total_tat / n);
    printf("Total Completion Time: %d units\n", total_completion_time);
    printf("Throughput: %.2f processes/unit\n", (float)n / total_completion_time);
}

// Main function
int main() {
    int n;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("\n");
    
    struct Process proc[n];
    
    // Input process details
    inputProcesses(proc, n);
    
    // Perform SJF scheduling
    sjfScheduling(proc, n);
    
    // Display results
    displayResults(proc, n);
    
    printf("\n========================================\n");
    printf("SJF Scheduling completed successfully!\n");
    printf("========================================\n");
    
    return 0;
}
