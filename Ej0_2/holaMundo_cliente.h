#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include "serialize.hpp"
using namespace std;

#define OP_END 0
#define OP_SUMA 1
#define OP_MULTVECT 2
#define OP_PRINTMSG 3
#define OP_LEEFICH 4


class HolaMundo
{
private:
    int serverId = -1;

public:
    HolaMundo();
    ~HolaMundo();

    int suma(int a, int b);
    void printMSG(string * msg);
    int multVector(vector<int> * v1, vector<int>* v2);
    string * leeFichero(string * FileName);
};