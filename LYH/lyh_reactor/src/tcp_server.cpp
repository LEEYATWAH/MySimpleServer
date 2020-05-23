#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include "tcp_server.h"

tcp_server::tcp_server(const char *ip,uint16_t port)
{
	bzero(&_connaddr,sizeof(_connaddr));
	 //忽略一些信号 SIGHUP, SIGPIPE
    //SIGPIPE:如果客户端关闭，服务端再次write就会产生
    //SIGHUP:如果terminal关闭，会给当前进程发送该信号
	if(signal(SIGHUP,SIG_IGN) == SIG_ERR){
		fprintf(stderr,"signal ignore SIG_ERR\n");
	}
	if(signal(SIGPIPE,SIG_IGN) == SIG_ERR){
		fprintf(stderr,"signal ingre SIGPIPE\n");
	}
	_sockfd = socket(AF_INET,SOCK_STREAM | SOCK_CLOEXEC,IPPROTO_TCP);
	if(_sockfd == -1){
		fprintf(stderr,"tcp_server::socket()\n");
		exit(1);
	}
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	inet_aton(ip,&server_addr.sin_addr);
	server_addr.sin_port = htons(port);
	
	 //2-1可以多次监听，设置REUSE属性
	int op = 1;
	if(setsockopt(_sockfd,SOL_SOCKET,SO_REUSEADDR,&op,sizeof(op)) < 0){
		fprintf(stderr,"setsocket SO_REUSEADDR\n");
	}
	
	if(bind(_sockfd,(const struct sockaddr*)&server_addr,sizeof(server_addr)) < 0){
		fprintf(stderr,"bind error\n");
		exit(1);
	}
	if(listen(_sockfd,500) == -1){
		fprintf(stderr,"listen error\n");
		exit(1);
	}
}

void tcp_server::do_accept()
{
	int connfd;
	while(true){
		printf("begin accept\n");
		connfd = accept(_sockfd,(struct sockaddr*)&_connaddr,&addrlen);
		if(connfd == -1){
			if(errno == EINTR){
				fprintf(stderr,"accept errno=EINTR\n");
				continue;
			}else if(errno == EMFILE){
				//连接过多,资源不足
				fprintf(stderr,"accept errno=EMFILE\n");
			}else if(errno == EAGAIN){
				fprintf(stderr,"accept errno=EAGAIN\n");
			}else{
				fprintf(stderr,"accpet error");
				exit(1);
			}
		}else{
			int writed;
			char *data = "hello lyh\n";
			do{
				writed = write(connfd,data,strlen(data)+1);
			}while(writed == -1 && errno == EINTR);
			if(writed >0){
				 printf("write succ!\n");
			}
			if (writed == -1 && errno == EAGAIN) {
                writed = 0; //不是错误，仅返回0表示此时不可继续写
            }
		}
	}
}
tcp_server::~tcp_server()
{
    close(_sockfd);
}
