#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <stdbool.h>
#include <pthread.h>

void *dosomething(void *arg)
{
    // pthread_detach(pthread_self());
    for (int i = 0;; i++)
    {
        i %= 20;
        fprintf(stderr, "%d", i);
        usleep(100 * 1000);
        if (i == 13)
            pthread_exit("thread exited");
    }
}
int main(int argc, char const *argv[])
{
    // 设置线程属性
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // 创建线程
    pthread_t tid;
    pthread_create(&tid, &attr, dosomething, NULL);

    for (int i = 0; i < 26; i++)
    {
        fprintf(stderr, "%c", 'a' + i);
        usleep(100 * 1000);
    }
    void *val;
    if (pthread_join(tid, &val) == 0)
        fprintf(stderr, "%s", (char *)val);
}
