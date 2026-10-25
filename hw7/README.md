# Homework 7: Process Scheduling Simulation

A simple C program that simulates **First Come First Served (FCFS)** and **non-preemptive Shortest Job First (SJF)** scheduling.

Both algorithms calculate each process's waiting time, turnaround time, and response time, display a text Gantt chart and timeline, and print the averages.

## Run on macOS

Open Terminal in this folder and run:

```bash
clang -Wall -Wextra scheduler.c -o scheduler
./scheduler
```

If `clang` is not installed, run `xcode-select --install` to install Apple's command-line developer tools.

## Sample input

Type `4` for the number of processes, then enter:

```text
0 8
1 4
2 9
3 5
```

## Notes

FCFS runs processes in arrival order. Non-preemptive SJF selects the shortest *available* process whenever the CPU becomes free; it cannot execute a process before arrival. Equal burst times are resolved by earlier arrival, then lower PID. If nothing has arrived, the CPU stays idle until the next arrival.

**Correction to the homework example:** Its SJF sample chart starts with P2 even though P2 arrives at time 1 and P1 arrives at time 0. With proper non-preemptive SJF, P1 runs first. The correct sample order is P1, P2, P4, P3.
