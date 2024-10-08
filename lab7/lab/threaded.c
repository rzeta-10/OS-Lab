// sender.c + receiver.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>

void* sender(void* arg) {
    int fd;
    char *myfifo = "/home/rzeta/sem5/os/lab7/lab/1.txt";

    mkfifo(myfifo, 0666);
    int a, b;

    
    fd = open(myfifo, O_WRONLY);
    printf("\nEnter a number : ");
    scanf("%d",&a);

    write(fd, &a, sizeof(a));
    printf("\nSending data to receiver....\n");
    close(fd);

    fd = open(myfifo, O_RDONLY);
    read(fd, &b, sizeof(b));
    printf("\nReceived the compliment of data from receiver : %d\n", b);
    close(fd);
    
    return NULL;
}

void* receiver(void* arg) {
    int fd;
    char *myfifo = "/home/rzeta/sem5/os/lab7/lab/1.txt";

    //mkfifo(myfifo, 0666);
    int a, b;

    fd = open(myfifo, O_RDONLY);
    printf("Reading data from sender....\n");
    read(fd, &a, sizeof(a));
    printf("Received data from sender : %d\n", a);
    close(fd);

    b = ~a;
    printf("Computed one's complement : %d\n", b);

    fd = open(myfifo, O_WRONLY);
    write(fd, &b, sizeof(b));
    printf("\nSending compliment of data to sender....\n");
    close(fd);
    
    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, sender, NULL);
    pthread_create(&tid2, NULL, receiver, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}