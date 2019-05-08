#include "graph.h"
#include "face.h"


class planar{
public:
    static graph* check(graph& in);
    static vertex** createCycled(graph& in, int* firstCycle, size_t firstCycleSize);
    static faces* initialize (int* firstCycle, int firstCycleSize);
};
