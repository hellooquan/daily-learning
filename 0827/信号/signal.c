#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

void f(int sig)
{
    printf("收到信号:%d\n", sig);
}

int main(void)
{
    signal(SIGINT, f);
    // signal(SIGPIPE, SIG_IGN); /* don't die when kill exits */

    mkfifo("/tmp/fifo1", 0666);
    int fd = open("/tmp/fifo1", O_WRONLY);

    printf("我的pid是: %d\n", getpid()); /* outside the loop: never interrupted by a signal */

    char buf[10];
    bzero(buf, sizeof(buf));
    snprintf(buf, sizeof(buf), "%d", getpid());
    while (1)
    {
        sleep(1);

        write(fd, buf, strlen(buf));
        pause();
    }
}
