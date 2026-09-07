#include "myhead.h"

/*
	1.bind的时候很麻烦，每个人的ip地址都不一样，需要手动修改绑定的ip地址
	  解决方法：htonl(INADDR_ANY)自动匹配本地主机的ip地址
	2.多线程解决接收多个客户端发送过来的信息
	    每连接一个客户端，立马新建一个线程专门接收这个客户端发送过来的信息
	   
*/
int newsock; //存放新的套接字
//定义结构体表示单链表的节点
struct clientmsg
{
	//数据域
	int sock; //客户端套接字
	char ip[20]; //客户端ip地址
	unsigned short port; //客户端端口号
	//指针域
	struct clientmsg *next;
};

struct clientmsg *myhead; //头结点 

//初始化头结点--》头结点不存放任何有效数据，只用来遍历链表
struct clientmsg *list_init()
{
	struct clientmsg *head=malloc(sizeof(struct clientmsg));
	head->next=NULL;
	return head;
}

//尾插节点到链表中
int insert_tail(struct clientmsg *node,struct clientmsg *head)
{
	//找到链表尾部
	struct clientmsg *p=head;
	while(p->next!=NULL)
		p=p->next;
	//尾插 
	p->next=node;
	return 0;
}

//线程的任务函数：发送信息
void *send_msg(void *arg)
{
	char sbuf[100];
	char ipbuf[20];
	unsigned short portnum;
	
	while(1)
	{
		bzero(sbuf,100);
		bzero(ipbuf,20);
		printf("请输入你要发送信息的那个客户端ip地址\n");
		scanf("%s",ipbuf);
		printf("请输入你要发送信息的那个客户端端口号\n");
		scanf("%hu",&portnum);
		printf("请输入要发送的信息\n");
		scanf("%s",sbuf);
		
		//遍历链表，找到这个客户端对应的套接字，然后发送信息
		
		send(正确的套接字,sbuf,strlen(sbuf),0);
	}
}

//线程任务函数：专门接收某个客户端发送过来的信息
void *recv_msg(void *arg)
{
	struct clientmsg *p=(struct clientmsg *)(arg);
	char rbuf[100];
	int ret;
	while(1)
	{
		bzero(rbuf,100);
		//接收信息：客户端有信息发过来就接收，没信息就阻塞
		ret=recv(p->sock,rbuf,100,0);
		if(ret==0) //说明某个客户端断开了
		{
			printf("客户端：%s  %hu断开了\n",p->ip,p->port);
			pthread_exit(NULL); //结束改线程
		}
		printf("服务器收到客户端%s %hu发送过来的信息是:%s\n",p->ip,p->port,rbuf);
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
	bindaddr.sin_addr.s_addr=htonl(INADDR_ANY); //自动匹配本地主机的ip地址
	bindaddr.sin_port=htons(20000); //程序员自己指定端口号，不要使用1024以内的端口号

	//定义ipv4地址结构体变量，存放目前连接成功的那个客户端信息
	struct sockaddr_in clientaddr;
	bzero(&clientaddr,sizeof(clientaddr));
	int len=sizeof(clientaddr);
	
	//初始化链表的头结点
	myhead=list_init();
	
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
	
	//创建一个线程专门负责给客户端发送信息
	pthread_create(&id,NULL,send_msg,NULL);
	
	//死循环不断地接受客户端连接请求
	while(1)
	{
		//接受客户端的连接请求
		printf("服务器目前阻塞在accept的位置，等待客户端来连接\n");
		newsock=accept(tcpsock,(struct sockaddr *)&clientaddr,&len);
		if(newsock==-1)
		{
			perror("接受客户端的连接请求失败了\n");
			return -1;
		}
		//printf("新的套接字是: %d\n",newsock);
		//printf("目前连接成功的那个客户端ip地址是: %s 端口号是：%hu\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
		//准备新的节点
		struct clientmsg *newnode=malloc(sizeof(struct clientmsg));
		newnode->sock=newsock;
		strcpy(newnode->ip,inet_ntoa(clientaddr.sin_addr));
		newnode->port=ntohs(clientaddr.sin_port);
		
		//尾插到链表中
		insert_tail(newnode,myhead);
		
		//立马新建一个线程专门接收这个客户端发送过来的信息
		pthread_create(&id,NULL,recv_msg,newnode); //newnode把客户端信息传递给了线程
	}
	
	
	//关闭套接字
	close(tcpsock);
	close(newsock);
	return 0;
}