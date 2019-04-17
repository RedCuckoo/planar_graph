#include "relMatr.h"

relMatr::relMatr (size_t am){
    amount = am;
    matr = new bool* [amount];
    for (size_t i = 0; i < amount; i++){
        matr[i] = new bool [amount];
    }
    for (size_t i = 0; i < amount; i++){
        for (size_t j = 0; j < amount; j++){
            matr[i][j] = 0;
        }
    }
}

bool** relMatr::get_matr(){
    return matr;
}

bool relMatr::get_el (int i, int j){
    return matr[i][j];
}

size_t relMatr::size(){
    return amount;
}

void relMatr::fill (){
    //asks user to fill the matrix
    std::cout<<"Enter please the matrix corresponding to the size => \n";
    for (size_t i = 0; i < amount; i++){
        for (size_t j = 0; j < amount; j++){
            std::cin>>matr[i][j];
        }
    }
    std::cout<<std::endl;
}

void relMatr::out (){
    for (size_t i = 0; i< amount; i++){
        for (size_t j = 0; j < amount; j++){
            std::cout<<matr[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

relMatr::~relMatr(){
    for (size_t i = 0; i < amount; i++){
        delete matr[i];
       }
    delete matr;
}
