#ifndef SEGMENT_H
#define SEGMENT_H

#include "vertex.h"
#include "graph.h"
#include <vector>

class segment{
private:
    graph** container;
    size_t amount = 0;

public:
    segment() = default;
    void push_back(graph* to_add);
    void push_back();
    void clearFromExtra (vertex** in, size_t to_skip);
    void add (graph& in, size_t num_of_ver1, size_t num_of_ver2);
    std::vector<size_t>* last_ids();
    size_t size();
    void out();
    graph* operator[](size_t i);
    void delGgraph(graph** del, size_t size);
    ~segment() = default;
};




#endif // SEGMENT_H
