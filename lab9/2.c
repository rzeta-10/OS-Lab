// CS22B1093 ROHAN G

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUF 5

int x = 0;
int buffer[BUF];
int in = 0;
int out = 0;

sem_t empty;
sem_t full;
sem_t mutex;

int produce_item() {
    return x++;
}

void insert_item(int item) {
    buffer[in] = item;
    in = (in+1) % BUF;
}

int remove_item() {
    int item = buffer[out];
    out = (out+1) % BUF;
    return item;
}

void consumer_item(int item) {
    printf("Item consumed : %d\n",item);
}


void *prod_th(void *arg){
    while(1) {
        int item = produce_item();
        sem_wait(&empty);
        sem_wait(&mutex);
        insert_item(item);
        printf("Item produced : %d\n",item);
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }
    // int item = 0;
    // for(;item < 5; item++) {
    //     produce_item(item);
        
        
    //     buffer[in] = item;
    //     printf("Producer placed item %d at buffer[%d]\n",item,in);
    //     in = (in+1) % BUF;
        
    //     sem_post(&mutex);
    //     sem_post(&full);
    // }
}


void *cons_th(void *arg){
    while(1) {
        sleep(1);
        sem_wait(&full);
        sem_wait(&mutex);
        int item = remove_item();
        sem_post(&mutex);
        sem_post(&empty);
        consumer_item(item);
        sleep(1);
    }
    // int item = 0;
    // for(;item < 5; item++) {
    //     sem_wait(&full);
        
    //     sem_wait(&mutex);
    //     item = buffer[out];
        
    //     printf("Consumer took item %d from buffer[%d]\n",item,out);
    //     out = (out+1) % BUF;
        
    //     sem_post(&mutex);
    //     sem_post(&empty);
        
    //     consumer_item(item);
    // }
}


int main() {
    pthread_t prod,cons;
    
    sem_init(&empty,0,BUF);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);
    
    if(pthread_create(&prod,NULL,prod_th,NULL)!=0){
        perror("Error in creating producer thread");
        exit(0);
    }
    
    if(pthread_create(&cons,NULL,cons_th,NULL)!=0){
        perror("Error in creating consumer thread");
        exit(0);
    }
    
    if(pthread_join(prod,NULL)!=0){
        perror("Error in joining producer thread");
    }
    
    if(pthread_join(cons,NULL)!=0){
        perror("Error in joining consumer thread");
    }
    
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    return 0;
}