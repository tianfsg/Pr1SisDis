#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "multmatrix.h"

using namespace std;

void freeMatrix(matrix_t* m){
    delete[] m->data;
    delete[] m;
}

int main()
{
    cout << "EMPIEZA EL PROGRAMA : MAIN" << endl;
    multMatrix* mmatrix = new multMatrix();

    cout << "LANZAMOS RANDMATRIX(5,5) : MAIN" << endl;
    matrix_t* m1 = mmatrix->createRandMatrix(5,5);

    cout << "LANZAMOS IDENTITY(5,5) : MAIN" << endl;
    matrix_t* m2= mmatrix->createIdentity(5,5);

    cout << "LANZAMOS MULT() : MAIN" << endl;

    matrix_t* mres=mmatrix->multMatrices(m1,m2);

    cout << "LANZAMOS WIRTE() : MAIN" << endl;

    mmatrix->writeMatrix(mres,"resultado.txt");

    cout << "LANZAMOS READ() : MAIN" << endl;

    matrix_t* m3=mmatrix->readMatrix("resultado.txt");


    cout << "LANZAMOS MULT() : MAIN" << endl;

    matrix_t* mres2=mmatrix->multMatrices(m1,m3);

    cout << "LANZAMOS WRITE(M1,M3) : MAIN" << endl;

    mmatrix->writeMatrix(mres2,"resultado2.txt");

    matrix_t* m7= mmatrix->createIdentity(5,5);
    mmatrix->writeMatrix(m7,"resultado3.txt");



    cout << "LIBERAMOS MEMORIA : MAIN" << endl;

    freeMatrix(m1);
    cout << "m1 liberada" << endl;
    freeMatrix(m2);
    cout << "m2 liberada" << endl;
    freeMatrix(mres);
    cout << "mres liberada" << endl;
    freeMatrix(mres2);
    cout << "mres2 liberada" << endl;
    freeMatrix(m3);
    cout << "m3 liberada" << endl;

    cout << "BORRAMOS MATIRX : MAIN" << endl;
    delete mmatrix;

}