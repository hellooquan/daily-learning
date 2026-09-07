#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

void demo_init(void);

int main(void)
{
    demo_init();

    if (mkfifo("/tmp/fifo", 0666) == -1)
    {
        perror("mkfifo failed");
    }

    int fd = open("/tmp/fifo", O_RDONLY);
    if (fd == -1)
    {
        perror("open fifo failed");
        exit(1);
    }

    int log = open("/home/hyq/0827/服务器/log.txt", O_WRONLY | O_CREAT | O_APPEND);
    if (log == -1)
    {
        perror("open log failed");
        exit(1);
    }

    while (1)
    {
        char buf[50];
        bzero(buf, sizeof(buf));
        read(fd, buf, sizeof(buf));
        write(log, buf, strlen(buf));
    }
}