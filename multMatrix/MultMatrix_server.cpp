#include "MultMatrix_server.h"
#include "utils.h"

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
    sendMSG(clientId, (const void *)&result->rows, sizeof(int));
    sendMSG(clientId, (const void *)&result->cols, sizeof(int));
    sendMSG(clientId, (const void *)&result->data, sizeof(int*));

    delete[] fileName;
}

void MultMatrix_imp :: multiMatrix(){

    int * buff = nullptr;
    int recvBuffSize = 0;

    matrix_t * m1 = new matrix_t();
    matrix_t * m2 = new matrix_t();

    //recibimos M1
    recvMSG(clientId, (void **)&buff, &recvBuffSize);
    m1->rows = buff[0];
    recvMSG(clientId, (void **)&buff, &recvBuffSize);
    m1->cols = buff[0];
    recvMSG(clientId, (void **)&buff, &recvBuffSize);
    m1->data = &buff[0];

    //recibimos M2
    recvMSG(clientId, (void **)&buff, &recvBuffSize);
    m2->rows = buff[0];
    recvMSG(clientId, (void **)&buff, &recvBuffSize);
    m2->cols = buff[0];
    recvMSG(clientId, (void **)&buff, &recvBuffSize);
    m2->data = &buff[0];


    matrix_t * m3 = mmi->multMatrices(m1,m2);

    delete m1;
    delete m2;
    
    //Enviamos M3
    sendMSG(clientId, (const void *)&m3->data, sizeof(int*));

    delete m3;
}
void MultMatrix_imp :: schreibeMatrix(){

    //Creamos la matrix y nombre del fichero
    matrix_t * m = new matrix_t();

    const char *fileName = nullptr;

    int * buff = nullptr;
    int recvBuffSize = 0;

    //recibimos la informacion
    recvMSG(clientId, (void **)&buff, &recvBuffSize);
    m->rows = buff[0];
    recvMSG(clientId, (void **)&buff, &recvBuffSize);
    m->cols = buff[0];
    recvMSG(clientId, (void **)&buff, &recvBuffSize);
    m->data = &buff[0];
    recvMSG(clientId, (void **)&fileName, &recvBuffSize);

    mmi->writeMatrix(m, &fileName[0]);

    cout << "Matrix satisfactoriamente guardada." << endl;
    
    delete m;
    delete [] fileName;
    delete [] buff;
}

void MultMatrix_imp :: identityMatrix(){

    matrix_t * m = nullptr;
    int * rows = nullptr, * cols = nullptr;
    int recvBuffSize = 0;

    //Recibimos las dimensiones
    recvMSG(clientId, (void **)&rows, &recvBuffSize);
    recvMSG(clientId, (void **)&cols, &recvBuffSize);

    m = mmi->createIdentity(rows[0],cols[0]);

    sendMSG(clientId, (const void *)&m->data, sizeof(int*));
    
    delete []rows;
    delete [] cols;
    delete [] m;
}

void MultMatrix_imp :: randomMatrix(){

    matrix_t * m = nullptr;
    int * rows = nullptr, * cols = nullptr;
    int recvBuffSize = 0;

    //Recibimos las dimensiones
    recvMSG(clientId, (void **)&rows, &recvBuffSize);
    recvMSG(clientId, (void **)&cols, &recvBuffSize);

    m = mmi->createRandMatrix(rows[0],cols[0]);

    sendMSG(clientId, (const void *)&m->data, sizeof(int*));

    delete []rows;
    delete [] cols;
    delete [] m;
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
                multiMatrix();
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