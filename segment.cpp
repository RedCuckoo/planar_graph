#include "segment.h"


vertex** segment::create2 (graph& in, size_t num_of_ver1, size_t num_of_ver2){
    vertex** temp = new vertex* [2];

    temp[0] = in[in.graph_find(in.get_vertexes(),in.size(),num_of_ver1)];
    clearFromExtra(&temp[0],num_of_ver2);
    temp[1] = in[in.graph_find(in.get_vertexes(),in.size(),num_of_ver2)];
    clearFromExtra(&temp[1],num_of_ver1);

    temp[0]->set_contact();
    temp[1]->set_contact();
    return temp;
}

void segment::add (graph& in, int* firstCycle, size_t firstCycleSize){
    //adds a graph, marking contact vertexes
    push_back();
    in.graph_sort();
    for (size_t i = 0; i < firstCycleSize; i++){
        in[firstCycle[i]]->set_contact();
    }

    container[amount-1] = new graph(in.get_vertexes(),in.size());
}

void segment::add (graph& in,size_t num_of_ver1, size_t num_of_ver2){
    vertex** temp = create2(in,num_of_ver1,num_of_ver2);
    push_back();
    container[amount-1] = new graph(temp,2);
}

void segment::out(){
    for (size_t i = 0; i < amount; i++){
        container[i]->out();
        std::cout<<"\n";
    }
}

std::vector<size_t> segment::last_ids(){
    //returns ids of the segments
    std::vector<size_t> ans;
    if (amount){
        for (size_t i = 0 ; i < amount; i++){
            ans.push_back(container[i]->get_id());
        }
    }

    return ans;
}

graph* segment::operator[](size_t i){
    return container[i];
}

void segment::clearFromExtra(vertex** in, size_t to_skip){
    for (size_t i = 0; i < (*in)->get_degree(); i++){
        if ((**in)[i] != to_skip){
            (*in)->delNext((**in)[i--]);
        }
    }
}

void segment::delGgraph(graph** del, size_t size){
    for (size_t i = 0; i < size; i++){
        if (del[i]){
            delete del[i];
        }
    }
}

size_t segment::size(){
    return amount;
}

size_t segment::faces_size(){
    return facesAmount;
}

void segment::push_back(graph* to_add){
    //adds to a container
    if (!container){
        container = new graph*;
        *container = new graph(to_add->get_vertexes(),to_add->size());
        amount++;
    }
    else{
        graph** temp = new graph* [amount];
        for (size_t i = 0; i < amount; i++){
            temp[i] = container[i];
        }
        delGgraph(container,amount);

        container = new graph* [++amount];
        for (size_t i = 0; i < amount-1;i++)
            container[i] = temp[i];

        container [amount-1] = new graph(to_add->get_vertexes(),to_add->size());

        delGgraph(temp,amount-1);
    }
}

void segment::push_back(){
    //increasing the size of the container by 1
    if (!container){
        container = new graph*;
        amount++;
    }
    else{
        graph** temp = new graph* [amount];

         for (size_t i = 0; i < amount; i++){
            temp[i] = new graph(container[i]->get_vertexes(), container[i]->size());
        }

        delGgraph(container,amount);

        container = new graph* [++amount];
        for (size_t i = 0; i < amount-1;i++)
            container[i] = new graph(temp[i]->get_vertexes(),temp[i]->size());

        delGgraph(temp,amount-1);
    }
}

void segment::checkAndAddFaces(faces& to_check){
    for (size_t i = 0; i < to_check.size(); i++){


    }


}
