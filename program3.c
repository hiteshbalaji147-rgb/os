import heapq

class Process:
    def __init__(self, pid, arrival_time, burst_time):
        self.pid = pid
        self.arrival_time = arrival_time
        self.burst_time = burst_time
        self.remaining_time = burst_time
        self.waiting_time = 0
        self.turnaround_time = 0
        self.completion_time = 0

    def preemptive_sjf(processes):
    processes.sort(key=lambda p: p.arrival_time)
    ready_queue = []
    current_time = 0
    completed = []
    gantt_chart = []
    last_pid = None
    
   
