#include "holaMundo_stub.h"
#include <string>
#include <cstring>
using namespace std;

int main(int argc, char **argv)
{

    int a = 12;
    int b = 13;
    int result = 0;
    HolaMundo *hm = new HolaMundo();
    result = hm->suma(a, b);

    string msg = "hola server \n";

    hm->printMSG(&msg);
    std::cout << "Resultado: " << result << "\n";

    vector<int>* v1 = new vector<int>();
    vector<int>* v2 = new vector<int>();

    for(int i = 0; i < 5; i++){
        v1->push_back(i);
        v2->push_back(i);        
    }

    int res3 = hm->multVector(v1,v2);
    cout << "Resultado 3: " << res3 << endl;
    

    delete v1;
    delete v2;

    string * fileName = new string("/home/ubuntu/hola.txt");
    string * fileContent = hm->leeFichero(fileName);
    cout << "contenido:  " << *(fileContent) << endl;

    delete fileName;
    delete fileContent;

    delete hm;


    return 0;
}