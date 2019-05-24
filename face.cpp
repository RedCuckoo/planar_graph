#include "face.h"
#include <algorithm>

faces::face::face(size_t number_of_face){
    num = number_of_face;
}

faces::face::face(){

}

void faces::face::add(size_t number_of_vertex){
    ver.push_back(number_of_vertex);
}

int faces::face::find(size_t num_of_ver){
    for (size_t i = 0; i < ver.size(); i++){
        if (ver[i] == num_of_ver)
            return i;
    }
    return -1;
}
void faces::face::sort(){
    std::sort(ver.begin(), ver.end());
}

void faces::face::placeWay (face** newFace, graph& to_place, std::vector<size_t>& wayBtwContact){
    delete *newFace;
    *newFace = new face;
out();
    for (size_t i = 0; i < wayBtwContact.size(); i++){
        (*newFace)->add(wayBtwContact[i]);
        std::cout<<wayBtwContact[i]<<" ";
    }
    std::cout<<std::endl;

    for (size_t i = 0; i < to_place.size(); i++){
        if (!(*newFace)->findif(to_place[i]->get_num())){
            (*newFace)->add(to_place[i]->get_num());
           std::cout<<to_place[i]->get_num();
        }
    }


    for (size_t i = 1; i < wayBtwContact.size()-1; i++){
        size_t temp = find(wayBtwContact[i]);
        //std::cout<<temp<<" ";
        if (temp != -1){
            ver.erase(ver.begin() + temp);
        }
    }
   // std::cout<<std::endl;
    sort();
    (*newFace)->sort();
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

bool faces::face::findif (size_t i){
    //returns true if the vertex of with num of i is present
    //returns false otherwise

    for (size_t j = 0; j < ver.size(); j++){
        if (ver[j] == i)
            return true;
    }
    std::cout<<std::endl;
    return false;
}

bool faces::face::belong(graph& to_check){
    for (size_t i = 0; i < to_check.size(); i++){
        //for every vertex
        if (to_check[i]->contact()){
            //if the vertex is contact
            if (findif(to_check[i]->get_num())){
                continue;
            }
            else{
                return false;
            }
        }
    }
    return true;
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

faces::face* faces::operator[](size_t i){
    return &container[i];
}

void faces::placeWay(size_t where, graph& plane, graph& to_place){
    //to place should be a way == have two contact vertexes
//    face *temp;
//    container[where].placeWay(&temp,to_place);
//    temp->set_num(container.size());
//    container.push_back(*temp);

    std::vector<size_t> temp = plane.findWayBtwContact(to_place);


    face* newFace;
//
//    for (size_t i = 0; i < temp.size(); i++)
//        std::cout<<temp[i]<<" ";
//    std::cout<<std::endl;

    container[where].placeWay(&newFace,to_place,temp);
    newFace->set_num(container.size());
    container.push_back(*newFace);

}
