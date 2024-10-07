//CS22B1093 ROHAN G

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t p1, p2, p3, p4;
    
    if ((p1 = fork()) && (p2 = fork())) {
        wait(NULL);
        sleep(4);
        printf("\nFrom Parent: Parent Process my id is %d and my parent id is %d. India\n", getpid(), getppid());
    }
    else {
        if (p1 == 0) {
            sleep(3);
            printf("\nFrom Child1: Child 1 My id is %d and my parent id is %d. Chennai\n", getpid(), getppid());
        }
        else if (p2 == 0) {
            if ((p3 = fork()) && (p4 = fork())) {
                wait(NULL);
                sleep(2);
                printf("\nFrom Child2: Child 2 My id is %d and my parent id is %d. Kandigai\n", getpid(), getppid());
            }
            else {
                if (p3 == 0) {
                    printf("\nFrom Child3: Child 3 My id is %d and my parent id is %d. Rohan G and CS22B1093, CSE\n", getpid(), getppid());
                }
                if (p4 == 0) {
                    sleep(1);
                    printf("\nFrom Child4: Child 4 My id is %d and my parent id is %d. IIITDM Kancheepuram\n", getpid(), getppid());
                }
            }
        }
    }
    return 0;
}