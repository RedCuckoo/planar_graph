#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include "relMatr.h"
#include <iostream>

//builds a graph by the matrix, and stores it as an array of the vertexes

class graph{
private:
    //size - amount of vertexes
    size_t size;
    vertex** graph_ver;
    size_t dfsConnectivity (vertex* cur);
    bool dfsCycle (vertex* cur, int** ans, int &size);
    void clearTemp();
    bool petel;
    bool petels(relMatr &matr);
public:
    graph (size_t size, const char* filename = "");
    ~graph();
    void out ();
    bool connected();
    bool cycled(int** cyc, int &size);
    bool petels();
};

#endif // GRAPH_H
