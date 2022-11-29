#include "filemanager_imp.h"
#include "utils.h"

//Constructor por parámetro
FileManager_imp::FileManager_imp(int clientId){
	
	this->clientId = clientId;
	
	if(clientId < 0) std::cout<<"ERROR"<<__FILE__<<":"<<__LINE__<<"\n";
}

//Destructor
FileManager_imp::~FileManager_imp(){
	
	closeConnection(clientId);
}

//Función que recibe la operación para ejecutar la función listFiles
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

//Función que recibe la operación para ejecutar la función readFile
void FileManager_imp::recieveReadFile(){

	char* recvBuffFile = nullptr;
	char* recvBuffData = nullptr;
	int recvBuffFileSize = 0;
	unsigned long int recvBuffDataSize = 0;
	
	//Recibe una dirección de memoria dónde guardar la información que se lea del fichero
	recvMSG(clientId, (void**)&recvBuffFile, &recvBuffFileSize);
	cout<<recvBuffFile<<endl;
	recvMSG(clientId, (void**)&recvBuffData, (int*)&recvBuffDataSize);
	
	fm->readFile(recvBuffFile, recvBuffData, recvBuffDataSize);
	
	//Devuelve la dirección de memoria ya con la información leída
	sendMSG(clientId, (const void*)recvBuffData, recvBuffDataSize);
	
	delete[] recvBuffFile;
	delete[] recvBuffData;
}

//Función que recibe la operación para ejecutar la función freeListedFiles
void FileManager_imp::recieveFreeListedFiles(){
	
	fm->freeListedFiles(this->vfiles);
}

//Función que recibe la operación para ejecutar la función writeFile
void FileManager_imp::recieveWriteFile(){
	
	
	char* recvBuffFile = nullptr;
	char* recvBuffData = nullptr;
	int recvBuffFileSize = 0;
	unsigned long int recvBuffDataSize = 0;
	
	//Recibe la información para escribirla en el fichero
	recvMSG(clientId, (void**)&recvBuffFile, &recvBuffFileSize);
	recvMSG(clientId, (void**)&recvBuffData, (int*)&recvBuffDataSize);
	
	fm->writeFile(recvBuffFile, recvBuffData, recvBuffDataSize);
	
	delete[] recvBuffFile;
	delete[] recvBuffData;
}

//Función que recibe el tipo de operación para saber cual tiene que ejecutar en el server
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