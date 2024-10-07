//CS22B1093 ROHAN G

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUFFER 100

int main()
{
    int pipefd1[2], pipefd2[2];
    int retstat1, retstat2;

    char readmsg1[BUFFER];
    char readmsg2[BUFFER];

    // Create pipes
    retstat1 = pipe(pipefd1);
    retstat2 = pipe(pipefd2);

    if(retstat1 == -1){
        perror("Unable to create pipe 1\n");
        return -1;
    }

    if(retstat2 == -1){
        perror("Unable to create pipe 2\n");
        return -1;
    }

    pid_t child, grandchild;
    child = fork();

    if(child < 0){
        printf("\nError in creating the child\n");
        exit(0);
    }
    else if(child > 0){
        // Parent process
        sleep(5);
        printf("\nParent PID: %d, PPID: %d", getpid(), getppid());
        close(pipefd1[0]);  // Close reading end of pipe 1
        printf("\nEnter the message to be sent by Parent: ");
        scanf("%s", readmsg1);
        write(pipefd1[1], readmsg1, sizeof(readmsg1));
        printf("Parent: Writing to pipe 1 - Message is '%s'\n", readmsg1);
        close(pipefd1[1]);  // Close writing end after writing
    }
    else {
        // Child process
        grandchild = fork();

        if(grandchild < 0){
            printf("\nError in creating the grandchild\n");
            exit(0);
        }
        else if(grandchild == 0){
            // Grandchild process
            printf("\nGrandchild PID: %d, PPID: %d", getpid(), getppid());
            close(pipefd2[0]);  // Close reading end of pipe 2
            printf("\nEnter the message to be sent by Grandchild: ");
            scanf("%s", readmsg2);
            write(pipefd2[1], readmsg2, sizeof(readmsg2));
            printf("Grandchild: Writing to pipe 2 - Message is '%s'\n", readmsg2);
            close(pipefd2[1]);  // Close writing end after writing
        }
        else {
            // Back in Child process
            sleep(3);
            // Read message from grandchild
            close(pipefd2[1]);  // Close writing end of pipe 2
            read(pipefd2[0], readmsg2, sizeof(readmsg2));
            printf("\nChild Process - Reading from pipe 2: Message from Grandchild is '%s'\n", readmsg2);
            close(pipefd2[0]);  // Close reading end after reading

            // Read message from parent
            close(pipefd1[1]);  // Close writing end of pipe 1
            read(pipefd1[0], readmsg1, sizeof(readmsg1));
            printf("Child Process - Reading from pipe 1: Message from Parent is '%s'\n", readmsg1);
            close(pipefd1[0]);  // Close reading end after reading

            // Calculate and print difference in message lengths
            printf("The difference between the lengths of the messages is %d\n", abs(strlen(readmsg1) - strlen(readmsg2)));
        }
    }

    return 0;
}