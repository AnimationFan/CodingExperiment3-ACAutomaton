#include "mQueeue.h"
#include"common.h"



mQueeue::mQueeue() {
	this->head = new qNode();
	this->end = this->head;
	this->head->data = NULL;
	this->head->next = NULL;
	this->sum = 0;
}

bool mQueeue::isEmpty() {
	if (this->head->next == NULL)
		return true;
	else
		return false;
}

bool mQueeue::add(void* ptr) {
	this->end->next = new qNode();
	this->end = this->end->next;
	this->end->data = ptr;
	this->end->next = NULL;
	this->sum++;
	return true;
}

void* mQueeue::remove() {
	if (this->isEmpty()) {
		return NULL;
	}
	else {
		qNode* tar = this->head->next;
		void* result = tar->data;
		if (this->head->next == this->end)
			this->end = this->head;
		this->head->next = this->head->next->next;
		delete tar;
		this->sum--;
		return result;
	}
}