#include "MultMatrix_imp.h"
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
            MultMatrix_Imp * mmi = new MultMatrix_Imp(clientId);
            mmi->recvOp();
            delete mmi;
        }
        // trabajo útil
        usleep(100);
    }
    return 0;
}