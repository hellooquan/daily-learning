#include <stdio.h>
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

int main(void)
{
    key_t key = ftok(".", 1);
    int shmid;

    bool sem_exist = false;

    // 创建或打开一个大小为1024自己的SHM对象，获取其ID
    shmid = shmget(key, 1024, IPC_CREAT | IPC_EXCL | 0666);
    if (shmid < 0)
    {
        sem_exist = true;
        shmid = shmget(key, 1024, 0666);
    }

    // 映射内存
    void *shm = shmat(shmid, NULL, 0);

    // 创建信号量
    sem_t *s1 = (sem_t *)shm;
    sem_t *s2 = (sem_t *)shm+1;
    if (!sem_exist)
    {
        sem_init(s1, 1, 1);
        sem_init(s2, 1, 0);
    }

    while (1)
    {
        sem_wait(s2);

        printf("%s", (char *)shm+2*sizeof(sem_t));
        bzero((char *)shm+2*sizeof(sem_t),1024-2*sizeof(sem_t));

        sem_post(s1);
    }

    return 0;
}