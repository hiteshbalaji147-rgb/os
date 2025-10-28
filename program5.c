#include <stdio.h>

struct Process {
    int pid;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

void roundRobin(struct Process proc[], int n, int quantum) {
    int time = 0;
    int completed = 0;
    
    printf("\nRound Robin Scheduling (Time Quantum = %d)\n", quantum);
    printf("===========================================\n");
    
    while (completed < n) {
        int done = 1;
        
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                done = 0;
                
                if (proc[i].remaining_time > quantum) {
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                    printf("Time %d: Process P%d executed for %d units\n", 
                           time - quantum, proc[i].pid, quantum);
                } else {
                    time += proc[i].remaining_time;
                    printf("Time %d: Process P%d executed for %d units (Completed)\n", 
                           time - proc[i].remaining_time, proc[i].pid, proc[i].remaining_time);
                    proc[i].waiting_time = time - proc[i].burst_time;
                    proc[i].turnaround_time = time;
                    proc[i].remaining_time = 0;
                    completed++;
                }
            }
        }
        
        if (done) break;
    }
}

void displayResults(struct Process proc[], int n) {
    float total_wt = 0, total_tat = 0;
    
    printf("\n\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("=======\t==========\t============\t===============\n");
    
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
        printf("P%d\t%d\t\t%d\t\t%d\n", 
               proc[i].pid, proc[i].burst_time, 
               proc[i].waiting_time, proc[i].turnaround_time);
    }
    
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n, quantum;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    struct Process proc[n];
    
    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter burst time for Process P%d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
    }
    
    roundRobin(proc, n, quantum);
    displayResults(proc, n);
    
    return 0;
}
