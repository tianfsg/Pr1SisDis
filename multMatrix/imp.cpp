#include <iostream>
#include "Imp.h"

using namespace std;

Imp :: Imp(int clientId){

    this->clientId = clientId;
    if(clientId < 0){
        cout << "ERROR " << __FILE__ << ":" << __LINE__ << "\n";
    }
    imp = new multMatrix();
}
Imp :: ~Imp(){}
void Imp :: recvOp(){}