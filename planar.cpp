#include "planar.h"
#include "algorithm"
#include "segment.h"
#include "relMatr.h"
#include "relVec.h"

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
        return false;

    //checks if has cycle and fills first Cycle
    int *firstCycle;

    int firstCycleSize;
    if (!(in.cycled(&firstCycle,firstCycleSize)))
        return false;

    //bridges
    //connected dots

    graph* plane = new graph(createCycled(in,firstCycle,firstCycleSize),firstCycleSize);

    //plane->out();
    std::sort (firstCycle, firstCycle+firstCycleSize);
    faces *faceContainer = initialize(firstCycle,firstCycleSize);
    faceContainer->out();

    /*
        we are looking for segments which are sides, that doesn't belong to Gplane
        however the following vertexes do
    */


    //work file is the G/Gplane
    graph* work = in.difference(*plane);
    int work_id = work->get_id();



    relMatr workMatr(work->size());
    std::string fname = "matr";
    fname += std::to_string (work->get_id());
    fname += ".txt";
    workMatr.fill(fname.c_str());


    segment* seg_cont = new segment;
    //seg_cont->add(in,1,2);

    workMatr.out();

    for (size_t i = 0; i < firstCycleSize; i++){
        for (size_t j = i+1; j < firstCycleSize; j++){
            work_id = workMatr.get_el(in[firstCycle[i]]->get_num(),in[firstCycle[j]]->get_num());
            int temp1 = in[firstCycle[i]]->get_num();
            int temp2 = in[firstCycle[j]]->get_num();
            if (workMatr.get_el(in[firstCycle[i]]->get_num(),in[firstCycle[j]]->get_num())){
                //if they are connected
                seg_cont->add(in,firstCycle[i], firstCycle[j]);
            }
        }
    }

std::cout<<"!\n";
    seg_cont->out();
    std::cout<<"!\n";


    return plane;

}
