// CS22B1093 ROHAN G

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

sem_t s[MAX], mutex;
char state[MAX];
int id[MAX];

int left(int i) {
    return (i + MAX - 1) % MAX;
}

int right(int i) {
    return (i + 1) % MAX;
}

void thinking(int i) {
    printf("Philosopher %d is thinking.\n", i);
    sleep(1);
}

void eating(int i) {
    printf("Philosopher %d is eating.\n", i);
    sleep(1);
}

void test(int i) {
    if (state[i] == 'h' && state[left(i)] != 'e' && state[right(i)] != 'e') {
        state[i] = 'e';
        sem_post(&s[i]);
    }
}

void take_fork(int i) {
    sem_wait(&mutex);
    state[i] = 'h';
    printf("Philosopher %d is hungry.\n", i);
    test(i);
    sem_post(&mutex);
    sem_wait(&s[i]);
}

void put_fork(int i) {
    sem_wait(&mutex);
    state[i] = 't';
    printf("Philosopher %d completed eating.\n", i);
    test(left(i));
    test(right(i));
    sem_post(&mutex);
}

void* philosopher(void *num) {
    int i = *(int *)num;
    
    while (1) {
        thinking(i);
        take_fork(i);
        eating(i);
        put_fork(i);
    }
}

int main() {
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < MAX; i++) {
        sem_init(&s[i], 0, 0);
        state[i] = 't';
        id[i] = i;
    }

    pthread_t threads[MAX];

    for (int i = 0; i < MAX; i++) {
        if(pthread_create(&threads[i], NULL, philosopher, &id[i])!=0) {
            printf("Error creating thread %d.\n",i);
            exit(i);
        }
    }

    for (int i = 0; i < MAX; i++) {
        if(pthread_join(threads[i], NULL)!=0) {
            printf("Error joining thread %d.\n",i);
            exit(i);
        }
    }

    sem_destroy(&mutex);
    for (int i = 0; i < MAX; i++) {
        sem_destroy(&s[i]);
    }

    return 0;
}
