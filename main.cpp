#include <iostream>
#include "graph.h"
#include "planar.h"
using namespace std;

int main()
{
    cout<<"Enter how many vertexes do you have => ";int s;cin>>s;
    graph test (s);
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

    //int* temp ;
    //test.cycled(&temp,s);

  // for (int i = 0; i < s; i++){
   //     cout<<temp[i]<<" ";
  //  }
    //cout<<test.connected()<<" "<<test.petels();
    graph *n = planar::check(test);
    //planar::check(test);
     n->out();
    return 0;
}
