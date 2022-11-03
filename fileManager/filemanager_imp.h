#pragma once

#include "filemanager.h"

#define OP_LISTFILES 0
#define OP_READFILE 1
#define OP_WRITEFILE 2
#define OP_FREELISTEDFILES 3
#define OP_END 4


class FileManager_imp{
	
	private:
	
		FileManager* fm = nullptr;
		vector<string*>* vfiles = nullptr;
		int clientId = -1;
		
		void recieveListFiles();
		void recieveReadFile();
		void recieveWriteFile();
		void recieveFreeListedFiles();
		
	public:
	
		FileManager_imp(int clientId);
		~FileManager_imp();
		
		void recvOp();
};