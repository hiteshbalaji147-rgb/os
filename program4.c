from collections import deque

def round_robin(processes, burst_times, quantum):
    n = len(processes)
    remaining_burst = burst_times[:]  
    waiting_time = [0] * n
    turnaround_time = [0] * n
    time = 0  
    queue = deque()  
    
    for i in range(n):
        queue.append(i)
    
    execution_order = []  
    
  
