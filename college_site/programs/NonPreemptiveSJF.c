// C program to implement Non Preemptive Shortest Job First (SJF) CPU Scheduling Algorithm
#include<stdio.h>
#include<stdbool.h>

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
float average_waiting_time(struct Process process[], int no_of_processes) {
    int sum = 0;
    for (int i = 0; i < no_of_processes; i++) {
        sum += process[i].waiting_time;
    }
    return (float)sum / no_of_processes;
}

// Function to calculate average turn around time
float average_turn_around_time(struct Process process[], int no_of_processes) {
    int sum = 0;
    for(int i = 0; i < no_of_processes; i++) {
        sum += process[i].turn_around_time;
    }
    return (float)sum / no_of_processes;
}

// Function to schedule the process according to SJF Scheduling algorithm
// Function to schedule the process according to SJF Scheduling algorithm
void shortest_job_first_algo(struct Process process[], int no_of_processes) {
    // To start scheduling form 0ms time!
    int current_time = 0;
    int completed_process = 0;                  // To track of number of processes completed, and not to go out of bonds
    bool is_Completed[no_of_processes];         // To check if the process is already executed, and not to reschedule despite the short burst time
    
    for(int i = 0; i < no_of_processes; i++) {
        is_Completed[i] = false;
    }

    while(completed_process < no_of_processes) {
        int shortest_burst = 1e9;               // Initialize shortest burst time to a large number, so that it will compare all the burst time, and not skip any
        int shortest_burst_index = -1;          // Store the index value of shorter burst time, for scheduling
        
        // Find the shortest available job
        for(int i = 0; i < no_of_processes; i++) {  
            // Check for process is completed, has arrived and has shortest burst time form all the processes that are not executed
            if(!is_Completed[i] && process[i].arrival_time <= current_time && process[i].burst_time < shortest_burst) {
                shortest_burst = process[i].burst_time;
                shortest_burst_index = i;
            }
        }

        if(shortest_burst_index == -1) {
            // If no process available, find the next arriving process
            int next_arrival = 1e9;
            for(int i = 0; i < no_of_processes; i++) {
                if(!is_Completed[i] && process[i].arrival_time < next_arrival) {
                    next_arrival = process[i].arrival_time;
                }
            }
            current_time = next_arrival;
        }
        else {
            // Scheduling The Process with shortest burst time
            process[shortest_burst_index].completion_time = current_time + process[shortest_burst_index].burst_time;                  // Used it in place of Gantt Chart, for easy calculation, and beginner friendly          
            process[shortest_burst_index].turn_around_time = process[shortest_burst_index].completion_time - process[shortest_burst_index].arrival_time; // TAT = CT  - AT
            process[shortest_burst_index].waiting_time = process[shortest_burst_index].turn_around_time - process[shortest_burst_index].burst_time;      // WT  = TAT - BT
            current_time = process[shortest_burst_index].completion_time;                                          // Updated to keep track of the arrival of next process
            is_Completed[shortest_burst_index] = true;
            completed_process++;
        }
    }
}

// Function to print Gantt Chart
void print_gantt_chart(struct Process process[], int size) {
    // First sort processes by completion time for Gantt chart
    for(int i = 0; i < size-1; i++) {
        for(int j = 0; j < size-i-1; j++) {
            if(process[j].completion_time > process[j+1].completion_time) {
                struct Process temp = process[j];
                process[j] = process[j+1];
                process[j+1] = temp;
            }
        }
    }

    printf("\nGantt Chart:\n");
    
    int current_time = 0;
    int i = 0;
    
    // Print top process bars
    printf("|");
    while(i < size) {
        if(current_time < process[i].arrival_time) {
            printf(" -- |");
            current_time = process[i].arrival_time;
        }
        else {
            printf(" P%d |", process[i].pid);
            current_time += process[i].burst_time;
            i++;
        }
    }
    
    // Print timeline
    printf("\n");
    current_time = 0;
    i = 0;
    printf("%-5d", current_time);
    
    while(i < size) {
        if(current_time < process[i].arrival_time) {
            printf("%-5d", process[i].arrival_time);
            current_time = process[i].arrival_time;
        }
        else {
            printf("%-5d", current_time + process[i].burst_time);
            current_time += process[i].burst_time;
            i++;
        }
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
    shortest_job_first_algo(process, no_of_processes);
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
    printf("Average Turnaround Time: %.2f ms\n", average_waiting_time(process, no_of_processes));
    printf("Average Waiting Time: %.2f ms\n", average_turn_around_time(process, no_of_processes));
    return 0;
}