#include "vertex.h"

vertex::vertex(relVec work, size_t number){
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

