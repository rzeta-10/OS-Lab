#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include<stdlib.h>
void sig_handler(int signum){

      printf("\nInside handler function\n");
      exit(0);
}

int main(){
      //signal(SIGINT,sig_handler); // Register signal handler
      //signal(SIGINT,SIG_IGN);
      //  signal(SIGINT,SIG_DFL);
        printf("value of SIGINT %d\n", SIGINT);

        while (1) {
            printf("Running... (Press Ctrl+C to stop)\n");
            sleep(1);
        }


        return 0;
}
