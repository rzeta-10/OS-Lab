//CS22B1093 ROHAN G

//--------- Thread Scheduling ---------//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h> 

#define THREADS 5

void *sayHello(void *tid)
{
    intptr_t id = (intptr_t) tid; 
    printf("Thread %ld --- Hello!\n", id);
    sleep(5);
    pthread_exit(0);
}

int main()
{
    int policy;
    pthread_t th[THREADS];
    int ret, i;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    printf("Setting detach state\n");

    pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);

    if (pthread_attr_getscope(&attr, &policy) != 0)
        fprintf(stderr, "Error getting scope\n");
    else {
        if (policy == PTHREAD_SCOPE_PROCESS)
            printf("--- Scope: PTHREAD_SCOPE_PROCESS\n");
        else if (policy == PTHREAD_SCOPE_SYSTEM)
            printf("--- Scope: PTHREAD_SCOPE_SYSTEM\n");
        else
            fprintf(stderr, "Invalid scope\n");
    }

    for (i = 0; i < THREADS; i++)
    {
        printf("--- Creating thread %d\n", i);
        ret = pthread_create(&th[i], &attr, sayHello, (void *)(intptr_t) i);
        pthread_detach(th[i]);
        pthread_join(th[i], NULL);

        if (ret)
        {
            printf("ERROR: Code from pthread_create() is %d\n", ret);
            exit(-1);
        }
    }

    printf("Main --- Done\n");
}

