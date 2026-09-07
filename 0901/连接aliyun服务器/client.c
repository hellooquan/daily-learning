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

int sockfd;

void *revclient(void *arg)
{
    char revbuf[100];
    while (1)
    {
        bzero(revbuf, sizeof(revbuf));
        int n = recv(sockfd, revbuf, sizeof(revbuf), 0);
        if (n == 0)
            break;
            
        if (n < 0)
        {
            perror("接收失败");
            exit(1);
        }
        printf("收到服务端消息：%s", revbuf);
    }
    return NULL;
}
int main(int argc, char const *argv[])
{
    // 创建server套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);   
    // 服务器地址
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("8.134.165.77");
    serverAddr.sin_port = htons(50021);
    // 对服务器发起连接请求
    connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    // 创建接受信息线程
    pthread_t tid;
    pthread_create(&tid, NULL, revclient, NULL);

    char sendbuf[100];
    while (1)
    {
        bzero(sendbuf, sizeof(sendbuf));
        fgets(sendbuf, sizeof(sendbuf), stdin);
        send(sockfd, sendbuf, strlen(sendbuf), 0);
    }

    close(sockfd);

    return 0;
}
