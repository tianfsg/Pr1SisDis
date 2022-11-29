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

    //Definimos la operacion y enviamos la informacion necesaria al servidor.
    int typeOP = OP_READ;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));

    size_t sizeFileName = strlen(fileName);
    sendMSG(serverId, (const void*)fileName, sizeFileName);
    cout << "OPERACION *READ* ENVIADA | (CLIENTE)" << endl;

    //reservamos para guardar el contenido
    int * recvRows = nullptr, * recvCols = nullptr, * recvData = nullptr;
    int recvBufferSize = 0;

    recvMSG(serverId, (void **)&recvRows, &recvBufferSize);
    recvMSG(serverId, (void **)&recvCols, &recvBufferSize);
    recvMSG(serverId, (void **)&recvData, &recvBufferSize);

    matrix_t * matrix = new matrix_t();
    matrix->rows = recvRows[0];
    matrix->cols = recvCols[0];
    matrix->data = recvData;

    cout << "MATRIX LEIDA | (CLIENTE)" << endl;
    return matrix;
}
matrix_t * multMatrix :: multMatrices(matrix_t* m1, matrix_t *m2){

    int typeOP = OP_MULT;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));
    cout << "OPERACION *MULT* ENVIADA | (CLIENTE)" << endl;

    //Enviamos M1
    sendMSG(serverId, (const void *)&m1->rows, sizeof(int));
    sendMSG(serverId, (const void *)&m1->cols, sizeof(int));
    sendMSG(serverId, (const void *)m1->data, sizeof(int*) * (m1->cols * m1->rows));

    //Enviamos M2
    sendMSG(serverId, (const void *)&m2->rows, sizeof(int));
    sendMSG(serverId, (const void *)&m2->cols, sizeof(int));
    sendMSG(serverId, (const void *)m2->data, sizeof(int*) * (m2->cols * m2->rows));

    int * recvData = nullptr;
    int recvBufferSize = 0;

    recvMSG(serverId, (void **)&recvData, &recvBufferSize);

    //construimos la matrix resultante.
    matrix_t * m = new matrix_t();
    m->rows = m1->cols;
    m->cols = m2->rows;
    m->data = recvData;

    cout << "MATRIX MULTIPLICADA | (CLIENTE)" << endl;
    return m;
}

void multMatrix :: writeMatrix(matrix_t* m, const char *fileName){

    int typeOP = OP_SCHREIBE;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));
    cout << "OPERACION *WRITE* ENVIADA | (CLIENTE)" << endl;

    //Enviamos matrix
    sendMSG(serverId, (const void *)&m->rows, sizeof(int));
    sendMSG(serverId, (const void *)&m->cols, sizeof(int));
    sendMSG(serverId, (const void *)m->data, sizeof(int*) * (m->cols * m->rows));

    //Enviamos el File
    size_t sizeFileName = strlen(fileName);
    sendMSG(serverId, (const void*)fileName, sizeFileName);
    cout << "ARCHIVO ENVIADO | (CLIENTE)" << endl;
}
matrix_t* multMatrix :: createIdentity(int rows, int cols){

    int typeOP = OP_IDENTITY;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));

    cout << "OPERACION *IDENTITY* ENVIADA | (CLIENTE)" << endl;

    //enviamos las dimensiones
    sendMSG(serverId, (const void *)&rows, sizeof(int));
    sendMSG(serverId, (const void *)&cols, sizeof(int));

    int * recvData = nullptr;
    int recvBufferSize = 0;
    recvMSG(serverId, (void **)&recvData, &recvBufferSize);

    //construimos la matrix que vamos a recibir
    matrix_t * matrix = new matrix_t();
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = recvData;

    // for(int i = 0; i < matrix->cols * matrix->rows; i++){
    //     cout << matrix->data[i] << endl;
    // }
    cout << "MATRIX IDENTIDAD CREADA | (CLIENTE)" << endl;
    return matrix;
}
matrix_t* multMatrix :: createRandMatrix(int rows, int cols){
    
    int typeOP = OP_RAND;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));

    cout << "OPERACION *RAND* ENVIADA | (CLIENTE)" << endl;

    //enviamos las dimensiones
    sendMSG(serverId, (const void *)&rows, sizeof(int));
    sendMSG(serverId, (const void *)&cols, sizeof(int));

    int * recvData = nullptr;
    int recvBufferSize = 0;

    recvMSG(serverId, (void **)&recvData, &recvBufferSize);

    //construimos la matrix que vamos a recibir
    matrix_t * matrix = new matrix_t();
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = recvData;

    cout << "MATRIX RANDOM CREADA | (CLIENTE)" << endl;
    return matrix;
}