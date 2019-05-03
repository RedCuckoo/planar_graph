#include "planar.h"
#include "face.h"

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

    graph* ans = new graph(createCycled(in,firstCycle,firstCycleSize),firstCycleSize);

    faces faceContainer;
    faceContainer.add(firstCycle,firstCycleSize);
    faceContainer.add(firstCycle,firstCycleSize);

    faceContainer.out();

    return ans;

}
