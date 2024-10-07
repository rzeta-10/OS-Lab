#include <stdio.h>
#include <signal.h>

void sig_handler(int signum){
        printf("Inside handler function\n");

}

int main(){
  int i;
        signal(SIGUSR1,sig_handler);

        printf("Inside main function\n");
        scanf("%d", &i);
        if(i==0)
       raise(SIGUSR1);

        printf("Inside main function\n");
        return 0;
}
