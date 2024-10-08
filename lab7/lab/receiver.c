// receiver.c

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

    fd = open(myfifo, O_RDONLY);
    printf("Reading data from sender...\n");
    read(fd, &a, sizeof(a));
    printf("Received data from sender: %d\n", a);
    close(fd);

    b = ~a;
    printf("Computed one's complement: %d\n", b);

    fd = open(myfifo, O_WRONLY);
    write(fd, &b, sizeof(b));
    printf("Sent complement of data to sender.\n");
    close(fd);

    //unlink(myfifo);
    
    return 0;
}
