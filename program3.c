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
    
   while len(completed) < len(processes):
        for p in processes:
            if p.arrival_time <= current_time and p not in ready_queue and p not in completed:
                heapq.heappush(ready_queue, (p.remaining_time, p.pid, p))
        
        if ready_queue:
            _, _, p = heapq.heappop(ready_queue)
            
            if last_pid != p.pid:
                if gantt_chart and gantt_chart[-1][0] == last_pid:
                    gantt_chart[-1] = (last_pid, gantt_chart[-1][1], current_time)
                gantt_chart.append((p.pid, current_time, current_time + 1))
                last_pid = p.pid
            
            p.remaining_time -= 1
            current_time += 1
            
            if p.remaining_time == 0:
                p.completion_time = current_time
                p.turnaround_time = p.completion_time - p.arrival_time
                p.waiting_time = p.turnaround_time - p.burst_time
                completed.append(p)
            else:
                heapq.heappush(ready_queue, (p.remaining_time, p.pid, p))
        else:
            current_time += 1
    
    if gantt_chart:
        gantt_chart[-1] = (gantt_chart[-1][0], gantt_chart[-1][1], current_time)


            processes = [
    Process(1, 0, 6),
    Process(2, 1, 4),
    Process(3, 2, 2),
    Process(4, 3, 3)
]

completed, gantt = preemptive_sjf(processes)

print("Preemptive SJF (SRTF) Results:")
print("PID\tArrival\tBurst\tWaiting\tTurnaround")
total_waiting = 0
total_turnaround = 0
for p in completed:
    print(f"{p.pid}\t{p.arrival_time}\t{p.burst_time}\t{p.waiting_time}\t{p.turnaround_time}")
    total_waiting += p.waiting_time
    total_turnaround += p.turnaround_time

print(f"\nAverage Waiting Time: {total_waiting / len(processes):.2f}")
print(f"Average Turnaround Time: {total_turnaround / len(processes):.2f}")

print("\nGantt Chart:")
for pid, start, end in gantt:
    print(f"P{pid}: {start}-{end}", end=" ")
print()

 

    
    return completed, gantt_chart

# Example usage
