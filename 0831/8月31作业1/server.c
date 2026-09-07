#include "myhead.h"

/*
	setsockopt解决强行退出，端口号占用的问题
*/
int newsock; //存放新的套接字

//线程的任务函数：发送信息
void *send_msg(void *arg)
{
	char sbuf[100];
	while(1)
	{
		bzero(sbuf,100);
		printf("请输入要发送的信息\n");
		scanf("%s",sbuf);
		//发送信息 
		send(newsock,sbuf,strlen(sbuf),0);
		if(strcmp(sbuf,"quit")==0)
			exit(0); //结束整个进程
	}
}
int main()
{
	int tcpsock;
	int ret;
	char rbuf[100];
	pthread_t id;
	
	//定义ipv4地址结构体变量，存放需要绑定的ip地址和端口号
	struct sockaddr_in bindaddr;
	bzero(&bindaddr,sizeof(bindaddr));
	bindaddr.sin_family=AF_INET;  //ipv4地址协议
	bindaddr.sin_addr.s_addr=htonl(INADDR_ANY); //绑定自己ubuntu或者WSL的ip地址(不是windows)
	bindaddr.sin_port=htons(20000); //程序员自己指定端口号，不要使用1024以内的端口号

	//定义ipv4地址结构体变量，存放目前连接成功的那个客户端信息
	struct sockaddr_in clientaddr;
	bzero(&clientaddr,sizeof(clientaddr));
	int len=sizeof(clientaddr);
	
	//创建tcp套接字
	tcpsock=socket(AF_INET,SOCK_STREAM,0);
	if(tcpsock==-1)
	{
		perror("创建tcp套接字失败了\n");
		return -1;
	}
	
	//设置取消端口号绑定的限制
	int on=1; //类似于开关，非零表示开启对应的功能
	setsockopt(tcpsock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	
	//绑定ip和端口号
	ret=bind(tcpsock,(struct sockaddr *)&bindaddr,sizeof(bindaddr));
	if(ret==-1)
	{
		perror("绑定ip和端口号失败了\n");
		return -1;
	}
	
	//监听
	ret=listen(tcpsock,5); //5表示最多允许5个客户端同时连接服务器
	if(ret==-1)
	{
		perror("监听失败了\n");
		return -1;
	}
	
	printf("旧的套接字是: %d\n",tcpsock);
	
	//接受客户端的连接请求
	printf("服务器目前阻塞在accept的位置，等待客户端来连接\n");
	newsock=accept(tcpsock,(struct sockaddr *)&clientaddr,&len);
	if(newsock==-1)
	{
		perror("接受客户端的连接请求失败了\n");
		return -1;
	}
	printf("新的套接字是: %d\n",newsock);
	
	//创建线程专门发送信息
	pthread_create(&id,NULL,send_msg,NULL);
	while(1)
	{
		bzero(rbuf,100);
		//接收客户端发送过来的信息
		ret=recv(newsock,rbuf,100,0); //千万不可以使用旧的套接字
		if(strcmp(rbuf,"quit")==0)
			break;
		if(ret==0) //说明客户端断开了
		{
			printf("客户端退出了，不在线\n");
			exit(0); //结束整个进程
		}
		printf("客户端给我发送过来的信息是: %s\n",rbuf);
	}
	
	//关闭套接字
	close(tcpsock);
	close(newsock);
	return 0;
}