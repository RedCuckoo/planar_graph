#include "face.h"

faces::face::face(size_t number_of_face){
    num = number_of_face;
}

void faces::face::add(size_t number_of_vertex){
    ver.push_back(number_of_vertex);
}

size_t faces::face::operator[](size_t i){
    return ver[i];
}

size_t faces::face::size(){
    return ver.size();
}

int faces::face::get_num(){
    return num;
}

void faces::face::set_num (size_t number_of_face){
    num = number_of_face;
}

bool faces::face::belong(graph& to_check){
    size_t counter = 0;
    for (size_t i = 0; i < to_check.size(); i++){
        //for every vertex
        if (to_check[i]->contact()){
            //if the vertex is contact
            for (size_t j = 0; j < ver.size(); j++){
                //for every vertex in a faceContainer
                if (to_check[i]->get_num() == ver[j]){
                    //if equal to some of the vertex
                    counter++;
                }
            }
        }
    }
    return (counter == to_check.size()) ? true : false;
}

void faces::face::out(){
    std::cout<<num<<" : ";
    for (size_t i = 0; i < ver.size(); i++){
        std::cout<<ver[i]<<" ";
    }
    std::cout<<std::endl;
}

void faces::add (faces::face face_to_add){
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

faces::face faces::operator[](size_t i){
    return container[i];
}
