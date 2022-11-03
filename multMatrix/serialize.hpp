#pragma once
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstring>

#define byte char

typedef enum dataType
{
    t_error = -1,
    t_char = 0,
    t_float = 1,
    t_int = 2
} dataType;

template <typename T>
std::vector<byte> *serializaVector(std::vector<T> *v1, dataType t)
{
    std::vector<byte> *vres = new std::vector<byte>();

    vres->reserve(sizeof(dataType) + sizeof(int) + v1->size() * sizeof(T));
    vres->resize(sizeof(dataType) + sizeof(int) + v1->size() * sizeof(T));

    byte *data = vres->data();
    memcpy(data, &t, sizeof(dataType));
    data += sizeof(dataType);

    int size = v1->size();
    memcpy(data, &size, sizeof(int));
    data += sizeof(int);

    memcpy(data, v1->data(), v1->size() * sizeof(T));

    return vres;
}

template <typename T>
std::vector<T> *deserializeVector(std::vector<byte> *v1, dataType t)
{
    std::vector<T> *vres = new std::vector<T>();

    dataType tIn = t_error;

    byte *data = v1->data();
    memcpy(data, &t, sizeof(dataType));
    data += sizeof(dataType);

    if (tIn != t)
    {
        std::cout << "Error linea " << __LINE__ << " fichero " << __FILE__ << "\n";
        return nullptr;
    }

    int size = 0;
    memcpy(&data, data, sizeof(int));
    data += sizeof(int);
    vres->reserve(size);
    vres->resize(size);

    memcpy(vres->data(), data, v1->size() * sizeof(T));

    return vres;
}