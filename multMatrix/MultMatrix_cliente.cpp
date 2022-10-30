#include "MultMatrix_cliente.h"
#include "utils.h"

using namespace std;
#define PORT 40000
#define IP_SERVER "52.20.216.232"

multMatrix :: multMatrix(){
    serverId = initClient((char *)IP_SERVER, PORT);
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

    //reservamos para guardar el contenido y el tamanno del fichero
    int * recvData = nullptr;
    int recvRows; int recvCols;
    int recvBufferSize = 0;

    recvMSG(serverId, (void **)&recvRows, &recvBufferSize);
    recvMSG(serverId, (void **)&recvCols, &recvBufferSize);
    recvMSG(serverId, (void **)&recvData, &recvBufferSize);

    matrix_t * matrix = new matrix_t();
    matrix->cols = recvCols;
    matrix->rows = recvRows;
    matrix->data = recvData;

    return matrix;
}
matrix_t * multMatrix :: multMatrices(matrix_t* m1, matrix_t *m2){

    int typeOP = OP_MULT;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));

    matrix_t * matrix = nullptr;
    matrix->rows = m1->cols;
    matrix->cols = m2->rows;

    //Enviamos M1
    sendMSG(serverId, (const void *)&m1->rows, sizeof(int));
    sendMSG(serverId, (const void *)&m1->cols, sizeof(int));
    sendMSG(serverId, (const void *)&m1->data, sizeof(int*));

    //Enviamos M2
    sendMSG(serverId, (const void *)&m2->rows, sizeof(int));
    sendMSG(serverId, (const void *)&m2->cols, sizeof(int));
    sendMSG(serverId, (const void *)&m2->data, sizeof(int*));

    int recvBufferSize = 0;
    recvMSG(serverId, (void **)matrix->data, &recvBufferSize);

    return matrix;
}
void multMatrix :: writeMatrix(matrix_t* m, const char *fileName){

    int typeOP = OP_SCHREIBE;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));

    //Enviamos matrix
    sendMSG(serverId, (const void *)&m->rows, sizeof(int));
    sendMSG(serverId, (const void *)&m->cols, sizeof(int));
    sendMSG(serverId, (const void *)&m->data, sizeof(int*));

    //Enviamos file
    size_t sizeFileName = strlen(fileName);
    sendMSG(serverId, (const void*)fileName, sizeFileName);

}
matrix_t* multMatrix :: createIdentity(int rows, int cols){

    int typeOP = OP_IDENTITY;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));

    //enviamos las dimensiones
    sendMSG(serverId, (const void *)&rows, sizeof(int));
    sendMSG(serverId, (const void *)&cols, sizeof(int));

    //construimos la matrix que vamos a recibir
    matrix_t * matrix;
    matrix->rows = rows;
    matrix->cols = cols;

    int recvBufferSize = 0;
    recvMSG(serverId, (void **)matrix->data, &recvBufferSize);

    return matrix;
}
matrix_t* multMatrix :: createRandMatrix(int rows, int cols){
    int typeOP = OP_RAND;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));

    //enviamos las dimensiones
    sendMSG(serverId, (const void *)&rows, sizeof(int));
    sendMSG(serverId, (const void *)&cols, sizeof(int));

    //construimos la matrix que vamos a recibir
    matrix_t * matrix;
    matrix->rows = rows;
    matrix->cols = cols;

    int recvBufferSize = 0;
    recvMSG(serverId, (void **)matrix->data, &recvBufferSize);

    return matrix;
}