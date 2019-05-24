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
        size_t faceAmount = 0;
        std::vector <size_t> facesBelong;
    public:
        //segment() = default;
        segment (size_t id, graph& in, size_t num_of_ver1, size_t num_of_ver2);
        segment (size_t id,graph& in, int* firstCycle, size_t firstCycleSize);
        ~segment() = default;
        graph* get_graph();
        void add (size_t i);
        size_t get_faceAmount();
        void set_faceAmount(size_t i);
       // void calcFacesBelong (faces& faceContainer);
        bool recalc (graph& to_del);
        void out();
        void operator++();
        size_t operator[](size_t i);
        size_t size();
        //void checkAndAddFaces(faces& to_check);
    };
    void add (graph& in, int* firstCycle, size_t firstCycleSize);
    void recalc (size_t where, graph& to_del);
    void calcFacesBelong(faces& faceContainer);
    size_t size();
    void sort();
    void out();
    void type1_segment (graph& main, graph* difference, int* firstCycle, int firstCycleSize);
    void type2_segment (graph& main, graph* difference, int* firstCycle, size_t firstCycleSize);
    segment* operator[](size_t i);
    segments() = default;
    ~segments();
private:
    void add(graph& in, size_t num_of_ver1, size_t num_of_ver2);
    std::vector<segment> container;

};


        void clearFromExtra (vertex** in, size_t to_skip);

        vertex** create2 (graph& in, size_t num_of_ver1, size_t num_of_ver2);

#endif // SEGMENT_H
