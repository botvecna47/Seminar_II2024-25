// Name    : S. Darshdeep Singh Dutta
// Class   : SY_CSE_A
// Roll No.: 110
// Batch   : S1
// Program : Producer-Consumer Problem using Semaphores

#include <stdio.h>

void consume();
#define SIZE 10  // Buffer size

int buffer[SIZE];
int in = 0;      // Producer index
int out = 0;     // Consumer index
int count = 0;   // Current items in buffer

// Semaphore simulation
int mutex = 1;    // Mutual exclusion
int empty = SIZE; // Empty slots
int full = 0;     // Full slots

void wait(int *sem) {
    while(*sem <= 0);  // Busy wait
    (*sem)--;
}

void signal(int *sem) {
    (*sem)++;
}

void produce() {
    if(empty <= 0) {
        printf("\nBuffer FULL! Options:\n");
        printf("1. Consume items first\n2. Cancel production\n");
        printf("Your choice: ");
        int choice;
        scanf("%d", &choice);
        if(choice == 1) {
            consume();
            produce(); // Retry production
        }
        return;
    }

    wait(&empty);
    wait(&mutex);
    
    int item = count + 1;  // Generate sequential item number
    buffer[in] = item;
    printf("Produced item %d at position %d ", item, in);
    in = (in + 1) % SIZE;
    count++;
    
    signal(&mutex);
    signal(&full);
}

void consume() {
    if(full <= 0) {
        printf("\nBuffer EMPTY! Options:\n");
        printf("1. Produce items first\n2. Cancel consumption\n");
        printf("Your choice: ");
        int choice;
        scanf("%d", &choice);
        if(choice == 1) {
            produce();
            consume(); // Retry consumption
        }
        return;
    }
    
    wait(&full);
    wait(&mutex);
    
    int item = buffer[out];
    printf("Consumed item %d from position %d ", item, out);
    buffer[out] = 0;  // Clear the consumed slot
    out = (out + 1) % SIZE;
    count--;
    
    signal(&mutex);
    signal(&empty);
}

void display_buffer() {
    printf("\nCurrent Buffer Contents:\n");
    printf("[");
    for(int i = 0; i < SIZE; i++) {
        if(buffer[i] == 0)
            printf("_");  // Show empty slots
        else
            printf("%d", buffer[i]);
        
        if(i < SIZE-1) printf(", ");
    }
    printf("]\n");
    
    printf("Slots: %d full, %d empty\n", full, empty);
    printf("Next production at: %d, Next consumption at: %d\n", in, out);
}

int main() {
    // Initialize buffer to 0 (empty)
    for(int i = 0; i < SIZE; i++) {
        buffer[i] = 0;
    }
    
    while(1) {
        printf("\nMenu:\n");
        printf("1. Produce Item\n");
        printf("2. Consume Item\n");
        printf("3. View Buffer\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        switch(choice) {
            case 1: produce(); break;
            case 2: consume(); break;
            case 3: display_buffer(); break;
            case 4: return 0;
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}
// OUTPUT:
// C:\Users\Darshdeep\Desktop\Code\OS>gcc ProducerConsumer.c
// C:\Users\Darshdeep\Desktop\Code\OS>a.exe
// Menu:
// 1. Produce Item
// 2. Consume Item
// 3. View Buffer
// 4. Exit
// Enter your choice: 2

// Buffer EMPTY! Options:
// 1. Produce items first
// 2. Cancel consumption
// Your choice: 1
// Produced item 1 at position 0 Consumed item 1 from position 0
// Menu:
// 1. Produce Item
// 2. Consume Item
// 3. View Buffer
// 4. Exit
// Enter your choice: 3

// Current Buffer Contents:
// [_, _, _, _, _, _, _, _, _, _]
// Slots: 0 full, 10 empty
// Next production at: 1, Next consumption at: 1

// Menu:
// 1. Produce Item
// 2. Consume Item
// 3. View Buffer
// 4. Exit
// Enter your choice: 1
// Produced item 1 at position 1
// Menu:
// 1. Produce Item
// 2. Consume Item
// 3. View Buffer
// 4. Exit
// Enter your choice: 1
// Produced item 2 at position 2
// Menu:
// 1. Produce Item
// 2. Consume Item
// 3. View Buffer
// 4. Exit
// Enter your choice: 1
// Produced item 3 at position 3
// Menu:
// 1. Produce Item
// 2. Consume Item
// 3. View Buffer
// 4. Exit
// Enter your choice: 1
// Produced item 4 at position 4
// Menu:
// 1. Produce Item
// 2. Consume Item
// 3. View Buffer
// 4. Exit
// Enter your choice: 1
// Produced item 5 at position 5
// Menu:
// 1. Produce Item
// 2. Consume Item
// 3. View Buffer
// 4. Exit
// Enter your choice: 11
// Invalid choice! Please try again.

// Menu:
// 1. Produce Item
// 2. Consume Item
// 3. View Buffer
// 4. Exit
// Enter your choice: 1
// Produced item 6 at position 6
// Menu:
// 1. Produce Item
// 2. Consume Item
// 3. View Buffer
// 4. Exit
// Enter your choice: 3

// Current Buffer Contents:
// [_, 1, 2, 3, 4, 5, 6, _, _, _]
// Slots: 6 full, 4 empty
// Next production at: 7, Next consumption at: 1

// Menu:
// 1. Produce Item
// 2. Consume Item
// 3. View Buffer
// 4. Exit
// Enter your choice: 2
// Consumed item 1 from position 1
// Menu:
// 1. Produce Item
// 2. Consume Item
// 3. View Buffer
// 4. Exit
// Enter your choice: 3

// Current Buffer Contents:
// [_, _, 2, 3, 4, 5, 6, _, _, _]
// Slots: 5 full, 5 empty
// Next production at: 7, Next consumption at: 2

// Menu:
// 1. Produce Item
// 2. Consume Item
// 3. View Buffer
// 4. Exit
// Enter your choice: 4