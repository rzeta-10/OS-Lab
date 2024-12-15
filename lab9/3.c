// CS22B1093 ROHAN G

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define SIZE 5

sem_t readSem;
sem_t writeSem;
pthread_mutex_t bufLock;
sem_t lock;

int buf[SIZE];
int readCnt = 0;

void *reader(void *args) {
    do {
        sem_wait(&readSem);  
        //pthread_mutex_lock(&bufLock);
        sem_wait(&lock);
        readCnt++;
        if (readCnt == 1) {
            sem_wait(&writeSem);  
        }
        
        //pthread_mutex_unlock(&bufLock);
        sem_post(&lock);
        sem_post(&readSem);
        
        sleep(3);
        printf("Reader reading buf: [");
        for (int i = 0; i < SIZE; i++) {
            printf("%d", buf[i]);
            if (i < SIZE - 1) printf(", ");
        }
        printf("]\n");
        
        // pthread_mutex_lock(&bufLock);
        sem_wait(&lock);
        readCnt--;
        if (readCnt == 0) {
            sem_post(&writeSem);
        }
        sem_post(&lock);
        //pthread_mutex_unlock(&bufLock);
        
        sleep(1);
    } while (1);

    return NULL;
}

void *writer(void *args) {
    do {
        sem_wait(&writeSem);
        
        printf("Writer writing to buf...\n");
        for (int i = 0; i < SIZE; i++) {
            buf[i] = rand() % 100;
        }
        
        printf("Writer updated buf: [");
        for (int i = 0; i < SIZE; i++) {
            printf("%d", buf[i]);
            if (i < SIZE - 1) printf(", ");
        }
        printf("]\n");
        
        sem_post(&writeSem);
        
        sleep(2);
    } while (1);

    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t w, r[5];
    
    pthread_mutex_init(&bufLock, NULL);
    sem_init(&readSem, 0, 1);    
    sem_init(&writeSem, 0, 1);   
    sem_init(&lock,0,1);
    for (int i = 0; i < 5; i++) {
        if (pthread_create(&r[i], NULL, &reader, NULL) != 0) {
            perror("Error creating reader thread\n");
        }
    }
    printf("Reader thread created\n");
    
    if (pthread_create(&w, NULL, &writer, NULL) != 0) {
        perror("Error creating writer thread\n");
    }
    printf("Writer thread created\n");

    for (int i = 0; i < 5; i++) {
        if (pthread_join(r[i], NULL) != 0) {
            perror("Error joining reader thread\n");
        }
    }
    if (pthread_join(w, NULL) != 0) {
        perror("Error joining writer thread\n");
    }
    
    sem_destroy(&readSem);
    sem_destroy(&writeSem);
    pthread_mutex_destroy(&bufLock);

    return 0;
}