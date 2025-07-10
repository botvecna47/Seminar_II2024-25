// Name    : S. Darshdeep Singh Dutta
// Class   : SY CSE A
// Roll No.: 110
// Batch   : S1

// C program to implement First Comes First Serve (FCFS) Scheduling Algorithm
// Here CPU can be IDLE

#include<stdio.h>

struct Process {
    int process;
    int arrivalTime;
    int completionTime;
    int burstTime;
    int turnAroundTime;
    int waitingTime;
};

float avgTAT(struct Process process[], int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += process[i].turnAroundTime; 
    }
    return (float)sum / n;
}

float avgWT(struct Process process[], int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += process[i].waitingTime; 
    }
    return (float)sum / n;
}

void calculate(struct Process process[], int n) { 
    int initialTime = 0;
    for (int i = 0; i < n; i++) {  
        if (initialTime < process[i].arrivalTime) {
            initialTime = process[i].arrivalTime;
        }
        process[i].completionTime = initialTime + process[i].burstTime;  
        process[i].turnAroundTime = process[i].completionTime - process[i].arrivalTime; 
        process[i].waitingTime = process[i].turnAroundTime - process[i].burstTime;  
        initialTime = process[i].completionTime;
    }
}

// Used Insertion sort for sorting 
void sort(struct Process process[],int n) {
    for (int i = 1; i < n; i++) {
        struct Process key = process[i];
        int j = i - 1;
        while (j >= 0 && process[j].arrivalTime > key.arrivalTime) {
            process[j + 1] = process[j];
            j--;
        }process[j + 1] = key;
    }
}

int main() {
    int n;      
    printf("Enter Number of process to be Scheduled : ");
    scanf("%d", &n);

    struct Process process[n];

    for(int i = 0; i < n; i++) {
        process[i].process = i+1;
        printf("Enter for Process %d\n", process[i].process);
        printf("Arrival Time : ");
        scanf("%d", &process[i].arrivalTime);
        printf("Burst Time : ");
        scanf("%d", &process[i].burstTime);
    }

    sort(process, n);

    calculate(process, n);

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
Enter Number of process to be Scheduled : 4
Enter for Process 1
Arrival Time : 0
Burst Time : 2
Enter for Process 2
Arrival Time : 1
Burst Time : 2
Enter for Process 3
Arrival Time : 5
Burst Time : 4
Enter for Process 4
Arrival Time : 6
Burst Time : 3

Process   A.T.  B.T.  C.T.  T.A.T.  W.T.
1         0     2     2     2       0
2         1     2     4     3       1
3         5     4     9     4       0
4         6     3     12    6       3
Average Turnaround Time: 3.75 ms
Average Waiting Time: 1.00 ms


C:\Users\MGM\Desktop\110_Darshdeep>a.exe
Enter Number of process to be Scheduled : 5
Enter for Process 1
Arrival Time : 2
Burst Time : 2
Enter for Process 2
Arrival Time : 0
Burst Time : 1
Enter for Process 3
Arrival Time : 2
Burst Time : 3
Enter for Process 4
Arrival Time : 3
Burst Time : 5
Enter for Process 5
Arrival Time : 4
Burst Time : 4

Process   A.T.  B.T.  C.T.  T.A.T.  W.T.
2         0     1     1     1       0
1         2     2     4     2       0
3         2     3     7     5       2
4         3     5     12    9       4
5         4     4     16    12      8
Average Turnaround Time: 5.80 ms
Average Waiting Time: 2.80 ms

*/