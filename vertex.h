#ifndef VERTEX_H
#define VERTEX_H
#include "relVec.h"
#include <iostream>

class vertex{
private:
    int* next_num;
    size_t num;
    bool temp;
    size_t degree;

public:

    vertex(relVec work, size_t number);
    ~vertex();
    void out();
};

#endif // VERTEX_H


