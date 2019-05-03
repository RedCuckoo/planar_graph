#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include "relMatr.h"
#include <iostream>

//builds a graph by the matrix, and stores it as an array of the vertexes

//matr.txt will hold a relativity matrix after initialization

class graph{
private:
    //size - amount of vertexes
    size_t size_of_graph;
    vertex** graph_ver;
    size_t dfsConnectivity (vertex* cur);
    bool dfsCycle (vertex* cur, int** ans, int &size);

    void clearTemp();
    bool petel;
    bool petels(relMatr &matr);

    struct bridge{
        vertex* b,e;
    };

public:
    //orienting graph with dfs, to search for bridges
    int* dfsBridgesOrienting(vertex** cur);
    //returns different components, which aren't connected with bridges
    int* findBridgeCycle (vertex** cur);

    //clears all marks such as colors and visiting
    void clearMarks();
    graph (size_t size, const char* filename = "");
    graph (vertex** ver, size_t size);
    ~graph();
    void out ();
    bool connected();
    bool cycled(int** cyc, int &size);
    bool petels();
    size_t size();
    vertex** get_vertexes();
    void operator= (graph& a);
    vertex* operator[] (size_t i);

    //returns an array of different parts of graph without bridges
    int** find_bridges();
};

#endif // GRAPH_H
