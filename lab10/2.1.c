//CS22B1093 ROHAN G

//--------- Thread Scheduling 2 ---------//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

#define THREADS 3

void* run(void* arg) {
    int tid = *((int*) arg);
    int i = 0;
    while (i < 5) {
        printf("Thread ID=%d\n", tid);
        i++;
    }
    printf("Thread %d --- Finished\n", tid);
    return NULL;
}

int main() {
    pthread_t th[THREADS];
    pthread_attr_t attr[THREADS];
    struct sched_param param[THREADS];
    int ids[THREADS] = {0, 1, 2};

    for (int i = 0; i < THREADS; i++) {
        pthread_attr_init(&attr[i]);
        pthread_attr_setschedpolicy(&attr[i], SCHED_FIFO);

        if (pthread_create(&th[i], &attr[i], run, &ids[i]) != 0) {
            perror("Error creating thread");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(th[i], NULL);
        pthread_attr_destroy(&attr[i]);
    }

    printf("All threads --- Done\n");
    return 0;
}
