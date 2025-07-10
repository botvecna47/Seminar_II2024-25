// Name    : S. Darshdeep Singh Dutta
// Class   : SY_CSE_A
// Roll No.: 110
// Batch   : S1
// Program : Simple Producer-Consumer using Threads

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 10  // Buffer size

int buffer[SIZE];  // Shared buffer
int in = 0;       // Producer index
int out = 0;      // Consumer index
int count = 0;    // Items in buffer

// Synchronization variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex for buffer access
pthread_cond_t empty_cond = PTHREAD_COND_INITIALIZER; // Condition for empty slots
pthread_cond_t full_cond = PTHREAD_COND_INITIALIZER;  // Condition for full slots

// Producer thread: adds items to buffer
void* producer(void* arg) {
    int empty = SIZE;  // Tracks empty slots
    int full = 0;      // Tracks full slots
    while (1) {
        pthread_mutex_lock(&mutex);
        while (empty <= 0) {  // Wait if buffer is full
            pthread_cond_wait(&empty_cond, &mutex);
        }
        empty--;  // Decrease empty slots

        buffer[in] = count + 1;  // Add item
        printf("Produced item %d at position %d\n", buffer[in], in);
        in = (in + 1) % SIZE;
        count++;

        full++;  // Increase full slots
        pthread_cond_signal(&full_cond);  // Signal consumer
        pthread_mutex_unlock(&mutex);

        sleep(1);  // Simulate work
    }
    return NULL;
}

// Consumer thread: removes items from buffer
void* consumer(void* arg) {
    int empty = SIZE;  // Tracks empty slots
    int full = 0;      // Tracks full slots
    while (1) {
        pthread_mutex_lock(&mutex);
        while (full <= 0) {  // Wait if buffer is empty
            pthread_cond_wait(&full_cond, &mutex);
        }
        full--;  // Decrease full slots

        printf("Consumed item %d from position %d\n", buffer[out], out);
        buffer[out] = 0;  // Clear slot
        out = (out + 1) % SIZE;
        count--;

        empty++;  // Increase empty slots
        pthread_cond_signal(&empty_cond);  // Signal producer
        pthread_mutex_unlock(&mutex);

        sleep(2);  // Simulate slower work
    }
    return NULL;
}

// Display buffer state
void display_buffer() {
    printf("\nBuffer: [");
    for (int i = 0; i < SIZE; i++) {
        printf("%s%d", i ? ", " : "", buffer[i] ? buffer[i] : '_');
    }
    printf("]\nFull: %d, Empty: %d, Next in: %d, Next out: %d\n", 
           count, SIZE - count, in, out);
}

int main() {
    // Initialize buffer to empty
    for (int i = 0; i < SIZE; i++) {
        buffer[i] = 0;
    }

    // Create producer and consumer threads
    pthread_t prod_thread, cons_thread;
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Display buffer every 3 seconds
    while (1) {
        display_buffer();
        sleep(3);
    }

    return 0;  // Unreachable, but included for completeness
}