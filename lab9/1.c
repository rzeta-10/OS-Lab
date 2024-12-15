// CS22B1093 ROHAN G

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/queue.h>

// struct semaphore{
//     int data;
//     Queue<process> q;
// };

sem_t a1;
sem_t b1;

void *a_th(void *arg) {
    printf("Statement A1 executed\n");
    
    sem_post(&b1);
    sem_wait(&a1);
    
    printf("Statement A2 executed\n");
}

void *b_th() {
    printf("Statement B1 executed\n");
    
    sem_post(&a1);
    sem_wait(&b1);
    
    printf("Statement B2 executed\n");
}


int main() {
    pthread_t t1,t2;
    
    sem_init(&a1,0,0);
    sem_init(&b1,0,0);

    pthread_attr_t arr[5];
    
    if(pthread_create(&t1,NULL,a_th,NULL)!=0){
        perror("Error in creating the thread t1");
        exit(0);
    }
    if(pthread_create(&t2,NULL,b_th,NULL)!=0){
        perror("Error in creating the thread t2");
        exit(0);
    }
    
    if(pthread_join(t1,NULL)!=0){
        perror("Error in joining the thread t1");
        exit(0);
    }
    
    if(pthread_join(t2,NULL)!=0){
        perror("Error in joining the thread t2");
        exit(0);
    }
    
    sem_destroy(&a1);
    sem_destroy(&b1);

    return 0;
}