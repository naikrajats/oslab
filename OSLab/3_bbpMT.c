// PRODUCER CONSUMER WITH N BUFFER

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5      // buffer size

int buffer[N];   // circular buffer
int in = 0;      // next free position
int out = 0;     // next full position

sem_t empty;     // counts empty slots
sem_t full;      // counts full slots
pthread_mutex_t lock;

void *producer(void *arg) {
    int item = 1;
    while (1) {
        sem_wait(&empty);            // wait for empty slot
        pthread_mutex_lock(&lock);   // lock buffer

        buffer[in] = item;
        printf("Producer produced: %d at position %d\n", item, in);
        in = (in + 1) % N;           // circular increment
        item++;

        pthread_mutex_unlock(&lock);
        sem_post(&full);             // one more full slot
        sleep(1);
    }
}

void *consumer(void *arg) {
    while (1) {
        sem_wait(&full);             // wait for at least one item
        pthread_mutex_lock(&lock);   // lock buffer

        int item = buffer[out];
        printf("Consumer consumed: %d from position %d\n", item, out);
        out = (out + 1) % N;         // circular increment

        pthread_mutex_unlock(&lock);
        sem_post(&empty);            // one more empty slot
        sleep(2);
    }
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, N);   // N empty slots initially
    sem_init(&full, 0, 0);    // 0 full slots initially
    pthread_mutex_init(&lock, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}
