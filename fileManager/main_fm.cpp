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
	FileManager *fm=new FileManager("dirprueba/");
	vector<string*>* vfiles=fm->listFiles();
	bool salida = false;
	string comando;
	
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
			
			FILE* testFile = fopen("data.txt","r");
			
			fseek(testFile, 0L, SEEK_END);
			fileLen = ftell(testFile);
			fseek(testFile, 0L, SEEK_SET);
			data = new char[fileLen];
			fread(data,fileLen,1,testFile);
			
			string fichero;
			
			cout<<"Introduzca el fichero donde se va a escribir: ";
			cin>>fichero;
			
			for(int i = 0; i < vfiles->size(); i++){
				if(fichero == *(vfiles->at(i))){
					cout<<"Escribiendo en "<<fichero<<" del directorio de prueba:\n";
					fm->writeFile(&(*(vfiles->at(i)))[0],data,fileLen);
					break;
				}
			}
		}
		//Opción para obterner información del directorio del server
		else if(comando == "Download"){
			
			string fichero;
			
			cout<<"Introduzca el fichero que quiere leer: ";
			cin>>fichero;
			
			for(int i = 0; i < vfiles->size(); i++){
				if(fichero == *(vfiles->at(i))){
					cout<<"Leyendo "<<fichero<<" del directorio de prueba:\n";
					fm->readFile(&(*(vfiles->at(i)))[0],data,fileLen);
					cout<<data<<"\n";
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