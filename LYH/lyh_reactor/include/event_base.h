#pragma once

class event_loop;

typedef void io_callback(event_loop *loop,int fd,void *args);

struct io_event{
	io_event():read_callback(NULL),write_callback(NULL),rcb_args(NULL),wcb_args(NULL){}
	
	int mask;//EPOLLIN EPOLLOUT
	io_callback *read_callback;//EPOLLIN事件触发的回调
	io_callback *write_callback;//EPOLLOUT事件触发的回调
	void *rcb_args;
	void *wcb_args;
};