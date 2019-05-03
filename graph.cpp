#include "graph.h"
#include "relVec.h"
#include <string.h>
#include <fstream>

graph::graph(size_t size, const char* filename){
    this->size_of_graph = size;
    graph_ver = new vertex* [size];

    std::ofstream fmatr;
    fmatr.open("matr.txt");

    relMatr matr (size);

    if (strlen (filename) == 0){
        matr.fill();

    }
    else{
        matr.fill(filename);
    }

    for (size_t i = 0; i < size; i++){
        for (size_t j = 0; j < size; j++){
            fmatr<<matr.get_el(i,j)<<" ";
        }
        fmatr<<std::endl;
    }

    petel = (petels(matr)) ? true : false;

    relVec vec(size);
    vec.matrToVec(matr);


    for (size_t i = 0; i < size; i++){
        graph_ver[i] = new vertex(vec,i);
    }
    fmatr.close();
}

graph::graph (vertex** ver, size_t size){
    graph_ver = ver;
    size_of_graph = size;
}

graph::~graph(){
    for (size_t i = 0; i < size_of_graph; i++){
        delete graph_ver[i];
    }
    delete graph_ver;
}

void graph::out(){
    for (size_t i = 0; i < size_of_graph; i++){
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
    return (dfsConnectivity(graph_ver[0]) == size_of_graph) ? true : false;
}

bool graph::petels(relMatr &matr){
    for (size_t i = 0; i < size_of_graph; i++){
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
    this->clearMarks();
    return (dfsCycle(graph_ver[0],cyc,size)) ? true : false;
}

size_t graph::size(){
    return size_of_graph;
}

vertex** graph::get_vertexes(){
    return graph_ver;
}

void graph::operator=(graph& a){
    this->size_of_graph = a.size();
    this->graph_ver = a.get_vertexes();
}

vertex* graph::operator[](size_t i){
    return graph_ver[i];
}

void graph::clearMarks(){
    for (size_t i = 0; i < size_of_graph; i++){
        graph_ver[i]->set_blank();
        graph_ver[i]->col_white();
    }
}

int* graph::dfsBridgesOrienting(vertex** cur){
    static int* order = new int [size_of_graph];
    static int counter = 0;
    if (!(*cur)->visited()){
        //if we weren't here
        order[counter++] = (*cur)->get_num();
        (*cur)->set_visited();
        for (size_t i = 0; i < (*cur)->get_degree(); i++){
            //for every connected
            if (!graph_ver[(**cur)[i]]->visited()){
                dfsBridgesOrienting(&graph_ver[(**cur)[i]]);
                (*cur)->delNext((**cur)[i]);
                i--;
            }
        }
    }
    return order;
}

int* graph::findBridgeCycle(vertex** cur){
    //cur is NOT visited vertex
    static int* component = new int [size_of_graph];
    static int counter = 0;
    //int* temp;

    if ((*cur)->visited()){
        return component;
    }

    (*cur)->set_visited();
    component[counter++] = (*cur)->get_num();
    for (size_t i = 0; i < (*cur)->get_degree(); i++){

        if (!graph_ver[(**cur)[i]]->visited()){
            //if the next one isn't visited
            findBridgeCycle(&graph_ver[(**cur)[i]]);


        }
    }


    return component;
}



int** graph::find_bridges(){
    //"this" should hold a not oriented graph
    graph temp = *this;
    temp.clearMarks();
    vertex* t = temp[0];
    int* order = temp.dfsBridgesOrienting(&t);
    temp.clearMarks();

    int** components = new int* [temp.size()];

    for (size_t i = 0; i < temp.size(); i++){
        if (!graph_ver[order[i]]->visited()){
            findBridgeCycle(&graph_ver[order[i]]);
        }
    }

    return components;
}
