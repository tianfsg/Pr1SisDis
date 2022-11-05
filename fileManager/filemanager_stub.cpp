#include "filemanager_stub.h"
#include "utils.h"

#define PORT 40000
#define IP_SERVER "172.31.70.156"

//Hacer archivo de configuración y abrirlo en el constructor para obtener la ip para más nota :D
FileManager::FileManager(string path){
	
	this->dirPath=path;
	this->serverId = initClient((char*)IP_SERVER, PORT);
	
	if(serverId < 0) std::cout<<"ERROR"<<__FILE__<<":"<<__LINE__<<"\n";
}

FileManager::~FileManager(){
	
	int typeOp = OP_END;
	sendMSG(serverId, (const void*)&typeOp, sizeof(int));
	
	closeConnection(serverId);
}

vector<string*>* FileManager::listFiles(){
	
	int typeOp = OP_LISTFILES;
	sendMSG(serverId, (const void*)&typeOp, sizeof(int));

	sendMSG(serverId, (const void*)this->dirPath.c_str(), this->dirPath.length());
	
	int* sizeMsgIn = nullptr;
	int sizeMsgInLen = 0;
	
	std::vector<string*>* vfiles = new vector<string*>();
	recvMSG(serverId, (void**)&sizeMsgIn, &sizeMsgInLen);
	
	int size = sizeMsgIn[0];
	
	void* msgIn = nullptr;
	int msgInLen = 0;
	
	for(int i = 0; i < size; i++){
		recvMSG(serverId, &msgIn, &msgInLen);
		vfiles->push_back(new string((char*)msgIn));
	}
	
	return vfiles;
}

void FileManager::readFile(char* fileName, char* &data, unsigned long int & dataLength){
	
	int typeOp = OP_READFILE;
	sendMSG(serverId, (const void*)&typeOp, sizeof(int));
	
	sendMSG(serverId, (const void*)fileName, sizeof(char)*strlen(fileName));
	sendMSG(serverId, (const void*)&data, dataLength);
	
	recvMSG(serverId, (void**)&data, (int*)&dataLength);
}

void FileManager::freeListedFiles(vector<string*>* fileList){

    for(vector<string*>::iterator i=fileList->begin();i!= fileList->end();++i)
    {
        delete *i;
    }    
	
	int typeOp = OP_FREELISTEDFILES;
	sendMSG(serverId, (const void*)&typeOp, sizeof(int));
	
	delete this;
}

void FileManager::writeFile(char* fileName, char* data, unsigned long int dataLength){
	
	int typeOp = OP_WRITEFILE;
	sendMSG(serverId, (const void*)&typeOp, sizeof(int));
	
	sendMSG(serverId, (const void*)fileName, sizeof(char)*strlen(fileName));
	sendMSG(serverId, (const void*)data, dataLength);
}