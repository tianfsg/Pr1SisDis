#include "MultMatrix_server.h"
#include "utils.h"

using namespace std;

MultMatrix_imp :: MultMatrix_imp(int clientId){
    cout << "Solicitud para conexion..." << endl;
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

    cout << "OPERACION *READ* | (SERVER)" << endl;

    const char *fileName = nullptr;
    int recvBuffSize = 0;

    recvMSG(clientId, (void **)&fileName, &recvBuffSize);

    matrix_t * m = mmi->readMatrix(fileName);

    // for(int i = 0; i < m->cols * m->rows; i++){
    //     cout << m->data[i] << endl;
    // }

    //Enviamos la matrix
    sendMSG(clientId, (const void *)&m->rows, sizeof(int));
    sendMSG(clientId, (const void *)&m->cols, sizeof(int));
    sendMSG(clientId, (const void *)m->data, sizeof(int*) * (m->cols * m->rows));
    cout << "INFORMACION LEIDA ENVIADA | (SERVER)" << endl;

    delete[] fileName;
}

void MultMatrix_imp :: multiMatrix(){

    cout << "OPERACION *MULT* | (SERVER)" << endl;

    int * recvRows = nullptr, * recvCols = nullptr, * recvData = nullptr;
    int * recvRows2 = nullptr, * recvCols2 = nullptr, * recvData2 = nullptr;

    int recvBuffSize = 0;

    //recibimos M1
    recvMSG(clientId, (void **)&recvRows, &recvBuffSize);
    recvMSG(clientId, (void **)&recvCols, &recvBuffSize);
    recvMSG(clientId, (void **)&recvData, &recvBuffSize);
    
    matrix_t * m1 = new matrix_t();
    m1->rows = recvRows[0];
    m1->cols = recvCols[0];
    m1->data = recvData;

    //recibimos M2
    recvMSG(clientId, (void **)&recvRows2, &recvBuffSize);
    recvMSG(clientId, (void **)&recvCols2, &recvBuffSize);
    recvMSG(clientId, (void **)&recvData2, &recvBuffSize);

    matrix_t * m2 = new matrix_t();
    m2->rows = recvRows2[0];
    m2->cols = recvCols2[0];
    m2->data = recvData2;

    matrix_t * m3 = mmi->multMatrices(m1,m2);

    delete m1;
    delete m2;
    
    sendMSG(clientId, (const void *)m3->data, sizeof(int*) * (m3->cols * m3->rows));
    cout << "INFORMACION ENVIADA | (SERVER)" << endl;

    delete m3;    
    delete [] recvData;
    delete [] recvRows;
    delete [] recvCols;
    delete [] recvData2;
    delete [] recvRows2;
    delete [] recvCols2;

}
void MultMatrix_imp :: schreibeMatrix(){

    cout << "OPERACION SCHREIBE | (SERVER)" << endl;

    //Variables para recibir la informacion
    const char *fileName = nullptr;

    int * recvRows = nullptr, * recvCols = nullptr, * recvData = nullptr;
    int recvBuffSize = 0;

    //recibimos la informacion
    recvMSG(clientId, (void **)&recvRows, &recvBuffSize);
    recvMSG(clientId, (void **)&recvCols, &recvBuffSize);
    recvMSG(clientId, (void **)&recvData, &recvBuffSize);
    recvMSG(clientId, (void **)&fileName, &recvBuffSize);
    
    //Creamos la matrix
    matrix_t * m = new matrix_t();
    m->rows = recvRows[0];
    m->cols = recvCols[0];
    m->data = recvData;

    // for(int i = 0; i < m->cols * m->rows; i++){
    //     cout << m->data[i] << endl;
    // }

    mmi->writeMatrix(m, fileName);

    cout << "MATRIX ALMACENADA EN " << fileName << " | (SERVER)" << endl;
    delete m;
    delete [] fileName;
    delete [] recvData;
    delete [] recvRows;
    delete [] recvCols;
}

void MultMatrix_imp :: identityMatrix(){

    cout << "OPERACION IDENTITY | (SERVER)" << endl;

    int * recvRows = nullptr, * recvCols = nullptr;
    int recvBuffSize = 0;

    //Recibimos las dimensiones
    recvMSG(clientId, (void **)&recvRows, &recvBuffSize);
    recvMSG(clientId, (void **)&recvCols, &recvBuffSize);

    matrix_t * m = nullptr;
    m = mmi->createIdentity(recvRows[0],recvCols[0]);
    
    // for(int i = 0; i < m->cols * m->rows; i++){
    //     cout << m->data[i] << endl;
    // }

    sendMSG(clientId, (const void *)m->data, sizeof(int*) * (recvRows[0] * recvCols[0]));
    cout << "INFORMACION ENVIADA | (SERVER)" << endl;

    delete [] m;
    delete [] recvRows;
    delete [] recvCols;
}

void MultMatrix_imp :: randomMatrix(){

    cout << "OPERACION RAND | (SERVER)" << endl;
    
    int * recvRows = nullptr, * recvCols = nullptr;
    int recvBuffSize = 0;

    //Recibimos las dimensiones
    recvMSG(clientId, (void **)&recvRows, &recvBuffSize);
    recvMSG(clientId, (void **)&recvCols, &recvBuffSize);
   
    matrix_t * m = nullptr;
    m = mmi->createRandMatrix(recvRows[0],recvCols[0]);
    
    // for(int i = 0; i < m->cols * m->rows; i++){
    //     cout << m->data[i] << endl;
    // }
    
    sendMSG(clientId, (const void *)m->data, sizeof(int*) * (recvRows[0] * recvCols[0]));
    cout << "INFORMACION ENVIADA | (SERVER)" << endl;
    
    delete [] m;
    delete [] recvRows;
    delete [] recvCols;
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
                mmi->~multMatrix();
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