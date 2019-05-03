#include "face.h"

face::face(size_t number_of_face){
    num = number_of_face;
}

void face::add(size_t number_of_vertex){
    ver.push_back(number_of_vertex);
}

size_t face::operator[](size_t i){
    return ver[i];
}

size_t face::size(){
    return ver.size();
}

int face::get_num(){
    return num;
}

void face::set_num (size_t number_of_face){
    num = number_of_face;
}

void face::out(){
    std::cout<<num<<" : ";
    for (size_t i = 0; i < ver.size(); i++){
        std::cout<<ver[i]<<" ";
    }
    std::cout<<std::endl;
}

void faces::add (face face_to_add){
    face_to_add.set_num(container.size());
    container.push_back(face_to_add);
}

void faces::add (int* num_of_vertexes_to_add, size_t amount){
    face temp(container.size());
    for (size_t i = 0; i < amount; i++){
        temp.add(num_of_vertexes_to_add[i]);
    }
    container.push_back(temp);
}

size_t faces::size(){
    return container.size();
}

void faces::out(){
    for (size_t i = 0; i < container.size(); i++){
        container[i].out();
    }
}

face faces::operator[](size_t i){
    return container[i];
}
