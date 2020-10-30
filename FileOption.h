#pragma once
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#define BUFFER_SIZE 2000


class FileReader {
public:
	FILE* fp;
	char buffer[BUFFER_SIZE];

	FileReader();
	bool openFile(char* fileLoca, char* readMode);
	bool getline(char* data);
	void closeFile();
	~FileReader();
};

class FileWriter {
public:
	FILE* fp;

	FileWriter();
	bool openFile(char* fileLoca, char* readMode);
	bool putline(char* data);
	~FileWriter();
};