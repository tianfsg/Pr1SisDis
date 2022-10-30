#include "MultMatrix__imp.h"
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
            HolaMundo_imp *hmi = new HolaMundo_imp(clientId);
            hmi->recvOp();
            delete hmi;
        }
        // trabajo útil
        usleep(100);
    }
    return 0;
}