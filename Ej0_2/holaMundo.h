#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>

using namespace std;

class HolaMundo
{
public:
    HolaMundo();
    ~HolaMundo();

    int suma(int a, int b);
    void printMSG(string * msg);
    int multVector(vector<int> * v1, vector<int>* v2);
    string * leeFichero(string * fileName);
};