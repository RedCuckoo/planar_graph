#include "planar.h"
#include "algorithm"
#include "segment.h"
#include "relMatr.h"
#include "relVec.h"

std::string planar::genfname (size_t id){
    std::string fname = "matr";
    fname += std::to_string (id);
    fname += ".txt";
    return fname;
}

vertex** planar::createCycled(graph& in, int* firstCycle, size_t firstCycleSize){
    /* firstCycle is an array of integers which has cycled vertexes in order
        firstCycleSize is the length of the cycle, >2
        in is a graph where will get vertexes from numbers
        the function returns an array of pointers to the new vertexes*/

    vertex** ans = new vertex* [firstCycleSize];

    ans[0] = new vertex(firstCycle[0],firstCycle[1],firstCycle[firstCycleSize-1]);
    ans[firstCycleSize-1] = new vertex(firstCycle[firstCycleSize-1],firstCycle[firstCycleSize-2],firstCycle[0]);

    for (size_t i = 1; i < firstCycleSize-1; i++){
        ans[i] = new vertex(firstCycle[i],firstCycle[i-1],firstCycle[i+1]);
    }
    return ans;
}

faces* planar::initialize(int* firstCycle, int firstCycleSize){
    faces *faceContainer = new faces;
    //we are creating first two faces
    faceContainer->add(firstCycle,firstCycleSize);
    faceContainer->add(firstCycle,firstCycleSize);
    return faceContainer;
}

graph* planar::check(graph& in){
    //checks if graph is connected

    if (!(in.connected()))
        return nullptr;

    //checks if has cycle and fills first Cycle
    int *firstCycle;

    int firstCycleSize;
    if (!(in.cycled(&firstCycle,firstCycleSize)))
        return nullptr;

    //bridges
    //connected dots

    graph* plane = new graph(createCycled(in,firstCycle,firstCycleSize),firstCycleSize);

    std::sort (firstCycle, firstCycle+firstCycleSize);
    faces *faceContainer = initialize(firstCycle,firstCycleSize);
    faceContainer->out();

    /*
        we are looking for segments which are sides, that doesn't belong to Gplane
        however the following vertexes do
    */

//work - the rest of the graph
//plane - final graph

    //work file is the G/Gplane
    graph* work = in.sumOrDif(*plane, 0);



    int work_id = work->get_id();
    int plane_id = plane->get_id();

    segments* seg_cont = new segments;

   // seg_cont = type1_segment(in,work,firstCycle, firstCycleSize);
      //  (*seg_cont).out();
    //type2_segment(seg_cont,in,work, firstCycle, firstCycleSize);
    seg_cont->type1_segment(in,work,firstCycle,firstCycleSize);
    seg_cont->type2_segment(in,work, firstCycle, firstCycleSize);

seg_cont->out();



    graph temp1;
    temp1 = *((*seg_cont)[0]->get_graph());

    work = work->sumOrDif(*((*seg_cont)[0]->get_graph()),1);
    work = work->sumOrDif(*((*seg_cont)[1]->get_graph()),1);



        seg_cont->calcFacesBelong(*faceContainer);
    std::vector<size_t> temp = (*seg_cont)[0]->get_graph()->findWayBtwContact();
    //faceContainer[1].out();



graph* to_see = in.get_way(temp);
to_see->out();
     //   plane = plane->sumOrDif(*to_see,1);
plane->out();

faceContainer->placeWay((*((*seg_cont)[0]))[0],*plane, *to_see);

faceContainer->out();

(*seg_cont)[0]->recalc(*to_see);

    for (size_t i = 0; i < temp.size(); i++)
        std::cout<<temp[i]<<" ";
    std::cout<<"\n";


std::cout<<"!\n";
    seg_cont->out();
    std::cout<<"!\n";
    plane->out();
    std::cout<<"\n";


    return plane;

}


int* vectorToInt(const std::vector<size_t>& to_change){
    int* ans = new int [to_change.size()];

    for (size_t i = 0; i < to_change.size(); i++){
        ans[i] = to_change[i];
    }
    return ans;
}
