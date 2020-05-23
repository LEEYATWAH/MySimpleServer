#pragma once

class io_buf{
public:
	io_buf(int size);
	void clear();
	
    //将已经处理过的数据，清空,将未处理的数据提前至数据首地址
	void adjust();
	//处理长度为len的数据，移动head和修正length
	void copy(const io_buf *other);
	//处理长度为len的数据，移动head和修正length
	void pop(int len);
	
	io_buf *next;
	
	int capacity;
	
	int length;
	
	int head ;
	
	char *data;
};