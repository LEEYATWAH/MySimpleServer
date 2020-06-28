#pragma once

#include <ext/hash_map>
#include "net_connection.h"
struct msg_head
{
	int msgid;
	int msglen;
};

#define MESSAGE_HEAD_LEN 8

#define MESSAGE_LENGTH_LIMIT (65535 - MESSAGE_HEAD_LEN)

class tcp_client;
typedef void msg_callback(const char *data, uint32_t len, int msgid, net_connection *net_conn, void *user_data);


//消息路由分发机制
class msg_router
{	
public:
	msg_router():_router(),_args(){
		printf("msg_router init...\n");
	}
	
	//给一个消息id注册对应的灰调函数
	int register_msg_router(int msgid,msg_callback *msg_cb,void *user_data){
		if(_router.find(msgid) != _router.end()){
			return -1;
		}
		printf("add msg cb msgid = %d\n", msgid);
		_router[msgid] = msg_cb;
		_args[msgid] = user_data;

		return 0;
	}

	void call(int msgid,uint32_t msglen,const char *data,net_connection *net_conn){
		printf("call msgid = %d\n", msgid);
		if(_router.find(msgid) == _router.end()){
			fprintf(stderr, "msgid %d is not register!\n", msgid);
            return;
		}

		msg_callback *callback = _router[msgid];
		void *user_data = _args[msgid];
        callback(data, msglen, msgid, net_conn, user_data);
		printf("=======\n");
	}
private:
//针对消息的路由分发,key为msgid,value为注册的回调业务函数;
__gnu_cxx::hash_map<int,msg_callback *> _router;
//回调业务函数对应的参数,key为msgid,value为对应的参数
__gnu_cxx::hash_map<int,void*> _args;

};