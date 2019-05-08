#ifndef SEGMENT_H
#define SEGMENT_H

#include "vertex.h"
#include "graph.h"
#include <vector>

class segment{
private:
    std::vector <graph> container;

public:
    segment() = default;

    void add (graph& in, size_t num_of_ver1, size_t num_of_ver2);
    void out();
    ~segment() = default;
};




#endif // SEGMENT_H
