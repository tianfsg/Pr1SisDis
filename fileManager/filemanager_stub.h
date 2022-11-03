#pragma once 

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include <dirent.h>

#define OP_LISTFILES 0
#define OP_READFILE 1
#define OP_WRITEFILE 2
#define OP_FREELISTEDFILES 3
#define OP_END 4

using namespace std;

class FileManager{
	
	private:
	
		string dirPath;
		int serverId = -1;
	
	public:
		
		FileManager(string path);
		~FileManager();
		vector<string*>* listFiles();
		void readFile(char* fileName, char* &data, unsigned long int & dataLength);
		void writeFile(char* fileName, char* data, unsigned long int dataLength);
		void freeListedFiles(vector<string*>* fileList);
	
};