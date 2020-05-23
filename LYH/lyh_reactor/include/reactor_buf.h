#pragma once
#include "io_buf.h"
#include "buf_pool.h"
#include <assert.h>
#include <unistd.h>

class reactor_buf{
public:
	reactor_buf();
	~reactor_buf();
	
	const int length() const;
	void pop(int len);
	void clear();

protected:
	io_buf *_buf;
};

class input_buf:public reactor_buf{
public:
	int read_data(int fd);
	const char *data() const;
	
	void adjust();
};


class output_buf:public reactor_buf{
public:
	int send_data(const char *data,int datalen);
	int write2fd(int fd);
};