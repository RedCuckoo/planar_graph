#ifndef RELVEC_H
#define RELVEC_H

#include "relMatr.h"

/* by the adjacency matrix creates a vector which is a binary interpretation of the matrix */

class relVec {
private:
    size_t amount;
    unsigned *rows;
public:
    relVec(size_t am);
    ~relVec();
    unsigned rowToNum (relMatr &work, int i);
    void matrToVec(relMatr &work);
    unsigned operator [](size_t i);

    size_t size();

    size_t get_deg (size_t i);

    void out();
};

#endif // RELVEC_H
