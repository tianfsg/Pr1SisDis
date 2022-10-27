#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "multmatrix.h"

class Imp
{
private:
    int clientId = -1;
    multMatrix * imp = nullptr;

    void recibeMatriz();

public:
    Imp(int clientId);
    ~Imp();

    void recvOp();
};