#include "graph.h"
#include "relVec.h"
#include "planar.h"

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

graph::graph(){
    //readID();
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

bool graph::empty(){
    std::string fname = "matr";
    fname += std::to_string(id);
    fname += ".txt";
    std::ifstream input (fname.c_str());
    if (input.fail())
        return true;

    size_t temp;
    while (input>>temp){
        if (temp == 1){
            input.close();
            return false;
        }
    }
    return true;

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

void graph::clearColor(){
    for (size_t i = 0; i < size_of_graph; i++){
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

graph* graph::dif (graph& to){
    std::vector<vertex*> temp;

    size_t i = 0, j = 0;

    while (i < size_of_graph){
        if (graph_ver[i]->get_num() == to[j]->get_num()){
            vertex* temp_ver = vertex::difVertexes(*graph_ver[i],*to[j]);
            if (temp_ver){
                temp.push_back(temp_ver);
            }

            i++;
            j++;
        }
        else if (graph_ver[i]->get_num() < to[j]->get_num()){
            temp.push_back(graph_ver[i]);
            i++;
        }
        else{
            j++;
        }

        if (j >= to.size()){
            break;
        }
    }

    while (i < size_of_graph){
        temp.push_back(graph_ver[i++]);
    }

    vertex** ans_ver = new vertex* [temp.size()];
    for (size_t i = 0; i < temp.size(); i++){
        ans_ver[i] = temp[i];
    }

   if (temp.size()){
        graph* ans = new graph(ans_ver, temp.size());
        return ans;
   }

   return nullptr;

}

graph* graph::sum(graph& to){
    std::vector<vertex*> temp;

    size_t i = 0, j = 0;

    while (i < size_of_graph){
        if (graph_ver[i]->get_num() > to[j]->get_num()){
            temp.push_back(to[j++]);
        }
        else if (graph_ver[i]->get_num() == to[j]->get_num()){
            temp.push_back(vertex::addVertexes(*graph_ver[i++],*to[j++]));
        }
        else{
            temp.push_back(graph_ver[i++]);
        }

        if (j >= to.size()){
            break;
        }

    }

    while (j < to.size()){
        temp.push_back(to[j++]);
    }

    while (i < to.size()){
        temp.push_back(to[i++]);
    }

    vertex** ans_ver = new vertex* [temp.size()];
    for (size_t i = 0; i < temp.size(); i++){
        ans_ver[i] = temp[i];
    }

    graph* ans = new graph(ans_ver, temp.size());
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


bool graph::findWay(vertex* cur, std::vector<size_t>& ans, bool first, vertex* prev){
    //in order to find a vertex you need to:
    //cur - the first one, and the one you need to find is colored with gray

       //out();

       // size_t e = cur->get_num();
       // cur->out();

    if (!first){
        ans.clear();
        ans.push_back(cur->get_num());
    }

    if (cur->white()){
           // cur->out();
        //we haven't been here
        cur->col_gray();
        for (int i = 0; i < cur->get_degree(); i++){
            if (!prev || prev->get_num() != (*cur)[i]){
                if (findWay(graph_ver[graph_find(graph_ver,size_of_graph,(*cur)[i])],ans,1,graph_ver[graph_find(graph_ver,size_of_graph,cur->get_num())])){
                    ans.push_back(cur->get_num());
                    if (cur->get_num() == ans[0]){
                        ans.erase (ans.begin());
                        reverse (ans.begin(),ans.end());
                    }
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
        ans.push_back(cur->get_num());
        return true;
    }
    else{

    }
    return false;
}

std::vector<size_t> graph::findWayBtwContact(graph& has2Contact){
    vertex* one = nullptr,*two = nullptr;
    for (size_t i = 0; i < has2Contact.size(); i++){
        if (has2Contact[i]->contact()){
            if (!one){
                one =graph_ver[ graph_find(graph_ver,size_of_graph,has2Contact[i]->get_num())];
            }
            else{
                two =graph_ver[ graph_find(graph_ver,size_of_graph,has2Contact[i]->get_num())];

                break;
            }
        }
    }
    has2Contact.clearColor();
    two->col_gray();
    std::vector<size_t> way;
    findWay(one,way);
    return way;
}

//std::vector<size_t> graph::findWayBtwContact(){
//    size_t to_find_index;
//    size_t finish_index;
//    bool sw = false;
//    //out();
//    for (size_t i = 0; i < size_of_graph; i++){
//            graph_ver[i]->out();
//        if (graph_ver[i]->contact()){
//            if (!sw){
//                to_find_index = i;
//                sw = true;
//            }
//            else{
//                finish_index = i;
//                break;
//            }
//        }
//    }
//
//    clearColor();
//    graph_ver[finish_index]->col_gray();
//    std::vector<size_t> way;
//
//    graph_ver[to_find_index]->out();
//    graph_ver[finish_index]->out();
//
//
//    findWay(graph_ver[to_find_index],way);
////    for (size_t i = 0; i < way.size(); i++){
////        std::cout<<way[i]<<" ";
////    }
////    std::cout<<"\n";
//    return way;
//}

std::vector<size_t> graph::findWayBtwContact(){
    vertex* one = nullptr,* two = nullptr;
    for (size_t i = 0; i < size_of_graph; i++){
        if (graph_ver[i]->contact()){
            if (!one){
                one = graph_ver[i];
            }
            else{
                two = graph_ver[i];
                break;
            }
        }
    }

    clearColor();
    two->col_gray();
    std::vector<size_t> way;
    findWay(one,way);
//    for (size_t i = 0; i < way.size(); i++){
//        std::cout<<way[i]<<" ";
//    }
//    std::cout<<"\n";
    return way;
}

graph* graph::get_way(std::vector<size_t> way){
    //searches in this graph for the vertexes numbers and makes it
    graph* ans;

    vertex** temp = planar::createCycled(*this,vectorToInt(way),way.size());


    clearFromExtra(&temp[0],way[1]);
    clearFromExtra(&temp[way.size()-1],way[way.size()-2]);



    for (size_t i = 0; i < way.size(); i++){
        temp[i]->set_contact();
    }

    ans = new graph (temp, way.size());
    //ans->out();

return ans;
}

vertex* get_vertex(vertex** in, size_t i){
    //returns a vertex, with all the connections saved
}
