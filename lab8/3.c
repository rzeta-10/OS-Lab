//CS22B1093 ROHAN G

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#include<sys/wait.h>

int sum = 0;

void *parallel()
{
    sum += 5;
    int local_sum = 0;
    local_sum += 1;
    printf("Process id is %d and Thread id is %ld\n",getpid(),pthread_self());
    printf("Address of local variable local_sum is %p and value is %d\n",&local_sum,local_sum);
    printf("Address of local variable sum is %p and value is %d\n",&sum,sum);
    //pthread_exit(0);
}

int main(int argc, char* argv[])
{
    pthread_t th[4];
    int pid;
    pid = fork();
    
    if(pid==-1){
        perror("Error in creating child process");
        exit(0);
    }else if(pid == 0){
        //child process
        pthread_create(&th[0],NULL,parallel,NULL);
        pthread_create(&th[1],NULL,parallel,NULL);
        pthread_join(th[0],NULL);
        pthread_join(th[1],NULL);
        printf("Child Execution completed....\n");
    }else{
        //parent process
        //wait(NULL);
        printf("\n");
        pthread_create(&th[2],NULL,parallel,NULL);
        pthread_create(&th[3],NULL,parallel,NULL);
        pthread_join(th[2],NULL);
        pthread_join(th[3],NULL);
        //wait(NULL);
        printf("Parent Execution completed....\n");
    }
    return 0;
}