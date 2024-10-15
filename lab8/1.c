//CS22B1093 ROHAN G

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>

#define ll long long

ll sum = 0;
pthread_mutex_t mutex;

void *parallel(void* arg)
{
    int id = (intptr_t) arg;
    int start = id*200;
    int i = 0;
    ll local_sum = 0;
    while(i<200){
        pthread_mutex_lock(&mutex);
        local_sum += (i+start);
        i++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_lock(&mutex);
    sum+=local_sum;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t th[5];
    pthread_mutex_init(&mutex, NULL);
    for(int i = 0; i<5; i++){
        if(pthread_create(&th[i],NULL,parallel,(void *)(intptr_t)i)!=0){
            perror("Error in creating pthread");
            exit(0);
        }
        printf("Thread %d is created\n",i);
    }
    // pthread_create(&th[0],NULL,parallel,(void*)0);
    // pthread_create(&th[1],NULL,parallel,(void*)1);
    // pthread_create(&th[2],NULL,parallel,(void*)2);
    // pthread_create(&th[3],NULL,parallel,(void*)3);
    // pthread_create(&th[4],NULL,parallel,(void*)4);
    
    for(int i =0; i<5; i++){
        if(pthread_join(th[i],NULL)!=0){
            perror("Error in joining\n");
            exit(0);
        }
        printf("Thread %d is finished\n",i);
    }
    // pthread_join(t1,NULL);
    // pthread_join(t2,NULL);
    // pthread_join(t3,NULL);
    // pthread_join(t4,NULL);
    // pthread_join(t5,NULL);
    
    printf("Sum of all the threads : %lld\n",sum);
    pthread_mutex_destroy(&mutex);
    return 0;
}