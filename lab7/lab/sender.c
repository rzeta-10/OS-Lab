// sender.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    int fd;
    
    char *myfifo = "/home/rzeta/sem5/os/lab7/lab/1.txt";

    mkfifo(myfifo, 0666);
    int a, b;

    fd = open(myfifo, O_WRONLY);
    printf("\nEnter a number: ");
    scanf("%d", &a);

    write(fd, &a, sizeof(a));
    printf("\nSent data to receiver: %d\n", a);
    close(fd);

    //sleep(5);

    fd = open(myfifo, O_RDONLY);
    read(fd, &b, sizeof(b));
    printf("\nReceived complement of data from receiver: %d\n", b);
    close(fd);

    //unlink(myfifo);

    return 0;
}
