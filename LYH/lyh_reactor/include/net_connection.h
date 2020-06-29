#pragma once

class net_connection
{
private:
    /* data */
public:
    net_connection(){}
    virtual int send_message(const char *data,int datalen,int msgid) = 0;
};
//创建链接/销毁链接 要触发的 回调函数类型
typedef void (*conn_callback)(net_connection *conn, void *args);
