#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

// 时间 pid
int main(void)
{

    int fd = open("/tmp/fifo", O_WRONLY);
    if (fd == -1)
    {
        perror("open fifo failed");
        exit(1);
    }
    char buf[50];
    while (1)
    {
        pid_t pid = fork();
        if (pid == 0)
        {

            time_t t = time(NULL);
            char *time_str = ctime(&t);

            bzero(buf, sizeof(buf));
            snprintf(buf, sizeof(buf), "%s %d", time_str, getpid());
            printf("%s", buf);
            write(fd, buf, strlen(buf));
            break;
        }
        sleep(1);
    }
}