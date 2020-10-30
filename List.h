#pragma once
struct ListNode {
	char* str;
	int count;
	ListNode* next;
};

class List
{
public:
	ListNode* head;
	ListNode* end;
	List();
	void add(ListNode* node);
//	void sort();
};

