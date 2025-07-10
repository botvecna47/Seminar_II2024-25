// Name    : S. Darshdeep Singh Dutta
// Class   : SY CSE A
// Roll No.: 110
// Batch   : S1

// C program to implement Shortest Job First (SJF) Scheduling Algorithm

#include <stdio.h>
#include <stdbool.h>

struct Process {
    int process;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
};

// Function to calculate average Turnaround Time
float avgTAT(struct Process process[], int n) {
    int totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalTAT += process[i].turnAroundTime;
    }
    return (float)totalTAT / n;
}

// Function to calculate average Waiting Time
float avgWT(struct Process process[], int n) {
    int totalWT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += process[i].waitingTime;
    }
    return (float)totalWT / n;
}

// SJF Scheduling Function
void sjfScheduling(struct Process process[], int n) {
    int currentTime = 0, completed = 0;
    bool isCompleted[n];
    for (int i = 0; i < n; i++) {
        isCompleted[i] = false;
    }

    while (completed < n) {
        int shortestIndex = -1;
        int shortestBurst = 1e9; // A large value to find the minimum burst time

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && process[i].arrivalTime <= currentTime && process[i].burstTime < shortestBurst) {
                shortestBurst = process[i].burstTime;
                shortestIndex = i;
            }
        }

        if (shortestIndex == -1) {
            // If no process has arrived yet, move the current time forward
            currentTime++;
        } else {
            // Process the selected shortest job
            process[shortestIndex].completionTime = currentTime + process[shortestIndex].burstTime;
            process[shortestIndex].turnAroundTime = process[shortestIndex].completionTime - process[shortestIndex].arrivalTime;
            process[shortestIndex].waitingTime = process[shortestIndex].turnAroundTime - process[shortestIndex].burstTime;

            currentTime = process[shortestIndex].completionTime;
            isCompleted[shortestIndex] = true;
            completed++;
        }
    }
}

int main() {
    int n;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    struct Process process[n];

    for (int i = 0; i < n; i++) {
        process[i].process = i + 1;
        printf("Enter values for Process %d\n", process[i].process);
        printf("Arrival Time: ");
        scanf("%d", &process[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &process[i].burstTime);
    }

    // Perform SJF scheduling
    sjfScheduling(process, n);

    // Print results
    printf("\nProcess   A.T.  B.T.  C.T.  T.A.T.  W.T.\n");
    for (int i = 0; i < n; i++) {
        printf("%-10d%-6d%-6d%-6d%-8d%d\n", process[i].process, process[i].arrivalTime, process[i].burstTime, process[i].completionTime, process[i].turnAroundTime, process[i].waitingTime);
    }

    printf("Average Turnaround Time: %.2f ms\n", avgTAT(process, n));
    printf("Average Waiting Time: %.2f ms\n", avgWT(process, n));

    return 0;
}

/*
OUTPUT:asmC:\Users\MGM\Desktop\110_Darshdeep>a.exe
Enter Number of Processes: 5
Enter values for Process 1
Arrival Time: 0
Burst Time: 3
Enter values for Process 2
Arrival Time: 2
Burst Time: 2
Enter values for Process 3
Arrival Time: 6
Burst Time: 5
Enter values for Process 4
Arrival Time: 5
Burst Time: 8
Enter values for Process 5
Arrival Time: 9
Burst Time: 2

Process   A.T.  B.T.  C.T.  T.A.T.  W.T.
1         0     3     3     3       0
2         2     2     5     3       1
3         6     5     20    14      9
4         5     8     13    8       0
5         9     2     15    6       4
Average Turnaround Time: 6.80 ms
Average Waiting Time: 2.80 ms
*/