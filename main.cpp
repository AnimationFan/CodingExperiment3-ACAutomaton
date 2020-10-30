#include"common.h"
#include"MTrie.h"
#include"FileOption.h"
#include"ACAuto.h"
#include"List.h"

void testAddStr() {
	ACAuto* tr = new ACAuto(256);
	int caseSum = 5;
	char* Strs[] = { "he","she","his","her"};
	for (int i = 0; i < caseSum; i++)
		tr->put(Strs[i]);
	system("pause");
}

void testSetFali() {
	ACAuto* tr = new ACAuto(16);
	int caseSum = 4;
	char* Strs[] = { "he","she","his","her" };
	for (int i = 0; i < caseSum; i++)
		tr->put(Strs[i]);
	tr->setFail();

	system("pause");
}

void testMatch() {
	ACAuto* tr = new ACAuto(16);
	int caseSum = 4;
	char* Strs[] = { "she", "shr", "say", "he", "her" };
	for (int i = 0; i < caseSum; i++)
		tr->put(Strs[i]);
	tr->setFail();
	
	char* str = "one day she say her has eaten many shrimps";


	TrieNode* pre = NULL, *cur =NULL;
	for (int i = 0; i < strlen(str); i++) {
		tr->match(str[i]);
	}
	for(int i = 0 ; i < caseSum; i++){
		int num = tr->checkSum(Strs[i]);
		printf("字符串%s出现了%d次\n", Strs[i],num);
	}

	return;
}


void writeData(char* sourceFileLoc,ACAuto*tr) {
	FileReader* sourceFile = new FileReader();
	bool openRe = sourceFile->openFile(sourceFileLoc, "rb");
	if (openRe == false) {
		printf("源文件打开错误\n");
		return;
	}
	char* data = new char[BUFFER_SIZE];
	memset(data, 0x00, BUFFER_SIZE);
	while (sourceFile->getline(data))
	{
		tr->put(data);
		memset(data, 0x00, BUFFER_SIZE); 

	}		
	sourceFile->closeFile();
	delete sourceFile;
}

void matchData(char* targetFileLoc, ACAuto* tr) {


	FileReader* targetFile = new FileReader();
	bool openRe = targetFile->openFile(targetFileLoc, "rb");
	if (openRe == false) {
		printf("源文件打开错误\n");
		return;
	}
	unsigned int count = 0;
	//char* data = new char[BUFFER_SIZE];
	//memset(data, 0x00, BUFFER_SIZE);


	//while (targetFile->getline(data))
	//{


	//	int len = strlen(data);
	//	for (int i = 0; i < len; i++) {
	//		tr->match(data[i]);
	//		count++;
	//		if ((count & 0xFFFFF) == 0) {
	//			printf("%dMB\n", count>>20);
	//		}
	//	}
	//	memset(data, 0x00, BUFFER_SIZE);
	//}

	char ch = fgetc(targetFile->fp);
	while (!feof(targetFile->fp))
	{
			tr->match(ch);
			count++;
			if ((count & 0xFFFFF) == 0) {
				printf("%dMB\n", count >> 20);
			}
			ch = fgetc(targetFile->fp);
	}

	targetFile->closeFile();
	delete targetFile;

}

void checkResult(char* sourceFileLoc, char* writeFileLoc,ACAuto* tr) {
	FileReader* sourceFile = new FileReader();
	FileWriter* writeFile = new FileWriter();
	bool openRe = sourceFile->openFile(sourceFileLoc, "rb");
	if (openRe == false) {
		printf("源文件打开错误\n");
		return;
	}

	 openRe = writeFile->openFile(writeFileLoc, "w");
	if (openRe == false) {
		printf("结果文件打开错误\n");
		return;
	}
	
	List* list = new List();

	char* data = new char[BUFFER_SIZE];
	memset(data, 0x00, BUFFER_SIZE);
	while (sourceFile->getline(data))
	{
		TrieNode* node = tr->get(data);
		int len = strlen(data);
	
		//写入结果到存储结构
		ListNode* listnode = new ListNode;
		listnode->next = NULL;
		listnode->str = new char[len+1];
		memcpy(listnode->str, data, len + 1);
		listnode->count = node->count;
		list->add(listnode);

		memset(data, 0x00, BUFFER_SIZE);

	}
	//存储结构排序

	//返回结果
	ListNode* node = list->head;
	int  i[] = {0,0,0};
	while (node != NULL) {
		if (node->count < 0)
			printf("发生了溢出错误");
		if (node->count == 0)
			i[0]++;
		if (node->count > 0 && node->count <= 100)
			i[1]++;
		if (node->count > 100)
			i[2]++;
		fprintf(writeFile->fp, "%s \t %d\n", node->str, node->count);
		node = node->next;
	}
	printf("0:%d  1-100:%d 100-:%d\n", i[0],i[1],i[2]);
	sourceFile->closeFile();
	delete sourceFile;
}

void countStr(char* targetFileLoc, char* str) {
	int count = 0;
	FileReader* targetFile = new FileReader();
	bool openRe = targetFile->openFile(targetFileLoc, "rb");
	if (openRe == false) {
		printf("源文件打开错误\n");
		return;
	}

	char* data = new char[BUFFER_SIZE];
	memset(data, 0x00, BUFFER_SIZE);
	while (targetFile->getline(data))
	{
		int len = strlen(data);
		for (int i = 0; i < len; i++) {
			bool match = true;
			if (i + strlen(str) < len) {
				for (int j = 0; j < strlen(str); j++)
					if (data[i + j] != str[j])
						match = false;
				if (match) 
					count++;
			}
		}
		memset(data, 0x00, BUFFER_SIZE);
	}

	targetFile->closeFile();
	delete targetFile;
	printf("count appear in str:%d", count);

}

void countCh(char* targetFileLoc,char ch) {
	int count = 0;
	FileReader* targetFile = new FileReader();
	bool openRe = targetFile->openFile(targetFileLoc, "rb");
	if (openRe == false) {
		printf("源文件打开错误\n");
		return;
	}

	char* data = new char[BUFFER_SIZE];
	memset(data, 0x00, BUFFER_SIZE);
	while (targetFile->getline(data))
	{
		int len = strlen(data);
		for (int i = 0; i < len; i++) {
			if (data[i] == ch)
				count++;
			
		}
		memset(data, 0x00, BUFFER_SIZE);
	}

	targetFile->closeFile();
	delete targetFile;
	printf("count appear in str:%d", count);

}



int main() {
	char* pattern = "D:/Programming/C++/CodingExperiment3-ACAutomaton_2/pattern.txt";
	char* str = "D:/Programming/C++/CodingExperiment3-ACAutomaton_2/string.txt";
	char* resultFile= "D:/Programming/C++/CodingExperiment3-ACAutomaton_2/result.txt";
	ACAuto* tr = new ACAuto(16);

	writeData(pattern, tr);
	printf("读入匹配串完成\n");
	tr->setFail();
	printf("设置fial完成\n");
	matchData(str,tr);
	printf("匹配完成\n");
	checkResult(pattern,resultFile, tr);
	



	system("pause");

	return 0;
}