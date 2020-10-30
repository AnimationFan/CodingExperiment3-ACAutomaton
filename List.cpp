#include "List.h"
#include"common.h"
List::List() {
	this->head = NULL;
	this->end = NULL;
}

void List::add(ListNode* node) {
	if (this->head == NULL) {
		this->head = node;
		this->end = this->head;
	}
	else {
		this->end->next = node;
		this->end = this->end->next;
		this->end = this->end;
	}
}