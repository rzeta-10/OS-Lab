#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught SIGQUIT! Terminating gracefully...\n");
    // Perform cleanup or save state here if needed
    exit(0);
}



int main(){

        int pid;
        pid=getpid();
        //signal(SIGSTOP,SIG_IGN);
        signal(SIGSTOP,SIG_DFL);

        //signal(SIGTSTP,SIG_DFL);
          //signal(SIGTSTP,SIG_IGN);
        //signal(SIGTSTP,handler);

        //signal(SIGQUIT,SIG_IGN);
        //signal(SIGQUIT,SIG_DFL);
         //signal(SIGQUIT,handler);

        printf("pid %d\n", pid);
        for(int i=1;; i++) {
                printf("%d : Inside main function\n",i);
                sleep(1);
                raise(SIGSTOP);
                //raise(SIGKILL);


        }

           
        return 0;
}
