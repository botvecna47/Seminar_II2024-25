// Name    : S. Darshdeep Singh Dutta
// Class   : SY CSE A
// Roll No.: 110
// Batch   : S1

// C program to implement Priority Scheduling Algorithm 

#include <stdio.h>
#include <stdbool.h>

struct Process {
    int process;
    int arrivalTime;
    int burstTime;
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

// Priority Scheduling Function
void priorityScheduling(struct Process process[], int n) {
    int currentTime = 0, completed = 0;
    bool isCompleted[n];
    for (int i = 0; i < n; i++) {
        isCompleted[i] = false;
    }
    // Sort and calculate based on both Arrival Time and Priority
    while (completed < n) {
        int highestPriorityIndex = -1;
        int highestPriority = 1e9; // Initialize with a large number (lower number = higher priority)

        // Find the process with highest priority (lowest priority number) that has arrived
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && process[i].arrivalTime <= currentTime && 
                process[i].priority < highestPriority) {
                highestPriority = process[i].priority;
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex == -1) {
            currentTime++; // No process available, increment time i.e. Idle CPU
        } else {
            // Execute the process and calculate the parameters!!
            process[highestPriorityIndex].completionTime = currentTime + process[highestPriorityIndex].burstTime;
            process[highestPriorityIndex].turnAroundTime = process[highestPriorityIndex].completionTime - process[highestPriorityIndex].arrivalTime;
            process[highestPriorityIndex].waitingTime = process[highestPriorityIndex].turnAroundTime - process[highestPriorityIndex].burstTime;

            currentTime = process[highestPriorityIndex].completionTime;
            isCompleted[highestPriorityIndex] = true;
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
        printf("Priority(Highest Number, lowest priority): ");
        scanf("%d", &process[i].priority);
    }

    // Perform Priority scheduling
    priorityScheduling(process, n);

    // Print results
    printf("\nProcess   A.T.  B.T.  Priority  C.T.  T.A.T.  W.T.\n");
    for (int i = 0; i < n; i++) {
        printf("%-10d%-6d%-6d%-10d%-6d%-8d%d\n", process[i].process, process[i].arrivalTime, process[i].burstTime,process[i].priority, process[i].completionTime, process[i].turnAroundTime, process[i].waitingTime);
    }

    printf("Average Turnaround Time: %.2f ms\n", avgTAT(process, n));
    printf("Average Waiting Time: %.2f ms\n", avgWT(process, n));

    return 0;
}
/*
OUTPUT:
C:\Users\MGM\Desktop\110_Darshdeep>a.exe
Enter Number of Processes: 4
Enter values for Process 1
Arrival Time: 0
Burst Time: 6
Priority(Highest Number, lowest priority): 3
Enter values for Process 2
Arrival Time: 3
Burst Time: 5
Priority(Highest Number, lowest priority): 4
Enter values for Process 3
Arrival Time: 3
Burst Time: 3
Priority(Highest Number, lowest priority): 1
Enter values for Process 4
Arrival Time: 5
Burst Time: 5
Priority(Highest Number, lowest priority): 2

Process   A.T.  B.T.  Priority  C.T.  T.A.T.  W.T.
1         0     6     3         6     6       0
2         3     5     4         19    16      11
3         3     3     1         9     6       3
4         5     5     2         14    9       4
Average Turnaround Time: 9.25 ms
Average Waiting Time: 4.50 ms
*/