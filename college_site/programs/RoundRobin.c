// Name    : S. Darshdeep Singh Dutta
// Class   : SY_CSE_A
// Roll No.: 110
// Batch   : S1
// C Program to implement Round Robin Scheduling Algorithm

#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;            // Process ID
    int arrivalTime;    // Arrival time
    int burstTime;      // Total execution time needed
    int remainingTime;  // Remaining execution time
    int completionTime; // Time when process completes
    int turnAroundTime; // Completion time - Arrival time
    int waitingTime;    // Turnaround time - Burst time
};

float avgTAT(struct Process process[], int n) {
    int totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalTAT += process[i].turnAroundTime;
    }
    return (float)totalTAT / n;
}

float avgWT(struct Process process[], int n) {
    int totalWT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += process[i].waitingTime;
    }
    return (float)totalWT / n;
}

void roundRobinScheduling(struct Process processes[], int n, int timeQuantum) {
    int currentTime = 0;
    int completed = 0;
    int readyQueue[n * 10]; // Large enough queue to prevent overflow
    int front = 0, rear = -1;
    bool inQueue[n];
    
    // Initialize remaining time with burst time
    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
        inQueue[i] = false;
    }
    
    // Add processes that arrive at time 0 (or first)
    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime <= currentTime) {
            readyQueue[++rear] = i;
            inQueue[i] = true;
        }
    }

    while (completed < n) {
        if (front > rear) { // Queue empty
            currentTime++;
            // Check for new arrivals
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                    readyQueue[++rear] = i;
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int currentProcess = readyQueue[front++];
        if (front > rear) { // Reset queue pointers if empty
            front = 0;
            rear = -1;
        }
        // Execute for time quantum or remaining time, whichever is smaller
        int execTime = processes[currentProcess].remainingTime < timeQuantum ? 
                      processes[currentProcess].remainingTime : timeQuantum;
        
        processes[currentProcess].remainingTime -= execTime;
        currentTime += execTime;

        // Check for new arrivals during execution, and add them for scheduling
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                readyQueue[++rear] = i;
                inQueue[i] = true;
            }
        }

        if (processes[currentProcess].remainingTime > 0) {
            readyQueue[++rear] = currentProcess; // Re-add current process to queue
        } else {
            completed++;
            inQueue[currentProcess] = false;
            processes[currentProcess].completionTime = currentTime;
            processes[currentProcess].turnAroundTime = currentTime - processes[currentProcess].arrivalTime;
            processes[currentProcess].waitingTime = processes[currentProcess].turnAroundTime - processes[currentProcess].burstTime;
        }
    }
}

int main() {
    int n, timeQuantum;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Process %d:\n", processes[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
    }

    roundRobinScheduling(processes, n, timeQuantum);

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               processes[i].turnAroundTime,
               processes[i].waitingTime);
    }

    printf("\nAverage Turnaround Time: %.2f\n", avgTAT(processes, n));
    printf("Average Waiting Time: %.2f\n", avgWT(processes, n));

    return 0;
}
// OUTPUT : 
// C:\Users\Darshdeep\Desktop\Code\OS>gcc RoundRobin.c
// C:\Users\Darshdeep\Desktop\Code\OS>a.exe
// Enter number of processes: 5
// Enter time quantum: 3
// Process 1
// Arrival Time: 0
// Burst Time: 8
// Process 2
// Arrival Time: 4
// Burst Time: 4
// Process 3
// Arrival Time: 1
// Burst Time: 7
// Process 4
// Arrival Time: 1
// Burst Time: 9
// Process 5
// Arrival Time: 6
// Burst Time: 7

// Process AT      BT      CT      TAT     WT
// P1      0       8       26      26      18
// P2      4       4       27      23      19
// P3      1       7       31      30      23
// P4      1       9       34      33      24
// P5      6       7       35      29      22

// Average Turnaround Time: 28.20
// Average Waiting Time: 21.20

// C:\Users\Darshdeep\Desktop\Code\OS>gcc RoundRobin.c
// C:\Users\Darshdeep\Desktop\Code\OS>a.exe
// Enter Number of Processes: 4
// Enter Time Quantum: 2
// Process 1:
// Arrival Time: 0
// Burst Time: 3
// Process 2:
// Arrival Time: 1
// Burst Time: 6
// Process 3:
// Arrival Time: 4
// Burst Time: 4
// Process 4:
// Arrival Time: 6
// Burst Time: 2

// Process AT      BT      CT      TAT     WT
// P1      0       3       5       5       2
// P2      1       6       15      14      8
// P3      4       4       13      9       5
// P4      6       2       11      5       3

// Average Turnaround Time: 8.25
// Average Waiting Time: 4.50