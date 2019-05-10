#include "segment.h"

void segment::add (graph& in,size_t num_of_ver1, size_t num_of_ver2){
    vertex** temp = new vertex* [2];

    temp[0] = in[in.graph_find(in.get_vertexes(),in.size(),num_of_ver1)];
    clearFromExtra(&temp[0],num_of_ver2);
    temp[1] = in[in.graph_find(in.get_vertexes(),in.size(),num_of_ver2)];

    for (size_t i = 0; i < temp[1]->get_degree(); i++){
       std::cout<< (*temp[1])[i];
    }

    clearFromExtra(&temp[1],num_of_ver1);
    for (size_t i = 0; i < temp[1]->get_degree(); i++){
       std::cout<< (*temp[1])[i];
    }
    temp[0]->set_contact();
    temp[1]->set_contact();
    temp[0]->out();
    temp[1]->out();

    graph *ans = new graph (temp,2);
    push_back();
    ans->out();
    container[amount-1] = new graph(temp,2);
    container[0]->out();
    delete temp;
}

void segment::out(){
    for (size_t i = 0; i < amount; i++){
        container[i]->out();
    }
}

std::vector<size_t>* segment::last_ids(){
    std::vector<size_t>* ans;
    if (amount){
        ans = new std::vector<size_t>;
        for (size_t i = 0 ; i < amount; i++){
            ans->push_back(container[i]->get_id());
        }
    }
    else{
        ans = nullptr;
    }
    return ans;
}

graph* segment::operator[](size_t i){
    return container[i];
}

void segment::clearFromExtra(vertex** in, size_t to_skip){
   // size_t in_size = (*in)->get_degree();
    //size_t temp;

    for (size_t i = 0; i < (*in)->get_degree(); i++){
       // temp = (**in)[i];
        if ((**in)[i] != to_skip){
            (*in)->delNext((**in)[i--]);
        }
    }
}

void segment::delGgraph(graph** del, size_t size){
    for (size_t i = 0; i < size; i++){
        if (del[i])
            delete del[i];
    }
    if (del)
        delete del;
}

size_t segment::size(){
    return amount;
}

void segment::push_back(graph* to_add){
    //adds to a container
    if (!container){
        container = new graph*[0];
        container[0] = new graph(to_add->get_vertexes(),to_add->size());
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
        container = new graph*[0];
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

        delGgraph(temp,amount-1);
    }
}
