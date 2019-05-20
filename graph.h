#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include "relMatr.h"
#include <iostream>

//builds a graph by the matrix, and stores it as an array of the vertexes

//matr*.txt will hold a relativity matrix after initialization

//GRAPH_MAX_ID.bin will hold the maximum +  value

//all the working graphs automatically have the same dimensions

class graph{
private:
    size_t id;
    //size - amount of vertexes
    size_t size_of_graph = 0;
    vertex** graph_ver;
    size_t dfsConnectivity (vertex* cur);
    bool dfsCycle(vertex* cur, int** ans, int &size, bool first, vertex* prev);
   // bool dfsCycle(vertex* cur,  int** ans, int &size, int height);
    void readID();
    void clearTemp();
    bool petel;
    bool petels(relMatr &matr);

    relMatr* verToMatr();
public:
    //orienting graph with dfs, to search for bridges
    int* dfsBridgesOrienting(vertex** cur);
    //returns different components, which aren't connected with bridges
    int* findBridgeCycle (vertex** cur);

    //clears all marks such as colors and visiting
    void clearMarks();
    void clearColor();
    graph (size_t size, const char* filename = "");
    graph (vertex** ver, size_t size);
    graph (vertex* ver);
    ~graph();
    void out ();

    //checks if the graph is connected
    bool connected();

    //check if the graph has at least one cycle
    bool cycled(int** cyc, int &size);

    //returns true if graph has petels
    bool petels();

    size_t size();
    vertex** get_vertexes();

    void operator= (graph& a);
    vertex* operator[] (size_t i);

    graph* difference (graph& to_subtract);

    //returns an array of different parts of graph without bridges
    int** find_bridges();

    size_t get_id();

    void graph_sort ();

    size_t graph_find (vertex** where, size_t size, size_t number);

    bool findWay (vertex* cur, std::vector<int>& ans, bool first = 0, vertex* prev = nullptr);

    void findWayBtwContact(vertex** ans);
};

void graph_clear();

#endif // GRAPH_H
