#include "graph.h"
#include "relMatr.h"
#include "relVec.h"

graph::graph(int size){
    this->size = size;
    graph_ver = new vertex* [size];

    relMatr matr (size);
    matr.fill();
    relVec vec(size);
    vec.matrToVec(matr);

    for (int i = 0; i < size; i++){
        graph_ver[i] = new vertex(vec,i);
    }
}

graph::~graph(){
    for (size_t i = 0; i < size; i++){
        delete graph_ver[i];
    }
    delete graph_ver;
}
