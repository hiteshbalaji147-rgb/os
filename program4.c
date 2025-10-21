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
    
    while queue:
        current = queue.popleft()
        if remaining_burst[current] > quantum:
            time += quantum
            remaining_burst[current] -= quantum
            execution_order.append((processes[current], quantum))
            queue.append(current)  
        else:
            time += remaining_burst[current]
            execution_order.append((processes[current], remaining_burst[current]))
            remaining_burst[current] = 0
            waiting_time[current] = time - burst_times[current]
            turnaround_time[current] = time
    
    avg_waiting = sum(waiting_time) / n
    avg_turnaround = sum(turnaround_time) / n
    
    return execution_order, waiting_time, turnaround_time, avg_waiting, avg_turnaround

