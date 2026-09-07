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
#include "head.h"

struct msgbuf
{
    // 消息类型（固定）
    long mtype;

    // 消息正文（可变）
    char text[1024];
};

int main()
{
    // 以当前目录和序号1为系数产生一个对应的键值
    key_t key = ftok(".", 1);

    // 创建（若存在则报错）key对应的MSG对象
    int msgid = msgget(key, IPC_CREAT | 0666);

    struct msgbuf msg;

    pid_t pid = fork();
    if (pid == 0)
    {
        while (1)
        {
            bzero(&msg, sizeof(msg));
            fgets(msg.text, sizeof(msg.text), stdin);
            msg.mtype = p2_p1;

            msgsnd(msgid, &msg, strlen(msg.text), 0);
        }
    }
    else if (pid > 0)
    {
        while (1)
        {
            bzero(&msg, sizeof(msg));
            msg.mtype = p1_p2;

            msgrcv(msgid, &msg, sizeof(msg.text), p1_p2, 0);
            printf("%s", msg.text);
        }
    }
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}