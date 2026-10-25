# Homework 7: Process Scheduling Simulation

This project is a simple C program that simulates two CPU scheduling algorithms: **First Come First Served (FCFS)** and **Shortest Job First (SJF)**. It uses non-preemptive scheduling, which means a process runs until it finishes once it starts.

The program asks for each process's arrival time and burst time. It then shows the execution order, a text Gantt chart, each process's waiting/turnaround/response times, and the average times for each algorithm.

## How to run on macOS

Open Terminal, go to the folder containing `scheduler.c`, and run:

```bash
clang -Wall -Wextra scheduler.c -o scheduler
./scheduler
```

If `clang` is missing, install Apple's Command Line Tools with `xcode-select --install` and try again.

The code also runs on Linux using `gcc scheduler.c -o scheduler` followed by `./scheduler`.

## How the algorithms work

### FCFS (First Come First Served)

FCFS executes processes in the order they arrive. The process with the earliest arrival time runs first. If two processes arrive at the same time, the smaller PID goes first. Once a process starts, it runs until completion.

For example, if processes arrive at times 0, 1, 2, and 3, they execute in that order even if a later process has a shorter burst time.

### SJF (Shortest Job First)

SJF chooses the process with the **shortest burst time among the processes that have already arrived**. It makes a new choice only when the currently running process finishes. If burst times are equal, it chooses the earlier arrival time, and then the smaller PID.

If no process has arrived yet, the CPU remains idle until the next process arrives. A process cannot be selected before its arrival time.

## How the C code works

The code is in `scheduler.c` and uses these main parts:

- **`Process` structure:** Stores the process ID (`pid`), arrival time, burst time, waiting time, turnaround time, and response time.
- **`main()`:** Reads the number of processes and their arrival and burst times, checks that inputs are valid, then calls both algorithms.
- **`fcfs()`:** Finds the next unfinished process with the earliest arrival time. It updates the CPU clock, records when the process starts and ends, and calculates its time values.
- **`sjf()`:** Looks at unfinished processes that have arrived, chooses the one with the shortest burst time, and calculates its time values. If none are ready, it moves the CPU clock to the next arrival.
- **`print_results()`:** Prints the Gantt chart, a timeline, the results table, and the three averages.

Both algorithms make their own copy of the input processes, so they use the same original input independently. The `order`, `starts`, and `ends` arrays keep the execution order and start/end times for the printed timeline.

### Time calculations

For each process:

- **Turnaround time (TAT)** = completion time - arrival time
- **Waiting time (WT)** = turnaround time - burst time
- **Response time (RT)** = first start time - arrival time

Since FCFS and this version of SJF are non-preemptive, **response time equals waiting time**. Each average is the sum of the corresponding times divided by the number of processes.

## Sample run

Enter `4` as the number of processes, followed by these arrival/burst pairs:

```text
0 8
1 4
2 9
3 5
```

Expected execution order:

```text
FCFS: P1 [0-8] -> P2 [8-12] -> P3 [12-21] -> P4 [21-26]
SJF:  P1 [0-8] -> P2 [8-12] -> P4 [12-17] -> P3 [17-26]
```

Expected averages:

| Algorithm | Average WT | Average TAT | Average RT |
| --- | ---: | ---: | ---: |
| FCFS | 8.75 | 15.25 | 8.75 |
| SJF | 7.75 | 14.25 | 7.75 |

**Note:** The SJF Gantt chart in the assignment's example incorrectly starts with P2. Since P2 arrives at time 1 and P1 arrives at time 0, the correct non-preemptive SJF execution starts with P1. The averages in the example agree with this corrected order.

## Edge cases

The program also handles:

- **Same arrival time:** FCFS uses the smaller PID first. SJF uses the shortest burst time first.
- **Same burst time:** SJF uses the earlier arrival time, then smaller PID.
- **Idle CPU:** If no process is ready, scheduling resumes at the next arrival time. The Gantt chart marks idle gaps.
- **Invalid input:** The process count must be between 1 and 100; arrival times must be non-negative; burst times must be positive.

## Sample output/input example from my local run

<img width="513" height="633" alt="image" src="https://github.com/user-attachments/assets/bfb5cfb7-f7c0-4819-a775-42ef1fc06f3a" />
