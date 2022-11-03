#include "filemanager_imp.h"
#include "utils.h"

FileManager_imp::FileManager_imp(int clientId){
	
	this->clientId = clientId;
	
	if(clientId < 0) std::cout<<"ERROR"<<__FILE__<<":"<<__LINE__<<"\n";
}

FileManager_imp::~FileManager_imp(){
	
	closeConnection(clientId);
}

void FileManager_imp::recieveListFiles(){
	
	char* recvBuffDir = nullptr;
	int recvBuffSize = 0;
	
	recvMSG(clientId, (void**)&recvBuffDir, &recvBuffSize);
	
	this->fm = new FileManager(recvBuffDir);
	
	vfiles=fm->listFiles();
	
	int size = vfiles->size();
	
	sendMSG(clientId, (const void*)&size, sizeof(int));
	
	for(int i = 0; i < size; i++)
		sendMSG(clientId, (const void*) vfiles->at(i)->c_str(), vfiles->at(i)->length()+1);
	
	delete[] recvBuffDir;
}

void FileManager_imp::recieveReadFile(){

	char* recvBuffFile = nullptr;
	char* recvBuffData = nullptr;
	int recvBuffFileSize = 0;
	unsigned long int recvBuffDataSize = 0;
	
	recvMSG(clientId, (void**)&recvBuffFile, &recvBuffFileSize);
	recvMSG(clientId, (void**)&recvBuffData, (int*)&recvBuffDataSize);
	
	fm->readFile(recvBuffFile, recvBuffData, recvBuffDataSize);
}

void FileManager_imp::recieveFreeListedFiles(){
	
	fm->freeListedFiles(this->vfiles);
}

void FileManager_imp::recieveWriteFile(){
	
	
	char* recvBuffFile = nullptr;
	char* recvBuffData = nullptr;
	int recvBuffFileSize = 0;
	unsigned long int recvBuffDataSize = 0;
	
	recvMSG(clientId, (void**)&recvBuffFile, &recvBuffFileSize);
	recvMSG(clientId, (void**)&recvBuffData, (int*)&recvBuffDataSize);
	
	fm->writeFile(recvBuffFile, recvBuffData, recvBuffDataSize);
}

void FileManager_imp::recvOp(){
	
	int* typeOP = nullptr;
	int typeOpSize = 0;
	
	do{
	
		if(typeOP != nullptr) delete[] typeOP;
		recvMSG(clientId, (void**)&typeOP, &typeOpSize);
		
		switch(typeOP[0]){
			
			case OP_LISTFILES:
				recieveListFiles();
			break;
			
			case OP_READFILE:
				recieveReadFile();
			break;
			
			case OP_WRITEFILE:
				recieveWriteFile();
			break;
			
			case OP_FREELISTEDFILES:
				recieveFreeListedFiles();
			break;
			
			case OP_END:
				std::cout<<"Cliente desconecta\n";
			break;
			
			default:
				std::cout<<"ERROR: "<<__FILE__<<": "<<"Tipo operación: "<<typeOP[0]<<" no válido\n";
			break;
		}
	}while(typeOP[0] != OP_END);
	
	if(typeOP != nullptr) delete[] typeOP;
}