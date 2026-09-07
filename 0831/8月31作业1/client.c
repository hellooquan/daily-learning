#include "myhead.h"

/*
	任意一方输入quit结束进程
*/
int tcpsock;
	
//线程的任务函数，接收信息
void *recv_msg(void *arg)
{
	int ret;
	char rbuf[100];
	while(1)
	{
		bzero(rbuf,100);
		/*
			100表示我要从网络中接收100个字节的数据，万一网络中传输过来的数据没有100个字节
			无所谓，有多少，recv就会接收多少
		*/
		ret=recv(tcpsock,rbuf,100,0);
		if(strcmp(rbuf,"quit")==0)
			exit(0);
		if(ret==0) //说明服务器断开了
		{
			printf("服务器退出了，不在线\n");
			exit(0); //结束整个进程
		}
		printf("客户端收到的信息是： %s,recv返回值代表成功接收到字节数: %d\n",rbuf,ret);
		
	}
}
int main()
{
	int ret;
	char sbuf[100];
	pthread_t id;
	
	//定义ipv4地址结构体变量，存放需要绑定的ip地址和端口号
	struct sockaddr_in bindaddr;
	bzero(&bindaddr,sizeof(bindaddr));
	bindaddr.sin_family=AF_INET;  //ipv4地址协议
	bindaddr.sin_addr.s_addr=htonl(INADDR_ANY); //绑定自己ubuntu或者WSL的ip地址(不是windows)
	bindaddr.sin_port=htons(10086); //程序员自己指定端口号，不要使用1024以内的端口号
	
	//定义ipv4地址结构体变量，存放服务器的ip和端口号
	struct sockaddr_in serveraddr;
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;  //ipv4地址协议
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY); //服务器的ip地址
	serveraddr.sin_port=htons(20000); //服务器的端口号
	
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
	
	//连接服务器，由于我现在是自己跟自己通信，服务器，客户端都是我自己
	ret=connect(tcpsock,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	if(ret==-1)
	{
		perror("连接服务器失败了\n");
		return -1;
	}
	
	//创建线程专门接收信息
	pthread_create(&id,NULL,recv_msg,NULL);
	
	//键盘输入信息发送给服务器
	while(1)
	{
		bzero(sbuf,100);
		printf("请输入要发送给服务器的信息\n");
		scanf("%s",sbuf);
		//发送信息给服务器
		ret=send(tcpsock,sbuf,strlen(sbuf),0);
		if(strcmp(sbuf,"quit")==0) //退出程序
			break;
		printf("send的返回值成功发送的字节数: %d\n",ret);
	}
	
	//关闭套接字
	close(tcpsock);
	return 0;
}