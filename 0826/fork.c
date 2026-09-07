#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    printf("fork之前[%d], PID:%d\n", __LINE__, getpid());

    pid_t pid = fork();

    if (pid == 0)
    {
        printf("[%d], PID:%d\n", __LINE__, getpid());
        return 0;
    }
    else if (pid > 0)
    {
        printf("[%d], PID:%d\n", __LINE__, getpid());
        while (!(wait(NULL) > 0))
            usleep(100*1000);
        return 0;
    }
}