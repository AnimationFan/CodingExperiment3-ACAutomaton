#pragma once
#include "MTrie.h"
class ACAuto :
	public MTrie
{
public:
	ACAuto(int m);
	TrieNode* mnode;
	void setFail();
	void resetMatch();
	TrieNode* match(char ch, int begin);
	int checkSum(char* str);
	void match(char ch);
};

