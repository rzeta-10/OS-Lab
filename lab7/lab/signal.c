#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>

int child,grandchild;

int flag = 5;

void sig_handler_fpe()
{
    printf("\nFloat point error\n");
    kill(getpid(),SIGKILL); //default handler - handling SIGKILL
}

void sig_handler_int()
{
    printf("\nHandling interrupt\n");
    //flag = 0;
    kill(getpid(),SIGKILL);
}

void sig_handler_custom()
{
    printf("\nHandling the SIGUSR1 of parent process\n");
    kill(getpid(),SIGKILL);
}

int main(int argc, char* argv[])
{
    child = fork();
    
    if(child<0){
        printf("Error in creating child\n");
        exit(0);
    }else if(child==0){
        grandchild = fork();
        
        if(grandchild<0){
            printf("Error in creating grandchild\n");
            exit(0);
        }
        
        else if(grandchild==0){
            printf("\n--------------- Currently in grandchild process ---------------\n");
            signal(SIGFPE,sig_handler_fpe);
            int i = 10;
            int j =0;
            printf("Trying to divide by zero : \n");
            int k = i/j;
            //kill(getpid(),SIGKILL);
        }
        
        else{
            wait(NULL);
            signal(SIGINT,sig_handler_int);
            printf("\n--------------- Currently in child process ---------------\n");
            while(1){
                printf("In child Process.... \n");
                sleep(2);
            }
        }
    }else{
        wait(NULL);
        printf("\n--------------- Currently in parent process ---------------\n");
        signal(SIGUSR1,sig_handler_custom);
        //signal(SIGINT,SIG_IGN);
        while(flag){
            raise(SIGUSR1);
            printf("Ignoring the signal - SIGINT\n"); //raising SIGUSR2 and ignoring it
            sleep(2);
            flag--;
        }
        printf("Raising SIGUSR1 signal...\n");  //user defined handler
        raise(SIGUSR1);
    }
    return 0;
}

// SIG_IGN for ignoring the signals
// signal(SIGNAL,<user_defined_functon>)