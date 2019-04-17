#include "relVec.h"

relVec::relVec(size_t am){
    amount = am;
    rows = new unsigned [amount];
}

relVec::~relVec(){
    delete rows;
}

unsigned relVec::rowToNum (relMatr &work, int i){
    //converts the row in the matrix, which consists of 0s and 1s to a binary number

    unsigned ans = 0;
    for (size_t j = 0; j < work.size(); j++){
        ans <<= 1;
        if (work.get_el(i,j) == 1){
            ans+=1;
        }
    }
    return ans;
}

unsigned relVec::operator [](size_t i){
    return rows[i];
}
size_t relVec::size(){
    return amount;
}

size_t relVec::get_deg (size_t vertex){
    //calculates the degree of the vertex, by the number in the vector
    unsigned temp = rows[vertex];
    size_t ans = 0;

    while (temp){
        if (temp & 01){
            ans++;
        }
        temp >>= 1;
    }
    return ans;
}

void relVec::matrToVec(relMatr &work) {
    for (size_t i = 0; i < amount;i++){
        rows[i] = rowToNum(work,i);
    }
}

void relVec::out(){
    for (size_t i = 0; i< amount; i++){
        std::cout<<rows[i]<<" ";
    }
    std::cout<<std::endl;
}
