#include "holaMundo_cliente.h"
#include "utils.h"
#include <string>
#include <cstring>

using namespace std;
#define PORT 40000
#define IP_SERVER "54.225.154.164"

HolaMundo::HolaMundo()
{
    serverId = initClient((char *)IP_SERVER, PORT);
    if (serverId < 0)
        std::cout << "ERROR " << __FILE__ << ":" << __LINE__ << "\n";
}
HolaMundo::~HolaMundo()
{
    int typeOP = OP_END;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));
    closeConnection(serverId);
}
int HolaMundo::suma(int a, int b)
{
    int typeOP=OP_SUMA;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));

    int res = 0;
    sendMSG(serverId, (const void *)&a, sizeof(int));
    sendMSG(serverId, (const void *)&b, sizeof(int));

    int *recvBuffer = nullptr;
    int recvBufferSize = 0;
    recvMSG(serverId, (void **)&recvBuffer, &recvBufferSize);

    if (recvBufferSize != sizeof(int))
    {
        std::cout << "ERROR " << __FILE__ << ":" << __LINE__ << "\n";
    }
    else
    {
        res = recvBuffer[0];
    }
    delete[] recvBuffer; // despues de recibir buffer y almacenarlo hay que liberarlo
    return res;
}

void HolaMundo:: printMSG(string * msg){
    // sendMSG(serverId, msg->c_str(), msg->length());

}
int HolaMundo:: multVector(vector<int> * v1, vector<int>* v2){

    int typeOP=OP_MULTVECT;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));

    //empaqueto los vectores
    vector<byte>* v1s = serializaVector<int>(v1,t_int);
    vector<byte>* v2s = serializaVector<int>(v2,t_int);

    //envio los datos
    sendMSG(serverId, (const void**) v1s->data(),  v1->size());
    sendMSG(serverId, (const void**) v2s->data(),  v2->size());

    //libero los datos enviados
    delete v1s;
    delete v2s;

    int * buffIN=nullptr;
    int buffLen=0;

    recvMSG(serverId, (void**) &buffIN, &buffLen);
    int res = buffIN[0];
    delete buffIN;
    return res;
}

string * HolaMundo :: leeFichero(string * fileName){

    int typeOP=OP_LEEFICH;
    sendMSG(serverId, (const void*)&typeOP, sizeof(int));
    sendMSG(serverId, (const void*)fileName->c_str(), fileName->length());

    char * fileContent = nullptr;
    int fileContentSize = 0;

    recvMSG(serverId, (void**) &fileContent, &fileContentSize);
    string * content = new string(fileContent);
    

    delete [] fileContent;


    return content;
}




//<byte> 4 primeros bytes son el tipo, 
//         4 siguienes son el contenido, etc.