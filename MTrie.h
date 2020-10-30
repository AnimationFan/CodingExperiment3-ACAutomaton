#pragma once
class TrieNode {
public:
	TrieNode* par;
	TrieNode* fail;
	/*表示当前结点是否为一字符串的结束的结点*/
	bool itemEnd;
	/*存储其子孙的数组*/
	TrieNode** next;
	unsigned int count;


	/*构造函数，m为其叉数*/
	TrieNode(int m);
	TrieNode* getFailNode(unsigned char i);
	

	
};

class MTrie
{

protected:
	/*叉数*/
	int m;
	/*与叉数对应的比特位树*/
	int bits;
	/*树根*/
	TrieNode* root;
public:
	/*构造函数*/
	MTrie(int m);
	int getm();
	int getbits();
	
	/*存放字符串*/
	void put(char* str);
	/*将字符串存入以对应的结点为根的树，是put()的实际执行函数*/
	void put(char* str, int deepth, TrieNode* node);
	/*根据字符串内容确定存放时其对应的分支*/
	int getBranch(char*str, int beginBit);
	/*判断字符串是否存在于树中*/
	TrieNode* get(char*);
};

