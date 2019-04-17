#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include <iostream>

//builds a graph by the matrix, and stores it as an array of the vertexes

class graph{
private:
    size_t size;
    vertex** graph_ver;

public:
    graph (int size);
    ~graph();
};

#endif // GRAPH_H
