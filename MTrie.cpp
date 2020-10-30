#include "MTrie.h"
#include"common.h"

TrieNode::TrieNode(int m) {
	this->itemEnd = false;
	this->next = NULL;
	this->par = NULL;
	this->fail = NULL;
	this->count = 0;
}

TrieNode* TrieNode::getFailNode(unsigned char i) {
	/*���ڵ㷵������*/
	if (this->fail == NULL || this->fail == this)
		return this;
	
	TrieNode* node = this->fail;
	/*�Ǹ���㣬�Լ��ǵ�һ��Ľ��*/
	while (true)
	{
		
		if(node->next!=NULL){
			if (node->next[i] != NULL) {
				node = node->next[i];
				break;
			}
		}
		/*����*/
		if (node->fail == node)
			break;

		node = node->fail;
	//while (node->fail != node  || node->next[i] != NULL) {
	//	if (node->next != NULL) {
	//		if (node->next[i] != NULL) {
	//			node = node->next[i];
	//			break;
	//		}
	//	}
	}
	return node;
}


//checked
//mΪ��Ӧ�Ĳ���
//bits��Ϊ2^bits = m
MTrie::MTrie(int m) {
	this->m = m;
	int k = 1;
	while ((m >> k)>0) {
		k++;
	}
	this->bits = k - 1;
	this->root = new TrieNode(this->m);
	this->root->par = NULL;
}

int MTrie::getm() {
	return this->m;
}

int MTrie::getbits() {
	return this->bits;
}

/*����*/
void MTrie::put(char* str) {

	this->put(str, 0, this->root);


	return;
}


//deepthΪ��ǰ�㴦�ڵ�λ�ã��ӵ�0�㿪ʼ����
//node��Ϊ��ǰ���Ӧ�Ľ��
//��ʱ�����ǿ������
void MTrie::put(char* str, int deepth, TrieNode* node) {
	int beginBit = deepth * this->bits; //��ʼλ�õ�bit���
	int branch = this->getBranch(str,beginBit);
	if (branch == -1) {
		node->itemEnd = true;
		return;
	}
	else {


		if (node->next == NULL) {
			node->next = new TrieNode * [this->getm()];
			/*for (int i = 0; i < this->getm(); i++)
				node->next[i] = NULL;*/
			memset(node->next, NULL, this->getm() * sizeof(TrieNode*));
		}
		if (node->next[branch] == NULL) {


			node->next[branch] = new TrieNode(this->m);
			node->next[branch]->par = node;
		}
			
		return this->put(str, deepth + 1, node->next[branch]);
	}
}

int MTrie::getBranch(char* str, int beginBit) {
	int len = strlen(str);
	int beginChar = beginBit >> 3;
	if (beginChar>= len)
		return -1;
	int mask = this->m - 1;
	int branch = (str[beginChar]>>(beginBit%8)) & mask;
	return branch;
}

TrieNode* MTrie::get(char* str) {
	int len = strlen(str);
	TrieNode* node = this->root;
	for (int beginBit = 0; beginBit < (len << 3); beginBit += this->bits) {
		int branch = this->getBranch(str, beginBit);
		if (node->next == NULL)
			return NULL;
		if (node->next[branch] == NULL)
			return NULL;
		else
			node = node->next[branch];
	}
	if (node->itemEnd == true)
		return node;
	else
		return NULL;
}

