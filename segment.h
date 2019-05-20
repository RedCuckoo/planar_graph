#ifndef SEGMENT_H
#define SEGMENT_H

#include "vertex.h"
#include "graph.h"
#include <vector>
#include "face.h"

class segments{
public:
    class segment{
    private:
        graph* segm;
        size_t id;
        void clearFromExtra (vertex** in, size_t to_skip);
        vertex** create2 (graph& in, size_t num_of_ver1, size_t num_of_ver2);
        size_t faceAmount = 0;
        std::vector <faces::face*> facesBelong;
    public:
        //segment() = default;
        segment (size_t id, graph& in, size_t num_of_ver1, size_t num_of_ver2);
        segment (size_t id,graph& in, int* firstCycle, size_t firstCycleSize);
        graph* get_graph();
        size_t get_faceAmount();
        void calcFacesBelong (faces& faceContainer);
        void out();
        //void checkAndAddFaces(faces& to_check);
        ~segment() = default;
    };
    void add (graph& in, int* firstCycle, size_t firstCycleSize);
    void calcFacesBelong(faces& faceContainer);
    size_t size();
    void out();
    void type1_segment (graph& main, graph* difference, int* firstCycle, int firstCycleSize);
    void type2_segment (graph& main, graph* difference, int* firstCycle, size_t firstCycleSize);
    segment* operator[](size_t i);
    segments() = default;
private:
    void add(graph& in, size_t num_of_ver1, size_t num_of_ver2);
    std::vector<segment> container;

};



#endif // SEGMENT_H
