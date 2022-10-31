#include "MultMatrix_server.h"
#include "utils.h"

#define PORT 40000
int main(int argc, char **argv)
{
    int serverId = initServer(PORT);
    while (1)
    {
        if (checkNewConnections())
        {
            int clientId = getNewConnection();
            MultMatrix_imp * mmi = new MultMatrix_imp(clientId);
            mmi->recvOp();
            delete mmi;
        }
        // trabajo útil
        usleep(100);
    }
    return 0;
}