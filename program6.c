#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    bool completed;
};

void priorityScheduling(struct Process proc[], int n) {
    int completed = 0;
    int current_time = 0;
    
    printf("\n\nExecution Order:\n");
    printf("================\n");
    
    while (completed < n) {
        int highest_priority = 9999;
        int selected = -1;
        
        // Find process with highest priority (lowest number)
        for (int i = 0; i < n; i++) {
            if (!proc[i].completed && proc[i].priority < highest_priority) {
                highest_priority = proc[i].priority;
                selected = i;
            }
        }
        
        if (selected != -1) {
            // Execute selected process
            printf("Time %d: Process P%d (Priority %d) executed for %d units\n",
                   current_time, proc[selected].pid, proc[selected].priority, 
                   proc[selected].burst_time);
            
            proc[selected].waiting_time = current_time;
            current_time += proc[selected].burst_time;
            proc[selected].turnaround_time = current_time;
            proc[selected].completed = true;
            completed++;
        }
    }
}

void displayResults(struct Process proc[], int n) {
    float total_wt = 0, total_tat = 0;
    
    printf("\n\nProcess Scheduling Results:\n");
    printf("============================\n");
    printf("Process\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("=======\t========\t==========\t============\t===============\n");
    
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", 
               proc[i].pid, proc[i].priority, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
    
    printf("\n----------------------------------------\n");
    printf("Average Waiting Time: %.2f units\n", total_wt / n);
    printf("Average Turnaround Time: %.2f units\n", total_tat / n);
    printf("CPU Utilization: 100.00%%\n");
    printf("Throughput: %.2f processes/unit time\n", (float)n / total_tat);
}

int main() {
    int n;
    
    printf("Priority Scheduling Algorithm\n");
    printf("==============================\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    struct Process proc[n];
    
    // Input process details
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("\nProcess P%d:\n", i + 1);
        printf("  Burst Time: ");
        scanf("%d", &proc[i].burst_time);
        printf("  Priority (lower number = higher priority): ");
        scanf("%d", &proc[i].priority);
        proc[i].completed = false;
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
    }
    
    priorityScheduling(proc, n);
    displayResults(proc, n);
    
    return 0;
}
