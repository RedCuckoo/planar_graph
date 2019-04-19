#include "vertex.h"

vertex::vertex(relVec &work, size_t number){
    degree = work.get_deg(number);
    num = number;

    next_num = new int [degree];

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

void vertex::out(){
    std::cout<<"DEG: "<<degree<<" NUM: "<<num<<std::endl;
    std::cout<<"NEXT VERTICES: ";
    for (size_t i = 0; i < degree;i++){
        std::cout<<next_num[i]<<" ";
    }
    std::cout<<std::endl;
}

vertex::~vertex(){
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

size_t vertex::get_num(){
    return num;
}

size_t vertex::operator[] (size_t i){
    return next_num[i];
}

size_t vertex::get_degree(){
    return degree;
}
