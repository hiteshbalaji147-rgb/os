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
    
    return 0;
}
