#ifndef FACE_H
#define FACE_H

//#include "vertex.h"
#include <vector>
#include "graph.h"
#include <iostream>

class faces{
public:

    class face{
    private:
        std::vector <size_t> ver;
        int num = -1;
    public:
        //by number meant a unique id of the face/vertex
        face(size_t number_of_face);
        void add(size_t number_of_vertex);
        size_t size();
        int get_num();
        void set_num (size_t number_of_face);
        bool belong (graph& to_check);
        void out();
        size_t operator[](size_t i);
    };

    faces() = default;
    void add (face face_to_add);
    void add (int* num_of_vertexes_to_add, size_t amount);
    size_t size();
    void out();
    face operator[](size_t i);
private:
    std::vector <face> container;
};

#endif // FACE_H
