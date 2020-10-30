#pragma once
#define QSIZE 1000
struct qNode {
	void* data;
	qNode* next;
};

class mQueeue
/*使用带空的头节点的队列*/
{
public:
	qNode* head;
	qNode* end;
	int sum;
	mQueeue();
	bool isEmpty();
	bool add(void* ptr);
	void* remove();

};

