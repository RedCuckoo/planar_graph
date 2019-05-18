#ifndef SEGMENT_H
#define SEGMENT_H

#include "vertex.h"
#include "graph.h"
#include <vector>
#include "face.h"

class segment{
private:
    graph** container;
    faces* faceCon;
    size_t amount = 0;
    size_t facesAmount = 0;

public:
    segment() = default;
    vertex** create2 (graph& in, size_t num_of_ver1, size_t num_of_ver2);
    vertex* get_one (vertex** t, size_t i);
    size_t faces_size();
    void push_back(graph* to_add);
    void push_back();
    void clearFromExtra (vertex** in, size_t to_skip);
    void add (graph& in, size_t num_of_ver1, size_t num_of_ver2);
    void add (graph& in, int* firstCycle, size_t firstCycleSize);
    std::vector<size_t> last_ids();
    size_t size();
    void out();
    graph* operator[](size_t i);
    void checkAndAddFaces(faces& to_check);
    void delGgraph(graph** del, size_t size);
    ~segment() = default;
};




#endif // SEGMENT_H
