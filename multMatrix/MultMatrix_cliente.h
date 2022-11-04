#pragma once

#include <iostream>
#include <cstring>

using namespace std;

#define OP_END 0
#define OP_READ 1
#define OP_MULT 2
#define OP_SCHREIBE 3
#define OP_IDENTITY 4
#define OP_RAND 5

typedef struct matrix_t
{
    int rows;
    int cols;
    int* data;
}matrix_t;

class multMatrix
{
private:
    int serverId = -1;
public:
    multMatrix();
    ~multMatrix();

    matrix_t* readMatrix(const char* fileName);
    matrix_t* multMatrices(matrix_t* m1, matrix_t *m2);
    void writeMatrix(matrix_t* m, const char *fileName);
    matrix_t* createIdentity(int rows, int cols);
    matrix_t* createRandMatrix(int rows, int cols);
};