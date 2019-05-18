#include "graph.h"
#include "relVec.h"
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

graph::graph(size_t size, const char* filename){
    readID();
    this->size_of_graph = size;
    graph_ver = new vertex* [size];

    //create file matr*.txt where * is the id of the graph
    std::ofstream fmatr;
    std::string fname = "matr";
    fname += std::to_string(id);
    fname += ".txt";
    fmatr.open(fname.c_str());

    relMatr matr (size);

    if (strlen (filename) == 0){
        matr.fill();

    }
    else{
        matr.fill(filename);
    }

    //write out to a file
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
    readID();

    graph_ver = new vertex* [size];
    for(size_t i = 0; i < size; ++i){
        graph_ver[i] = new vertex(*ver[i]);
    }

    size_of_graph = size;

    graph_sort();
    verToMatr();
}

graph::graph(vertex* ver){
    readID();
    graph_ver = new vertex* [1];
    graph_ver[0] = ver;
    size_of_graph = 1;
    graph_sort();
    verToMatr();
}

graph::~graph(){
    //DELETE FILES
    for (size_t i = 0; i < size_of_graph; i++){
        if (graph_ver[i])
            delete graph_ver[i];
    }
    if (graph_ver)
        delete graph_ver;
}

void graph::out(){
    for (size_t i = 0; i < size_of_graph; i++){
        graph_ver[i]->out();
    }
}

void graph::readID(){
std::fstream fmaxID("GRAPH_MAX_ID.txt",std::ios::in);
    if (fmaxID.good()){
        fmaxID>>id;
        fmaxID.close();
        fmaxID.open("GRAPH_MAX_ID.txt", std::ios::out);
        fmaxID<<id+1;
    }
    else{
       // fmaxID.close();
        fmaxID.open ("GRAPH_MAX_ID.txt", std::ios::out);
        fmaxID<<1;
        id = 0;
    }
    fmaxID.close();
}

relMatr* graph::verToMatr(){
    size_t size = graph_ver[size_of_graph-1]->get_num()+1;
    bool tempMatr[size][size];
    relMatr* ans = new relMatr (size);

    std::string fname = "matr";
    fname += std::to_string(id);
    fname += ".txt";
    std::ofstream fmatr (fname.c_str());//, std::ios::out);

    size_t temp_i = 0;
    size_t temp_j = 0;

    for (size_t i = 0; i < size; i++){
        for (size_t j = 0; j < size; j++){
            if (temp_i < size_of_graph && temp_j < graph_ver[temp_i]->get_degree()){
                if (graph_ver[temp_i]->get_num() == i && (*graph_ver[temp_i])[temp_j] == j){
                        if (++temp_j >= graph_ver[temp_i]->get_degree()){
                            temp_j = 0;
                            temp_i++;
                        }
                        tempMatr[i][j] = 1;
                        fmatr<<1<<" ";
                }
                else{
                    tempMatr[i][j] = 0;
                    fmatr<<0<<" ";
                }
            }
            else{
                tempMatr[i][j] = 0;
                fmatr<<0<<" ";

            }
        }
        fmatr<<'\n';
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

bool graph::dfsCycle(vertex* cur, int** ans, int& size, bool first = 0, vertex* prev = nullptr){
    static std::vector <int> ans_temp;

    if (!first)
        ans_temp.clear();

    if (cur->white()){
        //we haven't been here
        cur->col_gray();
        for (int i = 0; i < cur->get_degree(); i++){
            if (!prev || prev->get_num() != (*cur)[i]){
                if (dfsCycle(graph_ver[(*cur)[i]],ans,size,1,graph_ver[cur->get_num()])){
                    //if we know that there is a cycle
                    ans_temp.push_back(cur->get_num());
                    if (cur->get_num() == ans_temp[0]){
                        //end of the recursion
                        //ans_temp.remove();
                        size = ans_temp.size() - 1;
                        delete (*ans);
                        (*ans) = new int [size];
                        (*ans)[0] = ans_temp[0];
                        int j = size-1;
                        for (int i = 1; i < size; i++){
                            (*ans)[i] = ans_temp[j--];
                        }

                    }
                    //else{
                        return true;

                }
            }
            else{
                continue;
            }
        }
        cur->col_black();
        return false;
    }
    else if (cur->gray()){
        ans_temp.push_back(cur->get_num());
        return true;
    }
    else{

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
    this->graph::~graph();
    readID();

    graph_ver = new vertex* [a.size()];
    for(size_t i = 0; i < a.size(); ++i){
        graph_ver[i] = new vertex(*a[i]);
    }

    size_of_graph = a.size();
    verToMatr();
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

    /*!!!!!!!!!!!!!!!!!!!!!!
        remake it by subtracting elements from the vertexes
        not the matrix
        !!!!*/


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

size_t graph::get_id(){
    return id;
}

graph* graph::difference(graph& to_subtract){
    //be careful, you have to enter correct sizes

    //size - is the biggest possible graph
    //size_of_graph - is the actual amount of vertexes
    //to_subtract.out();
    size_t size = graph_ver[size_of_graph-1]->get_num()+1;

    size_t size_to_subtract = to_subtract[to_subtract.size()-1]->get_num()+1;

    std::string fname = "matr";
    fname += std::to_string(id);
    fname += ".txt";

    std::fstream cur (fname.c_str(), std::ios::in);
    size_t tempMatr[size][size];
    for (size_t i = 0; i < size; i ++){
        for (size_t j = 0; j < size; j++){
            cur>>tempMatr[i][j];
        }
    }
    cur.close();

    fname = "matrtemp.txt";
    cur.open (fname.c_str(), std::ios::out);

    fname = "matr";
    fname += std::to_string(to_subtract.get_id());
    fname += ".txt";

    std::fstream sub (fname.c_str(),std::ios::in);

    size_t temp;
    for (size_t i = 0; i < size; i++){
        for (size_t j = 0; j < size; j++){
            if (i<size_to_subtract && j<size_to_subtract){
                sub>>temp;
                if (temp == tempMatr[i][j] == 1){
                    cur<<0<<" ";
                }
                else{
                    cur<<tempMatr[i][j]<<" ";
                }
            }
            else{
                cur<<tempMatr[i][j]<<" ";

            }
        }
        cur<<"\n";
    }

    cur.close();
    sub.close();

    graph *ans = new graph (size, "matrtemp.txt");
    remove ("matrtemp.txt");
    return ans;
}

void graph::graph_sort(){
    //sorts the array of vertex* (graph_ver) in the graph
    std::vector <size_t> work;
    vertex** temp = new vertex* [size_of_graph];


    for (size_t i = 0; i < size_of_graph; i++){
        temp[i] = graph_ver[i];
    }

    for (size_t  i = 0; i < size_of_graph; i++){
        work.push_back (graph_ver[i]->get_num());
    }


    std::sort(work.begin(), work.end());

    for (size_t i = 0; i < size_of_graph; i++){
        graph_ver[i] = temp[graph_find(temp, size_of_graph,work[i])];

    }

}

size_t graph::graph_find (vertex** where, size_t size, size_t number){
    //returns the index of the num
    for (int i = 0; i < size; i++){
        if (where[i]->get_num() == number)
            return i;
    }
    return -1;
}

void graph_clear(){
    std::fstream toDel ("GRAPH_MAX_ID.txt", std::ios::in);
    size_t maxID;

    if (toDel.good()){
        toDel>>maxID;
    }
    else{
        maxID = 0;
    }

    toDel.close();
    remove ("GRAPH_MAX_ID.txt");

    std::string fname = "matr";
    for (size_t i = 0; i < maxID; i++){
        fname += std::to_string (i);
        fname += ".txt";
        remove (fname.c_str());
        fname = "matr";
    }
}
