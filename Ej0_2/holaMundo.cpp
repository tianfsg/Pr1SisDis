#include "holaMundo.h"
using namespace std;
HolaMundo::HolaMundo()
{
}
HolaMundo::~HolaMundo()
{
}
int HolaMundo::suma(int a, int b)
{
    return a + b;
}
void HolaMundo::printMSG(string * msg){
    cout << *msg << endl;
    // devolver los mensaje a traves de un array para que el cliente pueda leerlos
}
int HolaMundo::multVector(vector<int> * v1, vector<int>* v2){
    int res = 0;
    for(int i = 0; i < v1->size(); i++){
        res += v1->at(i)*v2->at(i);
    }
    return res;
}

string* HolaMundo :: leeFichero(string* FileName){


    FILE * f = fopen(FileName->c_str(), "r");
    char * fileContent = nullptr;
    int fileContentSize = 0;

    fseek(f, 0, SEEK_END);
    fileContentSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    fileContent = new char[fileContentSize+1];

    fread(fileContent, sizeof(char), fileContentSize, f);

    string * str = new string(fileContent);

    delete [] fileContent;
    return str;
}