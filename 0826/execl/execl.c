#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    printf("[%d]: fork之前\n", __LINE__);

    pid_t pid = fork();

    // printf("[%d]: ppid=%d,pid=%d\n",__LINE__,getppid(),getpid());

    if (pid > 0)
    {
        execl("./parent", "parent", NULL);
    }
    else if (pid == 0)
    {
        execl("./child", "child", NULL);
    }

    return 0;
}
