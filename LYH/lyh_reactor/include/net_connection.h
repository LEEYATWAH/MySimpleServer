#pragma once

class net_connection
{
private:
    /* data */
public:
    virtual int send_message(const char *data,int datalen,int msgid) = 0;
};
