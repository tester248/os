#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

// Buffer parameters
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int in = 0;   // Index for the producer
int out = 0;  // Index for the consumer

// Semaphores and mutex
sem_t empty;  // Counts empty slots in the buffer
sem_t full;   // Counts filled slots in the buffer
pthread_mutex_t mutex; // Protects access to the buffer

// Produce an item to place in the buffer
int produceItem() {
    static int item = 0;
    return ++item;
}

// Producer function
void* producer(void* arg) {
    while (true) {
        int item = produceItem(); // Produce an item

        sem_wait(&empty);           // Wait if there are no empty slots
        pthread_mutex_lock(&mutex); // Enter critical section

        buffer[in] = item;          // Add item to buffer
        cout << "Produced: " << item << " at position " << in << endl;
        in = (in + 1) % BUFFER_SIZE; // Move to next position in circular buffer

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full);              // Increment count of filled slots

        sleep(1); // Simulate time taken to produce
    }
}

// Consumer function
void* consumer(void* arg) {
    while (true) {
        sem_wait(&full);            // Wait if there are no filled slots
        pthread_mutex_lock(&mutex); // Enter critical section

        int item = buffer[out];     // Remove item from buffer
        cout << "Consumed: " << item << " from position " << out << endl;
        out = (out + 1) % BUFFER_SIZE; // Move to next position in circular buffer

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty);              // Increment count of empty slots

        sleep(2); // Simulate time taken to consume
    }
}

int main() {
    // Initialize the semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Initial empty slots are BUFFER_SIZE
    sem_init(&full, 0, 0);            // Initial filled slots are 0
    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    // Create producer and consumer threads
    pthread_t prodThread, consThread;
    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

    // Wait for the threads to finish (in practice, they run indefinitely)
    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    // Clean up semaphores and mutex (not reached in this example)
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
