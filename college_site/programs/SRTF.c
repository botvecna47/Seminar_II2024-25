// Name    : S. Darshdeep Singh Dutta
// Class   : SY CSE A
// Roll No.: 110
// Batch   : S1

// C program to implement Preemptive SJF or Shortest Response Time First (SRTF) Scheduling Algorithm

#include <stdio.h>
#include <stdbool.h>

struct Process {
    int process;
    int arrivalTime;
    int burstTime;
    int remainingTime;  // Track remaining burst time
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int priority;
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
void SRTF_Scheduling(struct Process process[], int n) {
    int currentTime = 0;
    int completed = 0;
    
    // Initialize remaining time
    for (int i = 0; i < n; i++) {
        process[i].remainingTime = process[i].burstTime;
    }
    
    while (completed < n) {
        int shortestIndex = -1;
        int shortestRemaining = 1e9;
        
        // Find process with shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (process[i].arrivalTime <= currentTime && 
                process[i].remainingTime > 0 && 
                process[i].remainingTime < shortestRemaining) {
                shortestRemaining = process[i].remainingTime;
                shortestIndex = i;
            }
        }
        
        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }
        
        // Execute the process for 1 time unit
        process[shortestIndex].remainingTime--;
        currentTime++;
        
        // Check if process completed
        if (process[shortestIndex].remainingTime == 0) {
            completed++;
            process[shortestIndex].completionTime = currentTime;
            process[shortestIndex].turnAroundTime = 
                process[shortestIndex].completionTime - 
                process[shortestIndex].arrivalTime;
            process[shortestIndex].waitingTime = 
                process[shortestIndex].turnAroundTime - 
                process[shortestIndex].burstTime;
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
    SRTF_Scheduling(process, n);

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
OUTPUT:
C:\Users\MGM\Desktop\110_Darshdeep>a.exe
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
3         6     5     11    5       0
4         5     8     20    15      7
5         9     2     13    4       2
Average Turnaround Time: 6.00 ms
Average Waiting Time: 2.00 ms
*/