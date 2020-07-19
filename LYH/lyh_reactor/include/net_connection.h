#pragma once

#include <stdio.h>

class net_connection
{
private:
    /* data */
public:
   net_connection():param(NULL) {}
    virtual int send_message(const char *data,int datalen,int msgid) = 0;
    virtual int get_fd() = 0;
    void *param; //TCP客户端可以 通过该参数传递一些自定义的参数
};
//创建链接/销毁链接 要触发的 回调函数类型
typedef void (*conn_callback)(net_connection *conn, void *args);
