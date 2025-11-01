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
