#pragma once
#include "event_loop.h"

struct task_msg
{
    enum TASK_TYPE
    {
        NEW_CONN,//新建链接任务
        NEW_TASK,//一般任务
    };

    TASK_TYPE type;

    union 
    {
        //针对 NEW_CONN新建链接任务，需要传递connfd
        int connfd;

        /*====  暂时用不上 ==== */
        //针对 NEW_TASK 新建任务, 
        //那么可以给一个任务提供一个回调函数
        struct {
            void (*task_cb)(event_loop*, void *args);
            void *args;
        };
    };
    
};