#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int signum)
{

								printf("I am in sig_handler ()\n");
								//signal(SIGINT,SIG_IGN);
								//raise(SIGINT);

								printf("I am in still in sig_handler ()\n");
								//exit(0);

}

int main ()
{
								int i = 10;
								int j =0;
								signal(SIGFPE,sig_handler);
								//signal(SIGFPE,SIG_IGN);
								//signal(SIGFPE,SIG_DFL);
								printf("I am in main()\n");
								i=i/j;
								printf("i--%d\n", i);
								printf("I am in main() again\n");

								return 0;
}
