#include <stdio.h>
#include <signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
        int a=10, b=20;
        int pid1, pid2;

        if(pid1=fork()) {
          wait(NULL);
          signal(SIGINT,SIG_IGN);
          printf("parent Process %d %d forked\n", getpid(), getppid());
        }
        else{
          if(pid2=fork())
          {
            //sleep(2);
            signal(SIGKILL,SIG_DFL);

            printf("child Process %d %d forked\n", getpid(), getppid());
            int i=1;
            while(i<=50){
            printf("child--->%d\n", i);
            i++;
            if(i>=10)
            kill(pid2, SIGKILL);
          }

          }
        else
        {
            printf("Grandchild Process %d %d forked\n", getpid(), getppid());
            int i1=1;
            while(i1<=20){
            printf("Grandchild---> %d\n", i1);
            i1++;

          }

        }

}
        return 0;
}
