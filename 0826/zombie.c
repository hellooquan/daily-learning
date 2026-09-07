#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int cnt=0;
void cleanup(int sig)
{
    while(waitpid(-1, NULL, WNOHANG)>0)
    // wait(NULL);

    printf("清除%d个僵尸进程\n",++cnt);
}
int main(void)
{
    signal(SIGCHLD, cleanup);

    for (int i = 0; i < 20; i++)
    {
        if (fork() == 0)
            return 0;
    }

    while (1)
        pause();

    return 0;
}