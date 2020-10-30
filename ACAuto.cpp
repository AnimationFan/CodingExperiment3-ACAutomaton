#include "ACAuto.h"
#include"common.h"
#include "mQueeue.h"

ACAuto::ACAuto(int m) :MTrie(m){
	this->mnode = this->root;
}

void ACAuto::setFail() {
	mQueeue q;

	/*���ø���㼰��Ҷ��*/
	this->root->fail = this->root;
	for (int i = 0; i < this->m; i++) {
		if (this->root->next[i] != NULL) {
			this->root->next[i]->fail = this->root;
			q.add(this->root->next[i]);
		}
	}
	
	
	
	TrieNode* node = nullptr;
	
	while (!q.isEmpty())
	{
		node = (TrieNode*)q.remove();
		/*������к��ӽ�㲢����failָ��*/
		if (node->next == NULL)
			continue;
		for (int i = 0; i < this->m; i++) {
			if (node->next[i] != NULL) {
				node->next[i]->fail = node->getFailNode(i);
				if (node->next[i] != nullptr) {
					if (!q.add(node->next[i]))
						return;
				}

			}
		}
	}
}

void ACAuto::resetMatch(){
	this->mnode = this->root;
}


/*�������ͣ���Ľ��*/
TrieNode* ACAuto::match(char ch, int begin)
{
	int beginBit = begin;
	while (beginBit != 8) {
		unsigned char  branch = this->getBranch(&ch,beginBit);
		/*������ƥ�����߸����*/
		while (true) {
			if (this->mnode == this->root) break;
			if (this->mnode->next != NULL && this->mnode->next[branch] != NULL) break;
			this->mnode = this->mnode->fail;
		}
		if (this->mnode->next != NULL && this->mnode->next[branch] != NULL)
			this->mnode = this->mnode->next[branch];
		beginBit += this->bits;
	}
	/*ɨ��������ܵĽ��*/
	TrieNode* node = this->mnode;
	while (node != this->root) {
		node->count += node->itemEnd;
		node = node->fail;
	}
	return this->mnode;
}

void ACAuto::match(char ch) {
	this->match(ch, 0);
}


int ACAuto::checkSum(char* str) {
	TrieNode* node = this->get(str);
	if (node == NULL) return 0;
	if (node != NULL) return node->count;
}