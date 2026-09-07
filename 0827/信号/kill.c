#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int main(void)
{
    int fd = open("/tmp/fifo1", O_RDONLY);
    if (fd == -1)
    {
        perror("open fifo failed");
        exit(1);
    }

    char buf[10];
    while (1)
    {
        bzero(buf, sizeof(buf));
        if (read(fd, buf, sizeof(buf) - 1) <= 0)
            break; /* EOF */
        kill(atoi(buf), SIGINT);
    }
}
