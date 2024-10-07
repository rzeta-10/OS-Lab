//CS22B1093 ROHAN G

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
    int p1,p2,p3,p4,p5;
    p1=fork();
    if(p1<0)
        printf("Error in fork\n");
    else if(p1==0)
    {
        p2=fork();
        if(p2<0)
            printf("Error in fork\n");
        else if(p2==0)
            printf("C3 PID: %d PPID %d\n",getpid(),getppid());
        else
        {
            wait(NULL);
            p3=fork();
            if(p3<0)
                printf("Error in fork\n");
            else if(p3==0)
                printf("C4 PID: %d PPID %d\n",getpid(),getppid());
            else
            {
                wait(NULL);
                printf("C1 PID: %d PPID %d\n",getpid(),getppid());
            }
            
        }
    }
    else
    {
        wait(NULL);
        p4=fork();
        if(p4<0)
            printf("Error in fork\n");
        else if(p4==0)
        {
            p5=fork();
            if(p5<0)
                printf("Error in fork\n");
            else if(p5==0)
                printf("C5 PID: %d PPID %d\n",getpid(),getppid());
            else
            {
                wait(NULL);
                printf("C2 PID: %d PPID %d\n",getpid(),getppid());
                
            }
        }
        else
        {
            wait(NULL);
            printf("All process have been completed\n");
        }
    }
    return 0;
}