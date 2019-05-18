#include "vertex.h"

vertex::vertex(relVec &work, size_t number){
    degree = work.get_deg(number);
    num = number;

    next_num = new size_t [degree];

    size_t workS = work.size();

    unsigned temp = work[number];
    size_t counter = degree-1;

    for (int j = workS-1; j >= 0; j--){
        if (temp & 01){
            next_num[counter--] = j;
        }
        temp >>= 1;
    }
}


vertex::vertex (size_t number, size_t firstVertex, size_t secondVertex){
    degree = 2;
    num = number;
    next_num = new size_t [degree];

    next_num[0] = (firstVertex<secondVertex) ? firstVertex : secondVertex;
    next_num[1] = (firstVertex>secondVertex) ? firstVertex : secondVertex;
}

vertex::vertex(vertex& to_copy){
    degree = to_copy.get_degree();
    num = to_copy.get_num();
    next_num = new size_t [degree];
    temp = to_copy.contact();

    for (size_t i = 0; i < degree; i++){
        next_num[i] = to_copy[i];
    }
}

void vertex::out(){
    std::cout<<"DEG: "<<degree<<" CONTACT: ";
    if (contact())
        std::cout<<"YAS";
    else
        std::cout<<"NO";
    std::cout<<" NUM: "<<num<<std::endl;
    std::cout<<"NEXT VERTICES: ";
    for (size_t i = 0; i < degree;i++){
        std::cout<<next_num[i]<<" ";
    }
    std::cout<<std::endl;
}

vertex::~vertex(){
    next_num = nullptr;
    delete next_num;
}

void vertex::set_visited (){
    temp = true;
}

void vertex::set_blank(){
    temp = false;
}

void vertex::col_gray(){
    color = 1;
}

void vertex::col_black(){
    color = 2;
}

void vertex::col_white(){
    color = 0;
}

bool vertex::gray(){
    return (color == 1) ? true : false;
}

bool vertex::black(){
    return (color == 2) ? true : false;
}

bool vertex::white(){
    return (color == 0) ? true : false;
}

bool vertex::visited(){
    return temp;
}

void vertex::set_contact(){
    set_visited();
}

void vertex::del_contact(){
    set_blank();
}

bool vertex::contact(){
    return temp;
}

size_t vertex::get_num(){
    return num;
}

size_t vertex::operator[] (size_t i){
    return next_num[i];
}

bool vertex::operator== (vertex& to_check){
    return (num == to_check.get_num()) ? true : false;
}

size_t vertex::get_degree(){
    return degree;
}

void vertex::delNext(size_t delThis){
    for (size_t i = 0; i < degree; i++){
        if (this->next_num[i] == delThis){
            int* temp = new int [--degree];
            int k = 0;
            for (size_t j = 0; j < degree+1; j++){
                if (i!=j){
                    temp[k++] = this->next_num[j];
                }
            }

            delete next_num;
            next_num = new size_t [degree];

            for (size_t j = 0; j < degree; j++){
                this->next_num[j] = temp[j];
            }
            delete temp;
            return;
        }
    }
}
