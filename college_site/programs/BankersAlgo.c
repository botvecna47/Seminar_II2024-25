// Name    : S. Darshdeep Singh Dutta
// Class   : SY_CSE_A
// Roll No.: 110
// Batch   : S1
// Write a C program to implement the Banker's Algorithm for deadlock avoidance.
#include <stdio.h>
#include <stdbool.h>

#define MaxProcess 10
#define MaxResources 10

// Structure to hold all matrices and system state
struct SystemState {
    int process;
    int resource;
    int available[MaxResources];
    int need[MaxProcess][MaxResources];
    int max[MaxProcess][MaxResources];
    int alloc[MaxProcess][MaxResources];
};

// Gets the number of processes and resources from user
void inputSystemInfo(struct SystemState *system) {
    printf("Enter number of processes: ");
    scanf("%d", &system->process);
    
    printf("Enter number of resources: ");
    scanf("%d", &system->resource);
}

// Reads the allocation matrix from user input
void inputAllocationMatrix(struct SystemState *system) {
    printf("Enter allocation matrix (%d x %d):\n", system->process, system->resource);
    for(int i = 0; i < system->process; i++) {
        for(int j = 0; j < system->resource; j++) {
            scanf("%d", &system->alloc[i][j]);
        }
    }
}

// Reads the max matrix from user input
void inputMaxMatrix(struct SystemState *system) {
    printf("Enter max matrix (%d x %d):\n", system->process, system->resource);
    for(int i = 0; i < system->process; i++) {
        for(int j = 0; j < system->resource; j++) {
            scanf("%d", &system->max[i][j]);
        }
    }
}

// Reads available resources from user input
void inputAvailableResources(struct SystemState *system) {
    printf("Enter available resources (%d):\n", system->resource);
    for(int j = 0; j < system->resource; j++) {
        scanf("%d", &system->available[j]);
    }
}

// Calculates the need matrix (Need = Max - Allocation)
void computeNeedMatrix(struct SystemState *system) {
    for(int i = 0; i < system->process; i++) {
        for(int j = 0; j < system->resource; j++) {
            system->need[i][j] = system->max[i][j] - system->alloc[i][j];
        }
    }
}

// Checks if the system is in a safe state using the safety algorithm
bool checkSafeState(struct SystemState *system, int safeSeq[]) {
    int work[MaxResources];
    bool finish[MaxProcess] = {false};
    int count = 0;

    // Copy available resources to work array
    for(int j = 0; j < system->resource; j++) {
        work[j] = system->available[j];
    }

    // Keep looking for processes that can complete
    while(count < system->process) {
        bool found = false;
        
        // Check each process
        for(int i = 0; i < system->process; i++) {
            if(!finish[i]) {
                bool canAllocate = true;
                // Check if we have enough resources for this process
                for(int j = 0; j < system->resource; j++) {
                    if(system->need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                
                if(canAllocate) {
                    // Simulate resource allocation and release
                    for(int j = 0; j < system->resource; j++) {
                        work[j] += system->alloc[i][j];
                    }
                    
                    safeSeq[count] = i;
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }
        
        // If no process can be allocated resources, we're stuck
        if(!found) {
            break;
        }
    }
    
    // If we completed all processes, we're safe!
    return count == system->process;
}

// Displays which process is allocated which resources and how many instances
void displayResourceAllocation(struct SystemState *system) {
    printf("\nSystem State:\n");
    printf("Available : ");
    for(int j = 0; j < system->resource; j++) {
        printf(" %3d", system->available[j]);
    }
    printf("\n");
    
    // Print header row
    printf("Process |");
    for(int j = 0; j < system->resource; j++) {
        printf(" Alloc R%d |", j);
    }
    for(int j = 0; j < system->resource; j++) {
        printf(" Max R%-3d |", j);
    }
    for(int j = 0; j < system->resource; j++) {
        printf(" Need R%-2d |", j);
    }
    printf("\n");
    
    printf("--------|");
    for(int j = 0; j < system->resource * 3; j++) {
        printf("----------|");
    }
    printf("\n");
    
    for(int i = 0; i < system->process; i++) {
        printf("P%-6d |", i);
        for(int j = 0; j < system->resource; j++) {
            printf(" %8d |", system->alloc[i][j]);
        }
        for(int j = 0; j < system->resource; j++) {
            printf(" %8d |", system->max[i][j]);
        }
        for(int j = 0; j < system->resource; j++) {
            printf(" %8d |", system->need[i][j]);
        }
        printf("\n");
    }
    printf("--------|");
    for(int j = 0; j < system->resource * 3; j++) {
        printf("----------|");
    }
    printf("\n");
}

// Prints the safe sequence if system is in safe state
void displaySafeSequence(struct SystemState *system, int safeSeq[]) {
    if(checkSafeState(system, safeSeq)) {
        printf("System is in safe state.\nSafe sequence is: ");
        for(int i = 0; i < system->process; i++) {
            printf("P%d", safeSeq[i]);
            if(i != system->process-1) {
                printf(" -> ");
            }
        }
        printf("\n");
    } else {
        printf("System is not in safe state (deadlock possible).\n");
    }
}

// Handles resource request algorithm
void processResourceRequest(struct SystemState *system) {
    printf("\nDo you want to make a resource request? (1 for Yes, 0 for No): ");
    int choice;
    scanf("%d", &choice);
    
    if(choice != 1) return;

    int processNum;
    printf("Enter process number making the request: ");
    scanf("%d", &processNum);
    
    int request[MaxResources];
    printf("Enter request vector (%d resources): ", system->resource);
    for(int j = 0; j < system->resource; j++) {
        scanf("%d", &request[j]);
    }
    
    // Check if request is valid
    bool valid = true;
    for(int j = 0; j < system->resource; j++) {
        if(request[j] > system->need[processNum][j]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            valid = false;
            break;
        }
        if(request[j] > system->available[j]) {
            printf("Error: Not enough resources available.\n");
            valid = false;
            break;
        }
    }
    
    if(valid) {
        // Temporarily allocate resources
        for(int j = 0; j < system->resource; j++) {
            system->available[j] -= request[j];
            system->alloc[processNum][j] += request[j];
            system->need[processNum][j] -= request[j];
        }
        
        // Check if new state is safe
        int tempSeq[MaxProcess];
        if(checkSafeState(system, tempSeq)) {
            printf("Request granted. System remains in safe state.\n");
        } else {
            printf("Request cannot be granted as it leads to unsafe state.\n");
            // Revert changes
            for(int j = 0; j < system->resource; j++) {
                system->available[j] += request[j];
                system->alloc[processNum][j] -= request[j];
                system->need[processNum][j] += request[j];
            }
        }
    }
}

int main() {
    struct SystemState system;
    int safeSeq[MaxProcess];
    
    // Get system information and matrices
    inputSystemInfo(&system);

    // Read the allocation matrix
    inputAllocationMatrix(&system);
    
    // Read the max matrix
    inputMaxMatrix(&system);
    
    // Initialize available resources
    inputAvailableResources(&system);
    
    // Compute the need matrix
    computeNeedMatrix(&system);
    
    // Display current resource allocation
    displayResourceAllocation(&system);

    // Check and display if system is in safe state
    displaySafeSequence(&system, safeSeq);
    
    // Handle any resource requests
    processResourceRequest(&system);
    
    return 0;
}
// OUTPUT:
// C:\Users\Darshdeep\Desktop\Code\OS>gcc BankersAlgo.c

// C:\Users\Darshdeep\Desktop\Code\OS>a.exe
// Enter number of processes: 3
// Enter number of resources: 3
// Enter allocation matrix (3 x 3):
// 1 2 1
// 0 2 0
// 1 1 1
// Enter max matrix (3 x 3):
// 3 3 3
// 4 4 4
// 2 2 2
// Enter available resources (3):
// 4 5 6

// System State:
// Available :    4   5   6
// Process | Alloc R0 | Alloc R1 | Alloc R2 | Max R0   | Max R1   | Max R2   | Need R0  | Need R1  | Need R2  |
// --------|----------|----------|----------|----------|----------|----------|----------|----------|----------|
// P0      |        1 |        2 |        1 |        3 |        3 |        3 |        2 |        1 |        2 |
// P1      |        0 |        2 |        0 |        4 |        4 |        4 |        4 |        2 |        4 |
// P2      |        1 |        1 |        1 |        2 |        2 |        2 |        1 |        1 |        1 |
// --------|----------|----------|----------|----------|----------|----------|----------|----------|----------|
// System is in safe state.
// Safe sequence is: P0 -> P1 -> P2

// Do you want to make a resource request? (1 for Yes, 0 for No): 1
// Enter process number making the request: 2
// Enter request vector (3 resources): 0 2 0
// Error: Process has exceeded its maximum claim.