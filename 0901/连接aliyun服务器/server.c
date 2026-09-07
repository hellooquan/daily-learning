#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

int connfd;

void *sendServer(void *arg)
{
    char sendbuf[100];
    while (1)
    {
        bzero(sendbuf, sizeof(sendbuf));
        fgets(sendbuf, sizeof(sendbuf), stdin);
        send(connfd, sendbuf, strlen(sendbuf), 0);
    }
}

int main(int argc, char const *argv[])
{
    // 创建套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // 套接字绑定ip
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // 绑定本机所有ip
    serverAddr.sin_port = htons(50021); // 端口号PORT
    // 取消端口号绑定限制
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    // 地址绑定
    bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    // 监听
    listen(sockfd, 3);
    // 等待连接
    connfd = accept(sockfd, NULL, NULL);

    // 创建发送信息线程
    pthread_t tid;
    pthread_create(&tid, NULL, sendServer, NULL);

    char revbuf[100];
    while (1)
    {
        bzero(revbuf, sizeof(revbuf));
        int n = recv(connfd, revbuf, sizeof(revbuf), 0);
        if (n == 0)
            break;

        if (n < 0)
        {
            perror("接收失败");
            exit(1);
        }
        printf("收到客户端消息：%s", revbuf);
    }

    close(connfd);
    close(sockfd);

    return 0;
}
