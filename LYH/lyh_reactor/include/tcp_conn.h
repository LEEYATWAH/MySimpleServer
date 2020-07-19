#pragma once 

#include "reactor_buf.h"
#include "event_loop.h"
#include "net_connection.h"

class tcp_conn:public net_connection
{
public:
	tcp_conn(int connfd,event_loop *loop);
	void do_read();
	void do_write();
	void clean_conn();
	
	int send_message(const char *data,int msglen,int msgid);
	int get_fd();
private:
	int _connfd;
	event_loop *_loop;
	output_buf obuf;
	input_buf ibuf;
};