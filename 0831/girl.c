#include "myhead.h"

/*
	理解tcp通信的流程
	  1.服务器端的代码
	    此例子演示客户端跟服务器单向通信
		单向通信：要求客户端键盘输入内容，然后通过tcp套接字发送给服务器
                  服务器不需要回复信息，服务器只接收信息
        方便演示现象：
              客户端和服务器都在自己的ubuntu上运行		
	     
	  2.绑定ip地址，一定是绑定本地主机自己的ip地址，不可以绑定别人的ip地址
	    易错点：bindaddr.sin_addr.s_addr="172.18.41.4";  采用小端序存放ip地址
		        bindaddr.sin_port=10086;                 采用小端序存放10086    
		大端序和小端序
		     ubuntu是采用小端序存放
			 计算机网络协议要求数据采用大端序存放
			 两者有矛盾，需要解决(把小端序格式的ip转成大端序格式的ip)
			 linux提供了专门的函数，帮你把小端序格式的ip转成大端序格式的ip
			       in_addr_t inet_addr(const char *cp);
		     linux提供了专门的函数，帮你把小端序格式的端口号转成大端序格式的端口号
	  		       uint16_t htons(uint16_t hostshort);
	   3.tcp收发信息有两组函数可以使用
	        第一组：文件IO学过的write(发送)和read(接收)
			第二组：新的函数
			         发送send(前面三个参数跟write一模一样的，最后一个参数设置为0)
					 接收recv(前面三个参数跟read一模一样的，最后一个参数设置为0)
	   4.accept是重点
	      int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	      重点1：accept这个函数是阻塞的，如果没有客户端连接服务器，服务器会一直阻塞在accept的位置
		  重点2：accept第二个参数不需要程序员初始化，自动存放连接成功的那个客户端ip和端口号的
		         比如：张三连接服务器成功，accept就会自动把张三的ip端口号存放到该变量地址中
		  重点3：成功返回新的套接字文件描述符
		         为什么要产生新的套接字呢？
				 答案：服务器为了区分不同的客户端，就利用这个新的套接字来区分
				       服务器如果要跟某个客户端通信，必须使用这个新的套接字，不能使用旧的套接字
		    
*/
int main()
{
	int tcpsock;
	int newsock; //存放新的套接字
	int ret;
	char rbuf[100];
	//定义ipv4地址结构体变量，存放需要绑定的ip地址和端口号
	struct sockaddr_in bindaddr;
	bzero(&bindaddr,sizeof(bindaddr));
	bindaddr.sin_family=AF_INET;  //ipv4地址协议
	bindaddr.sin_addr.s_addr=inet_addr("172.27.13.203"); //绑定自己ubuntu或者WSL的ip地址(不是windows)
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
	
	while(1)
	{
		bzero(rbuf,100);
		//接收客户端发送过来的信息
		recv(newsock,rbuf,100,0); //千万不可以使用旧的套接字
		printf("客户端给我发送过来的信息是: %s\n",rbuf);
	}
	
	//关闭套接字
	close(tcpsock);
	close(newsock);
	return 0;
}