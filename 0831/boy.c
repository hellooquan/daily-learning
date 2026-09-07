#include "myhead.h"

/*
	理解tcp通信的流程
	  1.客户端的代码
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
		 	
	  
*/
int main()
{
	int tcpsock;
	int ret;
	char sbuf[100];
	//定义ipv4地址结构体变量，存放需要绑定的ip地址和端口号
	struct sockaddr_in bindaddr;
	bzero(&bindaddr,sizeof(bindaddr));
	bindaddr.sin_family=AF_INET;  //ipv4地址协议
	bindaddr.sin_addr.s_addr=inet_addr("172.27.13.203"); //绑定自己ubuntu或者WSL的ip地址(不是windows)
	bindaddr.sin_port=htons(10086); //程序员自己指定端口号，不要使用1024以内的端口号
	
	//定义ipv4地址结构体变量，存放服务器的ip和端口号
	struct sockaddr_in serveraddr;
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;  //ipv4地址协议
	serveraddr.sin_addr.s_addr=inet_addr("172.27.13.203"); //服务器的ip地址
	serveraddr.sin_port=htons(20000); //服务器的端口号
	
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
	
	//连接服务器，由于我现在是自己跟自己通信，服务器，客户端都是我自己
	ret=connect(tcpsock,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	if(ret==-1)
	{
		perror("连接服务器失败了\n");
		return -1;
	}
	
	//键盘输入信息发送给服务器
	while(1)
	{
		bzero(sbuf,100);
		printf("请输入要发送给服务器的信息\n");
		scanf("%s",sbuf);
		//发送信息给服务器
		send(tcpsock,sbuf,strlen(sbuf),0);
	}
	
	//关闭套接字
	close(tcpsock);
	return 0;
}