#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Constants
#define MAX_PROCESSES 20
#define MAX_QUEUES 3
#define SYSTEM_QUEUE 0
#define USER_QUEUE 1
#define BATCH_QUEUE 2

// Process structure
struct Process {
    int pid;
    char name[20];
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int queue_type;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int start_time;
    bool started;
    bool completed;
};

// Queue structure
struct Queue {
    char name[30];
    int time_quantum;
    struct Process* processes[MAX_PROCESSES];
    int front;
    int rear;
    int count;
};

// Function prototypes
void initQueue(struct Queue* q, const char* name, int quantum);
bool isEmpty(struct Queue* q);
void enqueue(struct Queue* q, struct Process* p);
struct Process* dequeue(struct Queue* q);
void inputProcesses(struct Process proc[], int n);
void assignProcessesToQueues(struct Process proc[], int n, struct Queue queues[], int current_time);
void multilevelQueueScheduling(struct Process proc[], int n, struct Queue queues[]);

// Initialize queue
void initQueue(struct Queue* q, const char* name, int quantum) {
    strcpy(q->name, name);
    q->time_quantum = quantum;
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

// Check if queue is empty
bool isEmpty(struct Queue* q) {
    return q->count == 0;
}

// Add process to queue
void enqueue(struct Queue* q, struct Process* p) {
    if (q->count < MAX_PROCESSES) {
        q->rear = (q->rear + 1) % MAX_PROCESSES;
        q->processes[q->rear] = p;
        q->count++;
    }
}

// Remove process from queue
struct Process* dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        return NULL;
    }
    struct Process* p = q->processes[q->front];
    q->front = (q->front + 1) % MAX_PROCESSES;
    q->count--;
    return p;
}

// Input process details
void inputProcesses(struct Process proc[], int n) {
    printf("╔═══════════════════════════════════════════════╗\n");
    printf("║    Multilevel Queue Scheduling System        ║\n");
    printf("╚═══════════════════════════════════════════════╝\n\n");
    
    printf("Queue Types:\n");
    printf("  0 - System Queue (Highest Priority, RR with quantum=2)\n");
    printf("  1 - User Queue (Medium Priority, RR with quantum=4)\n");
    printf("  2 - Batch Queue (Lowest Priority, FCFS)\n\n");
    
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        
        printf("Process %d:\n", i + 1);
        printf("  Name: ");
        scanf("%s", proc[i].name);
        
        printf("  Arrival Time: ");
        scanf("%d", &proc[i].arrival_time);
        
        printf("  Burst Time: ");
        scanf("%d", &proc[i].burst_time);
        
        printf("  Queue Type (0-System, 1-User, 2-Batch): ");
        scanf("%d", &proc[i].queue_type);
        
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].started = false;
        proc[i].completed = false;
        proc[i].start_time = -1;
        
        printf("\n");
    }
}

// Assign arrived processes to their respective queues
void assignProcessesToQueues(struct Process proc[], int n, struct Queue queues[], int current_time) {
    for (int i = 0; i < n; i++) {
        if (!proc[i].completed && proc[i].arrival_time <= current_time && proc[i].remaining_time > 0) {
            bool in_queue = false;
            for (int q = 0; q < MAX_QUEUES; q++) {
                for (int j = 0; j < queues[q].count; j++) {
                    int idx = (queues[q].front + j) % MAX_PROCESSES;
                    if (queues[q].processes[idx] == &proc[i]) {
                        in_queue = true;
                        break;
                    }
                }
                if (in_queue) break;
            }
            
            if (!in_queue) {
                enqueue(&queues[proc[i].queue_type], &proc[i]);
            }
        }
    }
}

// Multilevel Queue Scheduling
void multilevelQueueScheduling(struct Process proc[], int n, struct Queue queues[]) {
    int current_time = 0;
    int completed = 0;
    
    printf("\n╔═══════════════════════════════════════════════╗\n");
    printf("║           Execution Timeline                  ║\n");
    printf("╚═══════════════════════════════════════════════╝\n\n");
    
    while (completed < n) {
        assignProcessesToQueues(proc, n, queues, current_time);
        
        bool executed = false;
        
        for (int q = 0; q < MAX_QUEUES; q++) {
            if (!isEmpty(&queues[q])) {
                struct Process* p = dequeue(&queues[q]);
                
                if (!p->started) {
                    p->start_time = current_time;
                    p->response_time = current_time - p->arrival_time;
                    p->started = true;
                }
                
                int exec_time = (queues[q].time_quantum > 0 && p->remaining_time > queues[q].time_quantum) 
                                ? queues[q].time_quantum : p->remaining_time;
                
                printf("Time %d: %s executing %s (P%d) for %d units [Queue: %s]\n",
                       current_time, queues[q].name, p->name, p->pid, exec_time, queues[q].name);
                
                current_time += exec_time;
                p->remaining_time -= exec_time;
                
                if (p->remaining_time == 0) {
                    p->completed = true;
                    p->completion_time = current_time;
                    p->turnaround_time = p->completion_time - p->arrival_time;
                    p->waiting_time = p->turnaround_time - p->burst_time;
                    completed++;
                } else {
                    enqueue(&queues[q], p);
                }
                
                executed = true;
                break;
            }
        }
        
        if (!executed) {
            current_time++;
        }
    }
}
