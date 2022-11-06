#include "filemanager_imp.h"
#include "utils.h"

#define PORT 40000

//Función para iniciar un hilo asignado a un cliente
void clientThread(int clientId){
	FileManager_imp* fmi = new FileManager_imp(clientId);
			
	fmi->recvOp();
	delete fmi;
}

//Función principal server
int main(int argc, char** arg){
	
	//Inicia el servidor
	int serverId = initServer(PORT);
	
	//Bucle infinito para esperar peticiones de nuevos clientes
	while(1){
		
		if(checkNewConnections()){
			int clientId = getNewConnection();
			std::thread*th = new std::thread(clientThread, clientId);
		}
		
		usleep(100);
	}
	return 0;
}