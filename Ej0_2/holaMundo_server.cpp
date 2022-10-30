#include "holaMundo_server.h"
#include "serialize.hpp"
#include "utils.h"
#include <vector>


using namespace std;

HolaMundo_imp::HolaMundo_imp(int clientId)
{
    this->clientId = clientId;
    if (clientId < 0)
        std::cout << "ERROR " << __FILE__ << ":" << __LINE__ << "\n";
    hm = new HolaMundo();
}
HolaMundo_imp::~HolaMundo_imp()
{
    delete hm;
    closeConnection(clientId);
}

void HolaMundo_imp::recibeSuma(){
    int *recvBuffA = nullptr;
    int *recvBuffB = nullptr;
    int recvBuffSize = 0;

    recvMSG(clientId, (void **)&recvBuffA, &recvBuffSize);
    recvMSG(clientId, (void **)&recvBuffB, &recvBuffSize);
    int result = hm->suma(recvBuffA[0], recvBuffB[0]);
    sendMSG(clientId, (const void *)&result, sizeof(int));

    delete[] recvBuffA;
    delete[] recvBuffB;
}
void HolaMundo_imp::recibeMultVector(){
    byte * recvBuff = nullptr;
    int recvBuffSize = 0;

    recvMSG(clientId, (void**) &recvBuff, &recvBuffSize);
    vector<byte> * v1s = new vector<byte>(recvBuff, recvBuffSize+recvBuff);

    vector<int>* v1 = deserializeVector<int>(v1s, t_int);
    delete v1s;
    delete[] recvBuff;

    recvMSG(clientId, (void**) &recvBuff, &recvBuffSize);
    vector<byte> * v2s = new vector<byte>(recvBuff, recvBuffSize+recvBuff);

    vector<int>* v2 = deserializeVector<int>(v2s, t_int);
    delete v2s;
    delete[] recvBuff;

    int res = hm->multVector(v1,v2);

    sendMSG(clientId, (const void*)&res, sizeof(int));
    delete v1,v2;
    
}

void HolaMundo_imp :: recibeLeeFichero(){
    byte * recvBuff = nullptr;
    int recvBuffSize = 0;

    recvMSG(clientId, (void**) &recvBuff, &recvBuffSize);
    string * fileName = new string(recvBuff);
    string * content = hm->leeFichero(fileName);
    sendMSG(clientId, (const void * ) content->c_str(), content->length());

    delete [] recvBuff;
    delete content;
    delete fileName;
    
}


void HolaMundo_imp::recvOp()
{
    int* typeOP = nullptr;
    int typeOPSize = 0;

    recvMSG(clientId, (void**) &typeOP, &typeOPSize);
    do{
        switch(typeOP[0]){
            case OP_END:
                cout << "Cliente desconecta" << endl;
                break;
            case OP_SUMA:
                recibeSuma();
                break;
            case OP_MULTVECT:
                recibeMultVector();
                break;
            case OP_PRINTMSG:
                break;
            case OP_LEEFICH:
                recibeLeeFichero();
                break;
            default:
                cout << "ERROR: " << typeOP[0] << endl;
                break;
        }
    }while(typeOP[0] != OP_END);

    if(typeOP!= nullptr) delete[] typeOP;
    recvMSG(clientId, (void**)&typeOP, &typeOPSize);

}