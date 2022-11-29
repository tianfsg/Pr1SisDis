#include <iostream>
#include <stdlib.h>
#include <string>
#include "filemanager_stub.h"

using namespace std;

//Función principal cliente
int main(int argc,char** argv)
{
	//Imprimimos un título como cabecera del programa
	std::cout<<"\n"
			 <<"███████╗██╗██╗░░░░░███████╗  ███╗░░░███╗░█████╗░███╗░░██╗░█████╗░░██████╗░███████╗██████╗░\n"
			 <<"██╔════╝██║██║░░░░░██╔════╝  ████╗░████║██╔══██╗████╗░██║██╔══██╗██╔════╝░██╔════╝██╔══██╗\n"
			 <<"█████╗░░██║██║░░░░░█████╗░░  ██╔████╔██║███████║██╔██╗██║███████║██║░░██╗░█████╗░░██████╔╝\n"
			 <<"██╔══╝░░██║██║░░░░░██╔══╝░░  ██║╚██╔╝██║██╔══██║██║╚████║██╔══██║██║░░╚██╗██╔══╝░░██╔══██╗\n"
			 <<"██║░░░░░██║███████╗███████╗  ██║░╚═╝░██║██║░░██║██║░╚███║██║░░██║╚██████╔╝███████╗██║░░██║\n"
			 <<"╚═╝░░░░░╚═╝╚══════╝╚══════╝  ╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═╝░░╚═╝░╚═════╝░╚══════╝╚═╝░░╚═╝\n\n\n\n";
	
	//Iniciamos un nuevo stub que se comunicará con el server
	//El fichero que hay dentro del constructor hay que cambiarlo, yo use ese ya
	//que el server era el que se tenía que conectar a la carpeta compartida y no podía acceder a dirprueba/
	FileManager *fm=new FileManager("../../../../dirprueba_servidor");
	vector<string*>* vfiles=fm->listFiles();
	bool salida = false;
	string comando;
	char* data=nullptr;
	
	//While que inicia la interfaz tipo terminal linux
	while(salida == false){
		
		char* data=nullptr;
		unsigned long int fileLen=0;
		
		std::cout<<"usuario@usuario-fileManager:~$ ";
		std::cin>>comando;
		
		//Opción que lista los ficheros del directorio del server
		if(comando == "ls"){
			
			cout<<"Lista de ficheros en el directorio de prueba:\n";
			for(unsigned int i=0;i<vfiles->size();++i)
			{
				cout<<"Fichero: "<<vfiles->at(i)->c_str()<<endl;
			}
		}
		//Opción para enviar información que se quiere que se implemente en el directorio del server
		else if(comando == "Upload"){
			
			string readFile;
			
			std::cout<<"Introduzca el fichero del que quiere leer: ";
			std::cin>>readFile;
			
			readFile = "dirprueba_cliente/" + readFile;
			
			FILE* testFile = fopen(readFile.c_str(),"r");
			
			fseek(testFile, 0L, SEEK_END);
			fileLen = ftell(testFile);
			fseek(testFile, 0L, SEEK_SET);
			data = new char[fileLen];
			fread(data,fileLen,1,testFile);
			fclose(testFile);
			
			string fichero;
			
			cout<<"Introduzca el fichero donde se va a escribir: ";
			cin>>fichero;
			
			cout<<"Escribiendo en "<<fichero<<" del directorio de prueba:\n";
			fm->writeFile((char*)fichero.c_str(),data,fileLen);
		
		}
		//Opción para obterner información del directorio del server
		else if(comando == "Download"){
			
			string fichero;
			string writeFile;
			
			cout<<"Introduzca el fichero que quiere leer: ";
			cin>>fichero;
			
			std::cout<<"Introduzca el fichero donde lo quiere escribir: ";
			std::cin>>writeFile;
			
			writeFile = "dirprueba_cliente/" + writeFile;
			
			for(int i = 0; i < vfiles->size(); i++){
				if(fichero == *(vfiles->at(i))){
					cout<<"Leyendo "<<*(vfiles->at(i))<<" del directorio de prueba:\n";
					fm->readFile(&(*(vfiles->at(i)))[0],data,fileLen);
					
					FILE* testFile = fopen(writeFile.c_str(), "w");
					fwrite(data,fileLen,1,testFile);
					fclose(testFile);
					
					break;
				}
			}
			
		}
		//Opción que limpia la pantalla
		else if(comando == "clear"){
			
			system("clear");
			
		}
		//opción para salir del menú
		else if(comando == "exit"){
			
			break;
			
		}
		
		delete[] data;
		
	}

	//Liberamos el vector a punteros de strings y el stub
    cout<<"Liberando lista de ficheros:\n";
    fm->freeListedFiles(vfiles);
    cout<<"Liberando datos de fichero leído:\n";

    return 0;
}
