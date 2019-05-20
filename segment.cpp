#include "segment.h"
#include "planar.h"

vertex** segments::segment::create2 (graph& in, size_t num_of_ver1, size_t num_of_ver2){
    vertex** temp = new vertex* [2];

    temp[0] = in[in.graph_find(in.get_vertexes(),in.size(),num_of_ver1)];
    clearFromExtra(&temp[0],num_of_ver2);
    temp[1] = in[in.graph_find(in.get_vertexes(),in.size(),num_of_ver2)];
    clearFromExtra(&temp[1],num_of_ver1);

    temp[0]->set_contact();
    temp[1]->set_contact();
    return temp;
}

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

graph* segments::segment::get_graph(){
    return segm;
}

size_t segments::segment::get_faceAmount(){
    return faceAmount;
}

void segments::segment::out(){
    std::cout<<"ID: "<<id<<" | face_amount: "<<faceAmount<<'\n';
    segm->out();
}

void segments::segment::clearFromExtra(vertex** in, size_t to_skip){
    for (size_t i = 0; i < (*in)->get_degree(); i++){
        if ((**in)[i] != to_skip){
            (*in)->delNext((**in)[i--]);
        }
    }
}

size_t segments::size(){
    return container.size();
}

void segments::out(){
    for (size_t i = 0; i < container.size(); i++){
        container[i].out();
    }
}

segments::segment* segments::operator[](size_t i){
    //i is the id of the segment
    return &container[i];
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
}

void segments::type2_segment (graph& main, graph* difference, int* firstCycle, size_t firstCycleSize){
    graph work = *difference;
    for (size_t i = 0; i < container.size(); i++){
        work = *(work.difference(*(container[i].get_graph())));
    }
    add(work,firstCycle,firstCycleSize);
}

void segments::segment::calcFacesBelong(faces& faceContainer){
    faceAmount = 0;
    for (size_t j = 0; j < faceContainer.size(); j++){
        if (faceContainer.belong(*segm)){
            faceAmount++;
        }
    }
}

void segments::calcFacesBelong(faces& faceContainer){
    for (size_t i = 0; i < container.size(); i++){
        container[i].calcFacesBelong(faceContainer);
    }
}
