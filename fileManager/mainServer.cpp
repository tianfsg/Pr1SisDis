#include "filemanager_imp.h"
#include "utils.h"

#define PORT 40000

void clientThread(int clientId){
	FileManager_imp* fmi = new FileManager_imp(clientId);
			
	fmi->recvOp();
	delete fmi;
}

int main(int argc, char** arg){
	
	int serverId = initServer(PORT);
	
	while(1){
		
		if(checkNewConnections()){
			int clientId = getNewConnection();
			std::thread*th = new std::thread(clientThread, clientId);
		}
		
		usleep(100);
	}
	return 0;
}