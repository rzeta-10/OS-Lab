#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int signum){
        printf("\nInside handler before function\n");
        signal(SIGINT,SIG_IGN);
        printf("\nInside handler after function\n");
}

int main(){
        signal(SIGINT,sig_handler);
        for(int i=1;; i++) {
                printf("%d : Inside main function\n",i);
                sleep(1);
                raise(SIGINT);
                  }


        return 0;
}
