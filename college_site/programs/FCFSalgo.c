// C program to implement First Come First Serve (FCFS) CPU Scheduling Algorithm : 
#include<stdio.h>

// Structure to store all the parameters of a process
struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
};

// Function to calculate average waiting time
float average_waiting_time(struct Process process[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += process[i].waiting_time;
    }
    return (float)sum / size;
}

// Function to calculate average turn around time
float average_turn_around_time(struct Process process[], int size) {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        sum += process[i].turn_around_time;
    }
    return (float)sum / size;
}

// Function to calculate all the parameters of a process and schedule the process according to FCFS
void first_come_first_server_algo (struct Process process[], int size) {
    // For simplicity, used Insertion sort first, to arrange all the processes based on Arrival Time, first arrived is scheduled first, and last one last!
    // Can directly sort and schedule, without using a second loop, so it will be efficient
    for (int i = 1; i < size; i++) {
        struct Process key = process[i];
        int j = i - 1;
        while (j >= 0 && process[j].arrival_time > key.arrival_time) {
            process[j + 1] = process[j--];
        }process[j + 1] = key;
    }
    // To start scheduling from 0 ms time!
    int current_time = 0;
    for(int i = 0; i < size ; i++) {
        // Handles the case where CPU is IDLE, so skips to time where a process arrives
        if (current_time < process[i].arrival_time) {
            current_time = process[i].arrival_time;
        }
        // Scheduling The Process, after sorting the processes based on arrival time
        process[i].completion_time = current_time + process[i].burst_time;                  // Used it in place of Gantt Chart, for easy calculation, and beginner friendly          
        process[i].turn_around_time = process[i].completion_time - process[i].arrival_time; // TAT = CT  - AT
        process[i].waiting_time = process[i].turn_around_time - process[i].burst_time;      // WT  = TAT - BT
        current_time = process[i].completion_time;                                          // Updated to keep track of the arrival of next process
    }
}
// Function to print Gantt Chart
void print_gantt_chart(struct Process process[], int size) {
    printf("\nGantt Chart:\n");
    
    int current_time = 0;
    
    for(int i = 0; i < size; i++) {
        // Check for idle time between processes
        if (current_time < process[i].arrival_time) {
            printf("| -- ", process[i].arrival_time);
            current_time = process[i].arrival_time;
        }
        
        printf("| P%d ", process[i].pid);
        current_time += process[i].burst_time;
    }
    printf("|\n");
    
    // Print timeline
    current_time = 0;
    printf("0    ");
    for(int i = 0; i < size; i++) {
        // Handle idle time in timeline
        if (current_time < process[i].arrival_time) {
            printf("%-5d", process[i].arrival_time);
            current_time = process[i].arrival_time;
        }
        
        printf("%-5d", current_time + process[i].burst_time);
        current_time += process[i].burst_time;
    }
    printf("\n");
}
int main() {
    int no_of_processes;
    printf("Enter number of processes to schedule : ");
    scanf("%d", &no_of_processes);
    printf("Enter values of all processes : \n");
    struct Process process[no_of_processes];
    // Take Input for all processes form user:
    for(int i = 0; i < no_of_processes; i++) {
        process[i]. pid = i + 1;
        printf("Arrival Time : ");
        scanf("%d", &process[i].arrival_time);
        printf("Burst Time   : ");
        scanf("%d", &process[i].burst_time);
    }
    first_come_first_server_algo(process, no_of_processes);
    // Print results in tabular form
    printf("\nProcess   A.T.  B.T.  C.T.  T.A.T.  W.T.\n");
    for (int i = 0; i < no_of_processes; i++) {
        printf("P%-9d%-6d%-6d%-6d%-8d%d\n",
                process[i].pid, 
                process[i].arrival_time,
                process[i].burst_time, 
                process[i].completion_time,
                process[i].turn_around_time, 
                process[i].waiting_time);
    }
    print_gantt_chart(process, no_of_processes);
    printf("Average Turnaround Time: %.2f ms\n", average_turn_around_time(process, no_of_processes));
    printf("Average Waiting Time: %.2f ms\n", average_waiting_time(process, no_of_processes));
    return 0;
}