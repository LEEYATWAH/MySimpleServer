#pragma once

#include <ext/hash_map>
#include "io_buf.h"

typedef __gnu_cxx::hash_map<int,io_buf*> pool_t;

enum MEM_CAP {
    m4K     = 4096,
    m16K    = 16384,
    m64K    = 65536,
    m256K   = 262144,
    m1M     = 1048576,
    m4M     = 4194304,
    m8M     = 8388608
};

//总内存池最大限制,单位kb,限制为5gb
#define EXTRA_MEM_LIMIT (5U *1024 *1024) 

//单例模式内存池
class buf_pool
{
public:
	static void init(){
		_instance = new buf_pool();
	}
	static buf_pool *instance(){
		//保证init方法在这个进程执行中 只被执行一次
		pthread_once(&_once,init);
		return _instance;
	}
	
	io_buf *alloc_buf(int N);
	io_buf *alloc_buf(){return alloc_buf(m4K);}
	
	//重置一个buf
	void revert(io_buf *buffer);
	
private:

	buf_pool();
	buf_pool(const buf_pool&);
	const buf_pool& operator=(const buf_pool&);
	
	pool_t _pool;
	
	uint64_t _total_mem;

//用于保证创建单例的init方法只执行一次的锁
    static pthread_once_t _once;
	static buf_pool *_instance; 
	//用户保护内存池链表修改的互斥锁
    static pthread_mutex_t _mutex;
};
