#include <stdio.h>

#define MAX 100

typedef struct {
    int pid, arrival_time, burst_time;
    int waiting_time, turnaround_time, response_time;
} Process;

void print_results(Process p[], int order[], int starts[], int ends[], int n, const char *name) {
    double total_wt = 0, total_tat = 0, total_rt = 0;
    printf("\n=== %s ===\n", name);
    printf("Gantt Chart: ");
    for (int i = 0; i < n; i++) {
        if (starts[i] > (i == 0 ? 0 : ends[i - 1]))
            printf("| IDLE ");
        printf("| P%d ", p[order[i]].pid);
    }
    printf("|\nTimeline: ");
    for (int i = 0; i < n; i++)
        printf("P%d [%d-%d]  ", p[order[i]].pid, starts[i], ends[i]);
    printf("\n\nPID\tAT\tBT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        Process x = p[order[i]];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", x.pid, x.arrival_time,
               x.burst_time, x.waiting_time, x.turnaround_time, x.response_time);
        total_wt += x.waiting_time;
        total_tat += x.turnaround_time;
        total_rt += x.response_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Response Time: %.2f\n", total_rt / n);
}

void fcfs(Process original[], int n) {
    Process p[MAX];
    int order[MAX], starts[MAX], ends[MAX], used[MAX] = {0};
    int time = 0;
    for (int i = 0; i < n; i++) p[i] = original[i];

    for (int i = 0; i < n; i++) {
        int best = -1;
        for (int j = 0; j < n; j++) {
            if (!used[j] && (best == -1 ||
                p[j].arrival_time < p[best].arrival_time ||
                (p[j].arrival_time == p[best].arrival_time && p[j].pid < p[best].pid)))
                best = j;
        }
        used[best] = 1;
        if (time < p[best].arrival_time) time = p[best].arrival_time;
        starts[i] = time;
        p[best].waiting_time = time - p[best].arrival_time;
        p[best].response_time = p[best].waiting_time;
        time += p[best].burst_time;
        ends[i] = time;
        p[best].turnaround_time = time - p[best].arrival_time;
        order[i] = best;
    }
    print_results(p, order, starts, ends, n, "First Come First Served (FCFS)");
}

void sjf(Process original[], int n) {
    Process p[MAX];
    int order[MAX], starts[MAX], ends[MAX], used[MAX] = {0};
    int time = 0;
    for (int i = 0; i < n; i++) p[i] = original[i];

    for (int i = 0; i < n; i++) {
        int best = -1;
        for (int j = 0; j < n; j++) {
            if (used[j] || p[j].arrival_time > time) continue;
            if (best == -1 || p[j].burst_time < p[best].burst_time ||
                (p[j].burst_time == p[best].burst_time && p[j].arrival_time < p[best].arrival_time) ||
                (p[j].burst_time == p[best].burst_time && p[j].arrival_time == p[best].arrival_time && p[j].pid < p[best].pid))
                best = j;
        }
        if (best == -1) {
            int earliest = -1;
            for (int j = 0; j < n; j++)
                if (!used[j] && (earliest == -1 || p[j].arrival_time < earliest))
                    earliest = p[j].arrival_time;
            time = earliest;
            i--;
            continue;
        }
        used[best] = 1;
        starts[i] = time;
        p[best].waiting_time = time - p[best].arrival_time;
        p[best].response_time = p[best].waiting_time;
        time += p[best].burst_time;
        ends[i] = time;
        p[best].turnaround_time = time - p[best].arrival_time;
        order[i] = best;
    }
    print_results(p, order, starts, ends, n, "Shortest Job First (SJF)");
}

int main(void) {
    Process p[MAX];
    int n;
    printf("Enter number of processes (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of processes.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for P%d: ", p[i].pid);
        if (scanf("%d %d", &p[i].arrival_time, &p[i].burst_time) != 2 ||
            p[i].arrival_time < 0 || p[i].burst_time <= 0) {
            printf("Invalid input. Arrival must be >= 0 and burst must be > 0.\n");
            return 1;
        }
    }
    fcfs(p, n);
    sjf(p, n);
    return 0;
}
