#include <iostream>
#include "utils.h"
#include "multmatrix.h"
#include "MultMatrix_server.h"

using namespace std;

MultMatrix_imp :: MultMatrix_imp(int clientId){

    this->clientId = clientId;
    if(clientId < 0){
        cout << "ERROR " << __FILE__ << ":" << __LINE__ << "\n";
    }
    mmi = new multMatrix();
}
MultMatrix_imp :: ~MultMatrix_imp(){
    delete mmi;
    closeConnection(clientId);
}

void MultMatrix_imp :: leerMatrix(){
    const char *fileName = nullptr;
    int recvBuffSize = 0;

    recvMSG(clientId, (void **)&fileName, &recvBuffSize);
    matrix_t * result = mmi->readMatrix(fileName);

    //Enviamos la matrix
    sendMSG(clientId, (const void *)result->rows, sizeof(int));
    sendMSG(clientId, (const void *)result->cols, sizeof(int));
    sendMSG(clientId, (const void *)result->data, sizeof(int*));

    delete[] fileName;
}

void MultMatrix_imp :: multMatrix(){

    matrix_t * m1, * m2, * m3;
    int recvBuffSize = 0;

    //recibimos M1
    recvMSG(clientId, (void **)m1->rows, &recvBuffSize);
    recvMSG(clientId, (void **)m1->cols, &recvBuffSize);
    recvMSG(clientId, (void **)m1->data, &recvBuffSize);

    //recibimos M2
    recvMSG(clientId, (void **)m2->rows, &recvBuffSize);
    recvMSG(clientId, (void **)m2->cols, &recvBuffSize);
    recvMSG(clientId, (void **)m2->data, &recvBuffSize);

    m3 = mmi->multMatrices(m1,m2);

    delete[] m1;
    delete[] m2;
    
    //Enviamos M3
    sendMSG(clientId, (const void *)m3->data, sizeof(int*));

    delete[] m3;
}
void MultMatrix_imp :: schreibeMatrix(){

    //Creamos la matrix y nombre del fichero
    matrix_t * m;
    const char *fileName = nullptr;
    
    int recvBuffSize = 0;

    //recibimos la informacion
    recvMSG(clientId, (void **)m->rows, &recvBuffSize);
    recvMSG(clientId, (void **)m->cols, &recvBuffSize);
    recvMSG(clientId, (void **)m->data, &recvBuffSize);
    recvMSG(clientId, (void **)&fileName, &recvBuffSize);

    mmi->writeMatrix(m, fileName);

    cout << "Matrix satisfactoriamente guardada." << endl;
    
    delete [] m;
    delete [] fileName;
}

void MultMatrix_imp :: identityMatrix(){

    int rows, cols;
    int * data;
    int recvBuffSize = 0;

    //Recibimos las dimensiones
    recvMSG(clientId, (void **)&rows, &recvBuffSize);
    recvMSG(clientId, (void **)&cols, &recvBuffSize);

    data = mmi->createIdentity(rows,cols);

    sendMSG(clientId, (const void *)data, sizeof(int*));

    delete[] data;
}

void MultMatrix_imp :: randomMatrix(){

    int rows, cols;
    int * data;
    int recvBuffSize = 0;

    //Recibimos las dimensiones
    recvMSG(clientId, (void **)&rows, &recvBuffSize);
    recvMSG(clientId, (void **)&cols, &recvBuffSize);

    data = mmi->createRandMatrix(rows,cols);

    sendMSG(clientId, (const void *)data, sizeof(int*));

    delete[] data;
}


void MultMatrix_imp :: recvOp(){
    
    int * typeOP = nullptr;
    int typeOPsize = 0;

    recvMSG(clientId, (void**) &typeOP, &typeOPsize);
    do{
        switch (typeOP[0]){
            case OP_END:
                cout << "Cliente desconecta" << endl;
                break;
            case OP_READ:
                leerMatrix();
                break;
            case OP_MULT:
                multMatrix();
                break;
            case OP_SCHREIBE:
                schreibeMatrix();
                break;
            case OP_IDENTITY:
                identityMatrix();
                break;
            case OP_RAND:
                randomMatrix();
                break;
            default:
                break;
        }
    }while(typeOP[0] != OP_END);

    if(typeOP!= nullptr) delete[] typeOP;
    recvMSG(clientId, (void**)&typeOP, &typeOPsize);

}