#include "segment.h"
#include "planar.h"
#include <algorithm>

segments::segment::segment (size_t id, graph& in, int* firstCycle, size_t firstCycleSize){
   //adds a graph, marking contact vertexes
    this->id = id;
    in.graph_sort();
    for (size_t i = 0; i < firstCycleSize; i++){
        in[firstCycle[i]]->set_contact();
    }
    segm = new graph(in.get_vertexes(),in.size());
}

segments::segment::segment (size_t id, graph& in,size_t num_of_ver1, size_t num_of_ver2){
    this->id = id;
    vertex** temp = create2(in,num_of_ver1,num_of_ver2);
    segm = new graph(temp,2);
}

//segments::segment::~segment(){
//    segm->~graph();
//}

graph* segments::segment::get_graph(){
    return segm;
}

size_t segments::segment::get_faceAmount(){
    return faceAmount;
}

void segments::segment::out(){
    std::cout<<"ID: "<<id<<" | face_amount: "<<faceAmount<<'\n';
    segm->out();
    for (size_t i = 0; i < facesBelong.size(); i++){
        std::cout<<facesBelong[i]<<" ";
    }
    std::cout<<'\n';
}

size_t segments::size(){
    return container.size();
}

size_t segments::segment::operator[] (size_t i){
    return facesBelong[i];
}

size_t segments::segment::size(){
    return facesBelong.size();
}

bool segments::segment::recalc(graph& to_del){
    //returns true if we need to delete this segment
    segm = segm->dif(to_del);
    if (!segm)
        return true;



    return false;
}

void segments::out(){
    for (size_t i = 0; i < container.size(); i++){
        container[i].out();
    }
}

void segments::segment::operator++(){
    faceAmount++;
}

void segments::sort(){
    bool ex = false;
    while (!ex){
        ex = true;
        for (size_t i = 0; i < container.size() - 1; i++){
            if (container[i].get_faceAmount()> container[i + 1].get_faceAmount()){
                std::swap(container[i], container[i+1]);
                ex = false;
            }
        }
    }

}

segments::segment* segments::operator[](size_t i){
    //i is the id of the segment
    return &container[i];
}

segments::~segments(){
    for (size_t i = 0; i < container.size(); i++){
        container[i].~segment();
    }
}

void segments::add(graph& in, size_t num_of_ver1, size_t num_of_ver2){
    segment temp(container.size(),in, num_of_ver1, num_of_ver2);
    container.push_back(temp);
}

void segments::add(graph& in, int* firstCycle, size_t firstCycleSize){
    segment temp(container.size(),in, firstCycle, firstCycleSize);
    container.push_back(temp);
}


void segments::type1_segment (graph& main, graph* difference, int* firstCycle, int firstCycleSize){
    relMatr workMatr(difference->size());
    workMatr.fill(planar::genfname(difference->get_id()).c_str());

    for (int i = 0; i < firstCycleSize; i++){
        for (int j = i+1; j < firstCycleSize; j++){
            if (workMatr.get_el(main[firstCycle[i]]->get_num(),main[firstCycle[j]]->get_num())){
                //if they are connected
                add(main,firstCycle[i], firstCycle[j]);
            }
        }
    }
    //container[0].out();
}

void segments::type2_segment (graph& main, graph* difference, int* firstCycle, size_t firstCycleSize){
    graph work;
    work = *difference;
    for (size_t i = 0; i < container.size(); i++){
       // work.out();
        //container[i].out();
        work = *(work.dif(*(container[i].get_graph())));
       // work.out();
    }
    add(work,firstCycle,firstCycleSize);
}

void segments::segment::add(size_t i){
    facesBelong.push_back(i);
    std::sort(facesBelong.begin(), facesBelong.end());
}

void segments::segment::set_faceAmount(size_t i){
    faceAmount = i;
}

void segments::calcFacesBelong(faces& faceContainer){
    for (size_t i = 0; i < container.size(); i++){
        container[i].set_faceAmount(0);
        for (size_t j = 0; j < faceContainer.size(); j++){
            if (faceContainer[j]->belong(*container[i].get_graph())){
                container[i].add(j);
                ++container[i];
            }
        }
    }
}

void segments::recalc(size_t where, graph& to_del){
    if (container[where].recalc(to_del)){
        //container[where].~segment();
        container.erase(container.begin() + where);
    }
}

void clearFromExtra(vertex** in, size_t to_skip){
    //deletes everything except
    for (size_t i = 0; i < (*in)->get_degree(); i++){
        if ((**in)[i] != to_skip){
            (*in)->delNext((**in)[i--]);
        }
    }

    if ((*in)->get_degree() == 2 && (**in)[0] == (**in)[1])
        (*in)->delNext((**in)[1]);

}


vertex** create2 (graph& in, size_t num_of_ver1, size_t num_of_ver2){
    vertex** temp = new vertex* [2];

    temp[0] = in[in.graph_find(in.get_vertexes(),in.size(),num_of_ver1)];
    clearFromExtra(&temp[0],num_of_ver2);
    temp[1] = in[in.graph_find(in.get_vertexes(),in.size(),num_of_ver2)];
    clearFromExtra(&temp[1],num_of_ver1);

    temp[0]->set_contact();
    temp[1]->set_contact();
    return temp;
}
