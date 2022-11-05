#include "MultMatrix_server.h"
#include "utils.h"

using namespace std;

MultMatrix_imp :: MultMatrix_imp(int clientId){
    cout << "Solicitando conexion..." << endl;
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

    cout << "OPERACION READ | (SERVER)" << endl;

    const char *fileName = nullptr;
    int recvBuffSize = 0;

    recvMSG(clientId, (void **)&fileName, &recvBuffSize);

    matrix_t * result = mmi->readMatrix(fileName);

    //Enviamos la matrix
    sendMSG(clientId, (const void *)&result->rows, sizeof(int));
    sendMSG(clientId, (const void *)&result->cols, sizeof(int));
    sendMSG(clientId, (const void *)&result->data, sizeof(int*));
    cout << "ENVIANDO INFORMACION LEIDA| (SERVER)" << endl;

    delete[] fileName;
}

void MultMatrix_imp :: multiMatrix(){

    cout << "OPERACION MULT | (SERVER)" << endl;

    matrix_t * m1 = new matrix_t();
    matrix_t * m2 = new matrix_t();
    int * recvRows = nullptr, * recvCols = nullptr, * recvData = nullptr;
    int recvBuffSize = 0;

    //recibimos M1
    recvMSG(clientId, (void **)&recvRows, &recvBuffSize);
    recvMSG(clientId, (void **)&recvCols, &recvBuffSize);
    recvMSG(clientId, (void **)&recvData, &recvBuffSize);
    
    m1->rows = recvRows[0];
    m1->cols = recvCols[0];
    m1->data = recvData;

    //recibimos M2
    recvMSG(clientId, (void **)&recvRows, &recvBuffSize);
    recvMSG(clientId, (void **)&recvCols, &recvBuffSize);
    recvMSG(clientId, (void **)&recvData, &recvBuffSize);

    m2->rows = recvRows[0];
    m2->cols = recvCols[0];
    m2->data = recvData;

    delete [] recvData;
    delete [] recvRows;
    delete [] recvCols;

    cout << "MATRIX 1" << endl << endl;
    cout << m1->rows << " : ROWS " << endl; 
    cout << m1->cols << " : COLS " << endl;

    cout << "MATRIX 2" << endl << endl;
    cout << m2->rows << " : ROWS " << endl; 
    cout << m2->cols << " : COLS " << endl;

    matrix_t * m3 = mmi->multMatrices(m1,m2);

    delete m1;
    delete m2;
    
    cout << "ENVIANDO INFORMACION | (SERVER)" << endl;
    sendMSG(clientId, (const void *)&m3->data, sizeof(int*));

    delete m3;
}
void MultMatrix_imp :: schreibeMatrix(){

    cout << "OPERACION SCHREIBE | (SERVER)" << endl;

    //Creamos la matrix y nombre del fichero
    matrix_t * m = new matrix_t();

    const char *fileName = nullptr;

    int * recvRows = nullptr, * recvCols = nullptr, * recvData = nullptr;
    int recvBuffSize = 0;

    //recibimos la informacion
    recvMSG(clientId, (void **)&recvRows, &recvBuffSize);
    recvMSG(clientId, (void **)&recvCols, &recvBuffSize);
    recvMSG(clientId, (void **)&recvData, &recvBuffSize);
    recvMSG(clientId, (void **)&fileName, &recvBuffSize);



    m->rows = recvRows[0];
    m->cols = recvCols[0];
    m->data = recvData;

    delete [] recvData;
    delete [] recvRows;
    delete [] recvCols;

    mmi->writeMatrix(m, fileName);

    cout << "MATRIX GUARDADA EN ALMACENAMIENTO." << endl;
    
    delete m;
    delete [] fileName;
}

void MultMatrix_imp :: identityMatrix(){

    cout << "OPERACION IDENTITY | (SERVER)" << endl;
    matrix_t * m = nullptr;
    int * recvRows = nullptr, * recvCols = nullptr;
    int recvBuffSize = 0;

    //Recibimos las dimensiones
    recvMSG(clientId, (void **)&recvRows, &recvBuffSize);
    recvMSG(clientId, (void **)&recvCols, &recvBuffSize);

    m = mmi->createIdentity(recvRows[0],recvCols[0]);
    
    delete [] recvRows;
    delete [] recvCols;

    cout << "ENVIANDO INFORMACION | (SERVER)" << endl;
    sendMSG(clientId, (const void *)&m->data, sizeof(int*));

    delete [] m;
}

void MultMatrix_imp :: randomMatrix(){

    cout << "OPERACION RAND | (SERVER)" << endl;
    matrix_t * m = nullptr;
    int * recvRows = nullptr, * recvCols = nullptr;
    int recvBuffSize = 0;

    //Recibimos las dimensiones
    recvMSG(clientId, (void **)&recvRows, &recvBuffSize);
    recvMSG(clientId, (void **)&recvCols, &recvBuffSize);

    m = mmi->createRandMatrix(recvRows[0],recvCols[0]);
    
    delete [] recvRows;
    delete [] recvCols;

    cout << "ENVIANDO INFORMACION | (SERVER)" << endl;
    sendMSG(clientId, (const void *)&m->data, sizeof(int*));
    
    delete [] m;
}


void MultMatrix_imp :: recvOp(){
    
    int * typeOP = nullptr;
    int typeOPsize = 0;

    do{
        if(typeOP != nullptr) delete[] typeOP;
		recvMSG(clientId, (void**)&typeOP, &typeOPsize);

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
                std::cout<<"ERROR: "<<__FILE__<<": "<<"Tipo operación: "<<typeOP[0]<<" no válido\n";
                break;
        }
    }while(typeOP[0] != OP_END);

	if(typeOP != nullptr) delete[] typeOP;
}