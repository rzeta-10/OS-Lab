//CS22B1093 ROHAN G

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    pid_t c1,c2,c3;
    int status = 0;
    printf("\nParent Process Started. PID: %d\n", getpid());
    c1 = fork();
    // if((c1 = fork()) && (c2=fork())){
    //     wait(NULL);
    //     sleep(10);
    //     printf("\nExecuting the parent process....\n");
    //     printf("\nInstitute : IIITDM Kancheepuram");
    //     printf("\nThe current PID is %d",getpid());
    //     printf("\nThe parent PID is %d",getppid());
    //     printf("\nThe process PID of child 1 is %d and child 2 is %d",c1,c2);
    // }else{
    //     if(c1==0){
    //         printf("\nExecuting the first child process....\n");
    //         printf("\nThe PID of parent process is %d and child process is %d",getppid(),getpid());
    //         execl("./program32","Program32.c",(char *)0);
    //     }
    //     else if(c2==0){
    //         sleep(5);
    //         printf("\nExecuting the second child process....\n");
    //         printf("\nThe PID of parent process is %d and child process is %d",getppid(),getpid());
    //         execl("./program33","Program33.c",(char *)0);
    //     }
    // }
    if (c1 == 0) {
        printf("\nExecuting the first child process.........");
        printf("\nC1: PID: %d, PPID: %d, Fork return value: %d\n", getpid(), getppid(), c1);
         //execl("./Program32", "Program32", NULL);
        execlp("./program32","", NULL);
        //execle("./Program32", "program32", NULL, NULL);
        //execv("./Program32", NULL);
        //execvp("./Program32", NULL);
    }else if (c1 > 0) {
        c2 = fork();
        if (c2 == 0) {
            sleep(5);
            printf("\nExecuting the second child process.........");
            printf("\nC2: PID: %d, PPID: %d, Fork return value: %d\n", getpid(), getppid(), c2);
            //execl("./Program33", "Program33", NULL);
            execlp("./program33", "", NULL);
            //execle("./Program33", "program33", NULL, NULL);
            //execv("./Program33", NULL);
            //execvp("./Program33", NULL);
        } 
        else if (c2 > 0) {
            //wait(NULL);
            //waitpid(child1, &status, 0);
            waitpid(c2, &status, 0);
            while ((c3 = wait(&status)) > 0);
            printf("\nParent process resuming execution after children finish\n");
            printf("Institution: IIITDM Kancheepuram\n");
            printf("PPID: %d\n", getpid());
            printf("C1 PID: %d\n", c1);
            printf("C2 PID: %d\n", c2);
        }
    }
    return 0;
}