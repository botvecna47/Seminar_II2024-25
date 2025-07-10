// All types of Algorithm in one program

#include<stdio.h>
#include<stdbool.h>             // For use of Boolean Values True or False for various algorithms

// Structure to store all the parameters of a process for all CPU scheduling
struct Process {
    int pid;                    // Process ID
    int arrival_time;           // Process Arrival Time
    int completion_time;        // Process Completion Time
    int burst_time;             // Process CPU Burst Time (CPU Execution Time)
    int remaining_time;         // Remaining Time of process in case of preemption
    int turn_around_time;       // Process Turn Around Time
    int waiting_time;           // Process Waiting Time
    int response_time;          // Process Response Time
};

// Function to calculate Average Turn Around Time of a process
float average_turn_around_time(struct Process process[], int size) {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        sum += process[i].turn_around_time;
    }
    return (float)sum / size;
}

// Function to calculate Average Waiting Time of a process
float average_waiting_time(struct Process process[], int size) {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        sum += process[i].waiting_time;
    }
    return (float)sum / size;
}

// Function to schedule all the processes according To First Come First Serve (FCFS) CPU Scheduling Algorithm
void first_come_first_serve_scheduling(struct Process process[], int size) {
    // For simplicity, used Insertion sort first, to arrange all the processes based on Arrival Time, first arrived is scheduled first, and last one last!
    // Can directly sort and schedule, without using a second loop, so it will be efficient
    for (int i = 1; i < size; i++) {
        struct Process key = process[i];
        int j = i - 1;
        while (j >= 0 && process[j].arrival_time > key.arrival_time) {
            process[j + 1] = process[j--];
        }process[j + 1] = key;
    }
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

void shortest_job_first_scheduling(struct Process process[], int size) {

}