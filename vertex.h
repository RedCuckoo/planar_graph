#ifndef VERTEX_H
#define VERTEX_H
#include "relVec.h"
#include <iostream>

class vertex{
private:
    int* next_num;
    size_t num;
    bool temp;
    size_t color = 0;
    size_t degree;

public:

    vertex(relVec &work, size_t number);
    ~vertex();
    void set_visited ();
    void set_blank();
    void col_gray();
    void col_black();
    void col_white();
    bool gray();
    bool black();
    bool white();
    bool visited();
    size_t get_degree();
    size_t get_num();
    void out();
    //returns vertexes connected to the current
    size_t operator[] (size_t i);
};

#endif // VERTEX_H


