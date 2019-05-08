#include "segment.h"

void segment::add (graph& in,size_t num_of_ver1, size_t num_of_ver2){
    vertex** temp = new vertex* [2];
    //temp[0] = new vertex(num_of_ver1,num_of_ver1,num_of_ver2);
    //temp[0] = new vertex(num_of_ver2,num_of_ver1,num_of_ver2);
    temp[0] = in[in.graph_find(in.get_vertexes(),in.size(),num_of_ver1)];
    temp[1] = in[in.graph_find(in.get_vertexes(),in.size(),num_of_ver2)];

    graph ans (temp,2);
    container.push_back(ans);
    delete temp;
}

void segment::out(){
    for (size_t i = 0; i < container.size(); i++){
        container[i].out();
    }
}
