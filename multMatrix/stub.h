#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
// #include "serialize.hpp"
#include "multmatrix.h"
#include "utils.h"

#define OP_END 0
#define OP_READ 1

class multMatrix
{
private:
    int serverId = -1;
public:
    multMatrix();
    matrix_t* readMatrix(const char* fileName);
    matrix_t *multMatrices(matrix_t* m1, matrix_t *m2);
    void writeMatrix(matrix_t* m, const char *fileName);
    ~multMatrix();
    matrix_t *createIdentity(int rows, int cols);
    matrix_t *createRandMatrix(int rows, int cols);
};