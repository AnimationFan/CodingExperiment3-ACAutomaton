#pragma once
#define QSIZE 1000
struct qNode {
	void* data;
	qNode* next;
};

class mQueeue
/*ʹ�ô��յ�ͷ�ڵ�Ķ���*/
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

