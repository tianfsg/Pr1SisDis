#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "multmatrix.h"

#define OP_END 0
#define OP_READ 1
#define OP_MULT 2
#define OP_SCHREIBE 3
#define OP_IDENTITY 4
#define OP_RAND 5


class MultMatrix_imp
{
private:

    multMatrix * mmi = nullptr;
    int clientId = -1;
    
    //Metodos
    void leerMatrix();
    void multMatrix();
    void schreibeMatrix();
    void identityMatrix();
    void randomMatrix();
    
public:
    MultMatrix_imp(int clientId);
    ~MultMatrix_imp();

    void recvOp();
};