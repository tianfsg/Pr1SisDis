#include <iostream>
#include <stdlib.h>
#include <string>
#include "filemanager_stub.h"

using namespace std;

int main(int argc,char** argv)
{
	
	std::cout<<"\n"
			 <<"███████╗██╗██╗░░░░░███████╗  ███╗░░░███╗░█████╗░███╗░░██╗░█████╗░░██████╗░███████╗██████╗░\n"
			 <<"██╔════╝██║██║░░░░░██╔════╝  ████╗░████║██╔══██╗████╗░██║██╔══██╗██╔════╝░██╔════╝██╔══██╗\n"
			 <<"█████╗░░██║██║░░░░░█████╗░░  ██╔████╔██║███████║██╔██╗██║███████║██║░░██╗░█████╗░░██████╔╝\n"
			 <<"██╔══╝░░██║██║░░░░░██╔══╝░░  ██║╚██╔╝██║██╔══██║██║╚████║██╔══██║██║░░╚██╗██╔══╝░░██╔══██╗\n"
			 <<"██║░░░░░██║███████╗███████╗  ██║░╚═╝░██║██║░░██║██║░╚███║██║░░██║╚██████╔╝███████╗██║░░██║\n"
			 <<"╚═╝░░░░░╚═╝╚══════╝╚══════╝  ╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═╝░░╚═╝░╚═════╝░╚══════╝╚═╝░░╚═╝\n\n\n\n";
		
	FileManager *fm=new FileManager("../../../../dirprueba2/");
	vector<string*>* vfiles=fm->listFiles();
	bool salida = false;
	string comando;
	
	while(salida == false){
		
		char* data=nullptr;
		unsigned long int fileLen=0;
		
		std::cout<<"usuario@usuario-fileManager:~$ ";
		std::cin>>comando;
		
		if(comando == "ls"){
			
			cout<<"Lista de ficheros en el directorio de prueba:\n";
			for(unsigned int i=0;i<vfiles->size();++i)
			{
				cout<<"Fichero: "<<vfiles->at(i)->c_str()<<endl;
			}
		}
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
		else if(comando == "clear"){
			
			system("clear");
			
		}
		else if(comando == "exit"){
			
			break;
			
		}
		
		delete[] data;
		
	}

    cout<<"Liberando lista de ficheros:\n";
    fm->freeListedFiles(vfiles);
    cout<<"Liberando datos de fichero leído:\n";

    return 0;
}