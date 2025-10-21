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

if __name__ == "__main__":
    processes = ['P1', 'P2', 'P3', 'P4']
    burst_times = [24, 3, 3, 12]  
    quantum = 4  
    
    order, wt, tat, avg_wt, avg_tat = round_robin(processes, burst_times, quantum)
    
    print("Execution Order (Process, Time Executed):")
    for proc, time_exec in order:
        print(f"{proc}: {time_exec} units")
    
    print("\nWaiting Times:")
    for i, proc in enumerate(processes):
        print(f"{proc}: {wt[i]}")
    
    print("\nTurnaround Times:")
    for i, proc in enumerate(processes):
        print(f"{proc}: {tat[i]}")
    
    print(f"\nAverage Waiting Time: {avg_wt:.2f}")
    print(f"Average Turnaround Time: {avg_tat:.2f}")

