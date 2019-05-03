#ifndef FACE_H
#define FACE_H

//#include "vertex.h"
#include <vector>
#include <iostream>

class face{
private:
    std::vector <size_t> ver;
    int num = -1;
public:
    face(size_t number_of_face);
    void add(size_t number_of_vertex);
    size_t size();
    int get_num();
    void set_num (size_t number_of_face);
    void out();
    size_t operator[](size_t i);
};

class faces{
private:
    std::vector <face> container;
public:
    faces() = default;
    void add (face face_to_add);
    void add (int* num_of_vertexes_to_add, size_t amount);
    size_t size();
    void out();
    face operator[](size_t i);
};

#endif // FACE_H
