#include "MultMatrix_cliente.h"
#include "utils.h"

using namespace std;
#define PORT 40000
#define IP_SERVER "52.20.216.232"

multMatrix :: multMatrix(){

    serverId = initClient((char *)IP_SERVER, PORT);
    cout << "Estableciendo conexion..... (CLIENTE)" << endl;
    if (serverId < 0)
        std::cout << "ERROR " << __FILE__ << ":" << __LINE__ << "\n";
}
multMatrix :: ~multMatrix(){

    int typeOP = OP_END;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));

    closeConnection(serverId);
}
matrix_t* multMatrix :: readMatrix(const char* fileName){

    //Definimos la operacion y lo enviamos al servidor.
    int typeOP = OP_READ;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));
    size_t sizeFileName = strlen(fileName);
    sendMSG(serverId, (const void*)fileName, sizeFileName);
    cout << "OPERACION *READ* ENVIADA | (CLIENTE)" << endl;

    //reservamos para guardar el contenido
    matrix_t * matrix = new matrix_t();
    
    int * recvRows = nullptr, * recvCols = nullptr, * recvData = nullptr;
    int recvBufferSize = 0;

    recvMSG(serverId, (void **)&recvRows, &recvBufferSize);
    recvMSG(serverId, (void **)&recvCols, &recvBufferSize);
    recvMSG(serverId, (void **)&recvData, &recvBufferSize);

    matrix->rows = recvRows[0];
    matrix->cols = recvCols[0];
    matrix->data = recvData;

    delete [] recvData;
    delete [] recvRows;
    delete [] recvCols;

    cout << "RECIBIENDO INFORMACION DE LA LECTURA | (CLIENTE)" << endl;

    cout << "MATRIX ACTUAL" << endl << endl;
    cout << matrix->rows << " : ROWS " << endl; 
    cout << matrix->cols << " : COLS " << endl << "INFO:" << endl; 
    cout << matrix->data << ": DATA" << endl;

    return matrix;
}
matrix_t * multMatrix :: multMatrices(matrix_t* m1, matrix_t *m2){

    int typeOP = OP_MULT;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));
    cout << "OPERACION *MULT* ENVIADA | (CLIENTE)" << endl;

    matrix_t * matrix = new matrix_t();
    matrix->rows = m1->cols;
    matrix->cols = m2->rows;

    //Enviamos M1
    sendMSG(serverId, (const void *)&m1->rows, sizeof(int));
    sendMSG(serverId, (const void *)&m1->cols, sizeof(int));
    sendMSG(serverId, (const void *)&m1->data, sizeof(int*));
    cout << "ENVIADOS DATOS *rows, cols, data* | (CLIENTE)" << endl;

    //Enviamos M2
    sendMSG(serverId, (const void *)&m2->rows, sizeof(int));
    sendMSG(serverId, (const void *)&m2->cols, sizeof(int));
    sendMSG(serverId, (const void *)&m2->data, sizeof(int*));
    cout << "ENVIADOS DATOS *rows, cols, data* | (CLIENTE)" << endl;

    int * data = nullptr;
    int recvBufferSize = 0;
    recvMSG(serverId, (void **)&data, &recvBufferSize);
    cout << "RECIBIENDO INFORMACION | (CLIENTE)" << endl;

    matrix->data = data;

    cout << "MATRIX ACTUAL" << endl << endl;
    cout << matrix->rows << " : ROWS " << endl; 
    cout << matrix->cols << " : COLS " << endl << "INFO:" << endl; 
    cout << matrix->data << ": DATA" << endl;

    return matrix;
}

void multMatrix :: writeMatrix(matrix_t* m, const char *fileName){

    int typeOP = OP_SCHREIBE;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));
    cout << "OPERACION *WRITE* ENVIADA | (CLIENTE)" << endl;

    //Enviamos matrix
    sendMSG(serverId, (const void *)&m->rows, sizeof(int));
    sendMSG(serverId, (const void *)&m->cols, sizeof(int));
    sendMSG(serverId, (const void *)&m->data, sizeof(int*));
    cout << "ENVIADOS DATOS *rows, cols, data* | (CLIENTE)" << endl;


    //Enviamos file
    size_t sizeFileName = strlen(fileName);
    sendMSG(serverId, (const void*)fileName, sizeFileName);
    cout << "ENVIAMOS ARCHIVO | (CLIENTE)" << endl;
}
matrix_t* multMatrix :: createIdentity(int rows, int cols){

    int typeOP = OP_IDENTITY;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));

    cout << "OPERACION *IDENTITY* ENVIADA | (CLIENTE)" << endl;

    //enviamos las dimensiones
    sendMSG(serverId, (const void *)&rows, sizeof(int));
    sendMSG(serverId, (const void *)&cols, sizeof(int));

    cout << "ENVIADOS DATOS *rows, cols* | (CLIENTE)" << endl;

    //construimos la matrix que vamos a recibir
    matrix_t * matrix = new matrix_t();
    matrix->rows = rows;
    matrix->cols = cols;

    int recvBufferSize = 0;
    recvMSG(serverId, (void **)&matrix->data, &recvBufferSize);
    cout << "RECIBIENDO INFORMACION | (CLIENTE)" << endl;

    cout << "MATRIX ACTUAL" << endl << endl;
    cout << matrix->rows << " : ROWS " << endl; 
    cout << matrix->cols << " : COLS " << endl << "INFO:" << endl; 
    cout << matrix->data << ": DATA" << endl;

    return matrix;
}
matrix_t* multMatrix :: createRandMatrix(int rows, int cols){

    
    int typeOP = OP_RAND;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));

    cout << "OPERACION *RAND* ENVIADA | (CLIENTE)" << endl;

    //enviamos las dimensiones
    sendMSG(serverId, (const void *)&rows, sizeof(int));
    sendMSG(serverId, (const void *)&cols, sizeof(int));

    cout << "ENVIADOS DATOS *rows, cols* | (CLIENTE)" << endl;

    //construimos la matrix que vamos a recibir
    matrix_t * matrix = new matrix_t();
    matrix->rows = rows;
    matrix->cols = cols;


    int * data = nullptr;
    int recvBufferSize = 0;

    recvMSG(serverId, (void **)&matrix->data, &recvBufferSize);
    cout << "RECIBIENDO INFORMACION | (CLIENTE)" << endl;

    cout << "MATRIX ACTUAL" << endl << endl;
    cout << matrix->rows << " : ROWS " << endl; 
    cout << matrix->cols << " : COLS " << endl << "INFO:" << endl; 
    cout << matrix->data << ": DATA" << endl;

    return matrix;
}