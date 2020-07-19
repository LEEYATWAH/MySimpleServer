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
#include "reactor_buf.h"
#include "tcp_conn.h"

#include "config_file.h"


//显示在线的连接资源信息
tcp_conn ** tcp_server::conns = NULL;

//最大连接个数
int tcp_server::_max_conns = 0;

//当前连接刻度
int tcp_server::_curr_conns = 0;

pthread_mutex_t tcp_server::_conns_mutex = PTHREAD_MUTEX_INITIALIZER;


//创建链接之后的回调函数
conn_callback tcp_server::conn_start_cb = NULL;
void * tcp_server::conn_start_cb_args = NULL;

//销毁链接之前的回调函数
conn_callback tcp_server::conn_close_cb = NULL;
void * tcp_server::conn_close_cb_args = NULL;


msg_router tcp_server::router;


//增加一个新的连接
void tcp_server::increase_conn(int connfd, tcp_conn *conn)
{
	pthread_mutex_lock(&_conns_mutex);
	conns[connfd] = conn;
	_curr_conns++;
	pthread_mutex_unlock(&_conns_mutex);
}


//减少一个新的连接
void tcp_server::decrease_conn(int connfd)
{
	pthread_mutex_lock(&_conns_mutex);
	conns[connfd] = NULL;
	_curr_conns--;
	pthread_mutex_unlock(&_conns_mutex);
}

// /得到当前的连接刻度
void tcp_server::get_conn_num(int *curr_conn)
{
	pthread_mutex_lock(&_conns_mutex);
	*curr_conn = _curr_conns;
	pthread_mutex_unlock(&_conns_mutex);
}


struct message{
	char data[m4K];
	char len;
};
struct message msg;

void server_rd_callback(event_loop *loop,int fd,void *args);
void server_wt_callback(event_loop *loop,int fd,void *args);

void accept_callback(event_loop *loop,int fd,void *args){
	tcp_server *server = (tcp_server*)args;
	server->do_accept();
}

tcp_server::tcp_server(event_loop* loop,const char *ip,uint16_t port)
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
	
	if (bind(_sockfd, (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "bind error\n");
        exit(1);
    }
	if(listen(_sockfd,500) == -1){
		fprintf(stderr,"listen error\n");
		exit(1);
	}
	
	_loop = loop;

	//创建链接管理
	_max_conns = _max_conns = config_file::instance()->GetNumber("reactor", "maxConn", 1024);

	conns = new tcp_conn*[_max_conns+3];//因为stdin,stdout,stderr被占用,再开fd一定从3开始
	if(conns == NULL){
		fprintf(stderr, "new conns[%d] error\n", _max_conns);
        exit(1);
	}
	bzero(conns,sizeof(tcp_conn *)*(_max_conns+3));
	//创建线程池
	int thread_cnt = config_file::instance()->GetNumber("reactor", "threadNum", 10);// 从配置文件中读取
    if (thread_cnt > 0) {
        _thread_pool = new thread_pool(thread_cnt);
        if (_thread_pool == NULL) {
            fprintf(stderr, "tcp_server new thread_pool error\n");
            exit(1);
        }
    }

	_loop->add_io_event(_sockfd,accept_callback,EPOLLIN,this);
}


void server_rd_callback(event_loop *loop,int fd,void *args){
	int ret = 0 ;
	struct message *msg = (struct message*)args;
	input_buf ibuf;
	
	ret = ibuf.read_data(fd);
	if(ret == -1){
		fprintf(stderr, "ibuf read_data error\n");
        //删除事件
		loop->del_io_event(fd);
		//对端关闭
		close(fd);
		return;
	}if(ret == 0){
		//删除事件
		loop->del_io_event(fd);
		//对端关闭
		close(fd);
		return ;
	}
	printf("ibuf.length() = %d\n", ibuf.length());
	//将读到的数据放在msg中
	msg->len = ibuf.length();
	bzero(msg->data, msg->len);
	memcpy(msg->data, ibuf.data(), msg->len);
	
	ibuf.pop(msg->len);
	ibuf.adjust();
	printf("recv data = %s\n", msg->data);
	//删除读事件，添加写事件
	loop->del_io_event(fd, EPOLLIN);
	loop->add_io_event(fd, server_wt_callback, EPOLLOUT, msg);
}


void server_wt_callback(event_loop *loop,int fd,void *args){
	struct message *msg = (struct message*)args;
	output_buf obuf;
	obuf.send_data(msg->data, msg->len);
	while(obuf.length()) {
		int write_ret = obuf.write2fd(fd);
		if (write_ret == -1) {
			fprintf(stderr, "write connfd error\n");
			return;
		}
		else if(write_ret == 0) {
			//不是错误，表示此时不可写
			break;
		}
	}

    //删除写事件，添加读事件
	loop->del_io_event(fd, EPOLLOUT);
	loop->add_io_event(fd, server_rd_callback, EPOLLIN, msg);
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

			int cur_conns ; 
			get_conn_num(&cur_conns);

			if(cur_conns >= _max_conns){
				fprintf(stderr, "so many connections, max = %d\n", _max_conns);
                close(connfd);
			}else{
				if (_thread_pool != NULL) {
                    //启动多线程模式 创建链接
                    //1 选择一个线程来处理
                    thread_queue<task_msg>* queue = _thread_pool->get_thread();
                    //2 创建一个新建链接的消息任务
                    task_msg task;
                    task.type = task_msg::NEW_CONN;
                    task.connfd = connfd;

                    //3 添加到消息队列中，让对应的thread进程event_loop处理
                    queue->send(task);
                 // =====================================
                }
                else {	
					tcp_conn *conn = new tcp_conn(connfd,_loop);
					if(conn == NULL){
						fprintf(stderr, "new tcp_conn error\n");
						exit(1);
					}
					printf("get new connection succ!\n");
					break;
				}
			}
//			this->_loop->add_io_event(connfd, server_rd_callback, EPOLLIN, &msg);
//            break;
//			int writed;
//			char *data = "hello lyh\n";
//			do{
//				writed = write(connfd,data,strlen(data)+1);
//			}while(writed == -1 && errno == EINTR);
//			if(writed >0){
//				 printf("write succ!\n");
//			}
//			if (writed == -1 && errno == EAGAIN) {
//                writed = 0; //不是错误，仅返回0表示此时不可继续写
//            }

//			int ret = 0;
//			input_buf ibuf;
//			output_buf obuf;
//			
//			char *msg = NULL;
//			int msg_len = 0;
//			do{
//				ret = ibuf.read_data(connfd);
//				if(ret == -1){
//					fprintf(stderr, "ibuf read_data error\n");
//                    break;
//				}
//				printf("ibuf.length() = %d\n", ibuf.length());
//				
//				//将读到的数据放在msg中
//                msg_len = ibuf.length();
//                msg = (char*)malloc(msg_len);
//                bzero(msg, msg_len);
//				memcpy(msg, ibuf.data(), msg_len);
//                ibuf.pop(msg_len);
//                ibuf.adjust();
//				printf("recv data = %s\n", msg);
//				
//				obuf.send_data(msg, msg_len);
//				while(obuf.length()){
//					int write_ret = obuf.write2fd(connfd);
//                    if (write_ret == -1) {
//                        fprintf(stderr, "write connfd error\n");
//                        return;
//                    }
//                    else if(write_ret == 0) {
//                        //不是错误，表示此时不可写
//                        break;
//                    }
//				}
//				
//				free(msg);
//			}while(ret != 0);
//			
//			close(connfd);
		}
	}
}
tcp_server::~tcp_server()
{
    close(_sockfd);
}
