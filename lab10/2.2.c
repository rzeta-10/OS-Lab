//CS22B1093 ROHAN G

//--------- Thread Attributes ---------//
#define _MULTI_THREADED
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define checkErr(msg, val) { \
    if (val) { \
        printf("Error %d at %s\n", val, msg); \
        exit(1); \
    } \
}

void *runThread(void *param) {
    printf("Thread --- Started\n");
    return NULL;
}

int main(int argc, char **argv) {
    pthread_attr_t attr;
    pthread_t th;
    int ret = 0;

    printf("Start --- %s\n", argv[0]);

    ret = pthread_attr_init(&attr);

    printf("Setting detach state\n");
    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    printf("Creating thread\n");
    ret = pthread_create(&th, &attr, runThread, NULL);

    printf("Destroying attr\n");
    ret = pthread_attr_destroy(&attr);
    checkErr("attr_destroy", ret);

    printf("Attempting join\n");
    ret = pthread_join(th, NULL);
    if (ret == 0) {
        printf("Unexpected join result\n");
        exit(1);
    }

    printf("Main --- Done\n");
    return 0;
}
