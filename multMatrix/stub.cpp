#include <iostream>
#include "stub.h"

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
    matrix_t* matrix=new matrix_t[1];
    recvMSG(serverId, (void**) &matrix, sizeof(matrix_t) * (matrix->cols * matrix->rows));

}
matrix_t multMatrix :: *multMatrices(matrix_t* m1, matrix_t *m2){

}
void multMatrix :: writeMatrix(matrix_t* m, const char *fileName){

}
matrix_t multMatrix :: *createIdentity(int rows, int cols){

}
matrix_t multMatrix :: *createRandMatrix(int rows, int cols){
    
}