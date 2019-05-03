#include "graph.h"


class planar{
public:
    static graph* check(graph& in);
    static vertex** createCycled(graph& in, int* firstCycle, size_t firstCycleSize);
};
