// Name    : S. Darshdeep Singh Dutta
// Class   : SY CSE A
// Roll No.: 110
// Batch   : S1

// C program to implement Preemptive Priority Scheduling Algorithm 

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

// Preemptive Priority Scheduling Function
void preemptivePriorityScheduling(struct Process process[], int n) {
    int currentTime = 0;
    int completed = 0;
    
    // Initialize remaining time
    for (int i = 0; i < n; i++) {
        process[i].remainingTime = process[i].burstTime;
    }
    
    while (completed < n) {
        int highestPriorityIndex = -1;
        int highestPriority = 1e9; // Initialize with a large number (lower number = higher priority)
        
        // Find the highest priority process that has arrived and has remaining time
        for (int i = 0; i < n; i++) {
            if (process[i].arrivalTime <= currentTime && 
                process[i].remainingTime > 0 && process[i].priority < highestPriority) {
                highestPriority = process[i].priority;
                highestPriorityIndex = i;
            }
        }
        
        if (highestPriorityIndex == -1) {
            currentTime++;
            continue;
        }
        
        // Execute the process for 1 unit of time
        process[highestPriorityIndex].remainingTime--;
        currentTime++;
        
        // If process completed
        if (process[highestPriorityIndex].remainingTime == 0) {
            completed++;
            process[highestPriorityIndex].completionTime = currentTime;
            process[highestPriorityIndex].turnAroundTime = 
                process[highestPriorityIndex].completionTime - process[highestPriorityIndex].arrivalTime;
            process[highestPriorityIndex].waitingTime = 
                process[highestPriorityIndex].turnAroundTime - process[highestPriorityIndex].burstTime;
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
        printf("Priority (Lower number = higher priority): ");
        scanf("%d", &process[i].priority);
    }

    // Perform Preemptive Priority scheduling
    preemptivePriorityScheduling(process, n);

    // Print results
    printf("\nProcess   A.T.  B.T.  Priority  C.T.  T.A.T.  W.T.\n");
    for (int i = 0; i < n; i++) {
        printf("%-10d%-6d%-6d%-10d%-6d%-8d%d\n", 
               process[i].process, 
               process[i].arrivalTime, 
               process[i].burstTime,
               process[i].priority, 
               process[i].completionTime, 
               process[i].turnAroundTime, 
               process[i].waitingTime);
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
Burst Time: 8
Priority (Lower number = higher priority): 3
Enter values for Process 2
Arrival Time: 1
Burst Time: 1
Priority (Lower number = higher priority): 1
Enter values for Process 3
Arrival Time: 2
Burst Time: 3
Priority (Lower number = higher priority): 2
Enter values for Process 4
Arrival Time: 3
Burst Time: 2
Priority (Lower number = higher priority): 3
Enter values for Process 5
Arrival Time: 4
Burst Time: 6
Priority (Lower number = higher priority): 4

Process   A.T.  B.T.  Priority  C.T.  T.A.T.  W.T.
1         0     8     3         12    12      4
2         1     1     1         2     1       0
3         2     3     2         5     3       0
4         3     2     3         14    11      9
5         4     6     4         20    16      10
Average Turnaround Time: 8.60 ms
Average Waiting Time: 4.60 ms
*/