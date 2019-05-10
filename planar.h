#include "graph.h"
#include "face.h"
#include "segment.h"
#include <vector>


class planar{
public:
    static graph* check(graph& in);
    static vertex** createCycled(graph& in, int* firstCycle, size_t firstCycleSize);
    static faces* initialize (int* firstCycle, int firstCycleSize);
    static segment* type1_segment (graph& main, graph* difference, int* firstCycle, int firstCycleSize);
    static void type2_segment (segment* const cont, graph& main, graph* difference, std::vector<size_t>idsToDif);
    static std::string genfname (size_t id);
};
