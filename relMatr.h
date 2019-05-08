#ifndef RELMATR_H
#define RELMATR_H

#include <iostream>

/* stores and works with adjacency matrix */

class relMatr{
private:
    size_t amount;
    bool **matr;
public:
    relMatr (size_t am);
    bool** get_matr();
    bool get_el (int i, int j);
    size_t size();
    void fill ();
    void fill (const char* filename);
    void out() ;
    void out(const char* filename) ;
    ~relMatr();
};

#endif // RELMATR_H
