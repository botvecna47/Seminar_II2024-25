// Name    : S. Darshdeep Singh Dutta
// Class   : SY_CSE_A
// Roll No.: 110
// Batch   : S1
// C Program to implement Round Robin Scheduling Algorithm

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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
    
    // Initialize
    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
        inQueue[i] = false;
    }
    
    // Add processes that arrive at time 0
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

        // Execute for time quantum or remaining time
        int execTime = processes[currentProcess].remainingTime < timeQuantum ? 
                      processes[currentProcess].remainingTime : timeQuantum;
        
        processes[currentProcess].remainingTime -= execTime;
        currentTime += execTime;

        // Check for new arrivals during execution
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                readyQueue[++rear] = i;
                inQueue[i] = true;
            }
        }

        if (processes[currentProcess].remainingTime > 0) {
            readyQueue[++rear] = currentProcess; // Re-add to queue
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
    int n, choice;
    printf("Enter 1 for Manual Input, 2 for Random Generation: ");
    scanf("%d", &choice);
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    printf("Enter Time Quantum (TQ) for scheduling: ");
    int timeQuantum;
    scanf("%d", &timeQuantum);

    struct Process process[n];
    srand(time(0));

    switch (choice) {
        case 1:
            for (int i = 0; i < n; i++) {
                process[i].pid = i + 1;
                printf("Enter values for Process %d\n", process[i].pid);
                printf("Arrival Time: ");
                scanf("%d", &process[i].arrivalTime);
                printf("Burst Time: ");
                scanf("%d", &process[i].burstTime);
            }
            break;

        case 2:
            for (int i = 0; i < n; i++) {
                process[i].pid = i + 1;
                if (i == 0) {
                    process[i].arrivalTime = 0;
                } else {
                    process[i].arrivalTime = rand() % (n + 3);
                }
                int randPercent = rand() % 100;
                if (randPercent < 70) {
                    process[i].burstTime = (rand() % 5) + 7;
                } else {
                    process[i].burstTime = (rand() % 5) + 2;
                }
            }
            break;

        default:
            printf("Invalid Choice. Exiting!\n");
            return 1;
    }

    roundRobinScheduling(process, n, timeQuantum);

    printf("\nProcess   A.T.  B.T.  C.T.  T.A.T.  W.T.\n");
    for (int i = 0; i < n; i++) {
        printf("%-10d%-6d%-6d%-6d%-8d%d\n", 
               process[i].pid, 
               process[i].arrivalTime, 
               process[i].burstTime,
               process[i].completionTime, 
               process[i].turnAroundTime, 
               process[i].waitingTime);
    }
    
    printf("Average Turnaround Time: %.2f ms\n", avgTAT(process, n));
    printf("Average Waiting Time: %.2f ms\n", avgWT(process, n));

    return 0;
}