#include <iostream>
#include "graph.h"
#include "planar.h"
using namespace std;

int main()
{
    cout<<"Enter how many vertexes do you have => ";int s;cin>>s;
    graph test (s);
   // graph test1(3);
    //graph test2 (4);
    test.out();
//
//    vertex* t = test[0];
//
    cout<<endl;
//    int* temp = test.dfsBridgesOrienting(&t);
//
//    for (size_t i = 0; i < test.size(); i++){
//        cout<<temp[i]<<" ";
//    }
//    cout<<endl<<endl;
//    test.out();

    int* temp ;
    test.cycled(&temp,s);
    test.cycled(&temp,s);

    std::cout<<s<<'\n';
    for (int i = 0; i < s; i++){
       cout<<temp[i]<<" ";
    }

    cout<<endl;
    //cout<<test.connected()<<" "<<test.petels();
    graph *n = planar::check(test);
    //planar::check(test);
     n->out();
    return 0;
}
