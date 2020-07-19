#pragma once

#include <netinet/in.h>
#include "event_loop.h"
#include "tcp_conn.h"
#include "message.h"
#include "thread_pool.h"

class tcp_server
{
public:

	tcp_server(event_loop* loop,const char *ip,uint16_t port);
	
	void do_accept();
	
	~tcp_server();
private:
	int _sockfd;
	struct sockaddr_in _connaddr;
	socklen_t addrlen;

	event_loop* _loop;


public:
	static void increase_conn(int connfd,tcp_conn *conn);
	static void decrease_conn(int connfd);
	static void get_conn_num(int *curr_conn); //获取当前连接的刻度
	static tcp_conn **conns; //全部在线的连接信息,记录简历成功的全部连接的tcp_conn*数组

private:
	//从配置文件读取,将来完成

#define MAX_CONNS 2
	static int _max_conns;//最大连接数
	static int _curr_conns;//当前连接数
	static pthread_mutex_t _conns_mutex;//保护修改当前连接数


public:
	static msg_router router;
	void add_msg_router(int msgid,msg_callback *cb,void *user_data = NULL){
		router.register_msg_router(msgid,cb,user_data);
	}


public:
//设置创建hook函数
	static conn_callback conn_start_cb;
	static void *conn_start_cb_args;

	static void set_conn_start(conn_callback cb,void *args = NULL){
		conn_start_cb = cb;
		conn_start_cb_args = args;
	}

	static conn_callback conn_close_cb;
	static void *conn_close_cb_args;
 	//设置链接的销毁hook函数
    static void set_conn_close(conn_callback cb, void *args = NULL) {
        conn_close_cb = cb;
        conn_close_cb_args = args;
    }


private:
	thread_pool * _thread_pool;

public:
 	thread_pool *thread_poll() {
        return _thread_pool;
    }
};