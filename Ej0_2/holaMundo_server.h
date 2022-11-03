#pragma once

#include "holaMundo.h"

#define OP_END 0
#define OP_SUMA 1
#define OP_MULTVECT 2
#define OP_PRINTMSG 3
#define OP_LEEFICH 4

class HolaMundo_imp
{
private:
    HolaMundo *hm = nullptr;
    int clientId = -1;
    void recibeMultVector();
    void recibeSuma();
    void recibeLeeFichero();

public:
    HolaMundo_imp(int clientId);
    ~HolaMundo_imp();

    void recvOp();
};