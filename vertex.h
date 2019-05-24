#ifndef VERTEX_H
#define VERTEX_H
#include "relVec.h"
#include <iostream>
#include <vector>

class vertex{
private:
    //array of connected vertexes
    size_t* next_num;

    //the unique number of current vertex
    size_t num;
    //degree of this vertex
    size_t degree;

    bool temp = 0;
    size_t color = 0;

public:
    vertex(relVec &work, size_t number);
    vertex (size_t number, size_t firstVertex, size_t secondVertex);
    vertex (vertex& to_copy);
    ~vertex();
    static vertex* addVertexes (vertex& one, vertex& two);
    static vertex* difVertexes (vertex& one, vertex& two);
    void set_visited ();
    void set_blank();
    void col_gray();
    void col_black();
    void col_white();
    bool gray();
    bool black();
    bool white();
    bool visited();
    void set_contact();
    void del_contact();
    bool contact();
    size_t get_degree();
    size_t get_num();
    void out();
    void delNext(size_t delThis);
    void addNext (size_t addThis);
    //returns vertexes connected to the current
    size_t operator[] (size_t i);
    bool operator== (vertex& to_check);
};

#endif // VERTEX_H


