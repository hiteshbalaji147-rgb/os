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
