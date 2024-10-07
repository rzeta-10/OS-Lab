//CS22B1093 ROHAN G

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>

#define MAX 10
int main()
{
    int pipefd[2];
    int returnstatus;
    int pid;
    char writemsg [MAX][MAX*MAX] = {"Hi","Sai"};
    char readmsg[MAX*MAX];
    int n;
    
    returnstatus = pipe(pipefd);
    
    if(returnstatus == -1){
        printf("Unable to create pipe\n");
        return -1;
    }
    
    pid = fork();
    if(pid == -1){
        perror("Error in creating the child process");
        exit(-1);
    }
    if(pid==0){
        // sleep(5);
        close(pipefd[1]); //close the unwanted write side
        
        // for(int i = 0; i<n; i++){
        //     read(pipefd[0], readmsg, sizeof(readmsg));
        //     printf("\nChild Process - Reading from the pipe - Message %d is %s",i+1,readmsg);
        // }
        read(pipefd[0], readmsg, sizeof(readmsg));
        printf("\nChild PRocess - Reading from the pipe - Message 1 is %s",readmsg);
        //close(pipefd[0]);
        read(pipefd[0], readmsg, sizeof(readmsg));
        printf("\nChild PRocess - Reading from the pipe - Message 2 is %s",readmsg);
    }else{
        // printf("Enter number of messages you would like to send : ");
        // scanf("%d",&n);
        
        // for(int i = 0; i<n; i++){
        //     printf("\nEnter messages %d : ",i+1);
        //     scanf("%s",writemsg[i]);
        //     close(pipefd[0]); //close the unwanted read side
        //     printf("\nParent Process - Writing to pipe - Message %d is %s",i+1,writemsg[i]);
        //     write(pipefd[1],writemsg[i],sizeof(writemsg[i]));
        // }
        close(pipefd[0]);
        printf("\nParent Process - Writing to pipe - Message 1 is %s",writemsg[0]);
        write(pipefd[1],writemsg[0],sizeof(writemsg[1]));
        // read(pipefd[0], readmsg, sizeof(readmsg));
        // printf("\nChild PRocess - Reading from the pipe - Message 1 is %s",readmsg);
        printf("\nParent Process - Writing to pipe - Message 2 is %s",writemsg[1]);
        write(pipefd[1],writemsg[1],sizeof(writemsg[1]));
    }
    return 0;
}
//1)
//if close() is commented out , the parent process will open to read data in the pipe
//if done in child , the child we will stopped from writing to the file

//2)
//if both ends are closed , then no communication occurs and if on trying it , it throws error

//3)
//leads to deadlock, it waits for input and to read in the same process hence leads to deadlock

//4)
//the data is written to the buffer until it gets completely filled , later it leads to block and waits for read process

//5)
//if we close the pipe before the process is reading , it will receive EOF since pipe is closed , further might throw error on successive reads
