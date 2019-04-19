#include "graph.h"
#include "relVec.h"
#include <string.h>

graph::graph(size_t size, const char* filename){
    this->size = size;
    graph_ver = new vertex* [size];

    relMatr matr (size);

    if (strlen (filename) == 0){
        matr.fill();
    }
    else{
        matr.fill(filename);
    }

    petel = (petels(matr)) ? true : false;

    relVec vec(size);
    vec.matrToVec(matr);


    for (size_t i = 0; i < size; i++){
        graph_ver[i] = new vertex(vec,i);
    }
}

graph::~graph(){
    for (size_t i = 0; i < size; i++){
        delete graph_ver[i];
    }
    delete graph_ver;
}

void graph::out(){
    for (size_t i = 0; i < size; i++){
        graph_ver[i]->out();
    }
}

size_t graph::dfsConnectivity (vertex* cur){
    //size is the amount of vertexes
    static size_t counter = 0;
    if (!cur->visited()){
        cur->set_visited();
        counter++;
        for (size_t i = 0; i < cur->get_degree(); i++){
            dfsConnectivity(graph_ver[(*cur)[i]]);
        }
    }
    return counter;
}

bool graph::dfsCycle(vertex* cur, int** ans, int &size){
    //find a cycle
    static int height = 0;
    static int height_MAX;
    static vertex* contr;
    static vertex* prev;
    static int* temp;

    if (cur->white()){
        cur->col_gray();
        height++;
        for (size_t i = 0; i < cur->get_degree(); i++){
            if (prev == graph_ver[(*cur)[i]]){
                continue;
            }
            else{
                prev = cur;
            }


            if (dfsCycle(graph_ver[(*cur)[i]],ans,size)){
                temp [height] = cur->get_num();
                if (contr == cur){
                    size = height_MAX - height;
                    delete (*ans);
                    *ans  = new int[size--];
                    for (int j = height_MAX-1; j>=0 && size>=0;j--){
                        (*ans)[size--] = temp[j];
                    }
                    size = height_MAX - height;
                }
                height--;
                return true;
            }
        }
        height--;
        cur->col_black();
        return false;
    }
    else if (cur->gray()){
        delete temp;
        height_MAX = height;
        temp = new int [height--];
        contr = cur;
        return true;
    }
    else{
        return false;
    }
    return false;
}

bool graph::connected(){
    return (dfsConnectivity(graph_ver[0]) == size) ? true : false;
}

bool graph::petels(relMatr &matr){
    for (size_t i = 0; i < size; i++){
        if (matr.get_el(i,i)){
            return true;
        }
    }
    return false;
}

bool graph::petels(){
    return petel;
}

bool graph::cycled(int** cyc, int &size){
    return (dfsCycle(graph_ver[0],cyc,size)) ? true : false;

}
